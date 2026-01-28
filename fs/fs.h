#ifndef FS_H
#define FS_H

#include "lib/types.h"

#define MAX_FILES 32
#define MAX_FILENAME 32
#define MAX_FILESIZE 4096

struct file {
    char name[MAX_FILENAME];
    uint8_t data[MAX_FILESIZE];
    uint32_t size;
    int used;
};

void fs_init(void);
int fs_create(const char* name);
int fs_delete(const char* name);
int fs_write(const char* name, const char* data, uint32_t size);
int fs_read(const char* name, char* buffer, uint32_t max_size);
int fs_list(char names[][MAX_FILENAME], int max_count);
int fs_exists(const char* name);
uint32_t fs_size(const char* name);

#endif
