#include <stdio.h>

void temp (double x);

int main ()
{
  double x;
  scanf ("%lf", &x);
  temp (x);
  return 0;
}

void temp (double x)
{
  double K, C, F;
  C = x;
  K = C + 273.15;
  F = 9.0 / 5.0 * C + 32;
  printf ("\\/\\/\\/\\   °C       K      °F\n"
          "  °C    %7.2f %7.2f %7.2f\n", C, K, F);
  K = x;
  C = K - 273.15;
  F = 9.0 / 5.0 * K - 459.67;
  printf ("   K    %7.2f %7.2f %7.2f\n", C, K, F);
  F = x;
  C = 5.0 / 9.0 * F - 160.0 / 9.0;
  K = 5.0 / 9.0 * F + 2298.35 / 9.0;
  printf ("  °F    %7.2f %7.2f %7.2f\n", C, K, F);
}










































































