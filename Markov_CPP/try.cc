#include <iostream>
using namespace std;
void fun(int &a){
  a++;
}
int main(){
  int a = 0;
  cout<<a<<endl;
  fun(a);
  cout<<a<<endl;
  return 0;
}
