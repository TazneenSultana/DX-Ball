#include<bits/stdc++.h>
#include <iostream>
#include <stdlib.h> //Needed for "exit" function
#include<windows.h>
//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<math.h>


using namespace std;

float angle=0.0;
//float paddle_x=0.0;
float ball_x=0.0;
float ball_y=-2.1;
float gap=0.0;
int xl=0.0;
int brick_no;
int broken_bricks=0;
int feature;
int t=0;
int kase=0;
float dx=0.2;
float dy=0.2;
float plx=-0.75;
float prx=0.75;
int speed=0;
int life=3;
int score=0;
bool wlcm=true;
bool c1=true;
bool start=false;
bool pause=false;
bool resume=false;
bool game_over=false;
bool color1=true;
bool color2=false;
bool big_paddle=false;
bool small_paddle=false;
bool high_speed=false;
bool low_speed=false;
bool super_mode=false;
bool double_points=false;


float paddle_left_bottom_x;
float paddle_left_bottom_y=-2.42;
float paddle_left_up_x;
float paddle_left_up_y=-2.22;
float paddle_right_up_x;
float paddle_right_up_y=-2.22;
float paddle_right_bottom_x;
float paddle_right_bottom_y=-2.42;
float extra_paddle_length=0.0;



struct brick{
      float left_bottom_x;
      float left_bottom_y;
      float left_up_x;
      float left_up_y;
      float right_up_x;
      float right_up_y;
      float right_bottom_x;
      float right_bottom_y;
      int broken;
};

brick arr[100];

void initialize()
{
    angle=0.0;
    //paddle_x=0.0;
    ball_x=0.0;
    ball_y=-2.1;
    gap=0.0;
    xl=0.0;
    broken_bricks=0;
    t=0;
    kase=0;
    dx=0.2;
    dy=0.2;
    plx=-0.75;
    prx=0.75;
    speed=0;
    life=3;
    score=0;
    wlcm=true;
    c1=true;
    start=false;
    pause=false;
    resume=false;
    game_over=false;
    color1=true;
    color2=false;
    big_paddle=false;
    small_paddle=false;
    high_speed=false;
    low_speed=false;
    super_mode=false;
    double_points=false;

    paddle_left_bottom_y=-2.42;
    paddle_left_up_y=-2.22;
    paddle_right_bottom_y=-2.42;
    paddle_right_up_y=-2.22;
    extra_paddle_length=0.0;


    //making all bricks unbroken
    for(int i=0;i<100;i++)
    {
        arr[i].broken=0;
    }
}



//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y) {    //The current mouse coordinates
	switch (key) {
		case 27: //Escape key
			exit(0);
            //Exit the program
        case 'p': pause=true;start=false;resume=false;wlcm=false;game_over=false;
                  break;
        case 's': start=true;pause=false;resume=false;wlcm=false;game_over=false;
                  break;
        case 'r': resume=true;pause=false;start=false;wlcm=false;game_over=false;
                  break;
        case 'w': wlcm=true;resume=false;pause=false;start=false;game_over=false; initialize();
                  break;
	}
}



//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);


}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}

void reset_ball_paddle()
{
    if(life==2)
    {
        dx=-0.2;
        dy=0.2;
    }
    else
    {
       dx=0.2;
       dy=0.2;
    }
    ball_x=0.0;
    ball_y=-2.0;
    plx=-0.75;
    prx=0.75;
    if(big_paddle) big_paddle=false;
    else if(small_paddle) small_paddle=false;
    else if(high_speed) {high_speed=false;speed=0;}
    else if(low_speed) {low_speed=false;speed=0;}
    else if(super_mode) super_mode=false;
    else if(double_points) double_points=false;

}

void drawLife()
{
   if(life>0)
   {
    //cout<<"life>0"<<endl;
     glPushMatrix();
        glTranslated(-5.4,-3.2,-8.0);
        glColor3f(0.0,1.0,0.0);
        glutSolidSphere(0.08,20,20);
    glPopMatrix();
   }

   if(life>1)
   {
       //cout<<"life>1"<<endl;
      glPushMatrix();
        glTranslated(-5.2,-3.2,-8.0);
        glColor3f(0.0,1.0,0.0);
        glutSolidSphere(0.08,20,20);
      glPopMatrix();
   }
   if(life>2)
   {
       //cout<<"life>2"<<endl;
     glPushMatrix();
        glTranslated(-5.0,-3.2,-8.0);
        glColor3f(0.0,1.0,0.0);
        glutSolidSphere(0.08,20,20);
    glPopMatrix();
   }
    if(arr[65].broken==1 && life!=0)
   {
    //cout<<"life>0"<<endl;
     glPushMatrix();
        glTranslated(-5.4,-3.2,-8.0);
        glColor3f(0.0,1.0,0.0);
        glutSolidSphere(0.08,20,20);
    glPopMatrix();
   }
}

