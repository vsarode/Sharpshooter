
#include<graphics.h>
#include<iostream.h>
#include<dos.h>
#include<process.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
int initmouse();
void exit();
void menu();
void about();
void help();
void getmousepos(int *,int *,int *);
void showmouseptr();
void hidemouseptr();
void restrictmouseptr(int ,int ,int ,int );
union REGS i,  o;
int mstatus,button,x,y,tempx,tempy;  //mouse variables

int gx = 4, gy = 15, gh = 23, gl = 33;		//gun upperrectangle
int gux = 4, guy = 15, guh = 42, gul = 13;	//gun lower rectangle
int ex1 = 350, ey1 = 310, eh1 = 330, el1 = 320;
int px = 0, py;					//bullet coordinates
int key , move , score = 0,lviflag=1;
int cx = 18, cy = 28, rad = 2;
int count=20;		//trigger
char scor[5],cnt[5];
char ss[5];
int j;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//->->->->->->->->->->->->->->->->  SCORING  <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void scoring()
{
	 setfillstyle(0,0);
	 settextstyle(6,HORIZ_DIR,3);
	 setcolor(WHITE);
	 outtextxy(460,447,"SCORE : ");
	 itoa(score, scor, 10);
	 outtextxy(540,447,scor);
	 outtextxy(100,447,"BULLETS : ");
	 itoa(count, cnt, 10);
	 outtextxy(190,447,cnt);


/*itoa(count,ss,10);
outtextxy(340,447,"TIME:");
outtextxy(400,447,ss);
  */
}


//*************************************************************************
//-+-+-+-+-+-+-+-+-+-+-+-+-+-$ GUNUP() $+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//*************************************************************************
void gup()
{
		scoring();
		setcolor(15);
	 rectangle(2,12,630,452);

	if(gy > 18)
	 {
		setcolor(0);
		setfillstyle(1,BLACK);

		bar(gux,guy,gul,guh);
		bar(gx,gy,gl,gh);
		circle(cx,cy,rad);

		cy-=10;
		gy -= 10;
		gh -= 10;
		guy -= 10;
		guh -= 10;

		setcolor(15);
		setfillstyle(6,RED);

		bar(gx,gy,gl,gh);
		bar(gux,guy,gul,guh);
		circle(cx,cy,rad);
	 }
}




//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//@@@@@@@@@@@@@@@@@@@@@@@@@    GUNDOWN()    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void gdown()
{
	 scoring();

	 setcolor(15);
	 rectangle(2,12,630,452);

	 if(gy < 420)
		{
			setcolor(0);
			setfillstyle(1,BLACK);
			bar(gx, gy, gl, gh);
			bar(gux,guy,gul,guh);
			circle(cx,cy,rad);

			cy+=10;
			gy += 10;
			gh += 10;
			guy += 10;
			guh += 10;

			setcolor(15);
			setfillstyle(6,RED);
			bar(gx, gh, gl, gy);
			bar(gux,guy,gul,guh);
			circle(cx,cy,rad);
		}
}


