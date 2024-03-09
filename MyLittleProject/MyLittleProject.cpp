


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>
using namespace std;
using namespace System;
using namespace System::IO;
//menu navigation
#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79
// question pull
char dan[8][55]={
 "Which student has the highest average grade?          ",
 "Which sutdent had enrolled earlier than others?       ",
 "List of elementary students yunger than 9 years       ",
 "Alphabetical list of sudents                          ",
 "Amount of high school students                        ",
 "Diagramm. Tutition fees comparison                    ",
 "Students with same age, but from different school     ",
 "Exit                                                  "
};
char BlankLine[ ]=" "; 

int FileLength;

struct person {
	char name[20]; 
	float grade;  
	long age;   
	char date[11]; 
	char school[20];
	long price;
};
//structure for alphabet list 
struct sp {
	char sname[20];
	float grade;
	long price;
	struct sp* nex; 
	struct sp* pre;
 } *slist; 

int menu(int);
void maximum(struct person*);
void first(struct person*);
void text_date(char *,char *);
void amount(struct person *);
void alfalist(struct person*);
void listinsert(struct person*,char*);
void listing(struct person*);
void diagram(struct person*);
void complexquestion(struct person*);
int main(array<System::String ^> ^args)
{
	int i,n;
	FILE *in;
	struct person *students;
	setlocale(LC_CTYPE,"Russian");
	Console::CursorVisible::set(false);
	Console::BufferHeight=Console::WindowHeight;
	Console::BufferWidth=Console::WindowWidth;
	Console::ForegroundColor=ConsoleColor::Yellow;
	Console::BackgroundColor=ConsoleColor::DarkMagenta;
	Console::Clear();
	if((in=fopen("student.dat","r"))==NULL) 
	{
		printf("\nNo such file!");
		getch(); exit(1);
	}
	fscanf(in,"%d",&FileLength);
	students=(struct person*)malloc(FileLength*sizeof(struct person));
	for(i=0;i<FileLength;i++)
		fscanf(in,"%s%f%ld%s%s%d", students[i].name, &students[i].grade, &students[i].age, students[i].date, students[i].school, &students[i].price);
	for(i=0;i<FileLength;i++)
		printf("\n%-20s    %1.1f    %7ld   %s   %-10s   %d", students[i].name, students[i].grade, students[i].age, students[i].date,students[i].school, students[i].price);
	getch();

	while(1)
	{
		Console::ForegroundColor=ConsoleColor::DarkGreen;
		Console::BackgroundColor=ConsoleColor::DarkGreen;
		Console::Clear();
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::DarkGreen;
		Console::CursorLeft=10;
		Console::CursorTop=4;
		printf(BlankLine);
		for(i=0;i<8;i++)
		{
			Console::CursorLeft=10;
			Console::CursorTop=i+5;
			printf(" %s ",dan[i]);
		}
		Console::CursorLeft=10;
		Console::CursorTop=12;
		printf(BlankLine);
		n=menu(8);
		//menu functions
		switch(n) {
			case 1: maximum(students); break;
			case 2: first(students); break;
			case 3: listing(students); break;
			case 4: alfalist(students); break;
			case 5: amount(students); break;
			case 6: diagram(students); break;
			case 7: complexquestion(students);break;
			case 8: exit(0);
			}
	}
	return 0;
}
// choosing menu options
int menu(int n)
{
	int y1=0,y2=n-1;
	char c=1;
	while (c!=ESC)
	// menu navigation with arrows
	{
		switch(c) {
			case DOWN: y2=y1; y1++; break;
			case UP: y2=y1; y1--; break;
			case ENTER: return y1+1;
			case HOME: y2=y1; y1=0; break;
			case END: y2=y1; y1=n-1; break;
		}
		if(y1>n-1){y2=n-1;y1=0;}
		if(y1<0) {y2=0;y1=n-1;}
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::Red;
		Console::CursorLeft=11;
		Console::CursorTop=y1+5;
		printf("%s",dan[y1]);
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::DarkGreen;
		Console::CursorLeft=11;
		Console::CursorTop=y2+5;
		printf("%s",dan[y2]);
		c=getch();
	}
	exit(0);
}
// searching max grade
void maximum(struct person* student)
{ 
	int i=0; struct person best;
	strcpy(best.name,student[0].name);
	best.grade=student[0].grade;
	for(i=1;i<FileLength;i++)
		if (student[i].grade>best.grade)
		{
			strcpy(best.name,student[i].name);
			best.grade=student[i].grade;
		}
	Console::ForegroundColor=ConsoleColor::Yellow; 
	Console::BackgroundColor=ConsoleColor::DarkMagenta;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Highest grade %1.1f",best.grade);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("belongs to %s",best.name); 
	getch();
}
// translating date to text
void text_date(char *s,char *sd)
{
	char s0[3],month[12][15]={
	"January","February","March","April","May","June",
	"July","August","September","October","November","December"};
	strcpy(s,sd+8);
	strcat(s," ");
	strncpy(s0,sd+5,2); s0[2]=0;
	strcat(s,month[ atoi(s0)-1]);
	strcat(s," ");
	strncat(s,sd,4);
	return;
}
// "eariest" student
void first(struct person* student)
{
	int i;
	char s[17];
	struct person* best=student; // var for "earliest" student
	for(i=1;i<FileLength;i++)
		if (strcmp(student[i].date,best->date)<0) // date comparison in form "YYYY.MM.DD" using strcmp 
			best=&student[i]; // put all data of new "earliest" student to best
	text_date(s,best->date); // translates date from "YYYY.MM.DD" to readable text
	Console::ForegroundColor=ConsoleColor::Yellow;  
	Console::BackgroundColor=ConsoleColor::DarkMagenta;  
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("The \"earliest\" student is %s", best->name); 
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Enrolled %s ",s); 
	getch();
}

