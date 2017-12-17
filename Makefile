all: shaders
	g++ main.cpp HelloTriangleApplication.cpp -lglfw -lvulkan -o main

shaders: shaders/vert.spv shaders/frag.spv

shaders/vert.spv: shaders/shader.vert
	glslangValidator -V shaders/shader.vert -o shaders/vert.spv

shaders/frag.spv: shaders/shader.frag
	glslangValidator -V shaders/shader.frag -o shaders/frag.spv
