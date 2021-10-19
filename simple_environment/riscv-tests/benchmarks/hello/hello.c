#include<stdio.h>
#include"asm.h"

int main()
{
        int x=3,y=7,z=0;
        ASM(x,y,z);
        printf("hello world: %d\n", z);
        return 0;
}