//???????????????????????????????????????????????????????????????????????????
//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{  ENEMY  }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
//???????????????????????????????????????????????????????????????????????????
void enemy()
{
	scoring();

	setcolor(15);
	rectangle(2,12,630,452);                            //limiting window

	delay(20);
	setfillstyle(11,YELLOW);
	bar(ex1,ey1,el1,eh1);
	bar(gux,guy,gul,guh);
	circle(cx,cy,rad);

	move=rand()%7;

	if(move==1 && ex1<=590 && el1<=590  && ey1>=70 && eh1>=70)
	{
		ex1 += 40;
		el1 += 40;
		ey1 -= 40;
		eh1 -= 40;
	}

	if(move==2 && ey1>=70 && eh1>=70)
	{
		ey1 -= 40;
		eh1 -= 40;
	}

	if(move==3 && ex1>=200 && el1>=200 && ey1>=70 && eh1>=70)
  {
		ex1 -= 40;
		el1 -= 40;
		ey1 -= 40;
		eh1 -= 40;
	}

 if(move==5 && ex1>=200  && el1>=200 && ey1<=370 && eh1<=370)
	{
		ex1 -= 40;
		el1 -= 40;
		ey1 += 40;
		eh1 += 40;
	}

	if(move==6 && ey1<=420 && eh1<=420)
	{
		ey1 += 40;
		eh1 += 40;
	}

	if(move==7 && ey1<=420 && eh1<=420 && ex1<=580 && el1<=580)
	{
		ex1 += 40;
		el1 += 40;
		ey1 += 40;
		eh1 += 40;
	}

	if(move==0 && ex1<=600 && el1<=600)
	{
		ex1 += 40;
		el1 += 40;
	}

	if(move==4 && ex1>=200  && el1>=200)
	{
		ex1 -= 40;
		el1 -= 40;
	}


	cleardevice();

	bar(ex1,ey1,el1,eh1);

	setfillstyle(6,RED);
	bar(gx, gh, gl, gy);
	bar(gux,guy,gul,guh);

	circle(cx,cy,rad);

	setcolor(15);
	rectangle(2,12,630,452);

	scoring();
}



//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
// %%%%%%%%%%%%%%%%%%%%%%%%%%%% VOID FIRE() %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

void fire()
{
	scoring();
	count--;
	enemy();

	setcolor(15);
	rectangle(2,12,630,452);

	px=35;
	py=(gy+gh)/2;
	sound(500);
	sound(1100);
	delay(200);
	nosound();
	for(px=35 ; px<649 ; px+=1)
		{

		 delay(2);
		 putpixel(px,py,14);

		 if(px % 5 ==0 )
		 {
			putpixel(px-1,py,0);
			putpixel(px-2,py,0);
			putpixel(px-3,py,0);
			putpixel(px-5,py,0);
			putpixel(px-4,py,0);
			putpixel(px,py,14);

		 if(py >= (ey1-2) && py <= (eh1+2) && px >= (ex1-3))
		 {
				score += 5;
				setcolor(RED);
			  //	settextstyle(7,0,10);
				outtextxy(225,447,"WELL HIT");
				for(j=1700;j<2000;j+=100)
				{
				sound(j);
				delay(150);
				nosound();
				}

				for(int i=0;i<15;i++)
				{
				 el1-=1;
				 ey1-=1;
				 ex1+=1;
				 eh1+=1;
				 setfillstyle(11,RED);
				 bar(ex1, ey1, el1, eh1);
				 delay(2);
		 }
				delay(200);

				setfillstyle(11,BLACK);
				bar(ex1, ey1, el1, eh1);

			for(int j=0;j<30;j++)
			{
				 ex1--; eh1--;
				 setfillstyle(11,BLACK);
				 bar(ex1, ey1, el1, eh1);
			}
			 delay(200);

			 setfillstyle(0,RED);
			 bar(ex1,ey1,el1,eh1);
			 putpixel(px,py,0);

			 enemy();
			 break;
		 }
		 }

		 if(kbhit())
		 {
			key = getch();

			if(key == 27)
			 exit(0);

			if(key == 72)
			 gup();

			if(key == 80)
			 gdown();

		 }
		}//for

}



//000000000000000000000000000000000000000000000000000000000000000000000000000
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< help() >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//000000000000000000000000000000000000000000000000000000000000000000000000000
void help()
{


	 setbkcolor(0);
	    settextstyle(7,0,3);
	 for(int i=480;i>=50;i-=5)
		{
		 cleardevice();
		 setcolor(i/4);
		 outtextxy(i,i+20,"Welcome to The world of shooters !!");
		 delay(40);
		}
	 delay(2000);

	 settextstyle(6,0,2);

	 setcolor(7);
	 outtextxy(60,150,"RULES:");

	 setcolor(6);
	 outtextxy(110,200,"Press SPACE_BAR for SHOOTING.");

	 setcolor(15);
	 outtextxy(110,250,"Press UP_ARROW for MOVE GUN to UP.");

	 setcolor(2);
	 outtextxy(110,300,"Press DOWN_ARROW for MOVE GUN to DOWN.");
	 delay(3000);
	       while(!kbhit())
	       {
	       }
	       cleardevice();
	       menu();


}
//****************************STARTPAGE()*********************
//************************************************************

