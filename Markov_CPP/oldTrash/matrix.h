#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>

class Matrix{
  std::vector<std::vector<double>> matrix;
 public:
  Matrix(int n);
  void transform(Matrix &) const;
  void clear();
  double get(int ,int ) const;
  int row() const;
  int col() const;
  int size() const;
  std::vector<double> row(int ) const;
  std::vector<double> col(int ) const;
  void addRow(std::vector<double> &);
  void addCol(std::vector<double> &);
  void set(int i, int j, double &t);
  Matrix operator +(const Matrix &);
  void operator +=(const Matrix &);
  bool operator ==(const Matrix &);
  Matrix operator *(const double);
  Matrix operator *(const Matrix &);
};

#endif
