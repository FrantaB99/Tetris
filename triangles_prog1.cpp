#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>

void SUS_converter (double *x_p, double *y_p, double *z_p)
{

  *y_p = *y_p * M_PI / 180;
  *y_p = *x_p * *x_p + *z_p * *z_p - 2 * *x_p * *z_p * cos (*y_p);
  *y_p = sqrt (*y_p);
}

void USU_converter (double *x_p, double *y_p, double *z_p)
{
  *x_p = *x_p * M_PI / 180;
  *z_p = *z_p * M_PI / 180;
  double beta = M_PI - *x_p - *z_p;
  *x_p = (*y_p * sin (*x_p)) / sin (beta);
  *z_p = (*y_p * sin (*z_p)) / sin (beta);
}

int is_it_triangle (double a, double b, double c);
void reshuffle (double *ap, double *bp, double *cp);
void compare (double a, double b, double c, double a2, double b2, double b3);

struct triangle 
{
  double a;
  double b;
  double c;
};

int main ()
{
  struct triangle t1;
  char theorem[10];
  if (scanf ("%s %lf %lf %lf", theorem, &t1.a, &t1.b, &t1.c) != 4 || 
             t1.a <= 0 || t1.b <= 0 || t1.c <= 0)
  {
    printf ("Nespravny vstup.\n");
    return 1;
  }
  if (strcmp (theorem, "SUS") == 0)
  {
    if (t1.b >= 180)
    {
      printf ("Strany netvori trojuhelenik.\n");
      return 1;
    }
    SUS_converter (&t1.a, &t1.b, &t1.c);
  }
  else if (strcmp (theorem, "USU") == 0)
  {
    if (t1.a + t1.b >= 180)
    {
      printf ("Strany netvori trojhelnik.\n");
      return 1;
    }
    USU_converter (&t1.a, &t1.b, &t1.c);
  }
  if (is_it_triangle (t1.a, t1.b, t1.c))
  {
    printf ("Strany netvori trojuhelnik.\n");
    return 1;
  }
  struct triangle t2;
  if (scanf ("%s %lf %lf %lf", theorem, &t2.a, &t2.b, &t2.c) != 4 ||
      t2.a <= 0 || t2.b <= 0 ||  t2.c <= 0)
  {
    printf ("Nespravny vstup.\n");
    return 1;
  }
  if (strcmp (theorem, "SUS") == 0)
  {
    if (t2.b >= 180)
    {
      printf ("Strany netvori trojuhelenik.\n");
      return 1;
    }
    SUS_converter (&t2.a, &t2.b, &t2.c);
  }
  else if (strcmp (theorem, "USU") == 0)
  {
    if (t2.a + t2.b >= 180)
    {
      printf ("Strany netvori trojhelnik.\n");
      return 1;
    }
    USU_converter (&t2.a, &t2.b, &t2.c);
  }
  if (is_it_triangle (t2.a, t2.b, t2.c))
  {
    printf ("Strany netvori trojuhelnik.\n");
    return 1;
  }
  compare (t1.a, t1.b, t1.c, t2.a, t2.b, t2.c);
  printf ("%f %f %f %f %f %f\n", t1.a, t1.b, t1.c, t2.a, t2.b, t2.c);
  return 0;
}


int is_it_triangle (double a, double b, double c)
{
  reshuffle(&a, &b, &c);
  if (a + b > c)
    return 0;
  else
    return 1;
}

void reshuffle (double *ap, double *bp, double *cp)
{
  double tmp;
  if (*bp <= *ap && *bp <= *cp)
  {
    tmp = *ap;
    *ap = *bp;
    *bp = tmp;
  } 
  else if (*cp <= *ap)
  {
    tmp = *ap;
    *ap = *cp;
    *cp = tmp;
  }
  if (*ap >= *bp && *ap >= *cp)
  {
    tmp = *cp;
    *cp = *ap;
    *ap = tmp;
  } 
  else if (*bp >= *cp)
  {
    tmp = *cp;
    *cp = *bp;
    *bp = tmp;
  }
}

void compare (double a, double b, double c, double a2, double b2, double c2)
{
  reshuffle (&a, &b, &c);
  reshuffle (&a2, &b2, &c2);
  if (a == a2 && b == b2 && c == c2)
    printf ("Trojuhelniky jsou shodne.\n");
  else if (fabs (a / a2 + b / b2 - 2 * c / c2) < DBL_EPSILON * 100 * c / c2)
    printf ("Trojuhelniky nejsou shodne, ale jsou podobne.\n"); 
  else
    printf ("Trojuhelniky nejsou shodne ani podobne.\n");
}

