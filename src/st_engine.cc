#include "st_engine.h"

const float ST::Engine::getRandom(float min, float max){
	return min + (rand() / (RAND_MAX / (max - min)));
}

const unsigned char* ST::Engine::readFile(const char* filename){
	FILE* in_file = 0;
	int err = fopen_s(&in_file, filename, "rb");
	assert(in_file);
	struct stat sb;
	assert(stat(filename, &sb) != -1);
	unsigned char* file_contents = (unsigned char*)malloc(sb.st_size + 1);
	if (file_contents) {
		fread(file_contents, sb.st_size, 1, in_file);
		file_contents[sb.st_size] = 0;
		fclose(in_file);
	}
	return file_contents;
}