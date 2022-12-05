#!/bin/bash
! test -d build && mkdir build

cd build

cmake ..

cmake --build .

cd ..

gcc -c main.c -m32 -fno-builtin -nostdlib -fno-stack-protector -g

mv main.o build/ && cd build

ld -static -m elf_i386 -e my_crt_entry Mycrt/libMycrt.a main.o -o main

cd ..

! test -d bin && mkdir bin

mv build/main bin/



