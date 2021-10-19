#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

typedef struct{
	char inst[100];
    char opname[20];

    int type[20];
    char tname[20][20];
    int ntype;

    char list[20][33];
    int listvalue[20];
    int nlist;
}Instruction;

Instruction templates[1024];
int ntemp=0;

///////////////////////////////////////////////////
char inst_part[20][20]={"opcode", "fuc4", 
					"rd",  "rs1", "rs2", "rss",   
					"imm5", "imm9", "bc", 
					"onebit", "twobits", "threebits", "fourbits", "fivebits", "sixbits", 
					"imm24", "imm14", "rd2", "rs3", "rd1"};
int inst_bits[20]={8, 4,
			  5, 5, 5, 5,
			  5, 9, 4, 
			  1, 2, 3, 4, 5, 6,
			  24, 14, 5, 5, 5};
int part_num=20;


////////////////////////////////////////////////////
//used to find this part end place
char split_char[20]={' ', ',', 
					 '<', '>', '|', 
					 '[', ']', '+', '-'};
int splitchar_num=9;

////////////////////////////////////////////////////
//used to distiguish different inst
char special_char[20]={'#', 'r', 'x',
					 '<', '>', '|', 
					 '[', ']', '+', '-'};
int specialchar_num=10;



int find_char(char str[], int s, char c);
int find_split(char str[], int s);
int find_next_start(char str[], int s);
void copy_str(char str[], char dst[], int s, int e);
bool cmp_start(char str[], char substr[]);
int inst_to_int(char str[], Instruction &inst);
void getlist(char str[], Instruction &inst);


bool read_inst_template(char filename[])
{
    FILE *p=fopen(filename,"r");
    if(p==NULL){
        cout <<filename<<" is not exist!"<<endl;
        return false;
    }

    char str[100];
    int i=0,j=0;
    while(!feof(p)){
        str[0]='\0';
        fgets(str,100,p);
		if(str[strlen(str)-1]=='\n')
			str[strlen(str)-1]='\0';
        //cout <<str<<endl;
        if(cmp_start(str,"inst: ")){
			strcpy(templates[ntemp].inst, &str[6]);
            inst_to_int(&str[6], templates[ntemp]);
            ntemp++;
        }
        else if(cmp_start(str,"list: ")){
            if(ntemp!=0)
                getlist(&str[6], templates[ntemp-1]);
        }
        else{
            //cout <<"may be wrong:"<<str<<endl;
        }
    }
    fclose(p);
	return true;
}

int find_inst(Instruction inst)
{
	for(int i=0;i<ntemp;i++){
		if(strcmp(inst.opname, templates[i].opname)!=0){
			continue;
		}
		if(inst.ntype!=templates[i].ntype){
			continue;
		}
		int j=0;
		for(j=0;j<inst.ntype;j++){
			if(inst.type[j]!=templates[i].type[j])
				break;
		}
		if(j<inst.ntype){
			continue;
		}
		return i;
	}
	return -1;
}


void get_inst_binary(Instruction &inst)
{
	int n=find_inst(inst);
	if(n==-1){
		cout <<"this instruction is not in the templates!"<<endl;
		return ;
	}

	cout <<"inst template: "<<templates[n].inst<<endl;
	
	int i=0;
	for(i=0;i<templates[n].nlist;i++){
		if(templates[n].listvalue[i]>=0){
			inst.listvalue[i]=templates[n].listvalue[i];
		}
		else{
			int index=(templates[n].listvalue[i]*-1)-2;
			int value=0;
			if(inst.tname[index][0]=='r')
				sscanf(&inst.tname[index][1], "%d",&value);
			else
				sscanf(&inst.tname[index][0], "%d",&value);
			inst.listvalue[i]=value;
		}
		cout <<templates[n].list[i]<<": "<<inst.listvalue[i]<<" | ";
	}
	cout <<endl;

	unsigned long binary=0;
	
/*	char part[20][20]={"opcode", "fuc4", 
						"rd",  "rs1", "rs2", "rss",   
						"imm5", "imm9"};
	int bits[20]={8, 4,
				  5, 5, 5, 5,
				  5, 9};
	int num=8;*/

	for(i=0;i<templates[n].nlist;i++){
		int j=0;
		for(j=0;j<part_num;j++){
			if(strcmp(templates[n].list[i],inst_part[j])==0){
				binary=binary<<inst_bits[j];	
				break;
			}
		}
		if(j==part_num){
			cout <<templates[n].list[i]<<" is not defined!"<<endl;
		}
		binary+=inst.listvalue[i];
	}
	printf("binary: 0x%08x\n", binary);
	printf("riscv: lui 0x%x\n", (binary>>7));
	printf("riscv: lui %d\n", (binary>>7));		//lui opcode is 7bits
}


