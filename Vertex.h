#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include "Vertex.h"

using namespace std;

class Vertex
{
private:
  float x, y, z;
  bool is_valid;
  int index;

public:
  Vertex(int i);
  float getX();
  float getY();
  float getZ();
  int getIndex();
  bool getFlag();
  void setIndex(int i);
  void setX(float x);
  void setY(float y);
  void setZ(float z);
  void setFlag(bool t);
  float distance(const Vertex* B);
};

#endif