void startpage()
{
setbkcolor(15);
int i=0;
setcolor(12);
for(i=0;i<50;i++)
{
cleardevice();
 circle(getmaxx()/2,getmaxy()/2,i);
delay(100);
}
 i=1;
while(i<25)
{
circle(getmaxx()/2,getmaxy()/2,i);

delay(100);
i++;
}
setcolor(12);
line(getmaxx()/2,getmaxy()/2-50,getmaxx()/2,getmaxy()/2+50);
delay(100);
 line(getmaxx()/2-50,getmaxy()/2,getmaxx()/2+50,getmaxy()/2);
 delay(500);
 //****************** font effect

 settextstyle(GOTHIC_FONT,0,5);
 for(i=0;i<=8;i++)
 {
  setcolor(i);
 outtextxy(110,getmaxy()/2-20,"SHARP       SHOOTER");
 delay(500);
 }
  setcolor(12);
 outtextxy(110,getmaxy()/2-20,"SHARP       SHOOTER");



 /* setcolor(12);
  settextstyle(TRIPLEX_FONT,0,5);
  outtextxy(110,getmaxy()/2-20,"SHARP        SHOOTER");
  delay(1000);
  setcolor(15) ;
  outtextxy(110,getmaxy()/2-20,"SHARP        SHOOTER");

  setcolor(12);
  settextstyle(GOTHIC_FONT,0,5);
  outtextxy(110,getmaxy()/2-20,"SHARP        SHOOTER");
   */

  delay(3000);
 }





