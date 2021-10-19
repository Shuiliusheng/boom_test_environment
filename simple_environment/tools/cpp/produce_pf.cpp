#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

char start[250]=
"\
#define ASM(x,y,z) asm volatile( \\\n\
    \" add x6,%[x],0        \\n\\t\" \\\n\
    \" add x7,%[y],0        \\n\\t\" \\\n\
    \" add x0,x0,x1     #start flag & switch  \\n\\t\" \\\n\
";

char end[250]="\
    \" add x0,x0,x2     #end flag  & switch     \\n\\t\" \\\n\
	\" add %[z],x7,0         \\n\\t\" \\\n\
	:[z]\"=r\"(z)            \\\n\
	:[x]\"r\"(x),[y]\"r\"(y) \\\n\
);                           	 \n \
";


void produce_assembly(char instlist[], char output[])
{
	int ninst=0;
	FILE *p=fopen(instlist,"r");
	if(p==NULL){
		cout <<instlist<<" is not exist!"<<endl;
		return ;
	}
	char str[100];
	while(!feof(p)){
		strcpy(str,"");
		fgets(str,100,p);
		if(strlen(str)>0){
			ninst++;
		}
	}
	fclose(p);
	cout <<"inst number that need to insert: "<<ninst<<endl;

	
	p=NULL;
	p=fopen(output,"w");
	if(p==NULL){
		cout <<"cannot creat "<<output<<endl;
		return ;
	}
	
	fprintf(p,"//produce the assembly of riscv for insert unicore code\n");
	fprintf(p,"//input: x -> x6, y -> x7\n");
	fprintf(p,"//output: x7 -> z\n");
	fprintf(p,"//switch to unicore: add x0,x0,x1 \n");
	fprintf(p,"//switch back riscv: add x0,x0,x2 \n");
	fprintf(p,"//start insert flag: add x0,x0,x1 \n");
	fprintf(p,"//end   insert flag: add x0,x0,x2 \n");
	fprintf(p,"//placefold: add x0,x0,x0 \n");

	fprintf(p,"%s", start);
	for(int i=0;i<ninst;i++){
		fprintf(p, "    \" add x0,x0,x0      # placefold  \\n\\t\" \\\n");
	}

	fprintf(p,"%s", end);
	fclose(p);
	cout <<"produce "<<output<<" successfully!"<<endl;
}

int main(int argv, char **args)
{
    if(argv<3){
        cout <<"parameter is not enought!"<<endl;
        cout <<"./run inst_list output_name"<<endl;
        return 0;
    }
    else{
        cout <<"insts for insert: "<<args[1]<<endl;
		cout <<"output filename : "<<args[2]<<endl;
        produce_assembly(args[1], args[2]);
    }
	return 0;
}
