#include <iostream>
#include "markov.h"
using namespace std;
/*
  std::map<std::string,double> state;
  std::map<char,std::map<std::string,double>> trans;
  std::string last;
*/
//public:

string Markov::predict(string s){
  string target = last;
  if(s.length()!=0){
    target = s;
  }
  auto k = trans.find(target);
  if(k!=trans.end()){
    auto p = k->second.begin();
    for(auto i=k->second.begin();i!=k->second.end();++i){
      if(i->second > p->second){
	p=i;
      }
    }
    return p->first;
  }else{
    return "";
  }
}	  

void Markov::feed(string s){
  if(s.length()!=0){
    auto it = state.find(s);
    if(it!=state.end()){
      state[s]+=1.0;
    }else{
      state[s]=1.0;
    }
    auto tit = trans.find(s);
    // if trans does not have s vector
    if(tit==trans.end()){
      map<string,double> n;
      n[s]=0.0;
      trans[s]=n;
    }
    if(last.length()!=0){
      auto lit = trans[last].find(s);
      if(lit==trans[last].end()){
	trans[last][s]=1.0;
      }else{
	trans[last][s]+=1.0;
      }
    }
    last=s;
  }
}

void Markov::feed(ifstream file){
  if(file.is_open()){
    string s;
    while(file>>s){
      this->feed(s);
    }
  }else{
    cerr<<"bad input file"<<endl;
  }
}

void Markov::getState(){
  for(auto i: state){
    cout<<i.first<<": "<<i.second<<" | ";
  }
  cout<<endl;
}

void Markov::getTrans(){
  for(auto i: trans){
    cout<<i.first<<": "<<endl<<"    ";
    for(auto j: i.second){
      cout<<j.first<<": "<<j.second<<" | ";
    }
    cout<<endl;
  }
}
