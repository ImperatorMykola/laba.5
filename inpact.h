three inpact::plut(three a, three b, string r)
{
	three c;
	c.od = r;
	c.R = 100000;
	c.left = &a;
	c.right = &b;
	return c;
}
void inpact::buildtree()
{
	stack <string> op;
	stack <three> ger;
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
			{
				three a, b, c;
				r = op.top();
				op.pop();
				a = ger.top();
				ger.pop();
				b = ger.top();
				ger.pop();
				c = plut(a, b, r);
				ger.push(c);
				r = q[i];
				op.push(r);
			}
			r.clear();
		}
		else if ((q[i] == '<' && q[i + 1] == '=') || (q[i] == '>' && q[i + 1] == '=') || (q[i] == '=' && q[i + 1] == '=') || (q[i] == '!' && q[i + 1] == '='))
		{
			r = q[i];
			r += q[i + 1];
			if (op.empty() || GetPriority(r) < GetPriority(op.top()))
				op.push(r);
			else
			{
				three a, b, c;
				r = op.top();
				op.pop();
				a = ger.top();
				ger.pop();
				b = ger.top();
				ger.pop();
				c = plut(a, b, r);
				ger.push(c);
				r = q[i];
				r += q[i + 1];
				op.push(r);
			}
			i++;
			r.clear();
		}
		else if (q[i] == ')')
		{
			while (op.top() != "(" || op.empty())
			{
				three a, b, c;
				r = op.top();
				op.pop();
				a = ger.top();
				ger.pop();
				b = ger.top();
				ger.pop();
				c = plut(a, b, r);
				ger.push(c);
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
				ger.push(c);
			}
		}
	}
	while (!op.empty())
	{
		three a, b, c;
		r = op.top();
		op.pop();
		a = ger.top();
		ger.pop();
		b = ger.top();
		ger.pop();
		cout << a.R << a.od << b.R << b.od;
		c = plut(a, b, r);
		ger.push(c);
	}
	d = ger.top();
}
