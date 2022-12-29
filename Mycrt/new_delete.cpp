//
// Created by 12096 on 2022/12/25.
//

extern "C" void* malloc(unsigned long long);
extern "C" void free(void*);

void* operator new(unsigned long long size) {
    return malloc(size);
}

void operator delete (void* ptr) {
    free(ptr);
}

void* operator new[](unsigned long long size) {
    return malloc(size);
}

void operator delete[] (void* ptr) {
    free(ptr);
}