void welcome()
{
   //for D
   glBegin(GL_QUADS);
   glColor3f(0.0,0.0,0.3);//black
   //glColor3f(0.0,0.0,0.0);
   glVertex3f(-1.8,0.8,-8.0);
   glVertex3f(-1.2,0.8,-8.0);
   glVertex3f(-1.2,0.6,-8.0);
   glVertex3f(-1.8,0.6,-8.0);
   glVertex3f(-1.2,0.6,-8.0);
   glVertex3f(-1.2,0.0,-8.0);
   glVertex3f(-1.4,-0.0,-8.0);
   glVertex3f(-1.4,0.6,-8.0);
   glVertex3f(-1.5,0.6,-8.0);
   glVertex3f(-1.5,0.0,-8.0);
   glVertex3f(-1.7,0.0,-8.0);
   glVertex3f(-1.7,0.6,-8.0);
   glVertex3f(-1.8,0.0,-8.0);
   glVertex3f(-1.8,-0.2,-8.0);
   glVertex3f(-1.2,-0.2,-8.0);
   glVertex3f(-1.2,0.0,-8.0);
   glEnd();


   //for X
   glBegin(GL_QUADS);
   glColor3f(0.0,0.0,0.4);
   //glColor3f(0.1,0.1,0.1);
   glVertex3f(-1.1,0.8,-8.0);
   glVertex3f(-0.9,0.8,-8.0);
   glVertex3f(-0.5,-0.2,-8.0);
   glVertex3f(-0.7,-0.2,-8.0);
   glVertex3f(-0.9,-0.2,-8.0);
   glVertex3f(-1.1,-0.2,-8.0);
   glVertex3f(-0.7,0.8,-8.0);
   glVertex3f(-0.5,0.8,-8.0);
   glEnd();

   //for B
   glBegin(GL_QUADS);
   glColor3f(0.3,0.3,0.8);
   //glColor3f(0.3,0.3,0.3);
   glVertex3f(-0.2,0.8,-8.0);
   glVertex3f(0.4,0.8,-8.0);
   glVertex3f(0.4,0.6,-8.0);
   glVertex3f(-0.2,0.6,-8.0);
   glVertex3f(0.4,0.6,-8.0);
   glVertex3f(0.4,0.0,-8.0);
   glVertex3f(0.2,0.0,-8.0);
   glVertex3f(0.2,0.6,-8.0);
   glVertex3f(0.0,0.6,-8.0);
   glVertex3f(0.0,0.0,-8.0);
   glVertex3f(-0.1,0.0,-8.0);
   glVertex3f(-0.1,0.6,-8.0);
   glVertex3f(-0.2,0.0,-8.0);
   glVertex3f(0.4,0.0,-8.0);
   glVertex3f(0.4,-0.2,-8.0);
   glVertex3f(-0.2,-0.2,-8.0);
   glVertex3f(0.0,0.35,-8.0);
   glVertex3f(0.4,0.35,-8.0);
   glVertex3f(0.4,0.25,-8.0);
   glVertex3f(0.0,0.25,-8.0);
   glEnd();

   //for A
   glBegin(GL_QUADS);
   glColor3f(0.0,0.0,0.6);
   //glColor3f(0.4,0.4,0.4);
   glVertex3f(0.5,0.8,-8.0);
   glVertex3f(1.1,0.8,-8.0);
   glVertex3f(1.1,0.6,-8.0);
   glVertex3f(0.5,0.6,-8.0);
   glVertex3f(0.9,0.6,-8.0);
   glVertex3f(1.1,0.6,-8.0);
   glVertex3f(1.1,-0.2,-8.0);
   glVertex3f(0.9,-0.2,-8.0);
   glVertex3f(0.9,0.6,-8.0);
   glVertex3f(0.7,0.6,-8.0);
   glVertex3f(0.7,-0.2,-8.0);
   glVertex3f(0.5,-0.2,-8.0);
   glVertex3f(0.5,0.6,-8.0);
   glVertex3f(0.7,0.35,-8.0);
   glVertex3f(0.9,0.35,-8.0);
   glVertex3f(0.9,0.25,-8.0);
   glVertex3f(0.7,0.25,-8.0);
   glEnd();

   //for 1st L
   glBegin(GL_QUADS);
   glColor3f(0.0,0.0,0.5);
   //glColor3f(0.1,0.1,0.1);
   glVertex3f(1.2,0.8,-8.0);
   glVertex3f(1.4,0.8,-8.0);
   glVertex3f(1.4,-0.2,-8.0);
   glVertex3f(1.2,-0.2,-8.0);
   glVertex3f(1.4,-0.2,-8.0);
   glVertex3f(1.4,0.0,-8.0);
   glVertex3f(1.8,0.0,-8.0);
   glVertex3f(1.8,-0.2,-8.0);
   glEnd();

   //for 2nd L
   glBegin(GL_QUADS);
   glColor3f(0.0,0.0,0.3);
   //glColor3f(0.0,0.0,0.0);
   glVertex3f(1.9,0.8,-8.0);
   glVertex3f(2.1,0.8,-8.0);
   glVertex3f(2.1,-0.2,-8.0);
   glVertex3f(1.9,-0.2,-8.0);
   glVertex3f(2.1,-0.2,-8.0);
   glVertex3f(2.1,0.0,-8.0);
   glVertex3f(2.5,0.0,-8.0);
   glVertex3f(2.5,-0.2,-8.0);
   glEnd();

   //for p
   glLineWidth(3);
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(-1.1,-1.9,-8.0);
   glVertex3f(-0.9,-1.9,-8.0);
   glVertex3f(-0.9,-1.9,-8.0);
   glVertex3f(-0.9,-2.0,-8.0);
   glVertex3f(-0.9,-2.0,-8.0);
   glVertex3f(-1.1,-2.0,-8.0);
   glVertex3f(-1.1,-2.0,-8.0);
   glVertex3f(-1.1,-2.2,-8.0);
   glVertex3f(-1.1,-1.9,-8.0);
   glVertex3f(-1.1,-2.0,-8.0);
   glEnd();

   //for r
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(-0.8,-2.0,-8.0);
   glVertex3f(-0.6,-2.0,-8.0);
   glVertex3f(-0.8,-2.0,-8.0);
   glVertex3f(-0.8,-2.2,-8.0);
   glEnd();

   //for e
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(-0.5,-2.0,-8.0);
   glVertex3f(-0.5,-2.2,-8.0);
   glVertex3f(-0.5,-2.0,-8.0);
   glVertex3f(-0.3,-2.0,-8.0);
   glVertex3f(-0.3,-2.0,-8.0);
   glVertex3f(-0.3,-2.1,-8.0);
   glVertex3f(-0.3,-2.1,-8.0);
   glVertex3f(-0.5,-2.1,-8.0);
   glVertex3f(-0.5,-2.2,-8.0);
   glVertex3f(-0.3,-2.2,-8.0);
   glEnd();

   //for 1st s
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(-0.2,-2.0,-8.0);
   glVertex3f(0.0,-2.0,-8.0);
   glVertex3f(-0.2,-2.0,-8.0);
   glVertex3f(-0.2,-2.1,-8.0);
   glVertex3f(-0.2,-2.1,-8.0);
   glVertex3f(0.0,-2.1,-8.0);
   glVertex3f(0.0,-2.1,-8.0);
   glVertex3f(0.0,-2.2,-8.0);
   glVertex3f(0.0,-2.2,-8.0);
   glVertex3f(-0.2,-2.2,-8.0);
   glEnd();


   //for 2nd s
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(0.1,-2.0,-8.0);
   glVertex3f(0.3,-2.0,-8.0);
   glVertex3f(0.1,-2.0,-8.0);
   glVertex3f(0.1,-2.1,-8.0);
   glVertex3f(0.1,-2.1,-8.0);
   glVertex3f(0.3,-2.1,-8.0);
   glVertex3f(0.3,-2.1,-8.0);
   glVertex3f(0.3,-2.2,-8.0);
   glVertex3f(0.3,-2.2,-8.0);
   glVertex3f(0.1,-2.2,-8.0);
   glEnd();

   //for 3rd s
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(0.7,-2.0,-8.0);
   glVertex3f(0.9,-2.0,-8.0);
   glVertex3f(0.7,-2.0,-8.0);
   glVertex3f(0.7,-2.1,-8.0);
   glVertex3f(0.7,-2.1,-8.0);
   glVertex3f(0.9,-2.1,-8.0);
   glVertex3f(0.9,-2.1,-8.0);
   glVertex3f(0.9,-2.2,-8.0);
   glVertex3f(0.9,-2.2,-8.0);
   glVertex3f(0.7,-2.2,-8.0);
   glEnd();

  //background border of press s
  glLineWidth(2);
   glBegin(GL_LINES);
   //cout<<"t: "<<t<<c1<<endl;
   if(c1 && t<10)
   {
      t++;
     // cout<<"executing"<<t<<endl;
     if(t==10)
     {
         c1=false;
         t=0;
     }
   }
   else
   {
     glColor3f(0.0,0.0,0.0);
     glVertex3f(-1.4,-1.8,-8.0);
     glVertex3f(-1.4,-2.4,-8.0);
     glVertex3f(-1.4,-2.4,-8.0);
     glVertex3f(1.2,-2.4,-8.0);
     glVertex3f(1.2,-2.4,-8.0);
     glVertex3f(1.2,-1.8,-8.0);
     glVertex3f(1.2,-1.8,-8.0);
     glVertex3f(-1.4,-1.8,-8.0);
     t++;
     if(t==10)
     {
         c1=true;
         t=0;
     }
   }
   glEnd();

   //background of press s
   glBegin(GL_QUADS);
   glColor3f(0.5,0.5,0.5);
   glVertex3f(-1.4,-1.8,-8.0);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(-1.4,-2.4,-8.0);
   glColor3f(0.6,0.6,0.6);
   glVertex3f(1.2,-2.4,-8.0);
   glColor3f(1.2,1.0,1.0);
   glVertex3f(1.2,-1.8,-8.0);
   glEnd();


   //for background
   glBegin(GL_QUADS);
   glColor3f(0.0,0.0,0.4);
   glVertex3f(-5.5,-3.3,-8.0);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(-5.5,3.3,-8.0);
   glColor3f(0.0,0.0,0.4);
   glVertex3f(5.5,3.3,-8.0);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(5.5,-3.3,-8.0);
   glEnd();
}

