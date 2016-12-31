#include "hmm.h"
#include <iostream>
using namespace std;

//private
/*
std::map<std::string, std::map<std::string,double>> trans;
std::map<std::string, std::map<std::string,double>> emission;
std::map<std::string, double> state;
std::map<std::string, double> module;
std::vector<std::string> hidden;
std::vector<std::string> shown;
*/

void HMM::forwardAlg(vector<string> &obs,
		vector<map<string, double>> &states,
		double &prob, int &index)
{
  double p;
  for(string i: obs){
    p=0.0;
    // P(shown | states) = Matrix(emission)[shown] * Matrix(state)
    for(auto j:states[index]){
      p+=j.second * emission[j.first][i];
    }
    prob*=p;
    index+=1;
    // P(state | state-1) = Matrix(state-1) * Matrix(trans)
    states.emplace_back(module);
    for(auto j:states[index]){
      for(auto k:trans[j.first]){
	states[index][k.first]+=states[index-1][j.first] * k.second;
      }
    }
  }
}

void HMM::viterbiAlg(vector<string> &obs,
		     vector<string> &store,
		     vector<map<string, double>> &states,
		     int &index)
{
  for(string i: obs){
    if(index){
      for(auto cur: states[index]){
	// in general 
	// p(current|observe)=*p(current|last)
	//                   *p(emission[current][observe])
	// where p(current|last)=p(trans[last][current])
	string last = store[index-1];
	double last_cur = trans[last][cur.first];
	double cur_obs = emission[cur.first][i];
	double last_prob = states[index-1][last];
	//cout<<last<<", trans: "<<last_cur<<" emit: "<<cur_obs<<" last prob "<<last_prob<<" current: "<<cur.first<<endl;
	states[index][cur.first] = last_cur * cur_obs * last_prob;
      }
    }else{
      // on the first observation
      // p( current | observe ) = p(current) * p(emission[current][observe])
      for(auto j: states[index]){
	states[index][j.first] *= emission[j.first][i];
      }
    }
    // find the maximum probability
    //cout<<states[index].size()<<endl;
    string maximum = states[index].begin()->first; 
    double max_prob = states[index].begin()->second;
    for(auto j: states[index]){
      if(j.second > max_prob){
	max_prob=j.second;
	maximum=j.first;
      }
    }
    store.emplace_back(maximum);
    states.emplace_back(module);
    index+=1;
  }
}

bool HMM::valid(){
  return trans.size() && emission.size() && state.size() && module.size() && shown.size() && hidden.size();
}

void HMM::clear(){
  trans.erase(trans.begin(),trans.end());
  emission.erase(emission.begin(),emission.end());
  state.erase(state.begin(),state.end());
  module.erase(module.begin(),module.end());
  hidden.erase(hidden.begin(),hidden.end());
  shown.erase(shown.begin(),shown.end());
}

void HMM::generateHS(){
  if(emission.size()){
    bool already=false;
    for(auto i: emission){
      hidden.emplace_back(i.first);
      if(!already){
	for(auto j: i.second){
	  shown.emplace_back(j.first);
	}
      }
    }
  }
}

void HMM::generateM(){
  if(trans.size()){
    if(!module.size()){
      module.erase(module.begin(),module.end());
    }
    for(auto i: trans){
      module[i.first]=0.0;
    }
  }
}

void HMM::generateTE(){
  if(!emission.size() && !trans.size()){
    // the emission block
    map<string,double> block;
    for(string i: shown){
      block[i]=0.0;
    }
    // the trans block
    map<string, double> block1;
    for(string i: hidden){
      block[i]=0.0;
      // set the emission
      emission[i]=block;
    }
    // set the trans
    for(string i: hidden){
      trans[i]=block1;
    }
    generateM();
  }// add throw later on
}
//public:

HMM::HMM(map<string, map<string ,double>> &trans,
    map<string, map<string ,double>> &emission,
    map<string, double> &state):
  trans{trans},
  emission{emission},
  state{state}
{
  map<string, double> block;
  // generate module
  // put trans keys to hidden
  // put emission subkeys to shown
  generateHS();
  generateM();
}

void HMM::setHiddenToEmit(std::vector<std::vector<std::string>> &v){
  if(this->valid()){
    this->clear();
  }
  if(v.size()>=2){
    hidden=v[0];
    shown=v[1];
  }
  generateTE();
}

void HMM::setTrans(map<string,map<string,double>> &t){
  trans = t;
  generateHS();
  generateM();
}

void HMM::setEmission(map<string, map<string,double>> &e){
  emission = e;
  generateHS();
}

void HMM::setState(map<string, double> &s){
  state = s;
}

double HMM::evaluate(vector<string> &obs)
{
  vector<map<string,double>> states;
  states.emplace_back(state);
  int index = 0;
  double prob = 1.0;
  forwardAlg(obs,states,prob,index);
  return prob;
}

double HMM::evaluate(vector<string> &obs, vector<string> &target){
  vector<map<string,double>> states;
  states.emplace_back(state);
  int index = 0;
  double prob = 1.0;
  forwardAlg(obs,states,prob,index);
  if(target.size()){
    double store = prob;
    forwardAlg(target, states, prob, index);
    prob = prob/store;
  }
  return prob;
}

void HMM::decode(vector<string> &v, vector<string> &store){
  vector<map<string,double>> states;
  for(auto i: trans){
    cout<<i.first<<":"<<endl<<"    ";
    for(auto j: i.second){
      cout<<j.first<<": "<<j.second<<"   ";
    }
    cout<<endl;
  }
  states.emplace_back(state);
  int index = 0;
  viterbiAlg(v,store,states,index);
}

void HMM::setTrans(string &last, string &cur, double prob){
  cout<<"("<<last<<", "<<cur<<")"<<endl;
  if(trans.size()){
    trans[last][cur]=prob;
  }
}

void HMM::setEmission(string &hide, string &show, double prob){
  if(emission.size()){
    emission[hide][show] = prob;
  }
}

void HMM::setState(string &hide, double prob){
  cout<<"set state"<<endl;
  if(module.size() && !state.size()){
    state=module;
  }
  state[hide]=prob;
}
