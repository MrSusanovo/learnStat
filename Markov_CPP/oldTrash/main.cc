#include <iostream>
#include <vector>
#include "markov.h"
using namespace std;

void run(Markov &m, string &s){
  m.feed(s);
  string r = m.predict();
  cout<<r<<endl;
}
int main(){
  Markov m;
  ofstream output{"record"};
  string cmd;
  int feed = -1;
  while(cin>>cmd){
    if(cmd=="/feed"){
      feed=1;
    }else if(cmd=="/run"){
      feed=0;
    }else if(cmd=="/state"){
      m.getState();
    }else if(cmd=="/trans"){
      m.getTrans();
    }else if(cmd==";"){
      output<<endl;
    }else{
      if(feed==1) m.feed(cmd);
      if(feed==0) run(m,cmd);
      output<<cmd<<" ";
    }
  }
  return 0;
}
