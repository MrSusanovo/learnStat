#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Vector{
  double *v;
  int *copy;
  const int  size;
 public:
  explicit Vector(int ); // initialize a vector with size
  explicit Vector(double *,int ,bool);// vectorize an array, which allocates new mem on heapX
  Vector(const Vector &);// copy ctor
  Vector(Vector &&);
  ~Vector();// dtor
  void setVal(int, double);// set the value of a certain number
  double operator[](const int) const;// same as array [i]
  int len() const;// return the length
  double dot(Vector &);// do the dot product
  Vector getCopy() const;// return a deep copy
  Vector operator *(Vector &);// do the position to position product
};

std::ostream& operator<<(std::ostream&, Vector);



class Matrix{
  double **matrix;
  const int row; // length of each Vector
  const int col;// total number of Vectors
  int * copy;
  std::map<std::string, int> rname;
  std::map<std::string, int> cname;
 public:
  explicit Matrix(int , int);
  explicit Matrix(double **,int ,int);// deep copy
  Matrix(Vector[], int, int);// deep copy
  Matrix(const Matrix &);// shallow copy
  Matrix(Matrix &&);// shallow
  ~Matrix();// detor
  Matrix trans() const;// return a deep copy transpose matrix
  double *operator[](const int);// get vector by index
  double *operator[](const std::string &);//get vector by string
  Matrix operator *(Matrix &); // get the pos to pos product matrix deep copy
  void setVal(int, int, double);// set value by index
  void setVal(std::string &, std::string &, double);// set value by string
  //void setName(std::string [], int, bool);// set R/Cname 
  void setName(std::vector<std::string> &,bool);// set R/Cname
  void setName(std::map<std::string, int> &, bool);// set R/Cname
  int getRow() const;// get num of row
  int getCol() const;// get num of col
  double getRC(std::string &, std::string &) const;
  Matrix getCopy() const;// get a deep copy matrix
};


//Vector operator *
#endif
