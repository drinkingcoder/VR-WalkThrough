//
//  OBJOperation.cpp
//  OpenGLInteraction
//
//  Created by drinking on 11/22/15.
//  Copyright © 2015 drinking. All rights reserved.
//

#include "OBJOperation.hpp"

float sqr(float k)
{
    return k*k;
}

void addNormal(Vertex3D v,Vertex3D& n)
{
    for(int i=0;i<3;i++)
        n.vtx[i]+=v.vtx[i];
}

void OBJOperation::loadOBJ(string fileName)
{
    ifstream fin;
    fin.open(fileName.c_str());
    shapeVertices.clear();
    textureVertices.clear();
    shapeFaces.clear();
    textureFaces.clear();
    string input;
    
    float *vtx1,*vtx2,*vtx3;
    float a1,a2,a3,b1,b2,b3,la,lb;
    while (1) {
        if(fin.eof()) break;
        fin >>input;
        if(input.compare("v") == 0) {
            Vertex3D vertex;
            fin >> vertex.vtx[0] >> vertex.vtx[1] >> vertex.vtx[2];
            shapeVertices.push_back(vertex);
            Vertex3D normal;
            normal.vtx[0] = normal.vtx[1] = normal.vtx[2] = 0;
            normals.push_back(normal);
        } else if( input.compare("vt") == 0) {
            Vertex2D vertex;
            fin >> vertex.vtx[0] >> vertex.vtx[1];
            textureVertices.push_back(vertex);
        } else if( input.compare("f") == 0) {
            Face shapeFace,textureFace;
            Vertex3D normal;
            char c;
            fin >> shapeFace.vertexIndex[0] >> c >> textureFace.vertexIndex[0];
            fin >> shapeFace.vertexIndex[1] >> c >> textureFace.vertexIndex[1];
            fin >> shapeFace.vertexIndex[2] >> c >> textureFace.vertexIndex[2];
            for(int i=0;i<3;i++)
            {
                shapeFace.vertexIndex[i]--;
                textureFace.vertexIndex[i]--;
            }
            shapeFaces.push_back(shapeFace);
            textureFaces.push_back(textureFace);
            vtx1 = shapeVertices[shapeFace.vertexIndex[0]].vtx;
            vtx2 = shapeVertices[shapeFace.vertexIndex[1]].vtx;
            vtx3 = shapeVertices[shapeFace.vertexIndex[2]].vtx;
            a1 = vtx2[0]-vtx1[0];
            a2 = vtx2[1]-vtx1[1];
            a3 = vtx2[2]-vtx1[2];
            b1 = vtx3[0]-vtx2[0];
            b2 = vtx3[1]-vtx2[1];
            b3 = vtx3[2]-vtx2[2];
            la = sqrt(sqr(a1)+sqr(a2)+sqr(a3));
            lb = sqrt(sqr(b1)+sqr(b2)+sqr(b3));
            a1 = a1/la;
            a2 = a2/la;
            a3 = a3/la;
            b1 = b1/lb;
            b2 = b2/lb;
            b3 = b3/lb;
            normal.vtx[0] = a2*b3-a3*b2;
            normal.vtx[1] = a3*b1-a1*b3;
            normal.vtx[2] = a1*b2-a2*b1;
            for(int i=0;i<3;i++)
                addNormal(normal,normals[shapeFace.vertexIndex[i]]);
        }
    }
    for(int i=0;i<normals.size();i++)
    {
        a1 = normals[i].vtx[0];
        a2 = normals[i].vtx[1];
        a3 = normals[i].vtx[2];
        la = sqrt(sqr(a1)+sqr(a2)+sqr(a3));
        for(int j=0;j<3;j++)
            normals[i].vtx[j]/=la;
    }
    fin.close();
}

void OBJOperation::drawOBJ(float x, float y, float z)
{
    glTranslatef(x, y, z);
    glRotatef(90, -1, 0, 0);
    texture->UseTexture();
    glBegin(GL_TRIANGLES);
    float diff[] = {0.85,0.35,1,1.0};
    float spec[] = {1,1,1,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    for(int i=0;i<shapeFaces.size();i++)
        for(int j=0;j<3;j++)
        {
            glTexCoord2fv(textureVertices[shapeFaces[i].vertexIndex[j]].vtx);
            glNormal3fv(normals[shapeFaces[i].vertexIndex[j]].vtx);
            glVertex3fv(shapeVertices[shapeFaces[i].vertexIndex[j]].vtx);
        }
    glEnd();
}