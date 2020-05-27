#include <stdio.h>

int binnary_length (int x)
{
	int length = 0;
	if (x == 0)
		length = 1;
	while (x > 0)
	{
		x = x >> 1;
		length ++;
	}
	return length;
}

void printf_binnary (int x)
{
	int length = binnary_length (x);
	printf ("%d = ", x);
	for (int i = 0; i < length; i++)
	{
		printf ("%d", x >> (length - 1 - i) & 1);
	}
	printf ("b\n");
}

int symmetry (int x)
{
	int length = binnary_length (x);
	int not_symmetric = 0;
	for (int i = 0; i < length / 2; i++)
	{
		if ((x >> (length - 1 - i) & 1) != (x >> i & 1))
			not_symmetric = 1;
	}
	return not_symmetric;
}

void printf_interval (int x, int y)
{
	for (int i = x; i <= y; i++)
	{
		if (symmetry (i) == 0)
			printf_binnary (i); 
	}
}

int sum (int x, int y)
{
	int sum = 0;
	for (int i = x; i <= y; i++)
	{
		if (symmetry (i) == 0)
			sum++;
	}
	return sum;		
}

int main ()
{
	int x, y;
	char ch;
	printf ("Vstupni intervaly:\n"); 
	while (!feof (stdin))
	{
		if (scanf (" %c %d %d", &ch, &x, &y) != 3 ||
			(ch != 'l' && ch != 'c') ||
			x < 0 || y < 0 ||
			y < x)
		{
			printf ("Nespravny vstup\n");
			return 1;
		}
		if (ch == 'l')
			printf_interval (x, y);
		else
			printf ("Celkem: %d\n", sum (x, y));
	}	
	return 0;
}



























