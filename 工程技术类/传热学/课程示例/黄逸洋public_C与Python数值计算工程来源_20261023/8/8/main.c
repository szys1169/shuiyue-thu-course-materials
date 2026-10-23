//
//  main.c
//  8
//
//  Created by sure on 14-12-31.
//  Copyright (c) 2014年 sure. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X_NUM 4
#define Y_NUM 6
const double dx=0.08;
const double dy=0.08;
const double h=40.0;
const double qw=1500.0;
const double lambda=45.0;
const double tf=25.0;
const double tw=200.0;

double t[X_NUM][Y_NUM];
void Initialize(double (*t)[Y_NUM],double t0);
double Max(double a,double b);
void PrintT(double (*t)[Y_NUM]);
double ComputeT(int i,int j);
void Inside(int i,int j,double *delta);
void Top(int t,int i,double *delta);
void Bottom(int b,int i,double *delta);
void Left(int l,int j,double *delta);
void Right(int r,int j,double *delta);
void TLcorner(int i,int j,double *delta);
void TRcorner(int i,int j,double *delta);
void BLcorner(int i,int j,double *delta);
void BRcorner(int i,int j,double *delta);



void Initialize(double (*t)[Y_NUM],double t0)
{
    int i;
    int j;
    for(j=0;j<Y_NUM;j++){
        for(i=0;i<X_NUM;i++){
            t[i][j]=t0;
        }
    }
}


void PrintT(double (*t)[Y_NUM])
{
    int i;
    int j;
    for(j=0;j<Y_NUM;j++){
        for(i=0;i<X_NUM;i++){
            printf("%-13.4lf ",t[i][j]);
        }
        printf("\n");
    }
}

double ComputeT(int i,int j)
{
    double n=0;
    double *delta=&n;
    if(i==0)
    {
        if(j==0){  TLcorner(i,j,delta);}
        else if(j==Y_NUM-1){ BLcorner(i,j,delta);}
        else{ Left(i,j,delta); }
    }
    else if(i==X_NUM-1)
    {
        if(j==0){
            TRcorner(i,j,delta);
        }else if(j==Y_NUM-1){
            BRcorner(i,j,delta);
        }else{
            Right(i,j,delta);
        }
    }
    else if(j==0) { Top(i,j,delta); }
    else if(j==Y_NUM-1) {  Bottom(i,j,delta);}
    else{ Inside(i,j,delta);
    }
    return *delta;
}
double Max(double a,double b)
{
    if(a>b){
        return a;
    }else{
        return b;
    }
}



void Inside(int i,int j,double *delta)
{
    double temp=(t[i+1][j]+t[i-1][j]+t[i][j+1]+t[i][j-1])/4;
    *delta=fabs(temp-t[i][j])/t[i][j];
    t[i][j]=temp;
}

void Top(int i,int j,double *delta)
{
    t[i][j]=tw;
    *delta=0;
}

void Bottom(int i,int j,double *delta)
{
    double temp=((dx/dy)*t[i][j-1]+(dy/dx)*(t[i-1][j]+t[i+1][j])/2+qw*dx/lambda)/((dx/dy)+(dy/dx));
    *delta=fabs(temp-t[i][j])/t[i][j];
    t[i][j]=temp;
}

void Left(int i,int j,double *delta)
{
    double temp=((dx/dy)*(t[i][j+1]+t[i][j-1])/2+(dy/dx)*t[i+1][j])/((dx/dy)+(dy/dx));
    *delta=fabs(temp-t[i][j])/t[i][j];
    t[i][j]=temp;
}

void Right(int i,int j,double *delta)
{
    double temp=((dy/dx)*t[i-1][j]+(dx/dy)*(t[i][j+1]+t[i][j-1])/2+h*tf*dy/lambda)/((dx/dy)+(dy/dx)+(h*dy/lambda));
    *delta=fabs(temp-t[i][j])/t[i][j];
    t[i][j]=temp;
}

void TLcorner(int i,int j,double *delta)
{
    t[i][j]=tw;
    *delta=0;
}

void TRcorner(int i,int j,double *delta)
{
    t[i][j]=tw;
    *delta=0;
}

void BLcorner(int i,int j,double *delta)
{
    double temp=((dy/dx)*t[i+1][j]+(dx/dy)*t[i][j-1]+qw*dx/lambda)/((dx/dy)+(dy/dx));
    *delta=fabs(temp-t[i][j])/t[i][j];
    t[i][j]=temp;
}

void BRcorner(int i,int j,double *delta)
{
    double temp=((dy/dx)*t[i-1][j]+(dx/dy)*t[i][j-1]+qw*dx/lambda+h*dy*tf/lambda)/((dx/dy)+(dy/dx)+h*dy/lambda);
    *delta=fabs(temp-t[i][j])/t[i][j];
    t[i][j]=temp;
}

int main()
{
    double t0=200.0;
    int count0=1000;
    double delta0=0.0001;
    double delta=0;
    int count=0;
    int i;
    int j;
    int accomplish=0;
    Initialize(&t[0],t0);
    PrintT(&t[0]);
    while(count<count0&&accomplish==0)
    {
        for(j=0;j<Y_NUM;j++)
        {
            for(i=0;i<X_NUM;i++)
            {
                if(i==0&&j==0){ delta=ComputeT(i,j);}
                else{ delta=Max(ComputeT(i,j),delta);}
            }
        }
        count++;
        printf("\ndiedaicishu%d:\n\n",count);
        PrintT(&t[0]);
        if(delta<delta0)
        {
            accomplish=1;
        }
    }
    if(accomplish==0){printf("\nbushoulian.\n");}
    else{printf("\njisuanwanchengdiedai%dci.\n",count);
        printf("\njieguoruxia:\n");
        
        
        PrintT(&t[0]);
    }
    getchar();
    fflush(stdin);
    return 0;
}

