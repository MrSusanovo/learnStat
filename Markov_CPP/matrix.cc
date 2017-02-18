#include "matrix.h"
using namespace std;
/*
int *v;
int *copy;
const int size;
*/

Vector::Vector (int size): size{size}
{
  v = new int [size];
  copy = new int;
  *copy = 1;
}

Vector::Vector(int *v,int size):
  v{v},
  size{size}
{
  copy = new int;
  *copy = 1;
}

Vector::Vector(const Vector &vec):
  v{vec.v},
  copy{vec.copy},
  size{vec.size}
{
  *copy +=1;
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

int Vector::operator[](const int i){
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
