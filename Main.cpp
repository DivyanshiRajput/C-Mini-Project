#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <sstream>

#include "Vertex.h"
#include "Face.h"
#include "plyFile.h"

using namespace std;

int main (int argc, char** argv)
{
  base* IMT2019029 = new plyFile();
  IMT2019029->read(argv[1]);
  IMT2019029->execute();
  IMT2019029->write();

  return 0;
}
