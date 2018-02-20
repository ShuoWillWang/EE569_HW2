// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Puzzle matching for P1_b
//*********************************************************



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

const double PI = 3.1415926;
using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char ImagedataOut[100000000];
extern unsigned char Imagedataori[100000000];
extern unsigned char Imagedata1[100000000];
extern unsigned char Imagedata2[100000000];
unsigned char Imagedata1f[100000000] = { 0 };
unsigned char Imagedata2f[100000000] = { 0 };

extern double itoy(double i, int Size2);
extern double jtox(double j);
extern double Returny(double y, int Size2);
extern double Returnx(double x);

void Warp_n(double a, double b, double c, double d, double e, double f, unsigned char *Imagedata, unsigned char *ImagedataOut, int Size1, int Size2, double *x1, double *x2, double *x3, int Size3, int Size4)
//warp operation given the A matrix and the output control points
//the output control points should be ordered clockwise
//the size of the input image do not have to be equal to the one of the output image
{
	double x1a[2], x2a[2], x3a[2], x1v[2], x2v[2], x3v[2];
	x1a[0] = x2[0] - x1[0]; x2a[0] = x3[0] - x2[0]; x3a[0] = x1[0] - x3[0];// get the vector on the edge:(clockwise)
	x1a[1] = x2[1] - x1[1]; x2a[1] = x3[1] - x2[1]; x3a[1] = x1[1] - x3[1];
	x1v[1] = -x1a[0]; x1v[0] = x1a[1];// get the vector orthogonal to the edge
	x2v[1] = -x2a[0]; x2v[0] = x2a[1];
	x3v[1] = -x3a[0]; x3v[0] = x3a[1];
	for (int i = 0; i<Size4; i++)
	{
		for (int j = 0; j<Size3; j++)
		{
			double x, y, temp1, temp2, temp3;
			x = jtox(j);
			y = itoy(i, Size4);
			temp1 = (x - x1[0]) * x1v[0] + (y - x1[1]) * x1v[1];
			temp2 = (x - x2[0]) * x2v[0] + (y - x2[1]) * x2v[1];
			temp3 = (x - x3[0]) * x3v[0] + (y - x3[1]) * x3v[1];
			if (temp1 >= 0 && temp2 >= 0 && temp3 >= 0)//judge if the points in the output image in the output warpping triangle
			{
				double x0, y0, i0, j0, di, dj, temp;
				int i00, i01, i10, i11;
				int j00, j01, j10, j11;
				x0 = a * x + b * y + c;
				y0 = d * x + e * y + f;
				i0 = Returny(y0, Size2);
				j0 = Returnx(x0);
				di = (i0 - (int)i0); dj = (j0 - (int)j0);
				i00 = (int)i0; j00 = (int)j0;
				i01 = (int)i0; j01 = (int)j0 + 1;
				i10 = (int)i0 + 1; j10 = (int)j0;
				i11 = (int)i0 + 1; j11 = (int)j0 + 1;
				temp = (1 - di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i00 + j00) + 0] + (di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i10 + j10) + 0] + (1 - di)*(dj)*(float)Imagedata[3 * (Size1 * i01 + j01) + 0] + (di)*(dj)*(float)Imagedata[3 * (Size1 * i11 + j11) + 0];
				ImagedataOut[3 * (Size3 * i + j) + 0] = temp;
				temp = (1 - di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i00 + j00) + 1] + (di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i10 + j10) + 1] + (1 - di)*(dj)*(float)Imagedata[3 * (Size1 * i01 + j01) + 1] + (di)*(dj)*(float)Imagedata[3 * (Size1 * i11 + j11) + 1];
				ImagedataOut[3 * (Size3 * i + j) + 1] = temp;
				temp = (1 - di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i00 + j00) + 2] + (di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i10 + j10) + 2] + (1 - di)*(dj)*(float)Imagedata[3 * (Size1 * i01 + j01) + 2] + (di)*(dj)*(float)Imagedata[3 * (Size1 * i11 + j11) + 2];
				ImagedataOut[3 * (Size3 * i + j) + 2] = temp;
			}
		}
	}
}

void Tran(double *ci, double *co, double x, double y, int type)//translation operation
{
	if (type == 1)
	{
		co[0] = ci[0] + x;
		co[1] = ci[1] + y;
	}
	else if (type == 2)
	{
		co[0] = ci[0] - x;
		co[1] = ci[1] - y;
	}
}

void Rot(double *ci, double *co, double theta, int type)//Rotation operation
{
	if (type == 1)
	{
		co[0] = cos(theta * PI / 180) * ci[0] - sin(theta * PI / 180) * ci[1];
		co[1] = sin(theta * PI / 180) * ci[0] + cos(theta * PI / 180) * ci[1];
	}
	else if (type == 2)
	{
		theta = -theta;
		co[0] = cos(theta * PI / 180) * ci[0] - sin(theta * PI / 180) * ci[1];
		co[1] = sin(theta * PI / 180) * ci[0] + cos(theta * PI / 180) * ci[1];
	}
}

