#include<iostream>
#include<math.h>
#include<GLUT/glut.h>
#include "FPP.hpp"
#include "OBJ.hpp"
#include "Element.hpp"
#include "Texture.hpp"

#define PI 3.1415926
#define BUFFERSIZE 10000

char Path[] = "/Users/drinkingcoder/Documents/university/专题研讨/OpenGLInteraction/";

enum {
    COW,
    ISIS,
    ElementNum
};

enum {
    VIEW,
    SELECT
} Mode = VIEW;

GLfloat eye[] = {0,0,0};
GLfloat Direction[] = {0,-1,0};
GLfloat UpDirection[] = {0,0,1};
GLuint selectBuffer[BUFFERSIZE];

int left_button = GLUT_UP,right_button = GLUT_UP;
int mouseX,mouseY;
FPP* fpp;
Element* elements[ElementNum];
Texture* wallTexture,*floorTexture,*ceilTexture;

void reshape(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(w,(GLfloat)w/h,0.1f,200.0f);
}

void idle()
{
	glutPostRedisplay();
}

void DrawWalls()
{
	float light_diff[] = {1, 1, 1, 1};
	float light_spec[] = {0.6f, 0.6f, 0.6f, 1.0f};
    
    float ball_diff[] = { 0.85f,0,0,1};
    float ball_spec[] = { 1,1,1,1};
    
    float floor_diff[] = {0.5,0.5,0.5,1};
    
    float ceil_diff[] = {0.9,0.9,0.9,1};
    
    wallTexture->UseTexture();
    int width = 500,height =500;
    float deltaw = 1.0/width, deltah = 1.0/height;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, light_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, light_spec);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
	glBegin(GL_QUADS);
    float row,col,trow,tcol;
    for(row=0;row<1;row+=deltah)
        for(col=0;col<1;col+=deltaw)
        {
            trow = (row-0.5)*10;
            tcol = (col-0.5)*10;
            glNormal3f(-1, 0, 0);
            glTexCoord2f(row, col);     glVertex3f(5, trow, tcol);
            glTexCoord2f(row, col+deltah);   glVertex3f(5, trow, tcol+deltah*10);
            glTexCoord2f(row+deltaw, col+deltah);   glVertex3f(5, trow+deltaw*10, tcol+deltah*10);
            glTexCoord2f(row+deltaw, col);   glVertex3f(5, trow+deltaw*10, tcol);
        }

    for(row=0;row<1;row+=deltah)
        for(col=0;col<1;col+=deltaw)
        {
            glNormal3f(0, 1, 0);
            trow = (row-0.5)*10;
            tcol = (col-0.5)*10;
            glTexCoord2f(row, col);     glVertex3f(trow,-5, tcol);
            glTexCoord2f(row, col+deltah);   glVertex3f(trow, -5,tcol+deltah*10);
            glTexCoord2f(row+deltaw, col+deltah);   glVertex3f(trow+deltaw*10,-5, tcol+deltah*10);
            glTexCoord2f(row+deltaw, col);   glVertex3f(trow+deltaw*10,-5, tcol);
        }
    for(row=0;row<1;row+=deltah)
        for(col=0;col<1;col+=deltaw)
        {
            trow = (row-0.5)*10;
            tcol = (col-0.5)*10;
            glNormal3f(1, 0, 0);
            glTexCoord2f(row, col);     glVertex3f(-5, trow, tcol);
            glTexCoord2f(row, col+deltah);   glVertex3f(-5, trow, tcol+deltah*10);
            glTexCoord2f(row+deltaw, col+deltah);   glVertex3f(-5, trow+deltaw*10, tcol+deltah*10);
            glTexCoord2f(row+deltaw, col);   glVertex3f(-5, trow+deltaw*10, tcol);
        }
    
    for(row=0;row<1;row+=deltah)
        for(col=0;col<1;col+=deltaw)
        {
            glNormal3f(0, -1, 0);
            trow = (row-0.5)*10;
            tcol = (col-0.5)*10;
            glTexCoord2f(row, col);     glVertex3f(trow,5, tcol);
            glTexCoord2f(row, col+deltah);   glVertex3f(trow, 5,tcol+deltah*10);
            glTexCoord2f(row+deltaw, col+deltah);   glVertex3f(trow+deltaw*10,5, tcol+deltah*10);
            glTexCoord2f(row+deltaw, col);   glVertex3f(trow+deltaw*10,5, tcol);
        }
    glEnd();
    ceilTexture->UseTexture();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ceil_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ball_spec);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    glBegin(GL_QUADS);
    for(row=0;row<1;row+=deltah)
        for(col=0;col<1;col+=deltaw)
        {
            glNormal3f(0, 0, -1);
            trow = (row-0.5)*10;
            tcol = (col-0.5)*10;
            glTexCoord2f(row, col);     glVertex3f(trow,tcol,5);
            glTexCoord2f(row, col+deltah);   glVertex3f(trow,tcol+deltah*10,5);
            glTexCoord2f(row+deltaw, col+deltah);   glVertex3f(trow+deltaw*10,tcol+deltah*10,5);
            glTexCoord2f(row+deltaw, col);   glVertex3f(trow+deltaw*10,tcol,5);
        }
    glEnd();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ball_spec);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    floorTexture->UseTexture();
    glBegin(GL_QUADS);
    for(row=0;row<1;row+=deltah)
        for(col=0;col<1;col+=deltaw)
        {
            glNormal3f(0, 0, 1);
            trow = (row-0.5)*10;
            tcol = (col-0.5)*10;
            glTexCoord2f(row, col);     glVertex3f(trow,tcol,-5);
            glTexCoord2f(row, col+deltah);   glVertex3f(trow,tcol+deltah*10,-5);
            glTexCoord2f(row+deltaw, col+deltah);   glVertex3f(trow+deltaw*10,tcol+deltah*10,-5);
            glTexCoord2f(row+deltaw, col);   glVertex3f(trow+deltaw*10,tcol,-5);
        }
    glEnd();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ball_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ball_spec);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    glTranslatef (4.0, 0.0, 0.0);
    glutSolidTeapot(1);
}

