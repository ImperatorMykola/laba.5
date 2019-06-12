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
  three plut(three, three, string);
  int GetPriority(string);
  void buildtree();
  double calculate();
  double carculate(three*);
};

inpact::inpact(string t)
{
  ifstream fic(t);
  string h, g;
  double a;
  while (!fic.eof())
  {
    getline(fic, h, '=');
    if (h[h.size() - 1] == ';')
      break;
    getline(fic, g, '\n');
    a = stod(g);
    pl.insert(pair <string, double> (h, a));
  }
  q = h.substr(0, h.size() - 1);
  buildtree();
}
