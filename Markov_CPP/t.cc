#include <iostream>
#include "matrix.h"
using namespace std;

int main(){
  int *v = new int[2];
  v[0] = 1;
  v[1] = 2;
  Vector vec(v, 2);
  Vector ve(vec);
  for(int i=0; i<2; i++){
    cout<<ve[i]<<endl;
  }
  return 0;
}
