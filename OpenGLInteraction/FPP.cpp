//
//  FPP.cpp
//  OpenGLInteraction
//
//  Created by drinking on 11/22/15.
//  Copyright © 2015 drinking. All rights reserved.
//

#include "FPP.hpp"


void FPP::MatrixMultiplication(float m1[4][4],float m2[4][1],float m3[4][1],int n,int p,int m)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            m3[i][j] = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<p;j++)
            for(int k=0;k<m;k++)
                m3[i][k]+= m1[i][j]*m2[j][k];
}

float FPP::sqr(float k)
{
    return k*k;
}

void FPP::RotateWithVector(float* vector,float* axis,float Theta)
{
    float m[4][4],w[4][1],ans[4][1];
    float q1,q2,q3,q4;
    q1 = cos(Theta*PI/360);
    q2 = sin(Theta*PI/360)*axis[0];
    q3 = sin(Theta*PI/360)*axis[1];
    q4 = sin(Theta*PI/360)*axis[2];
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
    w[1][0] = vector[0];
    w[2][0] = vector[1];
    w[3][0] = vector[2];
    MatrixMultiplication(m,w,ans,4,4,1);
    vector[0] = ans[1][0];
    vector[1] = ans[2][0];
    vector[2] = ans[3][0];
}

void FPP::TurnEyeLeft(float angle)
{
    RotateWithVector(Direction,UpDirection,-angle);
}

void FPP::TurnEyeRight(float angle)
{
    TurnEyeLeft(-angle);
}

void FPP::TurnEyeUp(float angle)
{
    float z[3];
    float a1,a2,a3,b1,b2,b3;
    a1 = Direction[0];
    a2 = Direction[1];
    a3 = Direction[2];
    b1 = UpDirection[0];
    b2 = UpDirection[1];
    b3 = UpDirection[2];
    z[0] = a2*b3-a3*b2;
    z[1] = a3*b1-a1*b3;
    z[2] = a1*b2-a2*b1;
    RotateWithVector(Direction,z,-angle);
    RotateWithVector(UpDirection,z,-angle);
}

void FPP::TurnEyeDown(float angle)
{
    TurnEyeUp(-angle);
}

void FPP::TurnSelf(float angle)
{
    RotateWithVector(UpDirection,Direction,-angle);
}

void FPP::GoLeft()
{
    float z[3];
    float a1,a2,a3,b1,b2,b3;
    a1 = Direction[0];
    a2 = Direction[1];
    a3 = Direction[2];
    b1 = UpDirection[0];
    b2 = UpDirection[1];
    b3 = UpDirection[2];
    z[0] = a2*b3-a3*b2;
    z[1] = a3*b1-a1*b3;
    z[2] = a1*b2-a2*b1;
    eye[0]+=z[0]/3.0;
    eye[1]+=z[1]/3.0;
    eye[2]+=z[2]/3.0;
}

void FPP::GoRight()
{
    float z[3];
    float a1,a2,a3,b1,b2,b3;
    a1 = Direction[0];
    a2 = Direction[1];
    a3 = Direction[2];
    b1 = UpDirection[0];
    b2 = UpDirection[1];
    b3 = UpDirection[2];
    z[0] = a2*b3-a3*b2;
    z[1] = a3*b1-a1*b3;
    z[2] = a1*b2-a2*b1;
    eye[0]-=z[0]/3.0;
    eye[1]-=z[1]/3.0;
    eye[2]-=z[2]/3.0;	
}

void FPP::GoForeward()
{
    eye[0]+=Direction[0]/15.0;
    eye[1]+=Direction[1]/15.0;
    eye[2]+=Direction[2]/15.0;
}

void FPP::GoBackward()
{
    eye[0]-=Direction[0]/5.0;
    eye[1]-=Direction[1]/5.0;
    eye[2]-=Direction[2]/5.0;
}

void FPP::GoUp()
{
    eye[0]+=UpDirection[0]/5.0;
    eye[1]+=UpDirection[1]/5.0;
    eye[2]+=UpDirection[2]/5.0;
}

void FPP::GoDown()
{
    eye[0]-=UpDirection[0]/5.0;
    eye[1]-=UpDirection[1]/5.0;
    eye[2]-=UpDirection[2]/5.0;
}