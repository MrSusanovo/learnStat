#include <iostream>
#include <map>
#include "matrix.h"
using namespace std;

void printVector(double * v, int length){
  for(int i = 0; i<length; i++){
    cout<<v[i]<<" ";
  }
  cout<<endl;
}

int main(){
  string cmd;
  string store;
  Matrix m(2,3);
  Matrix m1(2,3);
  for(int i = 0; i<2; i++){
    for(int j = 0; j< 3; j++){
      m.setVal(i, j , i*1.0);
      m1.setVal(i,j,j*2.0);
    }
  }
  /*
  for(int i=0; i<3; i++){
    for(int j=0; j<2; j++){
      m1.setVal(i,j, j*1.0);
    }
  }
  */
  Matrix r = m1*m;
  for(int i=0;i<m.getRow();i++){
    printVector(m[i],m.getCol());
  }
  cout<<endl;
  for(int i=0;i<m1.getRow();i++){
    printVector(m1[i],m.getCol());
  }
  cout<<endl;
  for(int i=0; i<r.getRow();i++){
    printVector(r[i],r.getCol());
  }
  return 0;
}
/*
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
  Vector &operator[](const int);// get vector by index
  Vector &operator[](const std::string &);//get vector by string
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
*/
