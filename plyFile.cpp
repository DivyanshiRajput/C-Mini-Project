#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include <iomanip>
#include <algorithm>

#include "base.h"
#include "Vertex.h"
#include "Face.h"
#include "plyFile.h"

using namespace std;

//function to read from the input file
void plyFile:: read(char* filename)
{
  string data; //used for storing line when we read from the input file
  file1.open(filename, ios:: in);
  int i = 0; //iterator for while loop
  while (data != "end_header") //loop to read the input file till end_header
  {
    getline(this->file1, data); //reads one line from the input and stores it as a string in data
    this->output.push_back(data);
    vector<string> tokens;
    string temp;
    stringstream ss(data) ;

    while(getline(ss,temp,' '))
    {
      tokens.push_back(temp);
    }
    if (tokens[0] == "element" && tokens[1] == "vertex") //for storing number_of_vertices in the input file
    {
      string temp;
      stringstream stream(data);
      int j = 0;
      while (getline(stream,temp,' ')) //splitting the line with character space
      {
        if (j == 2) //the third item will be the number of vertices
        this->number_of_vertices = stoi(temp);
        j++;
      }
    }
    else if (tokens[0] == "element" && tokens[1] == "face") //for storing number_of_faces in the input file
    {
      string temp;
      stringstream stream(data);
      int j = 0;
      while (getline(stream,temp,' ')) //splitting the line with character space
      {
        if (j == 2) //the third item will be the number of faces
          this->number_of_faces = stoi(temp);
        j++;
      }
    }
    i++;
  }

  for (int j = 0; j < this->number_of_vertices; j++) //taking input for all the vertices
  {
    getline(this->file1, data); //reading input for every vertex line by line
    string str;
    stringstream stream(data);
    Vertex temp(j); //temp Vertex object which can be added to the list of vertices later
    int k = 0;
    while (getline(stream, str, ' '))
    {
      if (k == 0) //condition for storing the x coordinate
      {
        temp.setX(stof(str));
      }
      else if (k == 1) //condition for storing the y coordinate
      {
        temp.setY(stof(str));
      }
      else if (k == 2) //condition for storing the z coordinate
      {
        temp.setZ(stof(str));
      }
      k++;
    }
    this->v.push_back(temp); //adds temp Vertex to the list of vertices
  }

  for (int j = 0; j < this->number_of_faces; j++) //taking input for all the faces
  {
    getline(this->file1, data);  //reading input for every face line by line
    string str;
    stringstream stream(data);
    int k = 0;
    vector<string> tokens;
    while (getline(stream, str, ' ')) //storing the size of the face and all the vertex indices as tokens
    {
      tokens.push_back(str);
      k++;
    }
    k=0;
    //we will be adding all the triangles to the list of faces
    if(stoi(tokens[0])>3) //if size of face is greater than 3 i.e. it is a square or polygon
    {
      // we fix one vertex and then divide the polygon into triangles
      // here I am setting it to the first vertex which is there in the face description
      int fixed_vertex_index=stoi(tokens[1]);
      for(k = 3; k < tokens.size(); ++k) //adding all the triangles to the face list
      {
        //creating new face and initialising all the values
        Face *temp= new Face();
        temp->setSize(3);
        temp->addVertex(&v[fixed_vertex_index]);
        temp->addVertex(&v[stoi(tokens[k-1])]);
        temp->addVertex(&v[stoi(tokens[k])]);
        temp->calculateArea();
        f.push_back(*temp); //adding all the triangles to the face list
      }
    }
    else //if the face is a triangle
    {
      //directly creating a face object and adding it to the face list
      Face *temp= new Face();
      temp->setSize(3);
      temp->addVertex(&v[stoi(tokens[1])]);
      temp->addVertex(&v[stoi(tokens[2])]);
      temp->addVertex(&v[stoi(tokens[3])]);
      temp->calculateArea();
      f.push_back(*temp);
    }
  }
  this->file1.close(); //closing the file after reading all the inputs of vertices and faces
}

//execute (sort the list of faces on the basis of area and prunes the vertices)
void plyFile:: execute()
{
  sort(this->f.begin(), this->f.end(), AreaComparator); //sorting the list of faces (triangles) on the basis of their area
  int n = floor(f.size() * 0.1); //calculating the 10% of the total number of faces
  for (int i = 0; i < n; i++) //removing faces which are in the lower 10% of the sorted list of triangles
  {
    this->f.erase(this->f.begin());
  }
  this->number_of_faces = f.size(); //updating the number of faces

  for (int i = 0; i < f.size(); i++) //marking the flag true for all the vertices which are still used in the face list
  {
    for (int j = 0; j < 3; j++)
    {
      if (!f[i].getVertices()[j]->getFlag())
      {
        f[i].getVertices()[j]->setFlag(true);
      }
      else
        continue;
    }
  }

  int new_index = 0;
  for (int i = 0; i < v.size(); i++) //storing the final list of vertices which needs to be written in the output file and updating the index of the vertices
  {
    if (v[i].getFlag())
    {
      v[i].setIndex(new_index); //setting new index for all the "currently in use" vertices
      new_index++;
      this->output.push_back(toString(v[i].getX()) + " " + toString(v[i].getY()) + " " + toString(v[i].getZ())) ; //pushing them into the list of string of output
      continue;
    }
    else
    {
      v.erase(v.begin() + i); //if vertex is not used removing it from the list of vertices
      i--;
    }
  }
  this->number_of_vertices = v.size(); //updating the number of vertices

  for (int i = 0; i < this->f.size(); i++) //iterating over all the faces to make the string which we will write to the output file
  {
    this->out = toString(f[i].getSize()) + " ";
    for (int k = 0; k < f[i].getSize(); k++)
    {
      this->out += toString(f[i].getVertices()[k]->getIndex()) + " ";
    }
    this->output.push_back(this->out) ;
  }
}

//function to write back to the output file
void plyFile:: write()
{
  this->file2.open("output.ply", ios:: out); //opening the output file in write mode
  for(int i = 0; i < this->output.size(); i++) //iterating over the strings which are to be written in the output file
  {
    if(this->output[i] == "") //if line is blank line
    {
      continue ;
    }
    vector<string> tokens;
    string temp;
    stringstream ss(this->output[i]) ;

    while(getline(ss,temp,' '))
    {
      tokens.push_back(temp);
    }

    if(tokens[0] == "element" && tokens[1] == "vertex") //replacing the number of vertices with new number of vertices
    {
      string temp = "element vertex " + toString(this->v.size()) + "\n";
      this->file2 << temp;
    }

    else if(tokens[0] == "element" && tokens[1] == "face") //replacing the number of faces with new number of faces
    {
      string temp = "element face " + toString(this->f.size()) + "\n";
      this->file2 << temp ;
    }

    else //writing to the main output file
    {
      this->file2 << output[i] << endl ;
    }

  }

  this->file2.close();
}

//converts float to string
string plyFile:: toString(float t)
{
  ostringstream ss;
  ss << t;
  string s(ss.str());
  return s;
}

//area comparator for 2 faces
bool plyFile:: AreaComparator (Face a, Face b)
{
  return a.getArea() < b.getArea();
}