/*void drawText(const char *text,int length,int x,int y)
{
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[10];
    glGetDoublev(GL_PROJECTION_MATRIX,matrix);
    glLoadIdentity();
    glOrtho(0,800,0,600,-5,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);
    for(int i=0;i<length;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}
*/

void showScore()
{
    int digit1=score%10;
    int digit2=score/10;
    float dis=0.6;

    //for :
    glPushMatrix();
      glTranslated(-0.1,-0.3,-8.0);
      glColor3f(0.0,0.0,0.0);
      glutSolidSphere(0.05,20,20);
    glPopMatrix();

    glPushMatrix();
      glTranslated(-0.1,-0.45,-8.0);
      glColor3f(0.0,0.0,0.0);
      glutSolidSphere(0.05,20,20);
    glPopMatrix();

    //for e
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(-0.3,-0.25,-8.0);
    glVertex3f(-0.5,-0.25,-8.0);
    glVertex3f(-0.5,-0.25,-8.0);
    glVertex3f(-0.5,-0.5,-8.0);
    glVertex3f(-0.5,-0.5,-8.0);
    glVertex3f(-0.3,-0.5,-8.0);
    glVertex3f(-0.3,-0.375,-8.0);
    glVertex3f(-0.3,-0.25,-8.0);
    glVertex3f(-0.3,-0.375,-8.0);
    glVertex3f(-0.5,-0.375,-8.0);
    glEnd();

    //for r
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(-0.6,-0.25,-8.0);
    glVertex3f(-0.8,-0.25,-8.0);
    glVertex3f(-0.8,-0.25,-8.0);
    glVertex3f(-0.8,-0.5,-8.0);
    glEnd();

    //for o
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(-0.9,-0.25,-8.0);
    glVertex3f(-1.1,-0.25,-8.0);
    glVertex3f(-1.1,-0.25,-8.0);
    glVertex3f(-1.1,-0.5,-8.0);
    glVertex3f(-1.1,-0.5,-8.0);
    glVertex3f(-0.9,-0.5,-8.0);
    glVertex3f(-0.9,-0.5,-8.0);
    glVertex3f(-0.9,-0.25,-8.0);
    glEnd();

    //for c
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(-1.2,-0.25,-8.0);
    glVertex3f(-1.4,-0.25,-8.0);
    glVertex3f(-1.4,-0.25,-8.0);
    glVertex3f(-1.4,-0.5,-8.0);
    glVertex3f(-1.4,-0.5,-8.0);
    glVertex3f(-1.2,-0.5,-8.0);
    glEnd();

    //for S
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(-1.5,0.0,-8.0);
    glVertex3f(-1.7,0.0,-8.0);
    glVertex3f(-1.7,0.0,-8.0);
    glVertex3f(-1.7,-0.25,-8.0);
    glVertex3f(-1.7,-0.25,-8.0);
    glVertex3f(-1.5,-0.25,-8.0);
    glVertex3f(-1.5,-0.25,-8.0);
    glVertex3f(-1.5,-0.5,-8.0);
    glVertex3f(-1.5,-0.5,-8.0);
    glVertex3f(-1.7,-0.5,-8.0);
    glEnd();




    switch(digit2)
    {
       case 0: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.3,0.0,-8.0);
               glEnd();
               break;
       case 1: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glEnd();
               break;
       case 2: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glEnd();
               break;
       case 3: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glEnd();
               break;
       case 4: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glEnd();
               break;
      case 5:  glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glEnd();
               break;
      case 6:  glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glEnd();
               break;
     case 7:   glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glEnd();
               break;
     case 8:   glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glEnd();
               break;
     case 9:   glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,0.0,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.6,-0.6,-8.0);
               glVertex3f(0.3,-0.6,-8.0);
               glVertex3f(0.6,-0.3,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.3,-0.3,-8.0);
               glVertex3f(0.3,0.0,-8.0);
               glEnd();
               break;

    }

    switch(digit1)
    {
       case 0: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glEnd();
               break;
       case 1: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glEnd();
               break;
       case 2: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glEnd();
               break;
       case 3: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glEnd();
               break;
       case 4: glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glEnd();
               break;
      case 5:  glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glEnd();
               break;
      case 6:  glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glEnd();
               break;
     case 7:   glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glEnd();
               break;
     case 8:   glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glEnd();
               break;
     case 9:   glLineWidth(5);
               glBegin(GL_LINES);
               glColor3f(0.0,0.0,1.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,0.0,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.6,-8.0);
               glVertex3f(0.3+dis,-0.6,-8.0);
               glVertex3f(0.6+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,-0.3,-8.0);
               glVertex3f(0.3+dis,0.0,-8.0);
               glEnd();
               break;
    }

    //for p
   glLineWidth(3);
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(-1.1,-1.9,-8.0);
   glVertex3f(-0.9,-1.9,-8.0);
   glVertex3f(-0.9,-1.9,-8.0);
   glVertex3f(-0.9,-2.0,-8.0);
   glVertex3f(-0.9,-2.0,-8.0);
   glVertex3f(-1.1,-2.0,-8.0);
   glVertex3f(-1.1,-2.0,-8.0);
   glVertex3f(-1.1,-2.2,-8.0);
   glVertex3f(-1.1,-1.9,-8.0);
   glVertex3f(-1.1,-2.0,-8.0);
   glEnd();

   //for r
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(-0.8,-2.0,-8.0);
   glVertex3f(-0.6,-2.0,-8.0);
   glVertex3f(-0.8,-2.0,-8.0);
   glVertex3f(-0.8,-2.2,-8.0);
   glEnd();

   //for e
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(-0.5,-2.0,-8.0);
   glVertex3f(-0.5,-2.2,-8.0);
   glVertex3f(-0.5,-2.0,-8.0);
   glVertex3f(-0.3,-2.0,-8.0);
   glVertex3f(-0.3,-2.0,-8.0);
   glVertex3f(-0.3,-2.1,-8.0);
   glVertex3f(-0.3,-2.1,-8.0);
   glVertex3f(-0.5,-2.1,-8.0);
   glVertex3f(-0.5,-2.2,-8.0);
   glVertex3f(-0.3,-2.2,-8.0);
   glEnd();

   //for 1st s
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(0.0,-2.0,-8.0);
   glVertex3f(-0.2,-2.0,-8.0);
   glVertex3f(-0.2,-2.0,-8.0);
   glVertex3f(-0.2,-2.1,-8.0);
   glVertex3f(-0.2,-2.1,-8.0);
   glVertex3f(0.0,-2.1,-8.0);
   glVertex3f(0.0,-2.1,-8.0);
   glVertex3f(0.0,-2.2,-8.0);
   glVertex3f(0.0,-2.2,-8.0);
   glVertex3f(-0.2,-2.2,-8.0);
   glEnd();


   //for 2nd s
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(0.1,-2.0,-8.0);
   glVertex3f(0.3,-2.0,-8.0);
   glVertex3f(0.1,-2.0,-8.0);
   glVertex3f(0.1,-2.1,-8.0);
   glVertex3f(0.1,-2.1,-8.0);
   glVertex3f(0.3,-2.1,-8.0);
   glVertex3f(0.3,-2.1,-8.0);
   glVertex3f(0.3,-2.2,-8.0);
   glVertex3f(0.3,-2.2,-8.0);
   glVertex3f(0.1,-2.2,-8.0);
   glEnd();

   //for 3rd w
   glBegin(GL_LINES);
   glColor3f(0.0,0.0,0.0);
   glVertex3f(0.9,-2.0,-8.0);
   glVertex3f(0.9,-2.2,-8.0);
   glVertex3f(0.9,-2.2,-8.0);
   glVertex3f(0.8,-2.1,-8.0);
   glVertex3f(0.8,-2.1,-8.0);
   glVertex3f(0.7,-2.2,-8.0);
   glVertex3f(0.7,-2.2,-8.0);
   glVertex3f(0.7,-2.0,-8.0);
   glEnd();


    //background border of press w
   glLineWidth(2);
   glBegin(GL_LINES);
  // cout<<"t: "<<t<<endl;
   if(c1 && t<10)
   {
     t++;
     if(t==10)
     {
         c1=false;
         t=0;
     }
   }
   else
   {
     glColor3f(0.0,0.0,0.0);
     glVertex3f(-1.4,-1.8,-8.0);
     glVertex3f(-1.4,-2.4,-8.0);
     glVertex3f(-1.4,-2.4,-8.0);
     glVertex3f(1.2,-2.4,-8.0);
     glVertex3f(1.2,-2.4,-8.0);
     glVertex3f(1.2,-1.8,-8.0);
     glVertex3f(1.2,-1.8,-8.0);
     glVertex3f(-1.4,-1.8,-8.0);
     t++;
     if(t==10)
     {
         c1=true;
         t=0;
     }
   }
   glEnd();

   //background of press w
   glBegin(GL_QUADS);
   glColor3f(0.5,0.5,0.5);
   glVertex3f(-1.4,-1.8,-8.0);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(-1.4,-2.4,-8.0);
   glColor3f(0.6,0.6,0.6);
   glVertex3f(1.2,-2.4,-8.0);
   glColor3f(1.2,1.0,1.0);
   glVertex3f(1.2,-1.8,-8.0);
   glEnd();

}

