#include<graphics.h>
#include<fstream.h>
#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
//--------------------------THEME MUSIC----------------------------
void smallbr()
{
     settextstyle(1,0,2);
     outtextxy(250,220," BRAINVITA ");
     settextstyle(1,0,8);
}
void music()
{       int x=40;

	sound(391);  //g
	setcolor(3);
	smallbr();
	delay(400);
	cleardevice();


	sound(440); //a
	setcolor(WHITE);
	outtextxy(140,200,"BRAINVITA");
	delay(1000);
	nosound();
	delay(100);
	cleardevice();

	sound(261*2); //c
	delay(250);
	nosound();
	delay(2);

	sound(261*2); //c
	setcolor(1);
	outtextxy(100+x,200,"B");
	delay(250);
	nosound();
	delay(2);

	sound(246*2); //b
	setcolor(2);
	outtextxy(100+x*2+10,200,"R");
	delay(250);
	nosound();
	delay(1);

	sound(261*2); //c
	setcolor(3);
	outtextxy(100+x*3+15,200,"A");
	delay(250);
	nosound();
	delay(60);

	sound(246*2); //b
	setcolor(4);
	outtextxy(100+x*4+15,200,"I");
	delay(250);
	nosound();
	delay(2);

	sound(220*2);//a
	setcolor(5);
	outtextxy(100+x*5,200,"N");
	delay(750);
	nosound();
	//end of first part


	sound(293*2); //d
	setcolor(6);
	outtextxy(100+x*6+10,200,"V");
	delay(250);
	nosound();
	delay(2);

	sound(293*2); //d
	setcolor(7);
	outtextxy(100+x*7+10,200,"I");
	delay(250);
	nosound();
	delay(2);

	sound(261*2); //c
	setcolor(8);
	outtextxy(100+x*8,200,"T");
	delay(250);

	sound(293*2); //d
	setcolor(9);
	outtextxy(100+x*9+10,200,"A");
	delay(250);
	nosound();
	delay(60);

	rectangle(130,190,540,300);

	sound(261*2); //c
	delay(250);

	sound(246*2);//b
	delay(350);
	nosound();
	cleardevice();

	rectangle(130,190,540,300);


	sound(391);  //g
	setcolor(WHITE);
	outtextxy(140,200,"BRAINVITA");


	delay(400);
	cleardevice();
	rectangle(130,190,540,300);


	sound(440); //a
	setcolor(GREEN);
	outtextxy(140,200,"BRAINVITA");
	delay(1000);
	nosound();



}
//--------------------------MOUSE  CODE----------------------------
class mouse
{	public:	int cx,cy,q;
		REGS regs;
		int no_buttons;
	public: mouse()
		{	regs.x.ax=0;
			int86(0x33,&regs,&regs);
			if(regs.x.ax==0xfff)no_buttons=regs.x.bx;
		}
		void show_mouse()//Displays the mouse pointer when
		{	regs.x.ax=0x01;//invoked
			int86(0x33,&regs,&regs);
		}
		void hide_mouse()//Hides the mouse pointer when
		{	regs.x.ax=0x02;//invoked
			int86(0x33,&regs,&regs);
		}
		void get_status()//Assigns the co-ordinates of the clicked
		{	regs.x.ax=0x03;//pixel to cx and cy

			int86(0x33,&regs,&regs);
			while(q!=1)
			{	regs.x.ax=0x03;
				int86(0x33,&regs,&regs);
				q=regs.x.bx;
				cx=regs.x.cx;
				cy=regs.x.dx;
			}
			q=0;
		}
}m;//This global object is used to invoke the various functions of class mouse
//---------------------DISPLAYS THE HEADING--------------------
void heading()
{
	setcolor(YELLOW);
	settextstyle(3, 0, 4);
	outtextxy(230, 0, "BRAIN VITA");
}
//-------------------BASE ARRAY CREATION-----------------------
const int H=640, V=240;//Horizontal and vertical dimensions of the screen
int b[7][7];//base array that is modified with every move
void init() //Initializes the base array to initial conditions
{
	for(int i=0; i<7; i++)
		for(int j=0; j<7; j++)
		 b[i][j]=1; //Positions that are initially filled
			    //initialized with 1,
	b[0][0]=b[0][1]=b[0][5]=b[0][6]=0;//those that are non-existent are
	b[1][0]=b[1][1]=b[1][5]=b[1][6]=0;//set to 0
	b[5][0]=b[5][1]=b[5][5]=b[5][6]=0;
	b[6][0]=b[6][1]=b[6][5]=b[6][6]=0;
	b[3][3]=-1;//and those that are empty initially are -1.
}
int fc=GREEN, sc=LIGHTGREEN, ec=BLACK, rad=20, otln=WHITE;
//fc-color of filled position, ec-color of empty position
//otln-outline color of circular positions, rad is the radius of each position
void cir(int cx, int cy, int col=fc)//Draws the circles for
{       setcolor(otln);	   //the initial layout
	circle(cx, cy, rad);//Circle is drawn

	setfillstyle(1, col);//Circle drawn is filled
	floodfill(cx, cy, otln);// with appropriate color
}
//-----------------------DISPLAYS COMMENT & SCORE BOXES----------------

