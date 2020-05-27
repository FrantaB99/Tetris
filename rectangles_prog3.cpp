#include <stdio.h>
#define RECT_NO_OVERLAP 0
#define RECT_OVERLAP    1
#define RECT_A_IN_B     2
#define RECT_B_IN_A     3
#define RECT_ERROR    (-1)

void sorter(int *ax, int *ay, int *bx, int *by)
{
	int tmp;
	if(*bx < *ax)
	{
		tmp = *ax;
		*ax = *bx;
		*bx = tmp;
	}
	if(*by < *ay)
	{
		tmp = *ay;
		*ay = *by;
		*by = tmp;
	}
}

int rectangle_position(int ax1, int ay1, int bx1, int by1,
	int ax2, int ay2, int bx2, int by2)
{
	sorter(&ax1, &ay1, &bx1, &by1);
	sorter(&ax2, &ay2, &bx2, &by2);
	if(ax1 == bx1 || ay1 == by1 ||
		ax2 == bx2 || ay2 == by2)
	{
		return RECT_ERROR;
	}
	else if(ax1 > ax2 && bx1 < bx2 &&
		ay1 > ay2 && by1 < by2)
	{
		return RECT_A_IN_B;
	}
	else if(ax1 < ax2 && bx1 > bx2 &&
		ay1 < ay2 && by1 > by2)
	{
		return RECT_B_IN_A;
	}
	else if(bx1 <= ax2 || ax1 >= bx2 ||
		ay1 >= by2 || by1 <= ay2)
	{
		return RECT_NO_OVERLAP;
	}
	else
	{
		return RECT_OVERLAP;
	}
}

int main()
{
	int ax1, ay1, bx1, by1, ax2, ay2, bx2, by2;
	scanf("%d %d %d %d %d %d %d %d", &ax1, &ay1, &bx1, &by1, &ax2, &ay2, &bx2, &by2);
	printf("%d\n", rectangle_position(ax1, ay1, bx1, by1, ax2, ay2, bx2, by2));
	return 0;	
}

























