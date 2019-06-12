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
		left = &p.left;
		right = &p.right;
	}
	three()
	{
		od = " ";
		R = 1000000;
		left=right=NULL;
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
	inpact (string t);
	three plut(three, three, string);
	int GetPriority(string);
	void pp(string);
	three po();
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
		pl.insert(pair <string, double> (h, a));
	}
	q = h.substr(0, h.size());
	buildtree();
}
void inpact::pp(string tt)
{
				string r;
				three a, b, c;
				r = op.top();
				op.pop();
				a = ger.top();
				ger.pop();
				b = ger.top();
				ger.pop();
				c = plut(a, b, r);
				cout << c.od;
				ger.push(c);
				op.push(tt);

		};
three inpact::po()
{
				string r;
				three a, b, c;
				r = op.top();
				op.pop();
				a = ger.top();
				ger.pop();
				b = ger.top();
				ger.pop();
				c = plut(a, b, r);
				cout << c.od << " "<< c.R << " "<< c.left->R << " " << c.right->R << " " <<c.right->od<< " "  << c.left->od << endl;
				ger.push(c);
				return c;
		};
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
three inpact::plut(three a, three b, string r)
{
	three c;
	c.od = r;
	c.R = 100000;
	// if(a.left==NULL)
	// 	a.od=" ";
	// if(a.right==NULL)
	// 	a.od=" ";
	// if(b.left==NULL)
	// 	b.od=" ";
	// if(b.right==NULL)
	// 	b.od=" ";
	c.left = &a;
	c.right = &b;
	return c;
}
void inpact::buildtree()
{
	string r;
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
		else if (q[i] == '(' || q[i] == '+' || q[i] == '-' || q[i] == '*' || q[i] == '/' || q[i] == '^' || (q[i] == '<' && q[i + 1] != '=') || (q[i] == '>' && q[i + 1] != '='))
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
			r += q[i];
			if (q[i + 1] == ')' || q[i + 1] == '(' || q[i + 1] == '+' || q[i + 1] == '-' || q[i + 1] == '*' || q[i + 1] == '/' || q[i + 1] == '^' || q[i + 1] == '<' || q[i + 1] == '>'||i==q.size()-1)
			{
				if (pl.find(r) != pl.end())
				{f = pl.find(r)->second;}
				else
					f = stod(r);
				three c;
				c.left = c.right = NULL;
				c.R = f;
				c.od=" ";
				r.clear();
				ger.push(c);
			}
		}
	}
	while (!op.empty())
	{
		d=po();
	}
//	d = ger.top();
	cout << d.od << " "<< d.R << d.left->R << " " << d.right->R << endl;

}
double inpact::calculate()
{
	return carculate(&d);
}
double inpact::carculate(three* vz)
{
	if (vz->od != " ")
	{
		if (vz->od == "+")
		{
			cout << "kb";
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
				return r *carculate(vz->left);
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
			return carculate(vz->right) < carculate(vz->left);
	}
	else if (vz->R != 1000000)
	{
		cout <<vz->R << "|";
		return vz->R;
	}
	return 1;
}