int main()
{
	char str[100];
    if(!read_inst_template("unicore_templates.txt")){
		return 0;
	}
	while(1){
		cout <<"input inst assembly:"<<endl;
		gets(str);
		
		if(strcmp(str,"exit")==0){
			break;
		}
		else if(strcmp(str,"help")==0){
			cout <<"template list:"<<endl;
			for(int i=0;i<ntemp;i++){
				cout <<templates[i].inst<<endl;
			}
		}
		
		Instruction inst;
		inst_to_int(str, inst);
		get_inst_binary(inst);
	}
	return 0;	
}


void getlist(char str[], Instruction &inst)	//get the binary parts list
{
    int s=0, e=0, p=0, v=0;
    inst.nlist=0;
    char part[40];
    while(1){
        part[0]='\0';
        v=-1;
        e=find_split(str,s);
        copy_str(str, part, s, e);
        p=find_char(part,0,'_');
        if(p!=-1){
            sscanf(&part[p+1],"%x", &v);
            part[p]='\0';
        }
        strcpy(inst.list[inst.nlist], part);
        
		if(v==-1){
			for(int i=0;i<inst.ntype;i++){
				if(strcmp(part,inst.tname[i])==0){	//找到对应在type中的位置
					v=-1*(2+i);
					break;
				}
			}
		}
		inst.listvalue[inst.nlist]=v;

        inst.nlist++;
        s=e+1;
		if(e>=strlen(str))
            break;
    }
//	for(int i=0;i<inst.nlist;i++){
//		cout <<inst.list[i]<<"("<<inst.listvalue[i]<<") ";
//	}
//	cout <<endl;
}

int inst_to_int(char str[], Instruction &inst)
{
	int e=0;
	int l=strlen(str);
	int i=find_char(str, 0, ' ');
	copy_str(str, inst.opname, 0, i);
	//cout <<inst.opname<<endl;
    inst.ntype=0;
	for(i;i<l;i++){
		i=find_next_start(str, i);
		if(i==-1){
			break;
		}
		for(int j=0;j<specialchar_num;j++){
			if(str[i]==special_char[j]){
				inst.type[inst.ntype]=j;
				strcpy(inst.tname[inst.ntype],"");
			}
		}
		
		if(str[i]=='r'||str[i]=='x'){//register
			e=find_split(str,i);
			copy_str(str,inst.tname[inst.ntype],i,e);
			inst.ntype++;
		}
		else if(str[i]=='#'){//imm
			e=find_split(str,i+1);
			copy_str(str,inst.tname[inst.ntype],i+1,e);
			inst.ntype++;
		}
	}
	
//	for(i=0;i<inst.ntype;i++)
//		cout <<inst.type[i]<<"("<<inst.tname[i]<<") ";
//	cout <<endl;
	return 0;
	
}


bool cmp_start(char str[], char substr[])
{
    if(strlen(substr)>strlen(str)){
        return false;
    }

    int l1=strlen(substr);
    char c=str[l1];
    str[l1]='\0';
    bool result = strcmp(substr,str)==0;
    str[l1]=c;
    return result;
}

int find_char(char str[], int s, char c)
{
	for(int i=s;i<strlen(str);i++){
		if(str[i]==c){
			return i;
		}
	}
	return -1;
}

int find_split(char str[], int s)
{
	for(int i=s;i<strlen(str);i++){
		for(int j=0;j<splitchar_num;j++){
			if(str[i]==split_char[j]){
				return i;
			}
		}
	}
	return strlen(str);
}

int find_next_start(char str[], int s)
{
	for(int i=s;i<strlen(str);i++){
		for(int j=0;j<specialchar_num;j++){
			if(str[i]==special_char[j]){
				return i;
			}
		}
		if(str[i]==' '||str[i]==',')
			continue;
	}
	return -1;
}


void copy_str(char str[], char dst[], int s, int e)
{
	if(e>strlen(str))
		return ;
	if(e<strlen(str))
	{
		char c=str[e];
		str[e]='\0';
		strcpy(dst,&str[s]);
		str[e]=c;
	}
	else{
		strcpy(dst,&str[s]);
	}
	//cout <<dst<<endl;
	
}

