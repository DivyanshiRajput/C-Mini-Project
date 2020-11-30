#ifndef FACE_H
#define FACE_H

#include <iostream>
#include "Face.h"
#include "Vertex.h"

using namespace std;

class Face
{
private:
  vector<Vertex*> vertices;
  float area;
  int n;
  float areaTriangle(Vertex* a, Vertex* b, Vertex* c);

public:

  Face();
  void addVertex(Vertex* v);
  void calculateArea();
  float getArea();
  int getSize();
  vector<Vertex*> &getVertices()
  {
    return vertices;
  }
  void setSize(int n);

};

#endif
