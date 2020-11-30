#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include <iomanip>

#include "base.h"
#include "Face.h"
#include "Vertex.h"

using namespace std;

Face:: Face()
{
  this->area = 0;
  this->n = 0;
}

//adds vertex to the list vertices of every face
void Face:: addVertex(Vertex* v)
{
  vertices.push_back(v);
}

//calculates the area of the face from all the vertices in the list
void Face:: calculateArea()
{
  float temp = 0;
  for (int i = 0; i< this->n - 2; ++i)
  {
    temp += areaTriangle(vertices[0],vertices[i+1],vertices[i+2]);
  }
  this->area = temp;
}

//used by calculateArea function to calculate area of triangles which are joined to form the polygon
float Face:: areaTriangle(Vertex* a, Vertex* b, Vertex* c)
{
  float A, B, C, side;

  A = a->distance(b);
  B = b->distance(c);
  C = c->distance(a);

  side=((A+B+C)/2);

  area = sqrt(side*(side-A)*(side-B)*(side-C));
  return area;
}

//getters
float Face:: getArea()
{
  return this->area;
}

int Face:: getSize()
{
  return this->n;
}

//setters
void Face:: setSize(int n)
{
  this->n = n;
}
