//
//  Element.cpp
//  OpenGLInteraction
//
//  Created by drinking on 11/23/15.
//  Copyright © 2015 drinking. All rights reserved.
//

#include "Element.hpp"

float Element::sqr(float k)
{
    return k*k;
}

void Element::MatrixMultiplication(float m1[4][4],float m2[4][1],float m3[4][1],int n,int p,int m)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            m3[i][j] = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<p;j++)
            for(int k=0;k<m;k++)
                m3[i][k]+= m1[i][j]*m2[j][k];
}

void Element::Move(float x,float y,float z)
{
    this->x+=x;
    this->y+=y;
    this->z+=z;
}


void Element::MouseMove(GLfloat* dir, GLfloat* updir , float ix, float iy)
{
    float axis[3];
    float a1,a2,a3,b1,b2,b3;
    a1 = updir[0];
    a2 = updir[1];
    a3 = updir[2];
    b1 = dir[0];
    b2 = dir[1];
    b3 = dir[2];
    axis[0] = a2*b3-a3*b2;
    axis[1] = a3*b1-a1*b3;
    axis[2] = a1*b2-a2*b1;
    this->Move(ix*axis[0]+iy*updir[0], ix*axis[1]+iy*updir[1], ix*axis[2]+iy*updir[2]);
}

void Element::Rotate(float Theta, float x, float y, float z)
{
    float m[4][4],w[4][1],ans[4][1];
    float q1,q2,q3,q4;
    q1 = cos(Theta*PI/360);
    q2 = sin(Theta*PI/360)*x;
    q3 = sin(Theta*PI/360)*y;
    q4 = sin(Theta*PI/360)*z;
    memset(m,0,sizeof(m));
    m[0][0] = 1;
    m[1][1] = sqr(q1)+sqr(q2)-sqr(q3)-sqr(q4);
    m[1][2] = 2*q2*q3-2*q1*q4;
    m[1][3] = 2*q2*q4+2*q1*q3;
    m[2][1] = 2*q2*q3+2*q1*q4;
    m[2][2] = sqr(q1)-sqr(q2)+sqr(q3)-sqr(q4);
    m[2][3] = 2*q3*q4-2*q1*q2;
    m[3][1] = 2*q2*q4-2*q1*q3;
    m[3][2] = 2*q3*q4+2*q1*q2;
    m[3][3] = sqr(q1)-sqr(q2)-sqr(q3)+sqr(q4);
    
    w[0][0] = 0;
    w[1][0] = rx;
    w[2][0] = ry;
    w[3][0] = rz;
    MatrixMultiplication(m,w,ans,4,4,1);
    rx = ans[1][0];
    ry = ans[2][0];
    rz = ans[3][0];
}

void Element::CalcAngle()
{
    float a1,a2,a3,b1,b2,b3;
    a1 = 0;
    a2 = 0;
    a3 = 1;
    b1 = rx;
    b2 = ry;
    b3 = rz;
    axis[0] = a2*b3-a3*b2;
    axis[1] = a3*b1-a1*b3;
    axis[2] = a1*b2-a2*b1;
    angle = acosf(rz)*180/PI;
}