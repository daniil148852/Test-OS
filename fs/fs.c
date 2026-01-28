#include "fs/fs.h"
#include "lib/string.h"

static struct file files[MAX_FILES];

void fs_init(void) {
    for (int i = 0; i < MAX_FILES; i++) {
        files[i].used = 0;
        files[i].size = 0;
        memset(files[i].name, 0, MAX_FILENAME);
    }
}

static struct file* find_file(const char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used && strcmp(files[i].name, name) == 0) {
            return &files[i];
        }
    }
    return (struct file*)0;
}

int fs_create(const char* name) {
    if (find_file(name)) return -1;
    
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].used) {
            files[i].used = 1;
            strncpy(files[i].name, name, MAX_FILENAME - 1);
            files[i].size = 0;
            return 0;
        }
    }
    return -1;
}

int fs_delete(const char* name) {
    struct file* f = find_file(name);
    if (!f) return -1;
    f->used = 0;
    return 0;
}

int fs_write(const char* name, const char* data, uint32_t size) {
    struct file* f = find_file(name);
    if (!f) return -1;
    if (size > MAX_FILESIZE) size = MAX_FILESIZE;
    memcpy(f->data, data, size);
    f->size = size;
    return size;
}

int fs_read(const char* name, char* buffer, uint32_t max_size) {
    struct file* f = find_file(name);
    if (!f) return -1;
    uint32_t to_read = f->size < max_size ? f->size : max_size;
    memcpy(buffer, f->data, to_read);
    return to_read;
}

int fs_list(char names[][MAX_FILENAME], int max_count) {
    int count = 0;
    for (int i = 0; i < MAX_FILES && count < max_count; i++) {
        if (files[i].used) {
            strncpy(names[count], files[i].name, MAX_FILENAME);
            count++;
        }
    }
    return count;
}

int fs_exists(const char* name) {
    return find_file(name) != (struct file*)0;
}

uint32_t fs_size(const char* name) {
    struct file* f = find_file(name);
    return f ? f->size : 0;
}
