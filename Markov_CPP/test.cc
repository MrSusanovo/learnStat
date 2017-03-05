#include <iostream>
#include "matrix.h"
using namespace std;

int main(){
  int size = 5;
  Vector vec(size);
  for(int i=0;i<size;i++){
    vec.setVal(i,i);
  }
  cout<<vec;
  Vector ve=vec;
  cout<<"number of vec copies: "<<vec.getCopy()<<endl;
  cout<<"ve.copy: "<<ve.getCopy()<<endl;
  cout<<"size:"<<vec.len()<<", "<<ve.len()<<endl;
  cout<<vec.dot(ve)<<endl;
  cout<<"times:"<<vec*ve;
  return 0;
}
