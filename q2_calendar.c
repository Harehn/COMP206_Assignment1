/*
Harehn Kaundun 260786113
Comp 206 Assignment 1 Question 1
The following program takes the daysize and firstday as arguments to produce a calendar for a year.
The program prints 30 days per month.
By using an array of 12 ints for the number of days, varying numbers of days can be printed.
*/

#include <stdio.h>

//prints character c n times
void PrintChar(int n, char c){
	while(n>0){
	printf("%c", c);
	n--;	
	}
}

// prints a date excluding the final |
//If Date >30 , a blank date is printed
void PrintDay(int n, int DAYSIZE){
	if(n<31){	
	printf("| %d",n);} else{
	printf("|  ");
	}
	if(n<10||n>30){
		PrintChar(DAYSIZE,' ');	
	}else 
	{PrintChar(DAYSIZE-1,' ');}

}

//prints a void date
void PrintBlankDay(int n,int DAYSIZE){
	while(n>0){
	PrintDay(31,DAYSIZE);
	n--;
	}
}

//Returns the number of characters in null terminated string
int NoOfChar(char *String){
	char *pointer=String;
	while(*pointer!='\0'){
		pointer++;	
	}
	return ((pointer-String)/sizeof(char));
}

//prints | Month | with the month centered
void PrintNameOfMonth(char* String,int DAYSIZE){
	printf("|");
	int NoOfSpaces= (((DAYSIZE+3)*7)-1-NoOfChar(String));
	PrintChar(NoOfSpaces/2, ' ');
	printf("%s",String);
	if(NoOfSpaces%2==0){
		PrintChar(NoOfSpaces/2, ' ');
	}else{
		PrintChar(((NoOfSpaces/2)+1), ' ');
	}
	printf("|\n");
}


//Prints dates and updates Firstday of next month
int PrintDates(int DAYSIZE,int FIRSTDAY){
	int NoOfDays=30;//Can be changed for number of days in the month
	int Date=1;
	PrintBlankDay(FIRSTDAY-1,DAYSIZE);//prints the leading empty slots
	
	//The following calculates the Number of spaces by determining the number of weeks.	
	int NoOfSpaces= (NoOfDays-8+FIRSTDAY)%7==0? (((((NoOfDays-8+FIRSTDAY)/7)+1)*7)+1) :(((((NoOfDays-8+FIRSTDAY)/7)+2)*7)+1);
	
	while(Date+FIRSTDAY<=NoOfSpaces){
		PrintDay(Date,DAYSIZE);
		Date++;
		if((((Date+FIRSTDAY)-2)%7)>0){//determines if a newline character should be printed
			
		}else{
		printf("|\n");}
	}	
	return ((FIRSTDAY-1+NoOfDays)%7)+1;//Determines the day on which the last date falls on and shifts it by 1
}

//draws separator line |----| of appropriate length
void Separator(int DAYSIZE){

	printf("|");			
	PrintChar((((DAYSIZE+3)*7)-1),'-');
	printf("|\n");

}

//Prints the n first letters of a String
void PrintStringChar(char *String,int size){
	int pointer;	
	while(size>pointer){
		printf("%c",String[pointer]);
		pointer++;
	}
}

//makes a String fill up a certain "size" by chopping part of it if size>allocated space or else add spaces
void PrintAlteredString(char* String, int size){
	if (NoOfChar(String)>=size){
		PrintStringChar(String,size-1);
		printf(" ");
	}else{
		printf("%s",String);
		PrintChar(size-NoOfChar(String),' ');
	}
}

//Prints the Day of the week
void PrintDayOfWeek(char * String,int DAYSIZE){
	printf("| ");
	PrintAlteredString(String,DAYSIZE+1);
}

//Prints the header where all days are printed as from Sunday to Saturday
//Can be altered by changing the array
void PrintDaysHeader(char **DAYS, int DAYSIZE){
	for(int n=0; n<7;n++){
	PrintDayOfWeek(DAYS[n],DAYSIZE);}
	printf("|\n");

}


//Prints the month, and dates
int PrintMonth(char* NameOfMonth, int DAYSIZE, int FIRSTDAY,char **DAYS){
	Separator(DAYSIZE);
	PrintNameOfMonth(NameOfMonth,DAYSIZE);
	Separator(DAYSIZE);
	PrintDaysHeader(DAYS, DAYSIZE);
	Separator(DAYSIZE);
	int a=PrintDates(DAYSIZE,FIRSTDAY);
	return a;
}

int main(int argc, char * argv[]) {
	//Checking for correct input
	if (argc !=3){
		printf("ERROR: Wrong number of arguments\n");
		return -1;
	}
	int DAYSIZE;
	int FIRSTDAY;
	sscanf(argv[1],"%d",&DAYSIZE);
	if(DAYSIZE<2){//Values like 14 are likely to blow out of proportion but no maximum has been specified
		printf("ERROR: Cannot print days smaller than size 2\n");
		return -1;
	}
	sscanf(argv[2],"%d",&FIRSTDAY);
	if(FIRSTDAY<1||FIRSTDAY>7){
		printf("ERROR: The first day of the week must be between 1 and 7\n");	
		return -1;
	}

	char* month[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	char *DAYS[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};	
	for (int n=0;n<12;n++){		
		FIRSTDAY=PrintMonth(month[n], DAYSIZE,FIRSTDAY,DAYS);
	}
	Separator(DAYSIZE);//The final separator line
	
		
	return 1;
}
