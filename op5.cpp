#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <unordered_map>
#include <stack>
using namespace std;
typedef std::unordered_map<string, double>  hash_map;

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
		left = right = NULL;
	}
};

class inpact
{
	three d;
	string q;
	hash_map pl;
	stack <string> op;
	stack <three> ger;
public:
	inpact(string t);
	int GetPriority(string);
	void pp(string);
	void po();
	void point(three*);
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
		if (fic.eof())
			break;
		getline(fic, g, '\n');
		a = stod(g);
		pl.insert(pair <string, double>(h, a));
	}
	q = h.substr(0, h.size());
	buildtree();
}
void inpact::pp(string tt)
{
	string r;
	three *a = new three, *b = new three, *c = new three;
	r = op.top();
	op.pop();
	*a = ger.top();
	ger.pop();
	*b = ger.top();
	ger.pop();
	c->od = r;
	c->left = a;
	c->right = b;
	ger.push(*c);
	op.push(tt);

};

void inpact::po()
{
	string r;
	three *a = new three, *b = new three, *c = new three;
	r = op.top();
	op.pop();
	*a = ger.top();
	ger.pop();
	*b = ger.top();
	ger.pop();
	
	c->od = r;
	c->left = a;
	c->right = b;


	ger.push(*c);
}
int inpact::GetPriority(string cur_operator)
{
	if (cur_operator == "+" || cur_operator == "-")
		return 2;
	if (cur_operator == "*" || cur_operator == "/")
		return 3;
	if (cur_operator == "==" || cur_operator == "!=" || cur_operator == "<=" || cur_operator == ">=" || cur_operator == ">" || cur_operator == "<")
		return 1;
	if (cur_operator == "^")
		return 4;
	if (cur_operator == "if" || cur_operator == "~")
		return 5;
	return 0;
}
void inpact::buildtree()
{
	string r;
	string to="";
	for (int i = 0; i < q.size(); i++)
	{
		if (q[i] == 'I' && q[i + 1] == 'F')
		{
			r = "IF";
			op.push(r);
			r = "~";
			op.push(r);
			i++;
		}
		else if (q[i] == '(')
		{
			r = q[i];
			op.push(r);
		}
		else if ( q[i] == '+' || q[i] == '-' || q[i] == '*' || q[i] == '/' || q[i] == '^' || (q[i] == '<' && q[i + 1] != '=') || (q[i] == '>' && q[i + 1] != '='))
		{
			r = q[i];
			if (op.empty() || GetPriority(r) > GetPriority(op.top()))
				op.push(r);
			else
				pp(r);
			r.clear();
		}
		else if ((q[i] == '<' && q[i + 1] == '=') || (q[i] == '>' && q[i + 1] == '=') || (q[i] == '=' && q[i + 1] == '=') || (q[i] == '!' && q[i + 1] == '='))
		{
			r = q[i];
			r += q[i + 1];
			if (op.empty() || GetPriority(r) > GetPriority(op.top()))
				op.push(r);
			else
				pp(r);
			i++;
			r.clear();
		}
		else if (q[i] == ')')
		{
			while (op.top() != "(" || op.empty())
			{
				po();
			}
			op.pop();
			r.clear();
		}
		else
		{
			double f;
			if (q[i] == ' ')
				continue;
			to += q[i];
			if (q[i + 1] == ')' || q[i + 1] == '(' || q[i + 1] == '+' || q[i + 1] == '-' || q[i + 1] == '*' || q[i + 1] == '/' || q[i + 1] == '^' || q[i + 1] == '<' || q[i + 1] == '>' || i == q.size() - 1)
			{
				if (pl.find(to) != pl.end())
				{
					f = pl.find(to)->second;
				}
				else
					f = stod(to);
				to.clear();
				three c;
				c.R = f;
				ger.push(c);
			}
		}
	}
	while (!op.empty())
	{
		po();
	}
	d = ger.top();
}
double inpact::calculate()
{
	point(&d);
	return carculate(&d);
}
void inpact::point(three* vz)
{
	if (vz->R != 1000000)
		return;
	point(vz->left);
	point(vz->right);
	return;
}
double inpact::carculate(three* vz)
{
	if (vz->od != " ")
	{
		if (vz->od == "+")
		{
			return carculate(vz->right) + carculate(vz->left);
		}
		if (vz->od == "-")
			return carculate(vz->right) - carculate(vz->left);
		if (vz->od == "*")
		{

			double r = carculate(vz->right);
			if (r == 0)
				return 0;
			else
				return r * carculate(vz->left);
		}
		if (vz->od == "/")
		{
			double r = carculate(vz->right);
			if (r == 0)
				return 0;
			else
				return r / carculate(vz->left);
		}
		if (vz->od == "^")
		{
			double l = carculate(vz->left);
			if (l == 0)
				return 1;
			else
				return pow(carculate(vz->right), l);
		}
		if (vz->od == "IF")
		{
			if (carculate(vz->right) == 1)
				return carculate(vz->left->right);
			else
				return carculate(vz->left->left);
		}
		if (vz->od == "==")
			return carculate(vz->right) == carculate(vz->left);
		if (vz->od == "!=")
			return carculate(vz->right) != carculate(vz->left);
		if (vz->od == ">=")
			return carculate(vz->right) >= carculate(vz->left);
		if (vz->od == "<=")
			return carculate(vz->right) <= carculate(vz->left);
		if (vz->od == ">")
			return carculate(vz->right) > carculate(vz->left);
		if (vz->od == "<")
		{
			return carculate(vz->right) < carculate(vz->left);
		}
	}
	else if (vz->od == " ")
	{
		return vz->R;
	}
	return 0;
}

int main()
{
	inpact r("input.txt");
	double q = r.calculate();
	cout << endl << "q =  " << q << endl;
	return 0;
}