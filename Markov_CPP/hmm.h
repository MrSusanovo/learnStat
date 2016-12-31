#ifndef __HMM_H__
#define __HMM_H__

#include <map>
#include <vector>
#include <string>

class HMM{
  std::map<std::string, std::map<std::string,double>> trans;
  std::map<std::string, std::map<std::string,double>> emission;
  std::map<std::string, double> state;
  std::map<std::string, double> module;
  std::vector<std::string> hidden;
  std::vector<std::string> shown;
  void forwardAlg(std::vector<std::string> &,
		  std::vector<std::map<std::string, double>> &,
		  double &, int &);
  void viterbiAlg(std::vector<std::string> &,
		  std::vector<std::string> &,
		  std::vector<std::map<std::string, double>> &,int &);
  void clear();
  bool valid();
  void generateHS();
  void generateTE();
  void generateM();
 public:
  HMM(std::map<std::string, std::map<std::string ,double>> &,
      std::map<std::string, std::map<std::string ,double>> &,
      std::map<std::string, double> &);
  HMM() = default;
  void setHiddenToEmit(std::vector<std::vector<std::string>> &);
  void setTrans(std::map<std::string, std::map<std::string,double>> &);
  void setEmission(std::map<std::string, std::map<std::string,double>> &);
  void setState(std::map<std::string, double> &);
  double evaluate(std::vector<std::string> &, std::vector<std::string> &);
  double evaluate(std::vector<std::string> &);
  void decode(std::vector<std::string> &, std::vector<std::string> &);
  void setTrans(std::string &,std::string &,double);
  void setEmission(std::string &,std::string &, double);
  void setState(std::string &,double);
};

#endif
