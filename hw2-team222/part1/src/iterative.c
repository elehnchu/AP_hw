

int gcd_iterative(int m, int n)
{
	int gcd; 
	int remainder; 
	
	if(m==0)
	{
		return(n);
	}
	else if(n==0)
	{
		return (m);
	}
	else 
	{
		while(n!=0)
		{
			remainder=m%n;
			m=n;
			n=remainder;
		}
		gcd=m;
	}
	return (gcd);
}
