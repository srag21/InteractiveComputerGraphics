#include<graphics.h>
#include<fstream.h>
#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>


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

void main()
{
	clrscr();
	int a=VGA, b=2;
	initgraph(&a,&b,"C:\\turboc3\\bgi");


	layout();


	getch();
	closegraph();

}