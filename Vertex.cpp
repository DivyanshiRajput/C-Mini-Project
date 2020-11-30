#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include <iomanip>

#include "Vertex.h"

//constructor
Vertex:: Vertex(int i)
{
  this->index = i;
  this->is_valid = false;
}

//calculates distance of this vertex from another vertex B
float Vertex :: distance(const Vertex* B)
{
    return sqrt(pow(x - B->x, 2) + pow(y - B->y, 2) + pow(z - B->z, 2));
}

//getters
float Vertex:: getX()
{
  return this->x;
}

float Vertex:: getY()
{
  return this->y;
}

float Vertex:: getZ()
{
  return this->z;
}

bool Vertex:: getFlag()
{
  return this->is_valid;
}

int Vertex:: getIndex()
{
  return this->index;
}

//setters
void Vertex:: setX (float x)
{
  this->x = x;
}

void Vertex:: setY (float y)
{
  this->y = y;
}

void Vertex:: setZ (float z)
{
  this->z = z;
}

void Vertex:: setFlag(bool t)
{
  this->is_valid = t;
}

void Vertex:: setIndex(int i)
{
  this->index = i;
}
