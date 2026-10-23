#include "RectangleRib.h"
#include "TriangleRib.h"
#include "ParabolaRib.h"

int main()
{
	ofstream fout("Result.txt");
	fout.setf(ios::fixed);
	fout.precision(3);

	RectangleRib Rrib;
	Rrib.initialize();
	Rrib.bulidEquation();
	Rrib.iteration();
	Rrib.output(&fout);

	TriangleRib Trib;
	Trib.initialize();
	Trib.bulidEquation();
	Trib.iteration();
	Trib.output(&fout);

	ParabolaRib Prib;
	Prib.initialize();
	Prib.bulidEquation();
	Prib.iteration();
	Prib.output(&fout);

	fout.close();
	return 0;
}