#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <iostream>
#include <map>
class Vector{
  int *v;
  int *copy;
  const int size;
 public:
  Vector (int );
  Vector(int *,int );
  Vector(const Vector &);
  ~Vector();
  void setVal(int, int);
  int operator[](const int);
  int len() const;
  Vector operator *(Vector &);
};

/*
class Matrix{
  int **m;
  const int col;
  const int row;
  std::map<std::string, int> r;
  std::map<std::string, int> c;
 public:
  friend int *operator[](const Matrix &);
  Matrix(int );
  Matrix(int **,int ,int);
  Matrix(const Matrix &);
  Matrix trans() const;
  void setVal(int, int, int);
  Vector getRow(int );
  Vector getCol(int );
};
*/

//Vector operator *
#endif
