#ifndef _SPACE_TURTLE_UTILITIES_H_
#define _SPACE_TURTLE_UTILITIES_H_ 1

#include <iostream>
#include <sys/stat.h>
#include <assert.h>

namespace ST {

    const unsigned char* readFile(const char* filename) {
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

    //const int getRandom(int min, int max) {
    //    return min + (rand() / (RAND_MAX / (max - min)));
    //}
}

#endif