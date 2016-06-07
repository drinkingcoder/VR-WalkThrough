//
//  Element.hpp
//  OpenGLInteraction
//
//  Created by drinking on 11/23/15.
//  Copyright © 2015 drinking. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include "Texture.hpp"
#include <math.h>

#define PI 3.1415926

using namespace std;

class Element {
protected:
    float axis[3],angle;
    virtual void CalcAngle();
    virtual float sqr(float k);
    float x,y,z;
    float rx,ry,rz;
    float selfAngle;
private:

    void MatrixMultiplication(float m1[4][4],float m2[4][1],float m3[4][1],int n,int p,int m);
public:
    int name;
    int selected;
    Texture* texture;
    Element() { selected = 0;x=y=z=rx=ry=selfAngle=0; rz=1; }
    virtual void Draw()=0;
    virtual void MouseMove(GLfloat* dir,GLfloat* updir, float ix,float iy);
    virtual void Move(float x,float y,float z);
    virtual void Rotate(float Theta,float x,float y,float z);
};

#endif /* Element_hpp */