void initial_score()
{
	setcolor(WHITE);
	settextstyle(3, 0, 3);
	outtextxy(30, 85, " SCORE: ");//Displays "SCORE"

	setcolor(LIGHTBLUE);
	settextstyle(3, 0, 3);
	outtextxy(130, 85, "00");//an initial score of zero is displayed
}
//---------------CHANGES THE COMMENT DISPLAYED WITH EVERY CLICK---------
int C_x=10, C_y=40, S_x=125, S_y=80;//top left co-ord. for comment
void comment(char com[], int col)
{
	int lc=170, hc=35;//length and height of comment eraser bar

	setfillstyle(BLACK, 0);
	bar(C_x, C_y, C_x+lc, C_y+hc);//Erases the previous comment

	setcolor(col);
	settextstyle(3, 0, 3);
	outtextxy(C_x+5, C_y+5, com);//Displays the appropriate comment

}
//------------------CHANGES THE SCORE AS THE USER PLAYS-------------
char s[3]={'0', '0', '\0'};//global score variable required in play,
//layout and score functions
void score()
{

	if (s[1]=='9')//Updates score by modifying the the string s
	{	s[0]++;
		s[1]='0';
	}
	else s[1]++;


	int ls=40, hs=45;//length and height of score for the erasing bar

	setcolor(BLACK);//Erases the previous score
	bar(S_x, S_y, S_x+ls, S_y+hs);//by drawing a black bar

	setcolor(LIGHTBLUE);
	settextstyle(3, 0, 3);
	outtextxy(S_x+5, S_y+5, s);//Displays score
}
//-----------------------DISPLAYS THE MENU BUTTON-----------------
int l=80, h=32, A_x=550, A_y=C_y;//co-ordinates are made global as they are
void menu_button()//required in both help and in play function
{	setcolor(WHITE);
	rectangle(A_x, A_y, A_x+l, A_y+h);//Box is drawn

	setcolor(MAGENTA);
	settextstyle(3, 0, 4);
	outtextxy(A_x+5, A_y-5, "MENU");//"MENU" is displayed in the box
}
//---------------------------CREATES LAYOUT----------------------
int inc=60;//distance between centers of two adjacent circles
int x_i=H/2-3*inc, y_i=85;//center co-ord of top left (non-existent) circle
void layout()
{	cleardevice();
	strcpy(s, "00");//score is reset each time a player begins a new game
	init(); //invokes the function that initializes the base array
	heading(); //invokes the heading function

	for(int i=0,x=x_i,  y=y_i; i<7; i++, x=x_i, y+=inc)
	{	for(int j=0; j<7; j++, x+=inc)
			if(b[i][j]!=0)
			{	if (b[i][j]==-1) cir(x, y, ec);
					else cir(x, y);

			} //centers for the circular positions are calculated
	}//row-wise & passed to previously defined cir() function
	initial_score();//invokes comment and score boxes
	menu_button();//invokes menu button
}
//-------CHECKS IF THERE EXISTS ATLEAST ONE VALID MOVE POSSIBLE AFTER
//--------EVERY MOVE  -----------------------------------------
void moves(int &c)
{
	c=0;//resets this counter variable to zero

		for(int i=0; (i<7)&&(c==0); i++)//traverses the array and
		{			//if atleast one valid move exists
			for(int j=0; (j<7)&&(c==0); j++)//upon finding a move,
				if (b[i][j]==-1)//is exited with the condition
				{
					if ((i<5)&&(b[i+1][j]==1)&&(b[i+2][j]==1))
						c=1;
					else if ((i>1)&&(b[i-1][j]==1)&&(b[i-2][j]==1))
						c=1;

					else if ((j<5)&&(b[i][j+1]==1)&&(b[i][j+2]==1))
						c=1;
					else if ((j>1)&&(b[i][j-1]==1)&&(b[i][j-2]==1))
						c=1;
				}
		}
}
void menu();//prototype to avoid compilation error
//------------------CHANGES THE DISPLAY AS THE USER PLAYS-----------------
void PLAY()
{	layout();//invokes the layout

	int X=x_i-inc/2, Y=y_i-inc/2;
	int c=4;//c is initialized to a non-zero value
	m.show_mouse();

	do
	{	delay(250);
		comment("   SELECT", CYAN);//displays instructions to user
		m.get_status();//gets status of mouse click
		//An co-ordinate axes shift (m.cx, m.cy --> X, Y) is used
		//to determine which position is selected, if at all
		int i=(m.cx-X)/inc, j=(m.cy-Y)/inc, x=x_i+inc*i, y=y_i+inc*j;

		if((j>=0)&&(j<7)&&(i>=0)&&(i<7)&&((m.cx-x)<=(2*rad))&&((m.cy-y)<=(2*rad))&&(b[i][j]==1))
		{	int x_1, y_1, I_1, J_1;
			x_1=x, y_1=y;
			I_1=i, J_1=j;

			m.hide_mouse();

			setfillstyle(2, sc);//Selects a marble upon clicking
			floodfill(x, y, otln);
			comment("    MOVE", 5);

			m.show_mouse();
			delay(150);

			m.get_status();
			//same as previous
			i=(m.cx-X)/inc, j=(m.cy-Y)/inc, x=x_i+inc*i, y=y_i+inc*j;
			int mx=x_i+inc*(i+I_1)/2, my=y_i+inc*(j+J_1)/2, mi=(I_1+i)/2, mj=(J_1+j)/2;

			if((j>=0)&&(j<7)&&(i>=0)&&(i<7)&&((m.cx-x)<=(2*rad))&&((m.cy-y)<=(2*rad))&&(((abs(i-I_1)==2)&&(abs(j-J_1)==0))||((abs(i-I_1)==0)&&(abs(j-J_1)==2)))&&(b[i][j]==-1)&&(b[mi][mj]==1))
			{
				m.hide_mouse();

				setfillstyle(1, fc); //Fills the position to
				floodfill(x, y, otln);//which a marble is moved
				b[i][j]=1;

				setfillstyle(1, ec);
				floodfill(x_1, y_1, otln);//empties the previous
				b[I_1][J_1]=-1;//position of the marble

				setfillstyle(1, ec);
				floodfill(mx, my, otln);//empties the intermeditate
				b[mi][mj]=-1;//position

				score(); //Updates the score
				moves(c);//checks if there exists
					 //atleast one valid move
				m.show_mouse();
			}
			else if(((m.cx-A_x)<=l)&&((m.cy-A_y)<=h))
			{
				m.hide_mouse();
				menu();//If users clicks on the menu button
				       //this condition invokes the menu function.
			}
			else
			{
				m.hide_mouse();
				setfillstyle(1, fc);//Resets the selected
				floodfill(x_1, y_1, otln);//position if the
				m.show_mouse(); //following move is not legal
				comment("ILLEGAL MOVE", RED);//Displays comment
				delay(200);//delay for the mouse
			}
		}
		else if (((m.cx-A_x)<=l)&&((m.cy-A_y)<=h))
		{
			m.hide_mouse();
			menu();//If users clicks on the menu button,
			       //this condition invokes the menu function.
		}
	}while(c);//exits loop when no more valid moves exist

	//The following lines diplay messages at the end of the game

	m.hide_mouse();//Hides the mouse

	setcolor(RED);//Draw a bar to diplay message
	bar(170, 230, 500, 305);


	setcolor(WHITE);
	settextstyle(3, 0, 6);

	if(strcmpi(s, "31")==0)//if score is 31, player wins
		outtextxy(171, 240, "  YOU WIN!");//message is displayed
			else //else player loses
				outtextxy(171, 240, " GAME OVER!");//message is displayed
	m.show_mouse();

	do
	{	delay(250);
		m.get_status();
		if(((m.cx-A_x)<=l)&&((m.cy-A_y)<=h))
		{       m.hide_mouse();
			menu();//If users clicks on the menu button
			       //this condition invokes the menu function.
		}
	}while(6);

}
//------------PROVIDES INSTRUCTIONS TO PLAY THE BRAIN VITA----------
void HELP()
{       cleardevice();
	heading();//invokes the heading
	ifstream f("HELP.TXT"); //opens the file containing the instruction
				//to be displayed
	char s[300];
//	int c=1;

	int y=50;
	setcolor(LIGHTBLUE);
	while(y<50+15*23)
	{
		f.getline(s, 300, '\n');//retrieves data from file

		settextstyle(6, 0, 3);//displays the data
		outtextxy(10, y, s);//retrieved

		y = y+23;//

	}
	f.close();//file is closed

	menu_button();//menu button is invoked
	m.show_mouse();
	do
	{	delay(250);
		m.get_status();
		if(((m.cx-A_x)<=l)&&((m.cy-A_y)<=h))
		{       m.hide_mouse();
			menu();//If users clicks on the menu button
			       //this condition invokes the menu function.
		}
	}while(6);
}
//-------------------------------MENU FUNCTION-----------------------
int length=85, breadth=45;
void seg(int t_l_x, int t_l_y, char s[])
{
	setcolor(RED);//creates the boxes
	rectangle(t_l_x, t_l_y, t_l_x+length, t_l_y+breadth);

	setcolor(WHITE);
	settextstyle(3, 0, 4);
	outtextxy(t_l_x+6, t_l_y+3, s);//displays the appropriate text
}
void menu()
{
	cleardevice();

	setcolor(YELLOW);   //Heading
	settextstyle(3, 0, 6);
	outtextxy(220, 20, "BRAIN VITA");

	const int s=3;
	char t[s][10]={"HELP", "PLAY", "EXIT"};

	int a[3][2];

	int x_i=270, y_i=120, v=100;
	for(int j=0; j<=2; j++, y_i+=v)
	{			a[j][0]=x_i; //stores the initial co-ordinates
				a[j][1]=y_i; //of each box drawn

				seg(x_i, y_i, t[j]);
	}
	do
	{		m.show_mouse();
			delay(250);
			m.get_status();

			int o=-1;
			for(int k=0; ((k<s)&&(o==-1)); k++)
			{	if (((m.cx-a[k][0])<=length)&&((m.cy-a[k][1])<=breadth))
					      o=k; //if user clicks on a box
						  //the number is stored
			}
			switch(o)//Selects appropriate option according to
			{                             //number stored
				case 0: m.hide_mouse();
					HELP();
					break;
				case 1: m.hide_mouse();
					PLAY();
					break;
				case 2: exit(0);
					break;
			}
	}while(6);
}
//-----------------------------MAIN FUNCTION---------------------------
void main()
{       clrscr();
	int a=VGA, b=2;
	initgraph(&a,&b,"C:\\tc\\bgi");
	initgraph(&a,&b,"C:\\tc\\bgi");

	smallbr();//invoking
	delay(1000);//the
	cleardevice();//theme
	music();//music

	menu(); //Invokes the menu function. The control is transferred
		//to appropriate functions from the menu function.
	getch();
	closegraph();
}