#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

unsigned char *data;
unsigned int size=0;


unsigned int find_insts(unsigned int insts[], int n, int start)
{
	unsigned char *bytes=(unsigned char *)malloc(n*4+1);
	memcpy(&bytes[0], &insts[0], n*4);
	n=n*4;

	for(int i=start;i<size;i++){
		int j=0;
		for(j=0;j<n&&(i+j)<size;j++){
			if(data[i+j]!=bytes[j]){
				break;
			}
		}
		if(j==n){
			return i;
		}
	}
	return -1;
}


bool replace_insts(int start, int end, char instfile[])
{
	if((end-start)%4!=0){
		cout <<"range is not 4bytes aligned!"<<endl;
		return false;
	}
	FILE *p=fopen(instfile,"r");
	if(p==NULL){
		cout <<instfile<<" is not exist!"<<endl;
		return false;
	}
	
	unsigned int *insts;
	int num=1000,ninst=0;
	insts = (unsigned int *)malloc((num)*4);
	char str[100];
	while(!feof(p)){
		strcpy(str,"");
		fgets(str,100,p);
		sscanf(str,"%x",&insts[ninst]);
		ninst++;
		if(ninst>num){
			cout <<"insts are too much!"<<endl;
			break;
		}
	}
	fclose(p);

	
	unsigned int temp;
	int size=end-start;
	for(int i=0;i<size&&i<ninst*4;i+=4){
		memcpy(&temp, &data[start+i], 4);
		memcpy(&data[start+i], &insts[i/4], 4);
		printf("0x%x: replace 0x%08x  ->  0x%08x\n", start+i,temp, insts[i/4]);
	}
	free(insts);
	return true;
}


int test(char filename[], char dstname[], char instfile[], int s)
{
	FILE *p=fopen(filename,"rb");
	if(p==NULL){
		cout <<filename<<" is not exist!"<<endl;
		return ;
	}
	fseek(p,0L,SEEK_END);
    size = ftell(p);
	data = (unsigned char *)malloc(size);

	fseek(p,0L,SEEK_SET);
	fread(data, 1, size, p);
	fclose(p);

	unsigned int insts[4];
	int num=1;
	insts[0]=0x00100033;
	insts[1]=0x00200033;
	int start=find_insts(insts, num, s);
	if(start==-1){
		cout <<"start flag is not found!"<<endl;
		return ;
	}
	int end=find_insts(&insts[1], num, start+1);
	if(end==-1){
		cout <<"end flag is not found!"<<endl;
		return ;
	}

	cout <<start<<" "<<end<<": "<<end-start-4<<" bytes"<<endl;
	
	if(replace_insts(start+4, end, instfile)){
		p=fopen(dstname,"wb");
		fwrite(data, 1, size, p);
		fclose(p);
	}

	free(data);
	return end+1;
}


int main(int argv, char **args)
{
	if(argv<4){
		cout <<"parameter is not enought!"<<endl;
		cout <<"./run src_binary dst_binary inst_list"<<endl;
		return 0;
	}
	else{
		cout <<"source binary: "<<args[1]<<endl;
		cout <<"dst    binary: "<<args[2]<<endl;
		cout <<"insts for insert: "<<args[3]<<endl;
		int n = test(args[1], args[2], args[3], 0);
		test(args[1], args[2], args[3], n+1);
	}
	//test("d:\\pk_hello", "d:\\pk_hello1", "d:\\insts.txt");
	return 0;
}
