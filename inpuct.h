double inpact::carculate(three* vz)
{
	if (vz->od != " ")
	{
		if (vz->od == "+")
		{
			cout << carculate(vz->right) + carculate(vz->left);
			return carculate(vz->right) + carculate(vz->left);
		}
		if (vz->od == "-")
			return carculate(vz->right) - carculate(vz->left);
		if (vz->od == "*")
		{
			double r = carculate(vz->right);
			cout << r;
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
			return carculate(vz->right) < carculate(vz->left);
	}
	else if (vz->od == " ")
		return vz->R;
	return 0;
}