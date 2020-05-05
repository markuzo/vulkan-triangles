#pragma once

#include <vector>
#include <thread>

class ImageWriterData {
public:
	const char* Data;
	//const char* Filename;
	int Width;
	int Height;
	int Comp;
	int Index;
};

class ImageWriter {
public:
	ImageWriter() {
		for (auto i = 0; i < _maxThreads; i++) {
			_threads.push_back(std::thread());

			auto data = new ImageWriterData();
			//data->Filename = (const char*)malloc(256);
			data->Data = (const char*)malloc(1920 * 1080 * 4);
			_data.push_back(data);
		}
	}

	~ImageWriter() {
		for (auto i = 0; i < _maxThreads; i++) {
			auto& t = _threads[i];
			if (t.joinable())
				t.join();
			delete _data[i];
		}
	}

	ImageWriterData* getNext() {
		_threadIndex = (_threadIndex + 1) % _maxThreads;

		if (_threads[_threadIndex].joinable())
			_threads[_threadIndex].join();

		return _data[_threadIndex];
	}

	// call getNext() before me
	void write() {
		_threads[_threadIndex] = std::thread(work, _data[_threadIndex]);
	}

	static void work(ImageWriterData* data);

private:
	const int _maxThreads = 100;
	std::vector<std::thread> _threads;
	std::vector<ImageWriterData*> _data;
	int _threadIndex = 0;
};