void won()
{
   showScore();

   //for W
   glLineWidth(5);
   glBegin(GL_LINES);
   glColor3f(1.0,0.2,0.0);
   glVertex3f(-1.0+0.5,1.5,-8.0);
   glVertex3f(-1.0+0.5,1.0,-8.0);
   glVertex3f(-1.0+0.5,1.0,-8.0);
   glVertex3f(-1.25+0.5,1.25,-8.0);
   glVertex3f(-1.25+0.5,1.25,-8.0);
   glVertex3f(-1.5+0.5,1.0,-8.0);
   glVertex3f(-1.5+0.5,1.0,-8.0);
   glVertex3f(-1.5+0.5,1.5,-8.0);
   glEnd();

   //for O
   glBegin(GL_LINES);
   glColor3f(1.0,0.5,0.0);
   glVertex3f(-0.9+0.5,1.5,-8.0);
   glVertex3f(-0.9+0.5,1.0,-8.0);
   glVertex3f(-0.9+0.5,1.0,-8.0);
   glVertex3f(-0.4+0.5,1.0,-8.0);
   glVertex3f(-0.4+0.5,1.0,-8.0);
   glVertex3f(-0.4+0.5,1.5,-8.0);
   glVertex3f(-0.4+0.5,1.5,-8.0);
   glVertex3f(-0.9+0.5,1.5,-8.0);
   glEnd();

   //for N
   glBegin(GL_LINES);
   glColor3f(1.0,1.0,0.0);
   glVertex3f(-0.3+0.5,1.5,-8.0);
   glVertex3f(-0.3+0.5,1.0,-8.0);
   glVertex3f(-0.3+0.5,1.5,-8.0);
   glVertex3f(0.2+0.5,1.0,-8.0);
   glVertex3f(0.2+0.5,1.0,-8.0);
   glVertex3f(0.2+0.5,1.5,-8.0);
   glEnd();


   glBegin(GL_QUADS);
   glColor3f(0.4,0.9,0.4);
   glVertex3f(-5.5,-3.3,-8.0);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(-5.5,3.3,-8.0);
   glColor3f(0.4,0.9,0.4);
   glVertex3f(5.5,3.3,-8.0);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(5.5,-3.3,-8.0);
   glEnd();
}


