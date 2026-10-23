#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxN 1000
const double l=0.019;
const double t0=20.0;
const double tg=150.0;
const double tw=170.0;
const double lambda=0.156;
const double a=0.00000008;
const double dx=0.002;
const double dT=2.0;


void Initialize(double t[],int n);
double compute(double t[],double tformer[],int n,double fo);
double Left(double tformer[],int i,double fo);
double Right(double tformer[],int i,double fo);
double Middle(double tformer[],int i,double fo);
void printTemperature(double t[],int n,int count);


double compute(double t[],double tformer[],int n,double fo)
{
  int i;
  for(i=0;i<=n;i++){
    if(i==0){t[i]=Left(tformer,i,fo);}
    else if(i==n){t[i]=Right(tformer,i,fo);}
    else{t[i]=Middle(tformer,i,fo);}
  }
  return fabs(tg-t[n]);
}



double Left(double tformer[],int i,double fo)
{
  return tw;
}

double Right(double tformer[],int i,double fo){
  return 2*fo*tformer[i-1]+(1-2*fo)*tformer[i];
}
void printTemperature(double t[],int n,int count){
  int i;
  printf("\n\n迭代次数: %5d  时刻 ： %.2lfs\n",count,count*dT);
  for(i=0;i<=n;i++){
    printf("%.2lf ",t[i]);
  }
}

double Middle(double tformer[],int i,double fo){
  return fo*(tformer[i-1]+tformer[i+1])+(1-2*fo)*tformer[i];
}

int main(){
  int count=0;
  int n=(int)(l/dx);
  double t[MaxN];
  double tformer[MaxN];
  double delta=fabs(tg-t0);
  double delta0=0.01;
  double fo=a*dT/(dx*dx);

   if(fo>0.5){
    printf("Fo>0.5, 请重新确定dx和dT，不稳定.");
    getchar();
    exit(-1);
  }
  Initialize(t,n);
  while(delta>delta0){
   // (t,tformer,n);
  int i=0;
  for(i=0;i<=n;i++){
    tformer[i]=t[i];
  }
  delta=compute(t,tformer,n,fo);
    count++;
    printTemperature(t,n,count);
  }
  printf("\n 计算完成,结果如下:\n");
  printTemperature(t,n,count);
  getchar();
  return 0;
}

void Initialize(double t[],int n){
  int i;
  for(i=0;i<=n;i++){
    t[i]=t0;
   }
}


