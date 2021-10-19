#!/bin/bash
../tools/placefold ../unicore.inst ./asm.h
riscv64-unknown-elf-gcc hello.cpp -static -o hello
riscv64-unknown-elf-objdump -D hello >hello.dump
cp hello ../pk_hello