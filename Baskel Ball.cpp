#define GL_SILENCE_DEPRECATION
#include <Windows.h>
#include <Mmsystem.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/glu.h>
#include <iostream>

void init()
{
    glClearColor(1,1,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);
}

void ball()
{
    glColor3f(1, 0, 0);
    glutWireSphere(0.2, 20, 20);
}
void basket()
{
    glColor3f(0, 1, 0);
    glutWireCone(0.4, 0.5, 20, 20);
}
void poll()
{
    glColor3f(0, 1, 1);
    glutSolidCube(0.5);
}
float ballX=0,ballY=1.8,basketX=0,basketY=-1.5,pollX=0.9,pollY=1.8;
int rand(),r;
float ballSpeed=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    printf("ballX=%f\n",ballX);
    printf("ballY=%f\n",ballY);
    printf("basketX=%f\n",basketX);
    printf("basketY=%f\n",basketY);

    ballY-=0.01;

    if(ballY<-2)
    {
        ballY=1.5;
        r=rand()%4;
        if(r==0)
        {
            ballX=-1.8;
            pollX=-1.8+0.9;
        }
        if(r==1)
        {
            ballX=-1;
            pollX=-1+0.9;
        }
        if(r==2)
        {
            ballX=1;
            pollX=1+0.9;
        }
        if(r==3)
        {
            ballX=1.8;
            pollX=1.8+0.9;
        }
    }

    glPushMatrix();
    glTranslatef(ballX, ballY, 0);
    ball();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(basketX, basketY, 0);
    glRotatef(90, 1, 0, 0);
    basket();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pollX, pollY, 0);
    glScalef(1.5, 0.4, 1);
    poll();
    glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

void skeys(int key,int x,int y)
{
    if(key==GLUT_KEY_LEFT)
        basketX-=0.3;
    if(key==GLUT_KEY_RIGHT)
        basketX+=0.3;
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Game");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(skeys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