void gameOver()
{
    //cout<<"score : "<<score<<"broken_bricks : "<<broken_bricks<<endl;

   showScore();
   glBegin(GL_QUADS);
   glColor3f(0.0,0.0,0.4);
   glVertex3f(-5.5,-3.3,-8.0);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(-5.5,3.3,-8.0);
   glColor3f(0.0,0.0,0.4);
   glVertex3f(5.5,3.3,-8.0);
   glColor3f(1.0,1.0,1.0);
   glVertex3f(5.5,-3.3,-8.0);
   glEnd();

  // std::string text="120";
  // drawText(text.data(),text.size(),50,200);

   //SDL_GL_SwapBuffers();

}

void drawFeatureIcon()
{
    if(big_paddle==true)
    {
        //cout<<"big_paddle"<<endl;
        glBegin(GL_QUADS);
        glColor3f(0.7,0.7,0.7);
        glVertex3f(5.1,-3.25,-8.0);
        glVertex3f(5.1,-3.2,-8.0);
        glVertex3f(5.3,-3.2,-8.0);
        glVertex3f(5.3,-3.25,-8.0);
        glEnd();

    }
    else if(small_paddle==true)
    {
        //cout<<"smallpaddle"<<endl;
        glBegin(GL_QUADS);
        glColor3f(0.7,0.7,0.7);
        glVertex3f(5.2,-3.25,-8.0);
        glVertex3f(5.2,-3.2,-8.0);
        glVertex3f(5.3,-3.2,-8.0);
        glVertex3f(5.3,-3.25,-8.0);
        glEnd();
    }
    else if(high_speed==true)
    {
        //cout<<"highSpeed"<<endl;
       glPushMatrix();
          glTranslated(5.2,-3.2,-8.0);
          glRotatef(90.0,0.0,1.0,0.0);
          glColor3f(0.0,0.0,1.0);
          glutSolidSphere(0.08,20,20);
        glPopMatrix();
    }
    else if(low_speed==true)
    {
        //cout<<"lowSpeed"<<endl;
       glPushMatrix();
          glTranslated(5.2,-3.2,-8.0);
          glColor3f(0.0,0.0,1.0);
          glutSolidSphere(0.06,20,20);
        glPopMatrix();
    }
    else if(super_mode==true)
    {
        //cout<<"superMode"<<endl;
        glPushMatrix();
          glTranslated(5.2,-3.2,-8.0);
          glColor3f(1.0,0.5,0.0);
          glutSolidSphere(0.1,20,20);
        glPopMatrix();
    }
    else if(double_points==true)
    {
       //cout<<"doublePoints"<<endl;
       glBegin(GL_LINES);
       glColor3f(1.0,0.5,0.0);
       glVertex3f(5.05,-3.1,-8.0);
       glVertex3f(5.15,-3.3,-8.0);
       glVertex3f(5.15,-3.1,-8.0);
       glVertex3f(5.05,-3.3,-8.0);
       glVertex3f(5.2,-3.1,-8.0);
       glVertex3f(5.3,-3.1,-8.0);
       glVertex3f(5.3,-3.1,-8.0);
       glVertex3f(5.3,-3.2,-8.0);
       glVertex3f(5.3,-3.2,-8.0);
       glVertex3f(5.2,-3.2,-8.0);
       glVertex3f(5.2,-3.2,-8.0);
       glVertex3f(5.2,-3.3,-8.0);
       glVertex3f(5.2,-3.3,-8.0);
       glVertex3f(5.3,-3.3,-8.0);
       glEnd();
    }
}

