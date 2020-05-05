#include "ImageWriter.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include <sstream>

void ImageWriter::work(ImageWriterData* data) {
	std::stringstream filenamestream;
    filenamestream << "images/";
    filenamestream << "img" << data->Index << ".bmp";
    std::string filename = filenamestream.str();
    const char* fname = filename.c_str();

	stbi_write_bmp(fname, data->Width, data->Height, data->Comp, data->Data);
}
