
#include<windows.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int width=400,height=300;
int score = 0;
char snum[10];
double xball=25,yball=150,vely=0,a=-0.001,r=10,count=0,offset=75,pipespeed=0.1,pipeaccel=0.000001;
double array[] = {100,200,300,400};
double ab[]={50,90,40,100};
bool distance(double a,double b)
{
    double d;
    d=sqrt((a-xball)*(a-xball)+(b-yball)*(b-yball));
    if(d>0.9*r)
        return false;
    else
    return true;
}
void init()
{
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,width,0,height);
}
void drawbar(double x,double y)
{
    glColor3f(0,0,1);

    glBegin(GL_QUADS);
    glVertex2f(x,0);
    glVertex2f(x+20,0);
    glVertex2f(x+20,y);
    glVertex2f(x,y);

    glVertex2f(x,y+offset);
    glVertex2f(x+20,y+offset);
    glVertex2f(x+20,height);
    glVertex2f(x,height);
    glEnd();
}
void printString(char *string, int x, int y)
{
    glColor3f(1,0,1);
    char *c;
    glRasterPos2f(x,y);
    for(c=string;*c!='\0';c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*c);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);


    glBegin(GL_LINES);
    for(double i=0;i<=6.28;i+=0.001)
    {
        glVertex2f(xball,yball);
        glVertex2f(xball+r*cos(i),yball+r*sin(i));
    }
    glEnd();
    for(int i=0;i<4;i++)
        drawbar(array[i],ab[i]);
    itoa(score,snum,10);
    printString(snum,0.5,0.5);
    glFlush();
    yball+=vely;
    vely+=a;
    for(int i=0;i<4;i++)
    {
        array[i]-=pipespeed;
    }
    pipespeed+=pipeaccel;
    if(array[0]<=-20)
    {
        for(int i=1;i<4;i++)
        {
            array[i-1]=array[i];
            ab[i-1]=ab[i];
        }
        array[3]=380;
        ab[3]=rand()%200+30;
        score += 1;
    }
    if(yball<=r)
        count=1;
    else if(array[0]<30 && array[0]>0)
    {
        double t,p;
        t=array[0];
        p=ab[0];
        if(distance(t,p) || distance(t+20,p) || distance(t,p+offset) || distance(t+20,p+offset))
        {
            printf("end");
            count=1;
        }
        else if(yball>p+offset-r || yball<p+r)
            count=1;
    }

    if(count==0)
        glutPostRedisplay();
    else
    {
        glColor3f(1,0,1);
        printString("GAMEOVER",150,150);
        printString("Score : ",155,125);
        printString(snum,225,125);
        glFlush();
    }

}

void SpecialKeyboard(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        //yball+=20;
        vely=0.25;
    }
}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("game");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(SpecialKeyboard);
    glutMainLoop();
    return 0;
}
