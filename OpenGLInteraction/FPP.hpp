//
//  FPP.hpp
//  OpenGLInteraction
//
//  Created by drinking on 11/22/15.
//  Copyright © 2015 drinking. All rights reserved.
//

#ifndef FPP_hpp
#define FPP_hpp

#define PI 3.1415926

#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <iostream>

class FPP {
public:
    GLfloat* eye;
    GLfloat* Direction;
    GLfloat* UpDirection;
    int& left_button;
    int& right_button;
    FPP(GLfloat* eye,GLfloat* Direction,GLfloat* UpDirection,int& lb,int& rb):eye(eye),Direction(Direction),UpDirection(UpDirection),left_button(lb),right_button(rb)
    {}
    
    void MatrixMultiplication(float m1[4][4],float m2[4][1],float m3[4][1],int n,int p,int m);
    float sqr(float k);
    void RotateWithVector(float* vector,float* axis,float Theta);
    void TurnEyeLeft(float angle);
    void TurnEyeRight(float angle);
    void TurnEyeUp(float angle);
    void TurnEyeDown(float angle);
    void TurnSelf(float angle);
    void GoLeft();
    void GoRight();
    void GoForeward();
    void GoBackward();
    void GoUp();
    void GoDown();
};

#endif /* FPP_hpp */
