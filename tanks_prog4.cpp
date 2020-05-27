#include <stdio.h>
#include <stdlib.h>

void scanf_array(int **array_pp, int size)
{
	*array_pp = (int *)malloc(size * sizeof(int));
	for(int i = 0; i < size; i++)
	{
		scanf("%d", &(*array_pp)[i]);	 
	}
}

void printf_array(int *array_p, int size)
{
	for(int i = 0; i < size; i++)
	{
		printf("%d ", array_p[i]);
	}
	printf("\n");
}

void scanf_steps(int *tanks_p, int **steps_pp, int size)
{
	*steps_pp = (int *)malloc(size * 4 * sizeof(int));
	int k = 0;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			(*steps_pp)[k] = tanks_p[(4 * i) + j];
			k++;
		}	 
	}
}

void bubble_sort(int *array_p, int size)
{
	for(int i = 0; i < size - 1; i++)
	{
		for(int j = 0; j < size - 1 - i; j++)
		{
			if(array_p[j + 1] < array_p[j])
			{
				int tmp = array_p[j + 1];
				array_p[j + 1] = array_p[j];
				array_p[j] = tmp;
			}
		}
	}
}

void duplicate_remover(int *array_p, int *size)
{
	for(int i = 0; i < *size - 1; i++)
	{
		for(int j = i + 1; j < *size; j++)
		{
			if(array_p[i] == array_p[j])
			{
				for(int k = j; k < *size - 1; k++)
				{
					array_p[k] = array_p[k + 1];
				}
				j--;
				*size = *size - 1;
			}
		}
	}	
}

void height_adjust(int *tanks_p, int size1)
{
	for(int i = 0; i < size1; i++)
	{
		tanks_p[4 * i + 1] = tanks_p[4 * i] + tanks_p[4 * i + 1];
	}
}

int main()
{
	int *tanks_p, size, *steps_p;
	double water;
	scanf("%d", &size);
	scanf("%lf", &water);
	int size1 = 4 * size;
	int size2 = 2 * size;
	scanf_array(&tanks_p, size1);
	height_adjust(tanks_p, size1);
	printf_array(tanks_p, size1);
	scanf_steps(tanks_p, &steps_p, size);
	bubble_sort(steps_p, size2);
	duplicate_remover(steps_p, &size2);
	printf_array(steps_p, size2);
	int total = 0;
	for(int i = 0; i < size2 - 1; i++)
	{
		int level = 0;
		for(int j = 0; j < size; j++)
		{
			if(steps_p[i + 1] <= tanks_p[4 * j + 1] &&
				steps_p[i + 1] > tanks_p[4 * j])
			{
				int tank = (steps_p[i + 1] - steps_p[i]) * tanks_p[4 * j + 2] *
					tanks_p[4 * j + 3];
				level += tank;
				total += tank;
			}
		}
		if((water = water - level) < 0)
		{
			water += level;
			double height = (water * 1.0 / level) * (steps_p[i + 1] - steps_p[i]) +
				steps_p[i];
			printf("voda se zastavi ve %f metrech\n", height);
			break;
		}
		if(water == 0)
		{
			printf("voda se astavi ve %d metrech\n", steps_p[i + 1]);
			break;
		}
		else if(i == size2 - 2 && water > 0)
		{
			printf("voda se preleje\n");
		}	
	}
	return 0;
}



















































