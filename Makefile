STB_INCLUDE_PATH = ./thirdparty/stb
TINYOBJ_INCLUDE_PATH = ./thirdparty/tinyobjloader
CFLAGS = -I$(STB_INCLUDE_PATH) -I$(TINYOBJ_INCLUDE_PATH)

main: shaders
	g++ main.cpp App.cpp $(CFLAGS) -lglfw -lvulkan -o main 

shaders: shaders/vert.spv shaders/frag.spv

shaders/vert.spv: shaders/shader.vert
	glslangValidator -V shaders/shader.vert -o shaders/vert.spv

shaders/frag.spv: shaders/shader.frag
	glslangValidator -V shaders/shader.frag -o shaders/frag.spv

run: main 
	./main	