//------------------------------------------------------------------------
//***************************GET EVENT()**********************************
//------------------------------------------------------------------------
void getevent()
{

	cleardevice();
	scoring();
	setcolor(15);
	setbkcolor(LIGHTBLUE);
	rectangle(2,12,630,452);

	while(count>0)
		{
		 key = getch();

		 if(score==50 && lviflag==1)
		 {
		 lviflag=2;
		 outtextxy(200,200,"Good!!! LEVEL 2 STARTED");
		 delay(100);
		 score=0;
		 count=15;
		 }

		 if(score==50 && lviflag==2)
		 {
		 lviflag=3;
		 outtextxy(200,200,"AWESOME!!! LEVEL 3 STARTED");
		 delay(100);
		 score=0;
		 count=10;
		 }
		 if(lviflag==3 && score==35)
		 { cleardevice();
		  outtextxy(220,200,"CONGRATS SHARPSHOOTER!! YOU DONE IT.....");
		  break;
		 }
		 if(key == 27)
			exit(0);

		 if(key == 72)
			gup(); //continue;

		 if(key == 80)
			gdown();// continue;

		 if(key == 32)
			fire();

	 }//while
	 if(count==0)
	 {
	 cleardevice();
		settextstyle(4,HORIZ_DIR,4);
	 outtextxy(200,200,"GAME OVER");
	 delay(500);
	 setcolor(getbkcolor());
	 outtextxy(200,200,"GAME OVER");
	 delay(500);
	 setcolor(15);
	 outtextxy(200,200,"GAME OVER");
	 delay(500);
	 setcolor(getbkcolor());
	 outtextxy(200,200,"GAME OVER");
	 delay(500);
	 setcolor(15);
	 outtextxy(200,200,"GAME OVER");
	 }
	 delay(500);
	 cleardevice();
	 menu();


}//getevent()


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!MENU()!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void menu()
{
	int i=0;
	setcolor(RED);
	setbkcolor(LIGHTBLUE);
	settextstyle(7,HORIZ_DIR,6);
	outtextxy(100,20,"SHARPSHOOTER");
	settextstyle(4,HORIZ_DIR,4);
	outtextxy(200,100,"New Game");
	rectangle(190,100,360,140);
	outtextxy(200,150,"Help");
	rectangle(190,150,360,190);
	outtextxy(200,200,"About us");
	rectangle(190,200,360,240);
	outtextxy(200,250,"Exit");
	rectangle(190,250,360,290);
	mstatus=initmouse();
	if(mstatus==0)
	printf("\nMouse not initialised.");
	showmouseptr();
     while(!i)
     {
	 getmousepos(&button,&x,&y);
	 if(button==1)
	 {

	 if((x>=190&&x<=360) && (y>=100&&y<=140) )
	 {
		cleardevice();
		button=-1;
		getevent();

	 }
	 if((x>=190&&x<360) && (y>=150&&y<190))
	 {
		button=-1;
		cleardevice();
		help();
	 }
	if((x>=190&&x<360) && (y>=200&&y<240) )
	{
		button=-1;
		cleardevice();
		about();
	}
	if((x>=190&&x<360) && (y>=250&&y<290))
	{    	i=1;
		button=-1;
		cleardevice();
		exit();

	}
      }
  }
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@EXIT()@!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void exit()
{
   setbkcolor(LIGHTGRAY);
   setcolor(BLUE);
   rectangle(60,60,getmaxx()-50,getmaxy()-50);
   settextstyle(4,0,6);
   outtextxy(200,100,"Thank You !");
   settextstyle(1,0,3);
   setcolor(MAGENTA);
   outtextxy(75,250," Have a nice day............");
   outtextxy(75,300," For any query contact :-");
   outtextxy(255,350,"Sharpshooter007@gmail.com");
   delay(3000);
   getch();
   closegraph();
}
//###########################About#######################################
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void about()
{
// while(!kbhit())
 //{
   setbkcolor(LIGHTGRAY);
   setcolor(BLUE);
   rectangle(60,60,getmaxx()-50,getmaxy()-50);
   settextstyle(4,0,6);
   outtextxy(200,100,"Created by:");
   settextstyle(1,0,3);
   setcolor(MAGENTA);
   outtextxy(75,150,"Hrushikesh S. Gadakh") ;
   outtextxy(75,200,"Vitthal V. Sarode");
   outtextxy(75,250,"Sachin P. Gaikwad");
   outtextxy(75,300,"For any queries contact us:");
   outtextxy(255,350,"Shapshooter007@gmail.com");
 // }
 delay(5000);
  cleardevice();
  menu();
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!! void main()!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//##########################################################################
void main()
{
	 int gd = DETECT, gm;

	 initgraph(&gd, &gm, "C://TC//BGI");
	 startpage();
	 cleardevice();
	 menu();

	 setcolor(15);
	 rectangle(2,12,630,452);

	 cleardevice();

		scoring();
	 setfillstyle(6,RED);
	 circle(cx,cy,rad);

	 bar(gx,gy,gl,gh);
	 bar(gux,guy,gul,guh);
	 setfillstyle(13,RED);
	 bar(ex1,ey1,el1,eh1);

	 getevent();
	 closegraph();
getch();
}

//*******************************mouse methods**********************
//*******************************************************************
int initmouse()
{
  i.x.ax=0;
  int86(0x33,&i,&o);
  return(o.x.ax);
}

void getmousepos(int *button,int *x,int *y)
{
  i.x.ax=3;
  int86(0x33,&i,&o);

  *button=o.x.bx;
  *x=o.x.cx;
  *y=o.x.dx;
}

void showmouseptr()
{
  i.x.ax=1;
  int86(0x33,&i,&o);
}

void hidemouseptr()
{
  i.x.ax=2;
  int86(0x33,&i,&o);
}

void restrictmouseptr(int x1,int y1,int x2,int y2)
{
  i.x.ax=7;
  i.x.cx=x1;
  i.x.dx=x2;
  int86(0x33,&i,&o);

  i.x.ax= 8;
  i.x.cx=y1;
  i.x.dx=y2;
  int86(0x33,&i,&o);
}
