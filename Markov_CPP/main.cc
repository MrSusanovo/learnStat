#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "hmm.h"
using namespace std;

template<typename T>
void print(vector<T> &v){
  for(auto i: v){
    cout<<i<<" ";
  }
  cout<<endl;
}

void readin(vector<vector<string>> &v, string &filename){
  ifstream iff{filename};
  string store;
  vector<string> entries;
  while(iff>>store){
    if(store=="/show"){
      v.emplace_back(entries);
      entries.erase(entries.begin(),entries.end());
    }else{
      entries.emplace_back(store);
    }
  }
  v.emplace_back(entries);
}

void Treadin(string &filename, HMM &h){
  ifstream iff{filename};
  string last;
  bool L=false;
  bool C=false;
  string cur;
  double d;
  string store;
  while(iff>>store){
    if(!L){
      last=store;
      L=true;
    }else if(!C){
      cur=store;
      C=true;
    }else{
      istringstream iss{store};
      iss>>d;
      h.setTrans(last,cur,d);
      L=C=false;
    }
  }
}

void Ereadin(string &filename, HMM &h){
  ifstream iff{filename};
  string last;
  bool L=false;
  bool C=false;
  string cur;
  double d;
  string store;
  while(iff>>store){
    if(!L){
      last=store;
      L=true;
    }else if(!C){
      C=true;
      cur=store;
    }else{
      istringstream iss{store};
      iss>>d;
      h.setEmission(last,cur,d);
      L=C=false;
    }
  }
}

void Sreadin(string &filename, HMM&h){
  ifstream iff{filename};
  string last;
  bool L=false;
  double d;
  string store;
  while(iff>>store){
    if(!L){
      last=store;
      L=true;
    }else{
      istringstream iss{store};
      iss>>d;
      h.setState(last,d);
      L=false;
    }
  }
}

// testing
int main(){
  HMM h;
  cout<<">>please enter your entreis file: ";
  string filename;
  vector<vector<string>> entries;
  cin>>filename;
  readin(entries,filename);
  h.setHiddenToEmit(entries);
  cout<<">>please enter your trans file: ";
  cin>>filename;
  Treadin(filename,h);
  cout<<">>please enter your emission file: ";
  cin>>filename;
  Ereadin(filename,h);
  cout<<">>please enter your state file: ";
  cin>>filename;
  Sreadin(filename,h);
  vector<string> a;
  vector<string> b;
  bool to_a=false;
  bool to_b=false;
  double prob;
  while(true){
    cout<<">>";
    cin>>filename;
    if(cin.eof()){
      cin.ignore();
      cin.clear();
      break;
    }
    if(filename=="/decode" || filename=="/eval"){
      a.erase(a.begin(),a.end());
      to_a=true;
    }else if(filename=="/tob"){
      to_a=false;
      to_b=true;
      b.erase(b.begin(),b.end());
    }else if(filename=="/sd"){
      h.decode(a,b);
      print<string>(b);
    }else if(filename=="/se"){
      if(to_b){
	h.evaluate(a,b);
	to_b=false;
      }else{
	to_a=false;
	prob=h.evaluate(a);
	cout<<prob<<endl;
      }
    }else if(filename=="/end"){
      break;
    }else if(filename=="/help"){
      cout<<"/decode: start input for decoding"<<endl;
      cout<<"/eval: start input for evaluation"<<endl;
      cout<<"/tob: switch input to b"<<endl;
      cout<<"/sd: finished input for decoding"<<endl;
      cout<<"/se: finished input for evaluate"<<endl;
    }else if(filename=="/ca"){
      a.erase(a.begin(),a.end());
    }else if(filename=="/cb"){
      b.erase(b.begin(),b.end());
    }else if(to_a){
      a.emplace_back(filename);
    }else if(to_b){
      b.emplace_back(filename);
    }
  }
  return 0;
}