void DrawOBJs()
{
    for(int i=0;i<ElementNum;i++)
    {
        glPushMatrix();
        glLoadName(elements[i]->name);
        elements[i]->Draw();
        glPopMatrix();
    }
}

void display()
{
    if(right_button == GLUT_DOWN) fpp->TurnSelf(10);
    if(left_button == GLUT_DOWN && Mode!=SELECT) fpp->GoForeward();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(eye[0],eye[1],eye[2],
		   eye[0]+Direction[0],eye[1]+Direction[1],eye[2]+Direction[2],
	   		UpDirection[0],UpDirection[1],UpDirection[2]
			);
	glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

	GLfloat LightPos0[] = {0,0,0,1};
	GLfloat LightWhite[] = {1,1,1,1};

	glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightWhite);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightWhite);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightWhite);
 
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0,  GL_LINEAR_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,0.03f);
    
    GLfloat LightPos1[4];
    LightPos1[0] = eye[0];
    LightPos1[1] = eye[1];
    LightPos1[2] = eye[2];
    LightPos1[3] = 1;
    glLightfv(GL_LIGHT1, GL_POSITION, LightPos1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightWhite);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightWhite);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightWhite);
    
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT1,  GL_LINEAR_ATTENUATION, 0.03f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION,0.03f);
  
	glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    glPushMatrix();
        DrawWalls();
    glPopMatrix();
    
    DrawOBJs();
    
	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'a': fpp->GoLeft(); break;
		case 'd': fpp->GoRight(); break;
		case 'w': fpp->GoForeward(); break;
		case 's': fpp->GoBackward(); break;
        case 'q': fpp->GoUp(); break;
        case 'e': fpp->GoDown(); break;
        case 'r':
            for(int i=0;i<ElementNum;i++)
                if(elements[i]->selected) elements[i]->Rotate(90, Direction[0], Direction[1], Direction[2]);
            break;
		default: break;
	}

}

void selectStarted(int x,int y)
{
    GLint vp[4];
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glSelectBuffer(BUFFERSIZE, selectBuffer);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glGetIntegerv(GL_VIEWPORT, vp);
    gluPickMatrix(x, vp[3]-y, 10, 10, vp);
    gluPerspective(vp[2],(GLfloat)vp[2]/vp[3],0.1f,200.0f);
    glMatrixMode(GL_MODELVIEW);
}

