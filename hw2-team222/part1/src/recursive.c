

int gcd_recursive(int m, int n)
{
	int gcd;
	if(m==0)
	{
		gcd=n;
	}
	else if(n==0)
	{
		gcd=m;
	}
	else
	{
		gcd=gcd_recursive(n, m%n);
	}
	return (gcd);

}
