#include <iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<dos.h>
using namespace std;

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 45
#define WIN_WIDTH 70

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char keys[10];
int keypos[10][2];
int score;
char flag =0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void drawborder()
{
	for(int i=0;i<SCREEN_WIDTH;i++)
	{
		gotoxy(i,SCREEN_HEIGHT);
		cout<<"!";
	}
	for(int i=0;i<SCREEN_HEIGHT;i++)
	{
		gotoxy(0,i);
		cout<<"!";
		gotoxy(SCREEN_WIDTH,i);
		cout<<"!";		
	}
	for(int i=0;i<SCREEN_HEIGHT;i++)
	{
		gotoxy(WIN_WIDTH,i);
		cout<<"!";
	}
}
void gen_alpha(int ind)
{
	keys[ind]='a'+ rand() % 26;
	keypos[ind][0]=2 + rand()%(WIN_WIDTH-2);
    keypos[ind][1]=1;
}
void draw_alpha(int ind)
{
	if(keypos[ind][0]!=0)
	{
		gotoxy(keypos[ind][0],keypos[ind][1]);
		cout<<keys[ind];
	}
	
}
void erase_alpha(int ind)
{
  if(keypos[ind][0]!=0)
	{
		gotoxy(keypos[ind][0],keypos[ind][1]);
		cout<<" ";
	}	
}
void reset_alpha(int ind)
{
   erase_alpha(ind);
   gen_alpha(ind);
}
void updatescore()
{
	gotoxy(WIN_WIDTH + 4, 5);
	cout<<"Score: "<<score<<endl;
}


void play()
{
	score=0;
	for(int i=0;i<10;i++)
	{
		keypos[i][0]=keypos[i][1]=1;
	}
	system("cls");
	drawborder();
	updatescore();
   	for(int i=0;i<10;i++)
   	{
   		gen_alpha(i);
	}
	gotoxy(WIN_WIDTH + 5, 2);cout<<"Typing Tutor";
	gotoxy(WIN_WIDTH + 5, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 5, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 5, 7);cout<<"best_of_luck";
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	while(1)
	{
		if(kbhit())
		{
			char ch=getch();
		    for(int i=0;i<10;i++)
			{
			if(ch==keys[i])
			{
				reset_alpha(i);
				score++;
			    updatescore();
			}
			}
			if(ch==27)
			{
				break;
			}
	
		}
		for(int i=0;i<10;i++)
		{
			draw_alpha(i);
		}
		Sleep(500);
		
	//	sleep(100);
		for(int i=0;i<10;i++)
		{
			erase_alpha(i);
			keypos[i][1]+=1;
			if(keypos[i][1]>SCREEN_HEIGHT )
			{
			    MessageBox(NULL, "GAME OVER", "GAME OVER", MB_ICONINFORMATION);
			    flag=2;
				//exit(0);
				break;
				
			}
			
		}
		if (flag ==2)
		break;
	}
	
	
}


int main(int argc, char** argv) {
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
     system("cls");
		gotoxy(15,5); cout<<" -------------------------- "; 
		gotoxy(15,6); cout<<" |     TYPING  TUTOR      | "; 
		gotoxy(15,7); cout<<" --------------------------";
		gotoxy(15,9); cout<<"1. Start Game";
		gotoxy(15,10); cout<<"2. Instructions";	 
		gotoxy(15,11); cout<<"3. Quit";
		gotoxy(15,13); cout<<"Select option: ";
        char op =getche();
        l:
		if(op=='1')
         play();
        else
          goto l;
		  exit(0);
          
 
	}while(1);	
	return 0;
}