void Mul(double *ci, double *co, double Sc, int type)//Scaling operation
{
	if (type == 1)
	{
		co[0] = Sc * ci[0];
		co[1] = Sc * ci[1];
	}
	else if (type == 2)
	{
		co[0] = ci[0] / Sc;
		co[1] = ci[1] / Sc;
	}
}

double abso(double a)//get the absolute value
{
	if (a >= 0)
		return a;
	else
		return -a;
}

void P1_b(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;

	int Size3 = 512, Size4 = 512, len = 100;

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	if (!(file = fopen("D:\\EE569_Assignment\\2\\Hillary.raw", "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}//path of the input image Hillary.raw (should be set here)
	fread(Imagedata1, sizeof(unsigned char), Size4*Size3*BytesPerPixel, file);
	fclose(file);

	if (!(file = fopen("D:\\EE569_Assignment\\2\\Trump.raw", "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}//path of the input image Trump.raw (should be set here)
	fread(Imagedata2, sizeof(unsigned char), Size4*Size3*BytesPerPixel, file);
	fclose(file);


	double *ie1, *ie2, *je1, *je2;
	ie1 = new double[10000];
	ie2 = new double[10000];
	je1 = new double[10000];
	je2 = new double[10000];
	int k1 = 0, k2 = 0;
	int i0;
	int ind1 = 1, ind2 = 1;
	for (int i = 0; i < Size2; i++)
	{
		int j0 = 0;
		for (int j = 0; j < Size1; j++)
		{
			if (Imagedata[3 * (Size1 * i + j) + 0] != 255)
			{
				j0++;
			}
			if ((Imagedata[3 * (Size1 * i + j) + 0] != 255 && Imagedata[3 * (Size1 * i + j - 1) + 0] == 255) || (Imagedata[3 * (Size1 * i + j) + 0] != 255 && Imagedata[3 * (Size1 * i + j + 1) + 0] == 255) || (Imagedata[3 * (Size1 * i + j) + 0] != 255 && Imagedata[3 * (Size1 * (i - 1) + j) + 0] == 255) || (Imagedata[3 * (Size1 * i + j) + 0] != 255 && Imagedata[3 * (Size1 * (i + 1) + j) + 0] == 255))
			{
				ie1[k1] = i;je1[k1] = j;//get the coorsinate of the edge of the first patch
				k1++;
			}
		}
		if (k1 != 0 && j0 == 0)//when scanning the last pixel of the first patch, record the coordinates and stop
		{
			ind1 = 0;
			i0 = i - 1;
		}
		if (ind1 == 0)
		{
			break;
		}
	}

	for (int i = i0 + 2; i < Size2; i++)
	{
		int j0 = 0;
		for (int j = 0; j < Size1; j++)
		{
			if (Imagedata[3 * (Size3 * i + j) + 0] != 255)
			{
				j0++;
			}
			if ((Imagedata[3 * (Size1 * i + j) + 0] != 255 && Imagedata[3 * (Size1 * i + j - 1) + 0] == 255) || (Imagedata[3 * (Size1 * i + j) + 0] != 255 && Imagedata[3 * (Size1 * i + j + 1) + 0] == 255) || (Imagedata[3 * (Size1 * i + j) + 0] != 255 && Imagedata[3 * (Size1 * (i - 1) + j) + 0] == 255) || (Imagedata[3 * (Size1 * i + j) + 0] != 255 && Imagedata[3 * (Size1 * (i + 1) + j) + 0] == 255))
			{
				ie2[k2] = i;je2[k2] = j;//get the coorsinate of the edge of the Second patch
				k2++;
			}
		}
		if (k2 != 0 && j0 == 0)
		{
			ind2 = 0;
		}
	}

	double maje1 = je1[0], mije1 = je1[0], maie1 = ie1[0], miie1 = ie1[0];

	for (int k = 0; k < k1; k++)//get maximum value and minimum value of the i and j in the first patch
	{
		if (maje1 < je1[k])
		{
			maje1 = je1[k];
		}
	}

	for (int k = 0; k < k1; k++)
	{
		if (mije1 > je1[k])
		{
			mije1 = je1[k];
		}
	}

	for (int k = 0; k < k1; k++)
	{
		if (maie1 < ie1[k])
		{
			maie1 = ie1[k];
		}
	}

	for (int k = 0; k < k1; k++)
	{
		if (miie1 > ie1[k])
		{
			miie1 = ie1[k];
		}
	}

	int iio[4] = { 0 }, jjo[4] = { 0 };

	for (int k = 0; k < k1; k++)//get the four corner points of the first patch(i-j coordinate)
	{
		if (ie1[k] == miie1)
		{
			jjo[0] = je1[k];
			iio[0] = ie1[k];
			break;
		}
	}

	for (int k = 0; k < k1; k++)
	{
		if (ie1[k] == maie1)
		{
			jjo[2] = je1[k];
			iio[2] = ie1[k];
		}
	}

	for (int k = 0; k < k1; k++)
	{
		if (je1[k] == mije1)
		{
			jjo[3] = je1[k];
			iio[3] = ie1[k];
		}
	}

	for (int k = 0; k < k1; k++)
	{
		if (je1[k] == maje1)
		{
			jjo[1] = je1[k];
			iio[1] = ie1[k];
			break;
		}
	}

	double x1[4], x2[4], y1[4], y2[4];
	x1[0] = jtox(jjo[0]); y1[0] = itoy(iio[0], Size1);//get the four corner points of the first patch (x-y coordinate)  (clockwise)
	x1[2] = jtox(jjo[2]); y1[2] = itoy(iio[2], Size1);
	x1[3] = jtox(jjo[3]); y1[3] = itoy(iio[3], Size1);
	x1[1] = jtox(jjo[1]); y1[1] = itoy(iio[1], Size1);

	cout << "The origin Cordinate for Hillary is: " << endl;
	cout << "The X: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << x1[s] << endl;
	}

	cout << endl;
	cout << "The Y: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << y1[s] << endl;
	}

	double maje2 = je2[0],  mije2 = je2[0], maie2 = ie2[0], miie2 = ie2[0];//get maximum value and minimum value of the i and j in the second patch

	for (int k = 0; k < k2; k++)
	{
		if (maje2 < je2[k])
		{
			maje2 = je2[k];
		}
	}

	for (int k = 0; k < k2; k++)
	{
		if (mije2 > je2[k])
		{
			mije2 = je2[k];
		}
	}

	for (int k = 0; k < k2; k++)
	{
		if (maie2 < ie2[k])
		{
			maie2 = ie2[k];
		}
	}

	for (int k = 0; k < k2; k++)
	{
		if (miie2 > ie2[k])
		{
			miie2 = ie2[k];
		}
	}

	double jja[4] = { 0 };
	double iia[4] = { 0 };

	for (int k = 0; k < k2; k++)//get the four corner points of the second patch(i-j coordinate)
	{
		if (ie2[k] == miie2)
		{
			jja[0] = je2[k];
			iia[0] = ie2[k];
		}
	}

	for (int k = 0; k < k2; k++)
	{
		if (ie2[k] == maie2)
		{
			jja[2] = je2[k];
			iia[2] = ie2[k];
			break;
		}
	}

	for (int k = 0; k < k2; k++)
	{
		if (je2[k] == mije2)
		{
			jja[3] = je2[k];
			iia[3] = ie2[k];
			break;
		}
	}

	for (int k = 0; k < k2; k++)
	{
		if (je2[k] == maje2)
		{
			jja[1] = je2[k];
			iia[1] = ie2[k];
		}
	}

	x2[0] = jtox(jja[0]); y2[0] = itoy(iia[0], Size1);//get the four corner points of the second patch (x-y coordinate) (clockwise)
	x2[2] = jtox(jja[2]); y2[2] = itoy(iia[2], Size1);
	x2[1] = jtox(jja[1]); y2[1] = itoy(iia[1], Size1);
	x2[3] = jtox(jja[3]); y2[3] = itoy(iia[3], Size1);

	cout << "The origin Cordinate for Trump is: " << endl;
	cout << "The X: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << x2[s] << endl;
	}

	cout << endl;
	cout << "The Y: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << y2[s] << endl;
	}

	for (int k = 0; k < k1; k++)
	{
		int a = ie1[k];
		int b = je1[k];
		ImagedataOut[1 * (Size1 * a + b) + 0] = 255;
	}

	for (int k = 0; k < k2; k++)
	{
		int a = ie2[k];
		int b = je2[k];
		ImagedataOut[1 * (Size1 * a + b) + 0] = 255;
	}

	double xo1[4], xo2[4], yo1[4], yo2[4];

	for (int i = 0; i < Size4; i++)//the the coordinates of the corner of the hole in Hillary  (clockwise)
	{
		for (int j = 0; j < Size3; j++)
		{
			if (Imagedata1[3 * (Size3 * i + j) + 0] == 255)
			{
				int a[8] = { 0 };
				a[0] = (int)Imagedata1[BytesPerPixel * ((Size3) * (i - 1) + (j - 1)) + 0];
				a[1] = (int)Imagedata1[BytesPerPixel * ((Size3) * (i - 1) + (j)) + 0];
				a[2] = (int)Imagedata1[BytesPerPixel * ((Size3) * (i - 1) + (j + 1)) + 0];
				a[3] = (int)Imagedata1[BytesPerPixel * ((Size3) * (i)+(j - 1)) + 0];
				a[4] = (int)Imagedata1[BytesPerPixel * ((Size3) * (i)+(j + 1)) + 0];
				a[5] = (int)Imagedata1[BytesPerPixel * ((Size3) * (i + 1) + (j - 1)) + 0];
				a[6] = (int)Imagedata1[BytesPerPixel * ((Size3) * (i + 1) + (j)) + 0];
				a[7] = (int)Imagedata1[BytesPerPixel * ((Size3) * (i + 1) + (j + 1)) + 0];
				if (a[1] != 255 && a[3] != 255)
				{
					xo1[0] = jtox(j);
					yo1[0] = itoy(i, Size3);
				}
				else if (a[1] != 255 && a[4] != 255)
				{
					xo1[1] = jtox(j);
					yo1[1] = itoy(i, Size3);
				}
				else if (a[4] != 255 && a[6] != 255)
				{
					xo1[2] = jtox(j);
					yo1[2] = itoy(i, Size3);
				}
				else if (a[3] != 255 && a[6] != 255)
				{
					xo1[3] = jtox(j);
					yo1[3] = itoy(i, Size3);
				}
			}
		}
	}

	cout << "The new Cordinate for Hillary is: " << endl;
	cout << "The X: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << xo1[s] << endl;
	}

	cout << endl;
	cout << "The Y: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << yo1[s] << endl;
	}

	for (int i = 0; i < Size4; i++)//the the coordinates of the corner of the hole in Trump  (clockwise)
	{
		for (int j = 0; j < Size3; j++)
		{
			if (Imagedata2[3 * (Size3 * i + j) + 0] == 255)
			{
				int a[8] = { 0 };
				a[0] = (int)Imagedata2[BytesPerPixel * ((Size3) * (i - 1) + (j - 1)) + 0];
				a[1] = (int)Imagedata2[BytesPerPixel * ((Size3) * (i - 1) + (j)) + 0];
				a[2] = (int)Imagedata2[BytesPerPixel * ((Size3) * (i - 1) + (j + 1)) + 0];
				a[3] = (int)Imagedata2[BytesPerPixel * ((Size3) * (i)+(j - 1)) + 0];
				a[4] = (int)Imagedata2[BytesPerPixel * ((Size3) * (i)+(j + 1)) + 0];
				a[5] = (int)Imagedata2[BytesPerPixel * ((Size3) * (i + 1) + (j - 1)) + 0];
				a[6] = (int)Imagedata2[BytesPerPixel * ((Size3) * (i + 1) + (j)) + 0];
				a[7] = (int)Imagedata2[BytesPerPixel * ((Size3) * (i + 1) + (j + 1)) + 0];
				if (a[1] != 255 && a[3] != 255)
				{
					xo2[0] = jtox(j);
					yo2[0] = itoy(i, Size3);
				}
				else if (a[1] != 255 && a[4] != 255)
				{
					xo2[1] = jtox(j);
					yo2[1] = itoy(i, Size3);
				}
				else if (a[4] != 255 && a[6] != 255)
				{
					xo2[2] = jtox(j);
					yo2[2] = itoy(i, Size3);
				}
				else if (a[3] != 255 && a[6] != 255)
				{
					xo2[3] = jtox(j);
					yo2[3] = itoy(i, Size3);
				}
			}
		}
	}

	cout << "The new Cordinate for Trump is: " << endl;
	cout << "The X: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << xo2[s] << endl;
	}
	
	cout << endl;
	cout << "The Y: " << endl;

	for (int s = 0; s < 4;s++)
	{
		cout << yo2[s] << endl;
	}

	cout << "INPUT THE STATISTIC INTO MATLAB: " << endl;
	system("pause");

	double temp, temp1, temp2, temp3, temp4, ii, jj;
	jj = Returnx(x1[0]);  //compare the pixel near corner of the patch
	ii = Returny(y1[0], Size2);
	temp = Imagedata[3 * (Size1 * ((int)ii + 1) + (int)jj + 1) + 0];
	jj = Returnx(xo1[0]) - 1; //compare the pixel near first corner of the hole
	ii = Returny(yo1[0], Size4) - 1;
	temp1 = Imagedata1[3 * (Size3 * (int)ii + (int)jj) + 0];
	jj = Returnx(xo1[1] + 1);//compare the pixel near third corner of the hole
	ii = Returny(yo1[1] + 1, Size4);
	temp2 = Imagedata1[3 * (Size3 * (int)ii + (int)jj) + 0];
	jj = Returnx(xo1[2] + 1);//compare the pixel near second corner of the hole
	ii = Returny(yo1[2] - 1, Size4);
	temp3 = Imagedata1[3 * (Size3 * (int)ii + (int)jj) + 0];
	jj = Returnx(xo1[3] - 1);//compare the pixel near forth corner of the hole
	ii = Returny(yo1[3] - 1, Size4);
	temp4 = Imagedata1[3 * (Size3 * (int)ii + (int)jj) + 0];
	cout << temp << '\t' << temp1 << '\t' << temp2 << '\t' << temp3 << '\t' << temp4 << endl;
	double xin1[2], xin2[2], xin3[2], xin11[2], xin21[2], xin31[2];
	if (abso(temp - temp1) <= 5)//1
	{
		xin1[0] = xo1[0]; xin2[0] = xo1[1]; xin3[0] = xo1[2];//set the output warp control points as 1, 2 and 3
		xin1[1] = yo1[0]; xin2[1] = yo1[1]; xin3[1] = yo1[2];
		cout << "the used coordinate of input (x) is 1st, 2nd and 3rd (Hillary)" << endl;
		xin11[0] = xo1[0]; xin21[0] = xo1[2]; xin31[0] = xo1[3];
		xin11[1] = yo1[0]; xin21[1] = yo1[2]; xin31[1] = yo1[3];
	}
	else if (abso(temp - temp2) <= 5)
	{
		xin1[0] = xo1[1]; xin2[0] = xo1[2]; xin3[0] = xo1[3];//set the output warp control points as 2, 3 and 4
		xin1[1] = yo1[1]; xin2[1] = yo1[2]; xin3[1] = yo1[3];
		cout << "the used coordinate of input (x) is 2nd, 3rd and 4th (Hillary)" << endl;
		xin11[0] = xo1[1]; xin21[0] = xo1[3]; xin31[0] = xo1[0];
		xin11[1] = yo1[1]; xin21[1] = yo1[3]; xin31[1] = yo1[0];
	}
	else if (abso(temp - temp3) <= 5)
	{
		xin1[0] = xo1[2]; xin2[0] = xo1[3]; xin3[0] = xo1[0];//set the output warp control points as 3, 4 and 1
		xin1[1] = yo1[2]; xin2[1] = yo1[3]; xin3[1] = yo1[0];
		cout << "the used coordinate of input (x) is 3rd, 4th and 1st (Hillary)" << endl;
		xin11[0] = xo1[2]; xin21[0] = xo1[0]; xin31[0] = xo1[1];
		xin11[1] = yo1[2]; xin21[1] = yo1[0]; xin31[1] = yo1[1];
	}
	else
	{
		xin1[0] = xo1[3]; xin2[0] = xo1[0]; xin3[0] = xo1[1];//set the output warp control points as 4, 1 and 2
		xin1[1] = yo1[3]; xin2[1] = yo1[0]; xin3[1] = yo1[1];
		cout << "the used coordinate of input (x) is 4th, 1st and 2nd (Hillary)" << endl;
		xin11[0] = xo1[3]; xin21[0] = xo1[1]; xin31[0] = xo1[2];
		xin11[1] = yo1[3]; xin21[1] = yo1[1]; xin31[1] = yo1[2];
	}

	//1.4646, 0.3939, -306.7222, -0.3939, 1.4545, -37.6970,

	double aa, bb, cc, dd, ee, ff;
	cout << "Input the parameters of matrix a, b, c, d, e and f: ";
	cin >> aa >> bb >> cc >> dd >> ee >> ff;//
	cout << endl;

	Warp_n(aa, bb, cc, dd, ee, ff, Imagedata, Imagedata1, Size1, Size2, xin1, xin2, xin3, 512, 512);
	Warp_n(aa, bb, cc, dd, ee, ff, Imagedata, Imagedata1, Size1, Size2, xin11, xin21, xin31, 512, 512);

	jj = Returnx(x2[0]);
	ii = Returny(y2[0], Size2);
	temp = Imagedata[3 * (Size1 * ((int)ii + 4) + (int)jj - 3) + 0];
	jj = Returnx(xo2[0] - 1);
	ii = Returny(yo2[0] + 1, Size4);
	temp1 = Imagedata2[3 * (Size3 * (int)ii + (int)jj) + 0];
	jj = Returnx(xo2[1]) + 1;
	ii = Returny(yo2[1], Size4) - 1;
	temp2 = Imagedata2[3 * (Size3 * (int)ii + (int)jj) + 0];
	jj = Returnx(xo2[2]) + 1;
	ii = Returny(yo2[2], Size4) + 1;
	temp3 = Imagedata2[3 * (Size3 * (int)ii + (int)jj) + 0];
	jj = Returnx(xo2[3]) - 2;
	ii = Returny(yo2[3], Size4) + 2;
	temp4 = Imagedata2[3 * (Size3 * (int)ii + (int)jj) + 0];
	cout << temp << '\t' << temp1 << '\t' << temp2 << '\t' << temp3 << '\t' << temp4 << endl;


	if (abso(temp - temp1) <= 6)
	{
		xin1[0] = xo2[0]; xin2[0] = xo2[1]; xin3[0] = xo2[2];
		xin1[1] = yo2[0]; xin2[1] = yo2[1]; xin3[1] = yo2[2];
		cout << "the used coordinate of input (x) is 1st, 2nd and 3rd (Trump)" << endl;
		xin11[0] = xo2[0]; xin21[0] = xo2[2]; xin31[0] = xo2[3];
		xin11[1] = yo2[0]; xin21[1] = yo2[2]; xin31[1] = yo2[3];
	}
	else if (abso(temp - temp2) <= 6)
	{
		xin1[0] = xo2[1]; xin2[0] = xo2[2]; xin3[0] = xo2[3];
		xin1[1] = yo2[1]; xin2[1] = yo2[2]; xin3[1] = yo2[3];
		cout << "the used coordinate of input (x) is 2nd, 3rd and 4th (Trump)" << endl;
		xin11[0] = xo2[1]; xin21[0] = xo2[3]; xin31[0] = xo2[0];
		xin11[1] = yo2[1]; xin21[1] = yo2[3]; xin31[1] = yo2[0];
	}
	else if (abso(temp - temp3) <= 6)//1
	{
		xin1[0] = xo2[2]; xin2[0] = xo2[3]; xin3[0] = xo2[0];
		xin1[1] = yo2[2]; xin2[1] = yo2[3]; xin3[1] = yo2[0];
		cout << "the used coordinate of input (x) is 3rd, 4th and 1st (Trump)" << endl;
		xin11[0] = xo2[2]; xin21[0] = xo2[0]; xin31[0] = xo2[1];
		xin11[1] = yo2[2]; xin21[1] = yo2[0]; xin31[1] = yo2[1];
	}
	else
	{
		xin1[0] = xo2[3]; xin2[0] = xo2[0]; xin3[0] = xo2[1];
		xin1[1] = yo2[3]; xin2[1] = yo2[0]; xin3[1] = yo2[1];
		cout << "the used coordinate of input (x) is 4th, 1st and 2nd (Trump)" << endl;
		xin11[0] = xo2[3]; xin21[0] = xo2[1]; xin31[0] = xo2[2];
		xin11[1] = yo2[3]; xin21[1] = yo2[1]; xin31[1] = yo2[2];
	}

	double aa1, bb1, cc1, dd1, ee1, ff1;
	cout << "Input the parameters of matrix a, b, c, d, e and f: ";
	cin >> aa1 >> bb1 >> cc1 >> dd1 >> ee1 >> ff1;//-0.0606, -0.7576, 528.6364, 0.7576, -0.0606, 23.4545,
	cout << endl;

	Warp_n(aa1, bb1, cc1, dd1, ee1, ff1, Imagedata, Imagedata2, Size1, Size2, xin1, xin2, xin3, 512, 512);
	Warp_n(aa1, bb1, cc1, dd1, ee1, ff1, Imagedata, Imagedata2, Size1, Size2, xin11, xin21, xin31, 512, 512);

	for (int i = 0; i < Size3; i++)
	{
		for (int j = 0; j < Size3; j++)
		{
			Imagedata1f[3 * (Size3 * i + j) + 0] = Imagedata1[3 * (Size3 * i + j) + 0];
			Imagedata1f[3 * (Size3 * i + j) + 1] = Imagedata1[3 * (Size3 * i + j) + 1];
			Imagedata1f[3 * (Size3 * i + j) + 2] = Imagedata1[3 * (Size3 * i + j) + 2];
		}
	}

	int jeo1, jeo2, ieo1, ieo2;

	jeo1 = Returnx(xo1[0]); 
	jeo2 = Returnx(xo1[3]);
	ieo1 = Returny(yo1[0], Size4); 
	ieo2 = Returny(yo1[3], Size4);
	for (int i = ieo1; i <= ieo2; i++)//insert the average into the white gaps in the Output image
	{
		Imagedata1f[3 * (Size3 * i + (int)jeo1) + 0] = (double)(Imagedata1[3 * (Size3 * (i) + ((int)jeo1 + 2)) + 0] + Imagedata1[3 * (Size3 * (i) + ((int)jeo1 - 2)) + 0]) / 2;
		Imagedata1f[3 * (Size3 * i + (int)jeo1) + 1] = (double)(Imagedata1[3 * (Size3 * (i) + ((int)jeo1 + 2)) + 1] + Imagedata1[3 * (Size3 * (i) + ((int)jeo1 - 2)) + 1]) / 2;
		Imagedata1f[3 * (Size3 * i + (int)jeo1) + 2] = (double)(Imagedata1[3 * (Size3 * (i) + ((int)jeo1 + 2)) + 2] + Imagedata1[3 * (Size3 * (i) + ((int)jeo1 - 2)) + 2]) / 2;
	}
	jeo1 = Returnx(xo1[1]);
	jeo2 = Returnx(xo1[2]);
	ieo1 = Returny(yo1[1], Size4);
	ieo2 = Returny(yo1[2], Size4);
	for (int i = ieo1; i <= ieo2; i++)
	{
		Imagedata1f[3 * (Size3 * i + (int)(jeo1)) + 0] = ((double)1 / 2) *(Imagedata1[3 * (Size3 * (i)+((int)(jeo1) + 2)) + 0] + Imagedata1[3 * (Size3 * (i)+((int)(jeo1) - 2)) + 0]);
		Imagedata1f[3 * (Size3 * i + (int)(jeo1)) + 1] = ((double)1 / 2) *(Imagedata1[3 * (Size3 * (i)+((int)(jeo1) + 2)) + 1] + Imagedata1[3 * (Size3 * (i)+((int)(jeo1) - 2)) + 1]);
		Imagedata1f[3 * (Size3 * i + (int)(jeo1)) + 2] = ((double)1 / 2) *(Imagedata1[3 * (Size3 * (i)+((int)(jeo1) + 2)) + 2] + Imagedata1[3 * (Size3 * (i)+((int)(jeo1) - 2)) + 2]);
	}
	jeo1 = Returnx(xo1[0]);
	jeo2 = Returnx(xo1[1]);
	ieo1 = Returny(yo1[0], Size4);
	ieo2 = Returny(yo1[1], Size4);
	for (int j = jeo1; j <= jeo2; j++)
	{
		Imagedata1f[3 * (Size3 * ((int)ieo1) + j) + 0] = (double)(Imagedata1[3 * (Size3 * (((int)ieo1)+ 3) + (j)) + 0] + Imagedata1[3 * (Size3 * (((int)ieo1)- 3) + (j)) + 0]) / 2;
		Imagedata1f[3 * (Size3 * ((int)ieo1) + j) + 1] = (double)(Imagedata1[3 * (Size3 * (((int)ieo1)+ 3) + (j)) + 1] + Imagedata1[3 * (Size3 * (((int)ieo1)- 3) + (j)) + 1]) / 2;
		Imagedata1f[3 * (Size3 * ((int)ieo1) + j) + 2] = (double)(Imagedata1[3 * (Size3 * (((int)ieo1)+ 3) + (j)) + 2] + Imagedata1[3 * (Size3 * (((int)ieo1)- 3) + (j)) + 2]) / 2;
	}
	jeo1 = Returnx(xo1[3]);
	jeo2 = Returnx(xo1[2]);
	ieo1 = Returny(yo1[3], Size4);
	ieo2 = Returny(yo1[2], Size4);
	for (int j = jeo1; j < jeo2; j++)
	{
		Imagedata1f[3 * (Size3 * (int)(ieo1) + j) + 0] = ((double)1 / 2) *(Imagedata1[3 * (Size3 * ((int)(ieo1)+2) + (j)) + 0] + Imagedata1[3 * (Size3 * ((int)(ieo1)-2) + (j)) + 0]);
		Imagedata1f[3 * (Size3 * (int)(ieo1) + j) + 1] = ((double)1 / 2) *(Imagedata1[3 * (Size3 * ((int)(ieo1)+2) + (j)) + 1] + Imagedata1[3 * (Size3 * ((int)(ieo1)-2) + (j)) + 1]);
		Imagedata1f[3 * (Size3 * (int)(ieo1) + j) + 2] = ((double)1 / 2) *(Imagedata1[3 * (Size3 * ((int)(ieo1)+2) + (j)) + 2] + Imagedata1[3 * (Size3 * ((int)(ieo1)-2) + (j)) + 2]);
	}

	if (!(file = fopen("D:\\EE569_Assignment\\2\\Hillary_Complete.raw", "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata1f, sizeof(unsigned char), Size4*Size3*3, file);//the output image of the hillary image without white gap
	fclose(file);

	if (!(file = fopen("D:\\EE569_Assignment\\2\\Hillary_Complete_O.raw", "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata1, sizeof(unsigned char), Size4*Size3 * 3, file);//the output image of the hillary image with white gap
	fclose(file);

	int jeo11, jeo21, ieo11, ieo21;

	for (int i = 0; i < Size3; i++)
	{
		for (int j = 0; j < Size3; j++)
		{
			Imagedata2f[3 * (Size3 * i + j) + 0] = Imagedata2[3 * (Size3 * i + j) + 0];
			Imagedata2f[3 * (Size3 * i + j) + 1] = Imagedata2[3 * (Size3 * i + j) + 1];
			Imagedata2f[3 * (Size3 * i + j) + 2] = Imagedata2[3 * (Size3 * i + j) + 2];
		}
	}

	jeo11 = Returnx(xo2[0]);
	jeo21 = Returnx(xo2[3]);
	ieo11 = Returny(yo2[0], Size4);
	ieo21 = Returny(yo2[3], Size4);

	for (int i = ieo11; i <= ieo21; i++)
	{
		Imagedata2f[3 * (Size3 * i + (int)jeo11) + 0] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 2)) + 0] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 2)) + 0]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11) + 1] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 2)) + 1] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 2)) + 1]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11) + 2] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 2)) + 2] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 2)) + 2]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11 + 1) + 0] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 1 + 2)) + 0] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 1 - 2)) + 0]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11 + 1) + 1] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 1 + 2)) + 1] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 1 - 2)) + 1]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11 + 1) + 2] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 1 + 2)) + 2] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 1 - 2)) + 2]) / 2;
	}

	jeo11 = Returnx(xo2[1]);
	jeo21 = Returnx(xo2[2]);
	ieo11 = Returny(yo2[1], Size4);
	ieo21 = Returny(yo2[2], Size4);

	for (int i = ieo11; i <= ieo21; i++)
	{
		Imagedata2f[3 * (Size3 * i + (int)jeo11) + 0] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 2)) + 0] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 2)) + 0]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11) + 1] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 2)) + 1] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 2)) + 1]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11) + 2] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 + 2)) + 2] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 2)) + 2]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11 - 1) + 0] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 1 + 2)) + 0] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 1 - 2)) + 0]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11 - 1) + 1] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 1 + 2)) + 1] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 1 - 2)) + 1]) / 2;
		Imagedata2f[3 * (Size3 * i + (int)jeo11 - 1) + 2] = (double)(Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 1 + 2)) + 2] + Imagedata2[3 * (Size3 * (i)+((int)jeo11 - 1 - 2)) + 2]) / 2;
	}

	jeo11 = Returnx(xo2[0]);
	jeo21 = Returnx(xo2[1]);
	ieo11 = Returny(yo2[0], Size4);
	ieo21 = Returny(yo2[1], Size4);

	for (int j = jeo11; j <= jeo21; j++)
	{
		Imagedata2f[3 * (Size3 * ((int)ieo11) + j) + 0] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11) + 3) + (j)) + 0] + Imagedata2[3 * (Size3 * (((int)ieo11) - 3) + (j)) + 0]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11) + j) + 1] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11) + 3) + (j)) + 1] + Imagedata2[3 * (Size3 * (((int)ieo11) - 3) + (j)) + 1]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11) + j) + 2] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11) + 3) + (j)) + 2] + Imagedata2[3 * (Size3 * (((int)ieo11) - 3) + (j)) + 2]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11 + 1) + j) + 0] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11 + 1) + 3) + (j)) + 0] + Imagedata2[3 * (Size3 * (((int)ieo11 + 1) - 3) + (j)) + 0]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11 + 1) + j) + 1] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11 + 1) + 3) + (j)) + 1] + Imagedata2[3 * (Size3 * (((int)ieo11 + 1) - 3) + (j)) + 1]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11 + 1) + j) + 2] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11 + 1) + 3) + (j)) + 2] + Imagedata2[3 * (Size3 * (((int)ieo11 + 1) - 3) + (j)) + 2]) / 2;
	}

	jeo11 = Returnx(xo2[3]);
	jeo21 = Returnx(xo2[2]);
	ieo11 = Returny(yo2[3], Size4);
	ieo21 = Returny(yo2[2], Size4);

	for (int j = jeo11; j <= jeo21; j++)
	{
		Imagedata2f[3 * (Size3 * ((int)ieo11) + j) + 0] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11) + 3) + (j)) + 0] + Imagedata2[3 * (Size3 * (((int)ieo11) - 3) + (j)) + 0]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11) + j) + 1] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11) + 3) + (j)) + 1] + Imagedata2[3 * (Size3 * (((int)ieo11) - 3) + (j)) + 1]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11) + j) + 2] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11) + 3) + (j)) + 2] + Imagedata2[3 * (Size3 * (((int)ieo11) - 3) + (j)) + 2]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11 - 1) + j) + 0] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11 - 1) + 3) + (j)) + 0] + Imagedata2[3 * (Size3 * (((int)ieo11 - 1) - 3) + (j)) + 0]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11 - 1) + j) + 1] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11 - 1) + 3) + (j)) + 1] + Imagedata2[3 * (Size3 * (((int)ieo11 - 1) - 3) + (j)) + 1]) / 2;
		Imagedata2f[3 * (Size3 * ((int)ieo11 - 1) + j) + 2] = (double)(Imagedata2[3 * (Size3 * (((int)ieo11 - 1) + 3) + (j)) + 2] + Imagedata2[3 * (Size3 * (((int)ieo11 - 1) - 3) + (j)) + 2]) / 2;
	}

	if (!(file = fopen("D:\\EE569_Assignment\\2\\Trump_Complete.raw", "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata2f, sizeof(unsigned char), Size4*Size3 * 3, file);//the output image of the trump image without white gap
	fclose(file);

	if (!(file = fopen("D:\\EE569_Assignment\\2\\Trump_Complete_O.raw", "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata2, sizeof(unsigned char), Size4*Size3 * 3, file);//the output image of the trump image with white gap
	fclose(file);

	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(ImagedataOut, sizeof(unsigned char), Size2*Size1*1, file);//the image of the edges of the patch
	fclose(file);
	system("pause");
}