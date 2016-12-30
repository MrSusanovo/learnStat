#include <vector>

#include "matrix.h"

using namespace std;

//std::vector<std::vector<double>> matrix;
//public:
Matrix::Matrix(int n){
  vector<vector<double>> v{n};
  matrix = v;
}

void Matrix::clear(){
  matrix.erase(matrix.begin(),matrix.end());
}

void Matrix::transform(Matrix &m) const{
  if(m.size()!=0){
    m.clear();
  }
  int len = matrix.size();
  for(int i = 0; i<len; i++){
    m.addRow(this->col(i));
  }
}

double Matrix::get(int r,int c) const{
  return matrix[r][c];
}

vector<double> Matrix::row(int r) const{
  vector<double> v=matrix[r];
  return v;
}

vector<double> Matrix::col(int c) const{
  vector<double> v{matrix.size()};
  int len = matrix.size();
  for(int i=0;i<len;i++){
    v[i]=matrix[i][c];
  }
  return v;
}

void Matrix::addRow(vector<double> &r){
  matrix.emplace_back(r);
}

void Matrix::addCol(vector<double> &c){
  int len = matrix.size();
  for(int i = 0;i<len;i++){
    matrix[i].emplace_back(c[i]);
  }
}

void Matrix::set(int i, int j, double &d){
  if((i<matrix.size() && i>=0) && (j<matrix.size() && j>=0)){
    matrix[i][j]=d;
  }
}

Matrix Matrix::operator +(const Matrix &m){
  if(m.size()==matrix.size()){
    Matrix r=m;
    int len = m.size();
    for(int i = 0; i < len; i++){
      for(int j = 0; j < len; j++){
	r.set(i,j,matrix[i][j]+m.get(i,j));
      }
    }
    return r;
  }else{
    Matrix r{0};
    return r;
  }
}

void Matrix::operator +=(const Matrix &m){
  if(m.size()==matrix.size()){
    int len = matrix.size();
    for(int i = 0; i < len; i++){
      for(int j = 0; j< len; j++){
	matrix[i][j]+=m.get(i,j);
      }
    }
  }
}

bool Matrix::operator ==(const Matrix &m){
  if(m.size()==matrix.size()){
    for(int i = matrix.size()-1;i>=0;i--){
      for(int j = matrix.size()-1;j>=0;j--){
	if(matrix[i][j]!=m.get(i,j)){
	  return false;
	}
      }
    }
  }else{
    return false;
  }
  return true;
}

Matrix Matrix::operator *(const double c){
  int len = matrix.size();
  Matrix m{len};
  for(int i=0;i<len;i++){
    for(int j=0;j<len;j++){
      m.set(i,j,matrix[i][j]*c);
    }
  }
  return m;
}

Matrix Matrix::operator *(const Matrix &m){
}