void drawBall()
{
   glPushMatrix();
        glTranslated(ball_x,ball_y,-8.0);
        if(super_mode==true)
        {
            if(color1)
            {
              glColor3f(1.0,0.5,0.0);
              color2=true;
              color1=false;
            }
            else if(color2)
            {
               glColor3f(1.0,1.0,0.0);
               color1=true;
               color2=false;
            }
        }
        else
        {
           glColor3f(0.0,0.0,1.0);
        }
        glutSolidSphere(0.1,20,20);
    glPopMatrix();
}

void drawPaddle()
{
    //xl=4.0;
    if(big_paddle)
    {
        extra_paddle_length=0.5;
    }
    else if(small_paddle)
    {
        extra_paddle_length=-0.2;
    }
    else
    {
        extra_paddle_length=0.0;
    }

    paddle_left_bottom_x=plx-extra_paddle_length;
    paddle_left_up_x=plx-extra_paddle_length;
    paddle_right_up_x=prx+extra_paddle_length;
    paddle_right_bottom_x=prx+extra_paddle_length;

     glBegin(GL_QUADS);
     glColor3f(0.3,0.3,0.3);
     glVertex3f(paddle_left_bottom_x,paddle_left_bottom_y,-8.0);
     glColor3f(0.9,0.9,0.9);
     glVertex3f(paddle_left_up_x,paddle_left_up_y,-8.0);
     glColor3f(0.3,0.3,0.3);
     glVertex3f(paddle_right_up_x,paddle_right_up_y,-8.0);
     glColor3f(0.9,0.9,0.9);
     glVertex3f(paddle_right_bottom_x,paddle_right_bottom_y,-8.0);
     glEnd();
}