void amount(struct person *student)
{ 
	int i,k=0;
	char sch[20];
	Console::ForegroundColor=ConsoleColor::Yellow;  
	Console::BackgroundColor=ConsoleColor::DarkMagenta;  
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Type school(high, secondary, elementary)");
	Console::CursorLeft=10;
	Console::CursorTop=16;
	scanf("%s",sch);
	for(i=0;i<FileLength;i++)
		if (strcmp(student[i].school,sch)==0)
			k++; // counter
	Console::ForegroundColor=ConsoleColor::Yellow;  
	Console::BackgroundColor=ConsoleColor::DarkMagenta;  
	Console::CursorLeft=10;
	Console::CursorTop=18;
	if(k==0)
	{
		printf("No such school");
		getch();
		return;
	}
	printf("Students of %s school",sch);
	Console::CursorLeft=10;
	Console::CursorTop=19;
	printf("Amount : %d",k); 
	getch();
}
// Alphabetical list created using doubly linked list
void alfalist(struct person* student)
{
	int i;
	struct sp* nt, *z;
	Console::ForegroundColor=ConsoleColor::Black;  
	Console::BackgroundColor=ConsoleColor::Gray;   
	Console::Clear();
	if(!slist)// if no list was created before we create it
		for(i=0;i<FileLength;i++)
			listinsert(student,student[i].name); // creating a list
	Console::Clear(); 
	printf("\n Alphabetical list of students");
	printf("\n =============================\n");
	for(nt=slist; nt!=0; nt=nt->nex) // list output using "nex" links
		printf("\n %-20s %1.1f",nt->sname,nt->grade); 
	Console::CursorLeft=50;
	Console::CursorTop=1;
	printf(" Reversed alphabetical list");
	Console::CursorLeft=50;
	Console::CursorTop=2;
	printf(" ==========================");
	for(nt=slist; nt!=0;z=nt, nt=nt->nex);
	for(nt=z,i=0;nt!=0;i++,nt=nt->pre)
	{	
		Console::CursorLeft=50;
		Console::CursorTop=4+i;
		printf(" %-20s %1.1f",nt->sname,nt->grade); // list output using "pre" links
	}
	getch();
}
// Вставка вкладчика в алфавитный список
void listinsert(struct person* student,char* sname)
{
	int i;
	struct sp *nov,*nt,*z=0;
	for(nt=slist; nt!=0 && strcmp(nt->sname,sname)<0; z=nt, nt=nt->nex);
	// for loop searches a place in list for new student
	// if new student goes to first place for loop is skipped
	if(nt && strcmp(nt->sname,sname)==0) // duplicates protaction
		return; 
	nov=(struct sp *) malloc(sizeof(struct sp)); // allocating memory for each student 
	strcpy(nov->sname,sname); 
	nov->nex=nt; // link to next one
	nov->grade=0; // putting 0 to grade var to be sure there is no random values there
	if(nt) 
		nt->pre=nov; 
	nov->pre=z;// link to previous one
	for(i=0;i<FileLength;i++) // идём по списку 
		if(strcmp(student[i].name,sname)==0)
		{
			nov->grade=student[i].grade; 
			nov->price=student[i].price;
		}
	if(!z) 
		slist=nov; // if new student goes to first place their address becomes first
	else 
		z->nex=nov; // otherwise "nex" link of previous student becomes link to this one 
	return; 
}
// list with conditions
void listing(struct person* student)
{
	int i;
	struct person* nt;
	Console::ForegroundColor=ConsoleColor::Black;  
	Console::BackgroundColor=ConsoleColor::Gray;  
	Console::Clear();
	printf("\n\r List of elementary students yunger than 9 years");
	printf("\n\r ===============================================\n\r");
	for(i=0,nt=student;i<FileLength;nt++,i++) 
		if (nt->age<9 && strcmp(nt->school,"elementary")==0) 
			printf("\n\r %-20s %ld",nt->name,nt->age); // вывод по условию 
	getch(); 
}
// Diagramm is made using pseudographics
// It is made out of colored spaces
void diagram(struct person *student)
{ 
	struct sp *nt;
	int i,ncolor;
	float len;
	long sum = 0 ;
	char str1[20]; // var for name
	char str2[20]; // var for percentage
	System::ConsoleColor Color;
	Console::ForegroundColor=ConsoleColor::Black;  
	Console::BackgroundColor=ConsoleColor::White;  
	Console::Clear(); 
	for(i=0;i<FileLength;i++) 
		sum = sum+student[i].price; // calculating sum 
	if(!slist) // if no list was created before we create it
		for(i=0;i<FileLength;i++)
			listinsert(student,student[i].name);

	Color=ConsoleColor::Black; ncolor=0; // put color var to 0 (black color)
	for(nt=slist,i=0; nt!=0; nt=nt->nex,i++)
	{
		 sprintf(str1,"%s",nt->sname);
		 sprintf(str2,"%3.1f%%",(nt->price*100./sum));
		 Console::ForegroundColor=ConsoleColor::Black; 
		 Console::BackgroundColor= ConsoleColor::White;
		 Console::CursorLeft=5; Console::CursorTop=i+1; // putting coursor to name position 
		 printf(str1); // name output
		 Console::CursorLeft=20; // putting coursor to percentage position
		 printf("%s",str2); // percentage output
		 Console::BackgroundColor=++Color; ncolor++; // changing to next color
		 Console::CursorLeft=30; // putting coursor to diagram position
		 for(len=0; len<nt->price*100/sum; len++) 
			 printf(" "); // output of spaces(amount depends on percentage)
		 if(ncolor==14) // if color gets white we change color to black again 
		 { 
			 Color=ConsoleColor::Black;
			 ncolor=0;
		 }
	 } 
	getch();
	return;
}

// Same age but different school
void complexquestion(struct person* student)
{
	int i,j,k=0;
	Console::ForegroundColor=ConsoleColor::Black;  
	Console::BackgroundColor=ConsoleColor::Gray;  
	Console::Clear();
	printf("\n\r Same age but different school");
	printf("\n\r =============================\n\n\r");

	for(i=1;i<FileLength;i++)
	{
		for(j=0;j<i;j++)
			if(student[i].age==student[j].age && strcmp(student[i].school,student[j].school)!=0)
			{
				printf(" %-20s %ld   %s\n",student[i].name,student[i].age, student[i].school);
				printf(" %-20s %ld   %s\n\n",student[j].name,student[j].age, student[j].school);			 
				k++; //counter
				break;
			}
	}
	if(k==0) printf("No such students");
	getch(); 
}