#ifndef PLYFILE_H
#define PLYFILE_H

#include "base.h"

class plyFile: public base
{

private:
  vector<Face> f; //stores all the faces
  vector<Vertex> v; //stores all the vertices
  int number_of_faces; //stores the number of faces
  int number_of_vertices; //stores the number of vertices
  vector<string> output; //stores all the output lines

public:
  string toString(float t);
  static bool AreaComparator(Face a, Face b);
  void read(char* filename);
  void execute();
  void write();
};

#endif