void drawBricks()
{
    brick_no=0;
     for(int j=0;j<6;j++)
    {

        for(int i=0;i<11;i++)
        {
          glBegin(GL_QUADS);
          if(j%2==0 && i%2==0)
          {
             glColor3f(0.7,0.0,0.0);
          }
          else if(j%2!=0 && i%2==0)
          {
              glColor3f(0.9,0.8,0.0);
          }
          else if(j%2==0 && i%2!=0)
          {
             glColor3f(0.9,0.8,0.0);
          }
          else if(j%2!=0 && i%2!=0)
          {
             glColor3f(0.7,0.0,0.0);
          }

          if(i>=1 && j>=1 ) gap=0.02;

          arr[brick_no].left_bottom_x=-5.5+i+gap;
          arr[brick_no].left_bottom_y=3.0-(0.3*j)-(gap*j);
          arr[brick_no].left_up_x=-5.5+i+gap;
          arr[brick_no].left_up_y=3.3-(0.3*j)-(gap*j);
          arr[brick_no].right_up_x=-4.5+i;
          arr[brick_no].right_up_y=3.3-(0.3*j)-(gap*j);
          arr[brick_no].right_bottom_x=-4.5+i;
          arr[brick_no].right_bottom_y=3.0-(0.3*j)-(gap*j);



          if((ball_x>=arr[brick_no].left_bottom_x && ball_x<=arr[brick_no].right_bottom_x) && (ball_y>=arr[brick_no].left_bottom_y && ball_y<=arr[brick_no].left_up_y))
          {

              if(arr[brick_no].broken==0)
              {
                arr[brick_no].broken=1;
                broken_bricks++;

                if(double_points) score+=2;
                else score+=1;


                //FEATURE SELECTION IN STATIC WAY *****************************************
                switch(broken_bricks)
                {
                    case 10: high_speed=true; break;
                    case 20: big_paddle=true;break;
                    case 30: super_mode=true; break;
                    case 45: low_speed=true; break;
                    case 55: small_paddle=true; break;
                    case 60: double_points=true; break;

                }

                switch(broken_bricks)
                {
                    case 15:high_speed=false; break;
                    case 25:big_paddle=false; break;
                    case 40: super_mode=false;break;
                    case 50: low_speed=false; break;
                    case 59: small_paddle=false;break;
                    case 65: double_points=false;break;
                }

              //CODE TO ACTIVATE FEATURES BASED ON RANDOM NUMBERS *************************************
              /*  if(broken_bricks==3 || broken_bricks==10 || broken_bricks==18 || broken_bricks==26 || broken_bricks==48)
                {
                    feature=rand()%5+1;
                    cout<<"feature: "<<feature<<endl;
                    switch(feature)
                    {
                        case 1: big_paddle=true;
                                break;
                        case 2: small_paddle=true;
                                break;
                        case 3: high_speed=true;
                                break;
                        case 4: low_speed=true;
                                break;
                        case 5: double_points=true;
                                break;
                    }
                }
                else if(broken_bricks==8 || broken_bricks==15 || broken_bricks==23 || broken_bricks==31 || broken_bricks==53)
                {
                    if(big_paddle) big_paddle=false;
                    else if(small_paddle) small_paddle=false;
                    else if(high_speed) {high_speed=false;speed=0;}
                    else if(low_speed) {low_speed=false;speed=0;}
                    else if(super_mode) super_mode=false;
                    else if(double_points) double_points=false;
                }


                if(broken_bricks>33 && broken_bricks<45)
                {
                    super_mode=true;

                }*/
                if(super_mode) {}//if features are selected based on random numbers, this line should be omitted.
                else
                {
                   dy=-dy;
                   ball_y+=dy;
                   //kase=2;
                }



              }
          }

          //decrease life and reset
          if(ball_y<-2.9)
          {
              if(life>0) life--;
              //cout<<"life : "<<life<<endl;
              if(life>0)
              {
                 Sleep(2000);
                 reset_ball_paddle();
              }
              else
              {

                  game_over=true;
              }

          }
         // cout<<"ball_x"<<ball_x<<endl;
          if(ball_x>= 5.48 || ball_x<= -5.48)
          {
              dx=-dx;
              ball_x+=dx;
              //kase=1;
              //cout<<"touched left/right wall"<<dx<<endl;
          }


        /*  if(ball_x<= -5.5)
          {
              cout<<"touched left wall"<<endl;
              dx = -dx;

          }*/

          if(ball_y>=3.3)
          {
             //cout<<"touched upper wall"<<endl;
             dy=-dy;
             ball_y+=dy;
             //kase=2;
          }

          if(((ball_x)>=paddle_left_up_x && (ball_x)<=paddle_right_up_x) && ((ball_y)<=paddle_left_up_y && (ball_y)>=paddle_left_bottom_y))
          {
              //cout<<"touched paddle"<<endl;
              dy=-dy;
              ball_y+=dy;
              //kase=2;
          }

         // arr[65].broken=1;
         // arr[32].broken=1;
         //cout<<"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"<<arr[55].left_bottom_x<<endl;
          if(arr[brick_no].broken==0)
          {
            //cout<<"brick drawn"<<endl;
            glVertex3f(arr[brick_no].left_bottom_x,arr[brick_no].left_bottom_y,-8.0);
            glVertex3f(arr[brick_no].left_up_x,arr[brick_no].left_up_y,-8.0);
            glVertex3f(arr[brick_no].right_up_x,arr[brick_no].right_up_y,-8.0);
            glVertex3f( arr[brick_no].right_bottom_x,arr[brick_no].right_bottom_y,-8.0);
            glEnd();
          }
           //if(brick_no==65) cout<<arr[brick_no].broken<<" ";
          //cout<<arr[10].right_up_x<<" "<<arr[10].right_up_y<<" ";
          brick_no++;

        }
    }

    }


