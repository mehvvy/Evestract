#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

uint8_t* ReadFile(const char* fileName, uint32_t* bufLen) {

    FILE* fp = fopen(fileName, "rb");
    if (fp == NULL) {
        // fprintf(stderr, "unable to open \"%s\"\n",fileName);
        return NULL;
    }

    long ret = fseek(fp, 0, SEEK_END);
    if (ret < 0) {
        // fprintf(stderr, "internal error seeking to end \"%s\"\n", fileName);
        fclose(fp);
        return NULL;
    }
    long len = ftell(fp);
    if (len < 0) {
        // fprintf(stderr, "internal error getting length \"%s\"\n", fileName);
        fclose(fp);
        return NULL;
    }
    ret = fseek(fp, 0, SEEK_SET);
    if (ret < 0) {
        // fprintf(stderr, "internal error seeking to start \"%s\"\n", fileName);
        fclose(fp);
        return NULL;
    }

    uint8_t* buf = (uint8_t*) malloc(len);
    if (buf == NULL) {
        // fprintf(stderr, "internal error allocating %ld bytes \"%s\"\n", len, fileName);
        fclose(fp);
        return NULL;
    }

    long rLen = fread(buf, 1, len, fp);
    if (rLen != len) {
        // fprintf(stderr, "internal error read \"%s\"\n", fileName);
        free(buf);
        fclose(fp);
        return NULL;
    }

    fclose(fp);

    *bufLen = (uint32_t) len;
    return buf;
}
