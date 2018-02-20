// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Homographic Transformation and Image Overlay for P1_c
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

extern double itoy(double i, int Size2);
extern double jtox(double j);
extern double Returny(double y, int Size2);
extern double Returnx(double x);

void HT(double a, double b, double c, double d, double e, double f, double g, double h, unsigned char *Imagedata, unsigned char *ImagedataOut, int Size1, int Size2, int Size3, int Size4)
//Homographic Transformation operation given the A matrix
//the size of the input image do not have to be equal to the one of the output image
{
	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			double x, y, temp1, temp2, temp3, temp4;
			x = jtox(j);
			y = itoy(i, Size2);
			if (1)
			{
				double x0, y0, w0, i0, j0, di, dj, temp01, temp02, temp03;
				int i00, i01, i10, i11;
				int j00, j01, j10, j11;
				x0 = a * x + b * y + c;//transform the coordinate in the output image to the one in the input patch
				y0 = d * x + e * y + f;
				w0 = g * x + h * y + 1;
				//cout << w0 << endl;
				x0 = x0 / w0;
				y0 = y0 / w0;
				//cout << x0 << endl;
				i0 = Returny(y0, Size4);
				j0 = Returnx(x0);
				di = (i0 - (int)i0); dj = (j0 - (int)j0);
				if (i0 >= 0 && j0 >= 0 && i0 <= Size4 - 1 && j0 < Size3 - 1)//judge if the coordinate corresponding to the output coordinate is in the trojan patch 
				{
					i00 = (int)i0; j00 = (int)j0;
					i01 = (int)i0; j01 = (int)j0 + 1;
					i10 = (int)i0 + 1; j10 = (int)j0;
					i11 = (int)i0 + 1; j11 = (int)j0 + 1;
					temp01 = (1 - di)*(1 - dj)*(float)Imagedata[3 * (Size3 * i00 + j00) + 0] + (di)*(1 - dj)*(float)Imagedata[3 * (Size3 * i10 + j10) + 0] + (1 - di)*(dj)*(float)Imagedata[3 * (Size3 * i01 + j01) + 0] + (di)*(dj)*(float)Imagedata[3 * (Size3 * i11 + j11) + 0];
					temp03 = (1 - di)*(1 - dj)*(float)Imagedata[3 * (Size3 * i00 + j00) + 2] + (di)*(1 - dj)*(float)Imagedata[3 * (Size3 * i10 + j10) + 2] + (1 - di)*(dj)*(float)Imagedata[3 * (Size3 * i01 + j01) + 2] + (di)*(dj)*(float)Imagedata[3 * (Size3 * i11 + j11) + 2];
					temp02 = (1 - di)*(1 - dj)*(float)Imagedata[3 * (Size3 * i00 + j00) + 1] + (di)*(1 - dj)*(float)Imagedata[3 * (Size3 * i10 + j10) + 1] + (1 - di)*(dj)*(float)Imagedata[3 * (Size3 * i01 + j01) + 1] + (di)*(dj)*(float)Imagedata[3 * (Size3 * i11 + j11) + 1];
					if (temp01 <= 244 && temp02 <= 244 && temp03 <= 244 && (temp01 != 0 || temp02 != 0 || temp03 != 0))//
					{
						ImagedataOut[3 * (Size1 * i + j) + 0] = temp01;
						ImagedataOut[3 * (Size1 * i + j) + 1] = temp02;
						ImagedataOut[3 * (Size1 * i + j) + 2] = temp03;
					}
				}
			}
		}
	}
}

void P1_c(int BytesPerPixel, char *a1, char *a2, char *a3, int Size1, int Size2)
{
	FILE *file;

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	int Size3 = 350, Size4 = 197, len1 = 350, len2 = 197;
	double cuti, cutj, cutx, cuty, cutxp, cutyp, cutip, cutjp;


	if (!(file = fopen(a3, "rb"))) {
		cout << "Cannot open file: " << a3 << endl;
		exit(1);
	}
	fread(Imagedataori, sizeof(unsigned char), len2*len1*BytesPerPixel, file);
	fclose(file);

	double x[4] = { 0 }, y[4] = { 0 }, ox[4], oy[4];

	x[0] = jtox(0); y[0] = itoy(0, Size4);
	x[1] = jtox(349); y[1] = itoy(0, Size4);
	x[2] = jtox(349); y[2] = itoy(196, Size4);
	x[3] = jtox(0); y[3] = itoy(196, Size4);

	cout << "The origin Cordinate is: " << endl;
	cout << "The X is: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << x[s] << endl;
	}
	cout << endl;
	cout << "The Y is: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << y[s] << endl;
	}

	double oi[4] = { 0 }, oj[4] = { 0 };
	cout << "Input the pixel coordinate of four points (for each point, i first, then j):" << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << "the No." << s + 1 << " point is: ";
		cin >> oi[s] >> oj[s];//in put the pixel location of the trojans corresponding to the one in the output image you want to put the trojans
		//first coordinate is the top left, then top right, then bottom right, last is the bottom left
	}

	ox[0] = jtox(oj[0]); oy[0] = itoy(oi[0], Size2);
	ox[1] = jtox(oj[1]); oy[1] = itoy(oi[1], Size2);
	ox[2] = jtox(oj[2]); oy[2] = itoy(oi[2], Size2);
	ox[3] = jtox(oj[3]); oy[3] = itoy(oi[3], Size2);

	//ox[0] = 326.5; oy[0] = 53.5;
	//ox[1] = 542.5; oy[1] = 218.5;
	//ox[2] = 713.5; oy[2] = 213.5;
	//ox[3] = 652.5; oy[3] = 31.5;

	cout << "The new Cordinate is: " << endl;

	cout << "The X is: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << ox[s] << endl;
	}

	cout << endl;
	cout << "The Y is: " << endl;
	for (int s = 0; s < 4;s++)
	{
		cout << oy[s] << endl;
	}

	cout << "INPUT THE STATISTIC INTO MATLAB: " << endl;
	system("pause");

	//double x1[2], x2[2], x3[2], x4[2];
	double ai, bi, ci, di, ei, fi, gi, hi;

	//x1[0] = ox[0]; x2[0] = ox[1]; x3[0] = ox[2]; x4[0] = ox[3];
	//x1[1] = oy[0]; x2[1] = oy[1]; x3[1] = oy[2]; x4[1] = oy[3];

	//ai = 0.0;
	//bi = 0.7381;
	//ci = 101.0802;
	//di = -0.9845;
	//ei = 0.1674;
	//fi = 600.9083;
	//gi = 0.0;
	//hi = -0.001;

	cout << "Input the 8 parameters: a,b,c,d,e,f,g and h: " << endl;
	cin >> ai >> bi >> ci >> di >> ei >> fi >> gi >> hi;
	HT(ai, bi, ci, di, ei, fi, gi, hi, Imagedataori, Imagedata, Size1, Size2, Size3, Size4);
	
	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);
	system("pause");
}
