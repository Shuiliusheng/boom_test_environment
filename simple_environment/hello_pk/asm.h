//produce the assembly of riscv for insert unicore code
//input: x -> x6, y -> x7
//output: x7 -> z
//switch to unicore: add x0,x0,x1 
//switch back riscv: add x0,x0,x2 
//start insert flag: add x0,x0,x1; add x0,x0,x2 
//end   insert flag: add x0,x0,x1; add x0,x0,x2 
//placefold: add x0,x0,x0 
#define ASM(x,y,z) asm volatile( \
    " add x6,%[x],0        \n\t" \
    " add x7,%[y],0        \n\t" \
    " add x0,x0,x1     #start flag & switch  \n\t" \
    " add x0,x0,x2     #start flag & placefold   \n\t" \
    " add x0,x0,x0      # placefold  \n\t" \
    " add x0,x0,x0      # placefold  \n\t" \
    " add x0,x0,x0      # placefold  \n\t" \
    " add x0,x0,x1     #end flag  & placefold   \n\t" \
    " add x0,x0,x2     #end flag  & switch     \n\t" \
	" add %[z],x7,0         \n\t" \
	:[z]"=r"(z)            \
	:[x]"r"(x),[y]"r"(y) \
);
