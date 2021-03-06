#include "matrix.h"
using namespace std;
/*
int *v;
int *copy;
const int size;
*/

Vector::Vector(int size): size{size}
{
  v = new double [size];
  copy = new int;
  *copy = 1;
}

Vector::Vector(double *vec,int size, bool shallow=false):
  size{size}
{
  if(shallow){
    //cerr<<"Shallow copy"<<endl;
    v = vec;
  }else{
    //cerr<<"Vector ctor: vec size shallow"<<endl;
    v = new double[size];
    for(int i=0;i<size;i++){
      //cerr<<"Vector ctor: vec["<<i<<"] = "<<vec[i]<<endl;
      v[i]=vec[i];
    }
  }
  copy = new int;
  *copy = 1;
}

Vector::Vector(const Vector &vec):
  v{vec.v},
  copy{vec.copy},
  size{vec.size}
{
  //cerr<<"copy ctor"<<endl;
  *copy+=1;
}
  

Vector::Vector(Vector &&temp):
  v{temp.v},
  copy{temp.copy},
  size{temp.size}
{
  //cerr<<"temp copy ctor"<<endl;
  *copy+=1;
}

Vector::~Vector(){
  //cerr<<"vector dtor"<<endl;
  *copy -= 1;
  if(copy == 0){
    delete[] v;
    delete copy;
  }
}

void Vector::setVal(int index, double num){
  if(index < size && index > 0){
    v[index] = num;
  }
}

double Vector::operator[](const int i) const{
  //cerr<<"vector [] correct"<<endl;
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

double Vector::dot(Vector & vec){
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
  matrix = new double *[row];
  copy = new int;
  *copy = 1;
  for(int i=0; i<rows; i++){
    matrix[i] = new double[col];
  }
}

Matrix::Matrix(double **m,int r,int c):
  row{r},
  col{c}
{
  matrix = new double *[row];
  copy = new int;
  *copy = 1;
  for(int i=0; i<row; i++){
    matrix[i] = new double[col];
    for(int j = 0; j<col; j++){
      matrix[i][j] = m[i][j];
    }
  }
}

Matrix::Matrix(Vector* m, int row, int col):
  row{row},
  col{col}
{
  matrix = new double *[row];
  for(int i=0; i<row; i++){
    matrix[i] = new double[col];
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
  rname{temp.rname},
  cname{temp.cname}
{
  *copy +=1;
}

Matrix::~Matrix(){
  //cerr<<"marix dtor"<<endl;
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

void Matrix::setVal(int r, int c, double v){
  if(r<row && c < col){
    //cerr<<"set "<<r<<" "<<c<<": "<<v<<endl;
    matrix[r][c]=v;
  }
}

void Matrix::setVal(string &r, string &c, double v){
  if(rname.size() && cname.size()){
    matrix[rname[r]][cname[c]]=v;
  }
}
double * Matrix::operator[](const int i){
  if(i<row){
    //cerr<<"matrix []: col "<<col<<endl;
    return matrix[i];
  }
}

double * Matrix::operator[](const string & key){
  if(rname.size()){
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

void Matrix::setName(vector<string> &v, bool isRow=false){
  int len = v.size();
  if(isRow){
    for(int i=0; i < len; i++){
      rname[v[i]] = i;
    }
  }else{
    for(int i=0; i < len; i++){
      cname[v[i]] = i;
    }
  }
}

/*
void Matrix::setName(string[] a, int s, bool isRow=false){
  if(isRow){
    for(int i = 0; i < s; i++){
      rname[a[i]] = i;
    }
  }else{
    for(int i=0; i < s ; i++){
      cname[a[i]] = i;
    }
  }
}
*/

void Matrix::setName(map<string,int> &m, bool isRow=false){
  if(isRow){
    rname=m;
  }else{
    cname=m;
  }
}

double Matrix::getRC(string &r, string &c) const{
  auto RIter = rname.find(r);
  auto CIter = cname.find(c);
  if(CIter!=cname.end() && RIter!=rname.end()){
    return matrix[RIter->second][CIter->second];
  }
}

Matrix Matrix::getCopy() const{
  Matrix m(row,col);
  double *rowPointer;
  for(int i = 0; i<row; i++){
    for(int j=0;j<col;j++){
      m.setVal(i,j,matrix[i][j]);
    }
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
    mat.setName(rname, true);
    mat.setName(cname, false);
    return mat;
  }
}
//Vector operator *
