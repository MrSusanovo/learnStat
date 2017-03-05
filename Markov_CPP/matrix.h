#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Vector{
  int *v;
  int *copy;
  int const size;
 public:
  Vector(int ); // initialize a vector with size
  Vector(int *,int );// vectorize an array, which allocates new mem on heapX
  Vector(const Vector &);// copy ctor
  Vector(Vector &&);
  ~Vector();// dtor
  void setVal(int, int);// set the value of a certain number
  int operator[](const int) const;// same as array [i]
  int len() const;// return the length
  int dot(Vector &);// do the dot product
  Vector getCopy() const;// return a deep copy
  Vector operator *(Vector &);// do the position to position product
};

std::ostream& operator<<(std::ostream&, Vector);



class Matrix{
  int **matrix;
  const int row; // length of each Vector
  const int col;// total number of Vectors
  int * copy;
  std::map<std::string, int> rname;
  std::map<std::string, int> cname;
 public:
  Matrix(int , int);
  Matrix(int **,int ,int);// deep copy
  Matrix(Vector[], int, int);// deep copy
  Matrix(const Matrix &);// shallow copy
  Matrix(Matrix &&);// shallow
  ~Matrix();// detor
  Matrix trans() const;// return a deep copy transpose matrix
  Vector &operator[](const int);// get vector by index
  Vector &operator[](const std::string &);//get vector by string
  Matrix operator *(Matrix &); // get the pos to pos product matrix deep copy
  void setVal(int, int, int);// set value by index
  void setVal(std::string &, std::string &, int);// set value by string
  void setName(std::string [], int);// set R/Cname 
  void setName(std::vector<std::string> &);// set R/Cname
  int getRow() const;// get num of row
  int getCol() const;// get num of col
  int getRC(std::string &, std::string &) const;
  Matrix getCopy() const;// get a deep copy matrix
};


//Vector operator *
#endif
