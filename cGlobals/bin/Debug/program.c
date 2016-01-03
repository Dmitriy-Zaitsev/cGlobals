#include <math.h>
#include <stdio.h>
#define sign(x) (x == 0 ? 0 : (x < 0 ? -1 : 1))
const double pi=0.3989422804014;
int N;

double I(double x, double eps)
{
   double t=x, sum=t, x2=x*x, s=0;
   int n;
   N=0;
   for(n=2; fabs(s-sum) > eps; n+=2)
   {
	  t*=-x2/n; s=sum; sum+=t/(n+1);
	  N++;
   }
   return 0.5+sum*pi;
}

double T(double x, double eps)
{
   double t=x, sum=t, x2=x*x, s=0;
   int n;
   N=0;
   for(n=3; fabs(s-sum) > eps; n+=2)
   {
	  t*=x2/n; s=sum; sum+=t;
	  N++;
   }
   return 0.5+sign(x)*sum*exp(-x2/2.)*pi;
}

double S(double x, double eps)
{
   double x2=x*x, rho=1./(3.-x2), sum=fabs(x)*rho, term=x2*sum, t=0, s;
   int n;
   N=0;
   rho*=3.; s=(sum*=3.);
   for(n=2; (x2<0) || ((fabs(s-t) > eps) ||
					   (fabs(s-sum) > eps)); n++)
   {
	  rho = 1./(1.+rho*x2*n/(4.*n*n-1));
	  term*=rho-1; t=s; s=sum; sum+=term;
	  x2=-x2;
	  N++;
   }
   return 0.5+sign(x)*sum*exp(-x2/2.)*pi;
}

double L(double x, double eps)
{
   double x2=x*x, y=exp(-x2/2.)*pi, sum, term, r, rho, t, s;
   N=0;
   if (x == 0) return 0.5;
   x2=1./x2; term=sum=y/fabs(x); r=s=0; rho=1;
   do
   {
	  r+=x2; rho=1./(1+r*rho); term*=rho-1;
	  t=s; s=sum; sum+=term;
	  N++;
   }
   while(fabs(s-t) > eps || fabs(s-sum) > eps);
   return (x > 0 ? 1-sum : sum);
}

void main(void)
{
   double x;
   double f;
   for(x=0.25; x<8; x+=0.25)
   {
#if TABLE
	  printf("\n  %4.2f", x);
	  f = I(x,0);
	  printf("\t%d\t%d", N, 8+11*N);
	  f = T(x,0);
	  printf("\t%d\t%d", N, 14+8*N);
	  f = S(x,0);
	  printf("\t%d\t%d", N, 23+25*N);
	  f = L(x,0);
	  printf("\t%d\t%d", N, 16+10*N);
#else
	  f = I(x,0);
	  printf("\nI(%4.2f)=%10.8g\t%d\t%d", x, f,N,8+11*N);
	  f = T(x,0);
	  printf("\nT(%4.2f)=%10.8g\t%d\t%d", x, f,N,14+8*N);
	  f = S(x,0);
	  printf("\nS(%4.2f)=%10.8g\t%d\t%d", x, f,N,23+25*N);
	  f = L(x,0);
	  printf("\nL(%4.2f)=%10.8g\t%d\t%d", x, f,N,16+10*N);
#endif
   }
}