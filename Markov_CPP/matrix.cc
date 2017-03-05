#include "matrix.h"
using namespace std;
/*
int *v;
int *copy;
const int size;
*/

Vector::Vector(int size): size{size}
{
  v = new int [size];
  copy = new int;
  *copy = 1;
}

Vector::Vector(int *vec,int size):
  size{size}
{
  v = new int[size];
  for(int i=0;i<size;i++){
    v[i]=vec[i];
  }
  copy = new int;
  *copy = 1;
}

Vector::Vector(const Vector &vec):
  v{vec.v},
  copy{vec.copy},
  size{vec.size}
{
  *copy+=1;
}


Vector::Vector(Vector &&temp):
  v{temp.v},
  copy{temp.copy},
  size{temp.size}
{
  *copy+=1;
}

Vector::~Vector(){
  *copy -= 1;
  if(copy == 0){
    delete[] v;
    delete copy;
  }
}

void Vector::setVal(int index, int num){
  if(index < size && index > 0){
    v[index] = num;
  }
}

int Vector::operator[](const int i) const{
  return v[i];
}

int Vector::len() const{
  return size;
}

Vector Vector::operator *(Vector &vec){
  if(vec.len() == size){
    Vector r(size);
    for(int i=0; i<size; i++){
      r.setVal(i, v[i] * vec[i]);
    }
    return r;
  }
}

int Vector::dot(Vector & vec){
  if(vec.len() == size){
    int result = 0;
    for(int i=0; i<size; i++){
      result += v[i] * vec[i];
    }
    return result;
  }
}

Vector Vector::getCopy() const{
  return Vector(v,size);
}

ostream& operator<<(ostream& out, Vector vec){
  int l = vec.len();
  for(int i=0; i<l; i++){
    out<<vec[i];
    if(i<l-1){
      out<<" ";
    }
  }
  out<<endl;
  return out;
}
    
/*
class Matrix{
  Vector *matrix;
  const int col;
  const int row;
  std::map<std::string, int> rname;
  std::map<std::string, int> cname;
*/
//public:

Matrix::Matrix(int rows, int cols):
  row{rows},
  col{cols}
{
  matrix = new int *[row];
  copy = new int;
  *copy = 1;
  for(int i=0; i<rows; i++){
    matrix[i] = new int[col];
  }
}

Matrix::Matrix(int **m,int r,int c):
  row{r},
  col{c}
{
  matrix = new int *[row];
  copy = new int;
  *copy = 1;
  for(int i=0; i<row; i++){
    matrix[i] = new int[col];
    for(int j = 0; j<col; j++){
      matrix[i][j] = m[i][j];
    }
  }
}

Matrix::Matrix(Vector* m, int row, int col):
  row{row},
  col{col}
{
  matrix = new int *[row];
  for(int i=0; i<row; i++){
    matrix[i] = new int[col];
    for(int j=0; j<col; j++){
      matrix[i][j] = m[i][j];
    }
  }
}

Matrix::Matrix(const Matrix &mat):
  matrix{mat.matrix},
  row{mat.row},
  col{mat.col},
  copy{mat.copy},
  rname{mat.rname},
  cname{mat.cname}
{
  *copy +=1;
}

Matrix::Matrix(Matrix &&temp):
  matrix{temp.matrix},
  row{temp.row},
  col{temp.col},
  copy{temp.copy},
  rname{mat.rname},
  cname{mat.cname}
{
  *copy +=1;
}

Matrix::~Matrix(){
  *copy -=1;
  if(*copy < 0){
    for(int i=0; i< row; i++){
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

Matrix Matrix::trans() const{
  Matrix m(col, row);
  m.rname=rname;
  m.cname=cname;
  for(int i = 0;i < row; i++){
    for(int j = 0;j < col; j++){
      m.setVal(j,i,matrix[i][j]);
    }
  }
  return m;
}

void Matrix::setVal(int r, int c, int v){
  if(r<row && c < col){
    matrix[r].setVal(c,v);
  }
}

void Matrix::setVal(string &r, string &c, int v){
  if(rname.begin() && cname.begin()){
    matrix[rname[r]].setVal(cname[c],v);
  }
}
Vector &Matrix::operator[](const int i){
  if(i<row){
    return matrix[i];
  }
}

Vector &Matrix::operator[](const string & key){
  if(rname.begin()){
    int i = rname[key];
    return matrix[i];
  }
}
  
int Matrix::getRow() const{
  return row;
}

int Matrix::getCol() const{
  return col;
}

void Matrix::setName(vector<string> &v){
  int len = v.size();
  if(len==row){
    for(int i=0; i < len; i++){
      rname[v[i]] = i;
    }
  }else if(len==col){
    for(int i=0; i < len; i++){
      cname[v[i]] = i;
    }
  }
}

void Matrix::setName(string[] &a, int s){
  if(s==row){
    for(int i = 0; i < s; i++){
      rname[a[i]] = i;
    }
  }else if(s==col){
    for(int i=0; i < s ; i++){
      cname[a[i]] = i;
    }
  }
}

int Matrix::getRC(string &r, string &c)const{
  if(rname.begin() && cname.begin()){
    return matrix[rname[r]][cname[c]];
  }
}

Matrix Matrix::getCopy() const{
  Matrix m(row,col);
  for(int i = 0; i<row; i++){
    m[i] = matrix[i].getCopy();
  }
  return m;
}

Matrix Matrix::operator *(Matrix &m){
  if(row==m.row && col == m.col){
    Matrix mat(row, col);
    for(int i = 0; i<row; i++){
      for(int j = 0; j<col; j++){
	mat.setVal(i,j,matrix[i][j] * m[i][j]);
      }
    }
    mat.setRname(rname);
    mat.setRname(cname);
    return mat;
  }
}
//Vector operator *
