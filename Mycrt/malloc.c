#include "mycrt.h"

typedef struct _heap_header {
    enum {
        HEAP_BLOCK_FREE = 0xABABABAB,
        HEAP_BLOCK_USED = 0xCDCDCDCD
    } type;
    unsigned size;
    struct _heap_header* next, *prev;
} heap_header;

static heap_header* list_head = 0;
static const int HEADER_SIZE = sizeof(heap_header);

void* addr_add(void* ptr, unsigned o) {
    return (char*) ptr + o;
}

static int brk(void* end_data_segment) {
    int ret = 0;
    asm("movl $45, %%eax \n\t"
            "movl %1, %%ebx \n\t"
            "int $0x80 \n\t"
            "movl %%eax, %0 \n\t"
            :
            "=r"(ret)
            :
            "m"(end_data_segment));
    return ret;
}

int my_crt_heap_init() {
    void* base = 0;
    unsigned heap_size = 1024 * 1024 * 32;
    base = (void*) brk(0);
    void* end = addr_add(base, heap_size);
    end = (void*) brk(end);
    if (!end) {
        return 0;
    }
    list_head = (heap_header*) base;
    list_head->size = heap_size;
    list_head->type = HEAP_BLOCK_FREE;
    list_head->next = 0;
    list_head->prev = 0;
    return 1;
}

void* malloc(unsigned long long size) {
    heap_header* header;
    if (size == 0) return 0;
    header = list_head;
    while (header != 0) {
        if (header->type == HEAP_BLOCK_USED) {
            header = header->next;
            continue;
        }
        if (header->size == size + HEADER_SIZE) {
            header->type = HEAP_BLOCK_USED;
            return addr_add(header, HEADER_SIZE);
        }
        else if (header->size > size + HEADER_SIZE) {
            //split
            heap_header* next = (heap_header*) addr_add(header, size + HEADER_SIZE);
            next->prev = header;
            next->next = header->next;
            next->type = HEAP_BLOCK_FREE;
            next->size = header->size - (size - HEADER_SIZE);
            header->next = next;
            header->size = size + HEADER_SIZE;
            header->type = HEAP_BLOCK_USED;
            return addr_add(header, HEADER_SIZE);
        }
        header = header->next;
    }
    return 0;
}

void free(void* ptr) {
    heap_header* header = (heap_header*) addr_add(ptr, -HEADER_SIZE);
    if (header->type == HEAP_BLOCK_FREE) {
        return;
    }
    header->type = HEAP_BLOCK_FREE;
    if (header->prev != 0 && header->prev->type == HEAP_BLOCK_FREE) {
        header->prev->next = header->next;
        if (header->next != 0) {
            header->next->prev = header->prev;
        }
        header->prev->size += header->size;
        header = header->prev;
    }
    if (header->next != 0 && header->next->type == HEAP_BLOCK_FREE) {
        header->size += header->next->size;
        header->next = header->next->next;
        if (header->next != 0) {
            header->next->prev = header;
        }
    }
}
