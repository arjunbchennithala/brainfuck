#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *dest;
FILE *source;

char *destname = "/tmp/BF_1234.c";
char *sourcename = "brain.bf";
char *outname;
char command[30] = "gcc /tmp/BF_1234.c ";
char flag[3] = "-o ";
int multi = 0;

int count = 0;

int compile(){
	if(multi){
		strcat(command,flag);
		strcat(command,outname);
	}
	return system(command);
}


char *interpreter(char c){
	switch(c){
		case '>':
			return "p++;\n";
		case '<':
			return "p--;\n";
		case '+':
			return "a[p]++;\n";
		case '-':
			return "a[p]--;\n";
		case '[':
			return "while(a[p]){\n";
		case ']':
			return "}\n";
		case ',':
			return "scanf(\"%hd\",&a[p]);\n";
		case '.':
			return "printf(\"%c\", a[p]);\n";
		default:
			return "\n";
	}
}

void initDestFile(){
	dest = fopen(destname,"w");
	fprintf(dest, "#include <stdio.h>\nvoid main(){\nunsigned short int a[300]={0};\nint p = 0;\n");
	fclose(dest);
	dest = fopen(destname,"a");
}

void writeDestFile(char *str){
	fprintf(dest, "%s",str);
}

void closeDestFile(){
	fprintf(dest, "}\n");
	fclose(dest);
	fclose(source);
}

void initSFile(){
	source = fopen(sourcename,"r");
}


void main(int argc,char* argv[]){
	if(argc>1){
		sourcename = argv[1];
		outname = (argc>2) ? argv[2] : "f.out";
		multi = (argc>2) ? 1 : 0;
		initDestFile();
		initSFile();
		char c;
		while((c = fgetc(source))!=EOF){
			writeDestFile(interpreter(c));
		}
		closeDestFile();
		compile();
	}else{
		printf("Simple BrainFuck Compiler for Linux\nAuthor : Arjun\nUsage : \"brainf <inputfilename> <outputfilename_optional>\"\n");
	}
	
}

