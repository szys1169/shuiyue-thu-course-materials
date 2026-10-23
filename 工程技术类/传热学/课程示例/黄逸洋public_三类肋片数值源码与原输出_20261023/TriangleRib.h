#ifndef _TRIANGLERIB_
#define _TRIANGLERIB_

#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

class TriangleRib
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
	bool IsinRib(int x, int y);
	double Quantity();
	void output(ofstream * out);
};

int TriangleRib::f(int x, int y)
{
	return (x - 1) * 196 + y;
}

bool TriangleRib::IsinRib(int x, int y)
{
	return ((y - 1) <= 6 - 0.15 * (x - 1)) && ((y - 1) >= 0.15 * (x - 1));
}

void TriangleRib::initialize()
{
	dx = 0.001;
	dy = 0.001;
	lambda = 187;
	h = 2800;
	tf = 300;
	N = 21;
	M = 7;
	T = new double[(N + 1) * (M + 1)];
	T_last = new double[(N + 1) * (M + 1) + 42];
	A = new double[((N + 2) * (M + 2) + 42) * ((N + 2) * (M + 2) + 42)];
	for (int i = 1; i <= 195; i++)
	{
		T[i] = 300;
		T_last[i] = 0;
	}
	for (int i = 1; i <= 195; i++)
		for (int j = 1; j <= 196; j++)
			A[f(i,j)] = 0;
};

void TriangleRib::bulidEquation()
{
	for (int i = 2; i <= 20; i++)
		for (int j = 2; j <= 6; j++)
			if (IsinRib(i,j))
			{
				int x = (j - 1) * 21 + i;
				A[f(x,x - 21)] = 1;
				A[f(x,x + 1)] = 1;
				A[f(x,x - 1)] = 1;
				A[f(x,x + 21)] = 1;
				A[f(x,x)] = -4;
			}
	for (int i = 1; i <= 21; i++)
		for (int j = 1; j <= 7; j++)
			if (! IsinRib(i,j))
			{
				int x = (j - 1) * 21 + i;
				A[f(x,x)] = 1;
				A[f(x,196)] = 300;
			}
	for (int i = 1; i <= 7; i++)
	{
		int x = i * 21 - 20;
		A[f(x,x)] = 1;
		A[f(x,196)] = 500;
	}

	A[f(148,148)] = 1;
	A[f(149,149)] = 1;
	A[f(148,196)] = 500;
	A[f(149,196)] = 500;
	for (int i = 2; i <= 20; i++)
	{
		int x = i;
		int y1 = int(7 - 0.15 * (i - 1));
		int y2 = 8 - y1;
		int i1 = (y1 - 1) * 21 + x;
		int i2 = (y2 - 1) * 21 + x;
		int b1 = 147 + 2 * i - 1;
		int b2 = 147 + 2 * i;
		double b = 7 - 0.15 * (i - 1) - y1;

		A[f(b1,b1 - 2)] = b / sqrt(0.15 * 0.15 + 1);
		A[f(b1,b1 + 2)] = b / sqrt(0.15 * 0.15 + 1);
		A[f(b1,i1)] = 2 / b;
		A[f(b1,196)] = - 2 * h * dx * sqrt(1 + 0.15 * 0.15) / lambda * tf;
		A[f(b1,b1)] = - (2 * b / sqrt(0.15 * 0.15 + 1) + 2 / b + 2 * h * dx * sqrt(1 + 0.15 * 0.15) / lambda);

		A[f(b2,b2 - 2)] = b / sqrt(0.15 * 0.15 + 1);
		A[f(b2,b2 + 2)] = b / sqrt(0.15 * 0.15 + 1);
		A[f(b2,i2)] = 2 / b;
		A[f(b2,196)] = - 2 * h * dx * sqrt(1 + 0.15 * 0.15) / lambda * tf;
		A[f(b2,b2)] = - (2 * b / sqrt(0.15 * 0.15 + 1) + 2 / b + 2 * h * dx * sqrt(1 + 0.15 * 0.15) / lambda);

		if (i1 != i2)
		{
			A[f(i1,i1 - 1)] = 1 + b;
			A[f(i1,i1 - 21)] = 2;
			A[f(i1,i1 + 1)] = 1 + b;
			A[f(i1,b1)] = 2 / b;
			A[f(i1,i1)] = - (4 + 2 * b + 2 / b);
		
			A[f(i2,i2 - 1)] = 1 + b;
			A[f(i2,i2 + 21)] = 2;
			A[f(i2,i2 + 1)] = 1 + b;
			A[f(i2,b2)] = 2 / b;
			A[f(i2,i2)] = - (4 + 2 * b + 2 / b);
		}
		else
		{
			A[f(i1,i1 - 1)] = 1 + b;
			A[f(i1,i1 + 1)] = 1 + b;
			A[f(i1,b1)] = 2 / b;
			A[f(i1,b2)] = 2 / b;
			A[f(i1,i1)] = - (2 + 2 * b + 4 / b);
		}
	}

	A[f(84,186)] = 0.15 / sqrt(0.15 * 0.15 + 1);
	A[f(84,187)] = 0.15 / sqrt(0.15 * 0.15 + 1);
	A[f(84,83)] = 0.3;
	A[f(84,196)] = - 2 * h * dx * sqrt(1 + 0.15 * 0.15) / lambda * tf;
	A[f(84,84)] = - (0.3 / sqrt(0.15 * 0.15 + 1) + 0.3);

	A[f(188,186)] = 0.15 / sqrt(0.15 * 0.15 + 1);
	A[f(188,187)] = 0.15 / sqrt(0.15 * 0.15 + 1);
	A[f(188,83)] = 0.3;
	A[f(188,196)] = - 2 * h * dx * sqrt(1 + 0.15 * 0.15) / lambda * tf;
	A[f(188,188)] = - (0.3 / sqrt(0.15 * 0.15 + 1) + 0.3);

}

void TriangleRib::iteration()
{
	bool flag = 1;
	for (int i = 1; i <= 188; i++)
		if (abs(T[i] - T_last[i]) > 0.01)
			flag = 0;
	if (flag)
		return;
	for (int i = 1; i <= 188; i++)
	{
		T_last[i] = T[i];
		T[i] = 0;
		for (int j = 1; j <= 188; j++)
			if (i != j)
				T[i] -= A[f(i,j)] * T_last[j];
		T[i] += A[f(i,196)];
		T[i] /= A[f(i,i)];
	}
	int cheat = 0;
	while (cheat < 1000)
	{
		cheat++;
		for (int j = 1; j <= 188; j++)
				T[1] -= A[f(1,j)] * T_last[j];
		T[1] += A[f(1,196)];
		T[1] /= A[f(1,1)];
	}
	iteration();
}

double TriangleRib::Quantity()
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
	temp = 4.33 * h;
	return temp;
}

void TriangleRib::output(ofstream * out)
{
	*out << "The result of triangle rib : " << endl;
	double Q = Quantity();
	double Q0 = h * 2 * sqrt(0.02 * 0.02 + 0.003 * 0.003) * 200;
	*out << "¦µ = " << Q << endl;
	*out << "¦µ0 = " << Q0 << endl;
	*out << "¦Ç = " << Q / Q0 * 100 << "%" << endl;
}

#endif