#include<graphics.h>
#include<fstream.h>
#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>

/*class for mouse function*/
class mouse
{
public:	int cx,cy,q;
		REGS regs;
		int no_buttons;
	public:
		mouse()
		{
			regs.x.ax=0;
			int86(0x33,&regs,&regs);
			if(regs.x.ax==0xfff)no_buttons=regs.x.bx;
		}
		void show_mouse()
		{
			regs.x.ax=0x01;
			int86(0x33,&regs,&regs);
		}
		void hide_mouse()
		{
			regs.x.ax=0x02;
			int86(0x33,&regs,&regs);
		}
		void get_status()
		{
			regs.x.ax=0x03;
			int86(0x33,&regs,&regs);
			while(q!=1)
			{
				regs.x.ax=0x03;
				int86(0x33,&regs,&regs);
				q=regs.x.bx;
				cx=regs.x.cx;

				cy=regs.x.dx;
			}
			q=0;

		}
}m;//object for mouse function

//function to print heading
void heading()
{

	settextstyle(3, 0, 4);
	outtextxy(225, 0, "BRAIN VITA");
}
const int H=640, V=240, rad=20;
int b[7][7];


//function to initialize base-array for the board layout
void init()
{

	for(int i=0; i<7; i++)
		for(int j=0; j<7; j++)
			     b[i][j]=1;

	b[0][0]=b[0][1]=b[0][5]=b[0][6]=0;
	b[1][0]=b[1][1]=b[1][5]=b[1][6]=0;
	b[5][0]=b[5][1]=b[5][5]=b[5][6]=0;
	b[6][0]=b[6][1]=b[6][5]=b[6][6]=0;
	b[3][3]=-1;

}

int bc=2;

//function overloaded to draw a circle
void cir(int cx, int cy, int col=bc, int otln=WHITE)
{

	setcolor(otln); 
	circle(cx, cy, rad);

	setfillstyle(1, col);
	floodfill(cx, cy, otln);
}
int C_x=1, C_y=1;


int x_i=125, y_i=85, inc=60;
//sets initial layout with help of base array
void layout()
{
	cleardevice();
	init();
	heading();
	for(int i=0,x=x_i,  y=y_i; i<7; i++, x=x_i, y+=inc)

	{

		for(int j=0; j<7; j++, x+=inc)

			if(b[i][j]!=0)
			{
				if (b[i][j]==-1)
					cir(x, y, BLACK);
					else
						cir(x, y);

			}
	}

}

//function that actual makes moves
void PLAY()
{
//	cleardevice();
//	init();
//	heading();
//	comment_box();
//	menu_button();
	layout();
	int X=x_i-inc/2, Y=y_i-inc/2;
	m.show_mouse();

	do
	{
		delay(1000);

		comment("  SELECT", 9);
		m.get_status();

		int i=(m.cx-X)/inc, j=(m.cy-Y)/inc, x=x_i+inc*i, y=y_i+inc*j;

		if((j>=0)&&(j<7)&&(i>=0)&&(i<7)&&(m.cx>=x-rad)&&(m.cx<=x+rad)&&(m.cy>=y-rad)&&(m.cy<=y+rad)&&(b[i][j]==1))
		{

			int x_1, y_1, I_1, J_1;
			x_1=x, y_1=y;
			I_1=i, J_1=j;


			setfillstyle(2, 4);
			floodfill(x, y, WHITE);

			delay(500);
			comment("   MOVE", 5);
			m.get_status();
			i=(m.cx-X)/inc, j=(m.cy-Y)/inc, x=x_i+inc*i, y=y_i+inc*j;
			int mx=x_i+inc*(i+I_1)/2, my=y_i+inc*(j+J_1)/2, mi=(I_1+i)/2, mj=(J_1+j)/2;

			if((j>=0)&&(j<7)&&(i>=0)&&(i<7)&&((m.cx>=x-rad)&&(m.cx<=x+rad)&&(m.cy>=y-rad)&&(m.cy<=y+rad)&&((abs(i-I_1)==2)&&(abs(j-J_1)==0)||((abs(i-I_1)==0)&&(abs(j-J_1)==2)))&&(b[i][j]==-1)&&(b[mi][mj]==1)))
			{

				setfillstyle(1, bc);
				floodfill(x, y, WHITE);
				b[i][j]=1;


				setfillstyle(1, BLACK);
				floodfill(x_1, y_1, WHITE);
				b[I_1][J_1]=-1;


				setfillstyle(1, BLACK);
				floodfill(mx, my, WHITE);
				b[mi][mj]=-1;

			}

			else if((m.cx>=A_x)&&(m.cx<=A_x+l)&&(m.cy>=A_y)&&(m.cy<=A_y+h))
			{
				menu();
			}
			
		}
		else if((m.cx>=A_x)&&(m.cx<=A_x+l)&&(m.cy>=A_y)&&(m.cy<=A_y+h))
		{
				menu();
		}
	}while(6);
}

//-----------------------------MAIN FUNCTION---------------------------

void main()
{
	clrscr();
	int a=VGA, b=2;
	initgraph(&a,&b,"C:\\turboc3\\bgi");


	menu();


	getch();
	closegraph();

}