#ifndef __MARKOV_H__
#define __MARKOV_H__

#include <fstream>
#include <map>
#include <string>

class Markov{
  std::map<std::string,double> state;
  std::map<std::string,std::map<std::string,double>> trans;
  std::string last;
 public:
  std::string predict(std::string s="");
  void feed(std::string s);
  void feed(std::ifstream file);
  void getState();
  void getTrans();
};
  
#endif
