#include <GL/glut.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define ROWS 40
#define COLUMNS 40
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define max 50
int posx[50]={20,20,20};int posy[50]={20,19,18};
short sdir=RIGHT;
int slen=3;
int gridX,gridY;
int food=1;
int x,y;
int score=0;
int i;
int fps=9;
char buf[10]={'0','1','2','3','4','5','6','7','8','9'};
char s[2]={48,48};
void timer_call()
{
glutPostRedisplay();
glutTimerFunc(1000/fps,timer_call,0);
}
void keyboard(int key,int x,int y)
{
switch(key)
{
case GLUT_KEY_UP:if(sdir!=DOWN)
sdir=UP;
break;

case GLUT_KEY_DOWN:if(sdir!=UP)
sdir=DOWN;
break;

case GLUT_KEY_RIGHT:if(sdir!=LEFT)
sdir=RIGHT;
break;

case GLUT_KEY_LEFT:if(sdir!=RIGHT)
sdir=LEFT;
break;

}


}
void reshape(int w,int h)
{
glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,ROWS,0.0,COLUMNS);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}
void initGrid(int rows,int columns)
{
gridX=columns,gridY=rows;
}
void init()
{
glClearColor(0.0,0.0,0.0,0.0);
initGrid(ROWS,COLUMNS);
}
void unit(int x,int y)
{
if(x==0||x==gridX-1||y==0||y==gridY-1)
{
glColor3f(1.0,0.0,0.0);
glLineWidth(3.0);
}
else
{
glColor3f(1.0,1.0,1.0);
glLineWidth(1.0);
}
// glRectf(x,y,x+1,y+1);
glBegin(GL_LINES);
glVertex2d(x,y); glVertex2d(x+1,y);
glVertex2d(x+1,y); glVertex2d(x+1,y+1);
glVertex2d(x+1,y+1);glVertex2d(x,y+1);
glVertex2d(x,y+1); glVertex2d(x,y);
glEnd();
}
void drawGrid()
{
for(int x=0;x<gridX;x++)
{
for(int y=0;y<gridY;y++)
{
if((x==0||y==0)||(x==gridX-1||y==gridY-1))
unit(x,y);
}
}
}
void drawBitmapText(char *string,float x,float y)
{
int i;
glColor3f(1,0,0);
glRasterPos2f(x, y);

int len=(int)strlen(string);
for (i=0;i<len;i++)
{
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
}
}
void output()
{
glClear(GL_COLOR_BUFFER_BIT);
drawBitmapText("!!GAME OVER!!",13,25);
drawBitmapText("SCORE:",15,20);
drawBitmapText(s,21,20);
drawBitmapText("PRESS 'r' TO RESTART",11,15);
drawBitmapText("PRESS 'q' TO QUIT",12,13);
glutSwapBuffers();
}
void snake()
{
glColor3f(1,0,0);
for (int i=slen-1;i>0;i--)
{
posx[i]=posx[i-1];
posy[i]=posy[i-1];
}
if(sdir==UP)
posy[0]++;
else if(sdir==DOWN)
posy[0]--;
else if(sdir==RIGHT)
posx[0]++;
else if(sdir==LEFT)
posx[0]--;
for(int i=0;i<slen;i++)
{
if(i==0)
glColor3f(0,0,1);
else
glColor3f(0,1,0);
glRectd(posx[i],posy[i],posx[i]+1,posy[i]+1);
}
if(posx[0]==0||posx[0]==gridX-1 ||posy[0]==0 || posy[0]==gridY-1)
{
printf("SCORE:%d\n",score);
printf("GAME OVER\n");
glutDisplayFunc(output);
}
for(int i=0;i<slen;i++)
{
if(posx[i+1]==posx[0] && posy[i+1]==posy[0])
{
printf("SCORE:%d\n",score);
printf("GAME OVER\n");
glutDisplayFunc(output);
}
}
if(posx[0]==x && posy[0]==y)
{


food=1;
slen++;
if(slen>max)
slen=max;
s[1]+=1;
if(s[1]==58)
{
s[0]++;
s[1]=48;
}
score+=1;
}
}

void drawfood()
{
int maxx=gridX-2;
int min=1;
int maxy=gridY-2;
if(food)
{
srand(time(NULL));
x=min+rand() % (maxx-min);
y=min+rand() % (maxy-min);
}
food=0;
glRectf(x,y,x+1,y+1);
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT);
snake();
drawGrid();
drawfood();
drawBitmapText("Score:",30,35);
drawBitmapText(s,35,35);
//drawBitmapText("q-Quit",30,32);
glutSwapBuffers();
}
void keyboard1(unsigned char key,int x,int y)
{
if(key=='q')
{
glutDisplayFunc(output);
exit(0);
}
if(key=='r')
{
posx[0]=20;
posy[0]=20;
score=0;
slen=3;
s[0]=48;
s[1]=48;
glutDisplayFunc(display);


glutSwapBuffers();
}
if(key=='i')
{
fps++;
}
if(key=='d')
{
fps--;
}
}
int main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
glutInitWindowSize(600,600);
glutCreateWindow("HUNGRY SNAKE");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutSpecialFunc(keyboard);
glutKeyboardFunc(keyboard1);
glutTimerFunc(0,timer_call,0);
init();
glutMainLoop();
return 0;
}