//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
    //cout<<"start"<<start<<" game_over"<<game_over<<" wlcm"<<wlcm<<endl;
	if(broken_bricks==66 && wlcm==false)
    {
        won();
        start=pause=resume=game_over=false;
    }
    else if(game_over==true && wlcm==false)
    {
        gameOver();
    }
    else if(start|| pause||resume)
    {
       drawBall();
       drawPaddle();
       drawBricks();
       drawLife();
       drawFeatureIcon();

    }
    else if(wlcm)
    {
        welcome();
    }

	glutSwapBuffers(); //Send the 3D scene to the screen
}

void update(int value)
{
    //if(ball_y<=1.0)
    //{
  if(high_speed) speed=-40;
  else if(low_speed) speed=40;
  else speed=0;

  if(start==true || resume==true)
  {
      //if(kase==1) dx=-dx;
     // else if(kase==2) dy=-dy;
     ball_x+=dx;
     ball_y+=dy;
     //cout<<"updated"<<dx<<endl;

  }
    //}
    glutPostRedisplay();
    glutTimerFunc(100+speed,update,0);


}

void SpecialInput(int key, int x, int y)
{

    switch(key)
    {
    case GLUT_KEY_LEFT:
        if(plx-extra_paddle_length-0.3>=-5.7 && !pause)
        {
           plx-=0.3;
           prx-=0.3;
           //cout<<"padLx"<<paddle_left_bottom_x<<endl;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(prx+extra_paddle_length+0.3<=5.7 && !pause)
        {
           plx+=0.3;
           prx+=0.3;
           //cout<<"padRxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<paddle_right_bottom_x<<endl;
        }
        break;
    }
}

int main(int argc, char** argv) {

	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 600); //Set the window size

	//Create the window
	glutCreateWindow("Basic Shapes");
	initRendering(); //Initialize rendering

	//Set handler functions for drawing, keypresses, and window resizes

       glutDisplayFunc(drawScene);
	   glutKeyboardFunc(handleKeypress);
	   glutReshapeFunc(handleResize);
       glutSpecialFunc(SpecialInput);//for using left arrow key and right arrow key

       glutTimerFunc(100,update,0);


	  glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	  return 0; //This line is never reached
}









