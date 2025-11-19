#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void Write(char *FName)
{
	FILE *FP;               	
	FP=fopen(FName , "a"); 		#opens file in append mode.File is created if not existing.
	if(!FP)						#Checks if file failed to open.
	{
		printf("\n");
		printf("\033[1;31m");  	#1 = bold / bright text. 37 = white color.
		printf("ERROR : OPENING FILE FAILED \n");
		printf("\033[1;37m");
		printf("\n");
		return;
	}
	else
	{
		char Data[1000];   		#A temporary storage to hold each line you type.
		
		while(fgets(Data,1000,stdin)!=NULL)		#If the user presses Ctrl+Z (Windows), fgets() returns NULL, and the loop stops.
		{
			fputs(Data,FP);		#Writes the content stored in Data to the file pointed by FP.
		}
		fclose(FP);				#Prevents file corruption and frees resources.
	}
}
void Show(char *Arg)   # Its purpose is to open the file and display its contents.
{
	FILE *PTR;		   # It will be used to read from the file.
	
	PTR=fopen(Arg , "r"); #The file must already exist. If it doesn’t, fopen() returns NULL.
	
	char CH; 			# This will store the characters read from the file using fgetc() later.
	if(!PTR) 			#checks if PTR == NULL → meaning file open failed.
	{
		printf("\033[1;31m");
		printf("ERROR : OPENING FILE FAILED\n");
		printf("\033[1;37m");
		printf("\n");
		return;
	}
	while((CH=fgetc(PTR))!=EOF)  # “This loop reads the file character by character until the end of the file is reached.”
	{
		printf("%c" , CH);
	}
	printf("\n");
	fclose(PTR);      # After finishing the reading process, I close the file to release system resources.
}
void main(int argc , char *argv[])  # argc = number of command-line arguments. 
{
	int Size=-1;
	int i=0;
	while(argv[i]!=NULL)  #Count the number of arguments manually, ./a.out file1 file2, Loop runs 3 times → Size = 2
	{
		Size++;
		i++;
	}
	# if ./a.out > filename → then the program should enter write mode.
	if(strcmp((strtok(argv[1] , "\n")),">")==0) # removes newline if present (unnecessary but harmless).
	{
		strtok(argv[2] , "\n");
		Write(argv[2]);   
	}
	else
	{
		for(int j=1 ; j<=Size ; j++)
		{
			printf("\n");
			printf("\033[1;33m");
			printf("%d) FILE NAME : %s\n\n" ,j, argv[j]);
			printf("\033[1;37m");
			strtok(argv[j] , "\n");
			Show(argv[j]);
			printf("\033[1;33m");
			printf("====================================\n");
			printf("\033[1;37m");
		}	
	}
}

