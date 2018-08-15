/*
Harehn Kaundun 260786113
Comp 206 Assignment 1 Question 1
The following program reads a file and replaces tags #A# by float values.
The program accepts 3 arguments, file path, and 2 floats. The file exits if there are any wrong input.
This version allows for only 2 tags to be replaced and any further tags would be left blank. 
By making a preliminary pass through the file and determining the number of tags and assigning default values would make a more flexible version.
*/
#include <stdio.h>

int main(int argc, char * argv[]) {
	//Checking for right number of input	
	if (argc !=4){
		printf("ERROR: Wrong number of arguments\n");
		return -1;
	}
	
	//Reading file and exiting if unreadable
	FILE * shape_template;
	if((shape_template = fopen(argv[1], "r")) == NULL){
		printf("Can't read from file %s\n", argv[1]);
		return -1;
	}

	/*
	The following takes each float argument and tests for invalid input.
	The function atof has not been used as erronous results have been obtained with tests like
	28.01asd
*/
	for(int n=2;n<argc;n++){
	int noOfDecimal=0;//Records number of '.'
	int lastCharIsDecimal=1;//Boolean to help to avoid these cases: 28.., 28., .75 
	char str[50];
	sscanf (argv[n],"%s",str);
	char *c=&(str[0]);
	/*The string is read character by character*/
	while (*c!='\0'){
		switch(*c){
		case '1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':case'0':
			lastCharIsDecimal=0;
			break;
		case '.':
			noOfDecimal++;
			if(lastCharIsDecimal==1||noOfDecimal>1){
				printf("Bad float argument");
				return -1;
			}
			lastCharIsDecimal=1;
			break;
		default:
			printf("bad float argument");
			return -1;
		}
		c++;
	}
	/*The following helps to avoid trailing decimal points ie '28.' */
	if(lastCharIsDecimal==1){
		printf("Bad float argument");
		return -1;
	}
	
	}

	float floatsToReplace[2];//For easier looping and ability to change to accept more floats
	sscanf(argv[2],"%f",&floatsToReplace[0]);
	sscanf(argv[3],"%f",&floatsToReplace[1]);

	char str[60];//for fgets
	int toreplace=0;//Boolean to know when to replace tags
	int i=0;//to loop through floatsToReplace
	while(fgets(str,60,shape_template)!=NULL){
		int n=0;
		while(str[n]!='\0'){
			if(str[n]=='#'){
				toreplace=!toreplace;
				if(!toreplace){printf("%.6f",floatsToReplace[i]);
					i++;}
				}
			if(!(toreplace)&&str[n]!='#'){
			printf("%c",str[n]);
				}
			n++;
		}
	
	}
	return 0;
}
