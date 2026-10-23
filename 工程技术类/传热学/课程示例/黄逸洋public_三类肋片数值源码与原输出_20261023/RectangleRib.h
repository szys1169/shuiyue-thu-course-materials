#ifndef _RECTANGLERIB_
#define _RECTANGLERIB_

#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

class RectangleRib
{
public:
	public:
	double *T;
	double *T_last;
	double *A;
	double dx, dy, lambda, qw, h, tf;
	int N, M;

	void initialize();
	void setOriginalValue();
	void bulidEquation();
	void iteration();
	int f(int x, int y);
	void output(ofstream * out);
	double Quantity();
};

int RectangleRib::f(int x, int y)
{
	return (x - 1) * 148 + y;
}

void RectangleRib::initialize()
{
	dx = 0.001;
	dy = 0.001;
	lambda = 187;
	h = 2800;
	tf = 300;
	N = 21;
	M = 7;
	T = new double[(N + 1) * (M + 1)];
	T_last = new double[(N + 1) * (M + 1)];
	A = new double[(N + 2) * (M + 2) * (N + 2) * (M + 2)];
	for (int i = 1; i <= 147; i++)
	{
		T[i] = 300;
		T_last[i] = 0;
	}
};

void RectangleRib::bulidEquation()
{
	for (int i = 2; i <= 20; i++)
		for (int j = 2; j <= 6; j++)
		{
			int x = (j - 1) * 21 + i;
			for (int k = 1; k <= 148; k++)
				A[f(x,k)] = 0;
			A[f(x,x - 21)] = 1;
			A[f(x,x + 1)] = 1;
			A[f(x,x - 1)] = 1;
			A[f(x,x + 21)] = 1;
			A[f(x,x)] = -4;
		}

	for (int i = 1; i <= 7; i++)
	{
		int x = i * 21 - 20;
		for (int j = 1; j <= 148; j++)
			A[f(x,j)] = 0;
		A[f(x,x)] = 1;
		A[f(x,148)] = 500;
	}

	for (int i = 2; i <= 6; i++)
	{
		int x = i * 21;
		for (int j = 1; j <= 148; j++)
			A[f(x,j)] = 0;
		A[f(x,x + 21)] = 1;
		A[f(x,x - 21)] = 1;
		A[f(x,x + 1)] = 2;
		A[f(x,x)] = -(4 + 2 * h * dx / lambda);
		A[f(x,148)] = - 2 * h * dx / lambda * tf;
	}
	for (int i = 2; i <= 20; i++)
	{
		int x = i;
		for (int j = 1; j <= 148; j++)
			A[f(x,j)] = 0;
		A[f(x,x + 1)] = 1;
		A[f(x,x - 1)] = 1;
		A[f(x,x + 21)] = 2;
		A[f(x,x)] = -(4 + 2 * h * dx / lambda);
		A[f(x,148)] = - 2 * h * dx / lambda * tf;
		x = i + 126;
		for (int j = 1; j <= 148; j++)
			A[f(x,j)] = 0;
		A[f(x,x + 1)] = 1;
		A[f(x,x - 1)] = 1;
		A[f(x,x - 21)] = 2;
		A[f(x,x)] = -(4 + 2 * h * dx / lambda);
		A[f(x,148)] = - 2 * h * dx / lambda * tf;
	}
	int x = 21;
	for (int j = 1; j <= 148; j++)
		A[f(x,j)] = 0;
	A[f(x,x - 1)] = 1;
	A[f(x,x + 21)] = 1;
	A[f(x,x)] = - (2 + 2 * h * dx / lambda);
	A[f(x,148)] = - 2 * h * dx * tf / lambda; 
	x = 147;
	for (int j = 1; j <= 148; j++)
		A[f(x,j)] = 0;
	A[f(x,x - 1)] = 1;
	A[f(x,x - 21)] = 1;
	A[f(x,x)] = - (2 + 2 * h * dx / lambda);
	A[f(x,148)] = - 2 * h * dx * tf / lambda; 
}

void RectangleRib::iteration()
{
	bool flag = 1;
	for (int i = 1; i <= 147; i++)
		if (abs(T[i] - T_last[i]) > 0.01)
			flag = 0;
	if (flag)
		return;
	for (int i = 1; i <= 147; i++)
	{
		T_last[i] = T[i];
		T[i] = 0;
		for (int j = 1; j <= 147; j++)
			if (i != j)
				T[i] -= A[f(i,j)] * T_last[j];
		T[i] += A[f(i,148)];
		T[i] /= A[f(i,i)];
	}
	iteration();
}

double RectangleRib::Quantity()
{
	double temp = 0.0;
	for (int i = 2; i <= 21; i++)
	{
		temp += h * dx * (T[i] - 300);
		temp += h * dx * (T[i + 126] - 300);
	}
	for (int i = 2; i <= 6; i++)
	{
		int x = i * 21;
		temp += h * dx * (T[x] - 300);
	}
	return temp * 0.63;
}

void RectangleRib::output(ofstream * out)
{
	*out << "The result of rectangle rib : " << endl;
	double Q = Quantity();
	double Q0 = h * 0.046 * 200;
	*out << "¦µ = " << Q << endl;
	*out << "¦µ0 = " << Q0 << endl;
	*out << "¦Ç = " << Q / Q0 * 100 << "%" << endl;
}



#endif