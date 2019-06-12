#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef std::unordered_map<std::string, double>  hash_map;

struct three
{
  string od;
  double R;
  three* left;
  three* right;
  void operator=(three p)
  {
    od = p.od;
    R = p.R;
    left = p.left;
    right = p.right;
  }
  three()
  {
    od = " ";
    R = 1000000;
  }
};

class inpact
{
  three d;
  string q;
  hash_map pl;
public:
  inpact (string t);
  /*three plut(three, three, string);
  int GetPriority(string);
  void buildtree();
  double calculate();
  double carculate(three*);*/
};
