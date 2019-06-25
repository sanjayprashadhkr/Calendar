#include<stdio.h>
#include<conio.h>
#include<bios.h>
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define DIM 7
#define WIDTH 5
#define HEIGHT 1
#define VL 179
#define HL 196
#define LT 218
#define RT 191
#define LB 192
#define RB 217
#define TT 194
#define BT 193
#define LST 180
#define RST 195
#define CROSS 197
#define BS 8
#define SP 32
#define LEFT 19200
#define RIGHT 19712
#define UP 18432
#define DOWN 20480
#define ESC 283
#define HOME 18176
#define END 20224
int dayofdate(int,int,int);
int isleapyear(int);
void drawbox();
void fillbox(int,int);
int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int main()
{
	clrscr();
	int key,headlocation[2]={19,4};
	int m=1,y=2019;
	drawbox();
	fillbox(m,y);
	gotoxy(headlocation[0],headlocation[1]);
	printf("MONTH:%d YEAR:%d",m,y);
	do
	{
		while(bioskey(1)==0);
		key=bioskey(0);
		if(key==RIGHT)
		{
			m++;
			if(m==13)
			{
				m=1;
				y++;
			}
			clrscr();
			drawbox();
			fillbox(m,y);
		}
		if(key==LEFT)
		{
			m--;
			if(m==0)
			{
				m=12;
				y--;
			}
				clrscr();
				drawbox();
				fillbox(m,y);
		}
		if(key==UP)
		{
		  y--;
		  clrscr();
		  drawbox();
		  fillbox(m,y);
		}
		if(key==DOWN)
		{
			y++;
			clrscr();
			drawbox();
			fillbox(m,y);
		}
		gotoxy(headlocation[0],headlocation[1]);
		printf("MONTH:%d YEAR:%d",m,y);
	}while(key!=ESC);
	return 0;
}
void fillbox(int mon,int year)
{
	int bcol=18,brow=5,index1,index2,daylimit;
	char days[7][3]={"MON","TUE","WED","THU","FRI","SAT","SUN"};
	gotoxy(++bcol,++brow);
	for(index1=0;index1<7;index1++)
	{
		printf("%c",SP);++bcol;
		for(index2=0;index2<3;index2++)
		{
			printf("%c",days[index1][index2]);bcol+=1;
		}
		printf("%c",SP);++bcol;
		gotoxy(++bcol,brow);
	}
	if(mon==2)
		daylimit=month[mon]+isleapyear(year);
	else if(mon==1 || mon>2)
	{
		daylimit=month[mon];
	}
	bcol=18;brow=8;
	gotoxy(18,8);
	int colincrement=6,rowincrement=2;
	for(index1=1;index1<=daylimit;index1++)
	{
	      int dd=dayofdate(index1,mon,year);
	      switch(dd)
	      {
	      case 0:
			gotoxy(bcol+(colincrement*6)+3,brow);
			break;
		case 1:
			gotoxy(bcol+3,brow);
			break;
		case 2:
			gotoxy(bcol+(colincrement*1)+3,brow);
			break;
		case 3:
			gotoxy(bcol+(colincrement*2)+3,brow);
			break;
		case 4:
			gotoxy(bcol+(colincrement*3)+3,brow);
			break;
		case 5:
			gotoxy(bcol+(colincrement*4)+3,brow);
			break;
		case 6:
			gotoxy(bcol+(colincrement*5)+3,brow);
			break;
	      }
	      printf("%d",index1);
	      if(dd==0)
		brow+=2;
	}

}
void drawbox()
{
   int bcol,brow,count1,count2,count3;
   bcol=(SCREEN_WIDTH-((DIM*WIDTH)+DIM+1))/2;
   brow=(SCREEN_HEIGHT-((DIM*HEIGHT)+DIM+1))/2;
   gotoxy(bcol,brow);
   printf("%c",LT);
   for(count1=1;count1<=DIM;count1++)
   {
	for(count2=1;count2<=WIDTH;count2++)
	{
		printf("%c",HL);
	}
	printf("%c",TT);
   }
   printf("%c%c",BS,RT);
   for(count3=1;count3<=DIM;count3++)
   {
	 gotoxy(bcol,++brow);
	 printf("%c",VL);
	 for(count1=1;count1<=DIM;count1++)
	 {
		for(count2=1;count2<=WIDTH;count2++)
		{
			printf("%c",SP);
		}
		printf("%c",VL);
	 }
	 if(count3!=DIM)
	 {
		gotoxy(bcol,++brow);
		 printf("%c",RST);
		 for(count1=1;count1<=DIM;count1++)
		 {
			for(count2=1;count2<=WIDTH;count2++)
			{
				printf("%c",HL);
			}
			printf("%c",CROSS);
		}
		printf("%c%c",BS,LST);
	 }
   }
   gotoxy(bcol,++brow);
   printf("%c",LB);
   for(count1=1;count1<=DIM;count1++)
   {
	for(count2=1;count2<=WIDTH;count2++)
	{
	 printf("%c",HL);
	}
	printf("%c",BT);
   }
   printf("%c%c",BS,RB);
}
int dayofdate(int eday,int emonth,int eyear)
{
	int index,index2,rday=1,rmonth=1,ryear=1900;
	long int days_sum=0;
	/*for(index=1;index<rmonth;index++)//counting Months
	{
		days_sum+=month[index];
	}
	for(index=rday
	if(rmonth<=2)
		days_sum+=isleapyear(ryear);    */
	//Adding Inbetween years
	for(index=ryear;index<eyear;index++)
	{
		for(index2=1;index2<=12;index2++)
		{
			days_sum+=month[index2];
		}
		days_sum+=isleapyear(index);
	}
	for(index=1;index<emonth;index++)
	{
		days_sum+=month[index];
	}
	if(emonth>2)
		days_sum+=isleapyear(eyear);
	days_sum+=eday;
	return days_sum%7;
}
int isleapyear(int year)
{
	if(year%4==0)
	{
		if(year%100==0)
		{
			if(year%400==0)
				return 1;
			else
				return 0;
		}
		else
			return 1;
	}
	else
		return 0;
}