void selectFinished()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glFlush();
    int hits = glRenderMode(GL_RENDER);
    cout << "hits = " << hits << endl;
    if (hits == 0) return;
    int selectedName=-1;
    GLfloat min=99999999999;
    GLuint* ptr = selectBuffer;
    for(int i=0;i<hits;i++)
    {
        int num = *ptr;
        cout << "num = " << num << endl;
        ptr++;
        GLfloat value= *(GLfloat*)ptr;
        cout << "min_val = " << value << endl;
        ptr+=2;
        for(int j=0;j<num;j++)
        {
            if(value<min)
            {
                min = value;
                selectedName = *ptr;
            }
            ptr++;
        }
    }
    cout << "selectName = " << selectedName << endl;
    for(int i=0;i<ElementNum;i++)
        if(elements[i]->name == selectedName)
        {
            elements[i]->selected = 1 - elements[i]->selected;
            if(elements[i]->selected) Mode = SELECT;
            else Mode = VIEW;
            break;
        }
}

void mouse(int button,int state,int x,int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        selectStarted(x,y);
        DrawOBJs();
        selectFinished();
    }
	switch(button) {
		case GLUT_LEFT_BUTTON:left_button = state;break;
		case GLUT_RIGHT_BUTTON:right_button = state;break;
	}
	mouseX = x;
	mouseY = y;
}

void mousemotion(int x,int y)
{
	if(left_button == GLUT_DOWN)
	{
        if(Mode == SELECT) {
            for(int i=0; i<ElementNum; i++)
                if(elements[i]->selected) elements[i]->MouseMove(Direction, UpDirection ,(x-mouseX)/100.0, (y-mouseY)/100.0);
        } else {
            fpp->TurnEyeRight((x-mouseX)/5.0);
            fpp->TurnEyeDown((y-mouseY)/5.0);
        }
		mouseX = x;
		mouseY = y;
	}
}

void InitTextures()
{
    char tmp[200];
    GLuint texture[4];
    Texture* text = new Texture();
    glGenTextures(4, texture);
    wallTexture = new Texture();
    char wallfile[] = "/OpenGLInteraction/Crack.bmp";
    char isisfile[] = "/OpenGLInteraction/texture2.bmp";
    char cowfile[] = "/OpenGLInteraction/Texture.bmp";
    strcpy(tmp,Path);
    strcat(tmp,wallfile);
    wallTexture->LoadTexture(tmp, texture[0]);
    strcpy(tmp,Path);
    strcat(tmp,isisfile);
    text->LoadTexture(tmp, texture[1]);
    elements[ISIS]->texture = text;
/*    text = new Texture();
    text->LoadTexture("/Users/drinkingcoder/Documents/university/专题研讨/OpenGLInteraction/OpenGLInteraction/cow.bmp", texture[3]);*/
    elements[COW]->texture = text;
    strcpy(tmp,Path);
    strcat(tmp,cowfile);
    text = new Texture();
    text->LoadTexture(tmp, texture[2]);
    floorTexture = text;
    ceilTexture = text;
}

void InitOBJ()
{
    char tmp[200];
    char cowfile[] = "/OpenGLInteraction/Cow_dABF.obj";
    char isisfile[] = "/OpenGLInteraction/isis_dABF.obj";
    OBJ* obj;
    strcpy(tmp,Path);
    strcat(tmp,cowfile);
    obj = new OBJ();
    obj->loadOBJ(tmp);
    obj->Move(0, 0, 2);
    obj->Rotate(90, -1, 0 , 0);
    obj->name = COW+1;
    elements[COW] = obj;
    obj = new OBJ();
    strcpy(tmp,Path);
    strcat(tmp,isisfile);
    obj->loadOBJ(tmp);
    obj->Move(-1, 0, 0);
    obj->name = ISIS+1;
    elements[ISIS] = obj;
    cout << elements[COW]->name << endl;
    cout << elements[ISIS]->name << endl;
}

int main(int argc,char* argv[])
{
    fpp = new FPP(eye,Direction,UpDirection,left_button,right_button);
    InitOBJ();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow("Lab_VR");
    
    InitTextures();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemotion);

	glutMainLoop();
	return 0;
}
