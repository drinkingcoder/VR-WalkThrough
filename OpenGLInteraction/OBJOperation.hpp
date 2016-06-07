//
//  OBJOperation.hpp
//  OpenGLInteraction
//
//  Created by drinking on 11/22/15.
//  Copyright © 2015 drinking. All rights reserved.
//

#ifndef OBJOperation_hpp
#define OBJOperation_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GLUT/glut.h>
#include <vector>
#include <math.h>
#include "Texture.hpp"

using namespace std;

typedef struct Vertex3D {
    float vtx[3];
} Vectex3D;

typedef struct Vertex2D {
    float vtx[2];
}Vertex2D;

typedef struct HalfEdge {
    int Next;
    int Reverse;
    int StartPoint,EndPoint;
    int Face;
} HalfEdge;

typedef struct Face {
    int vertexIndex[3];
} Face;

class OBJOperation {
public:
    int name;
    Texture* texture;
    vector<HalfEdge> halfEdge;
    vector<Vertex3D> shapeVertices;
    vector<Vertex2D> textureVertices;
    vector<Face> shapeFaces;
    vector<Vertex3D> normals;
    vector<Face> textureFaces;
    float x,y,z;
    float angle,rx,ry,rz;
    OBJOperation() { x=y=z=angle=rx=ry=rz=0;}
    void loadOBJ(string fileName);
    void drawOBJ(float x,float y,float z);
};

#endif /* OBJOperation_hpp */
