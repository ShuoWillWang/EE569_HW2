// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Warpping for P1_a (Professor's method)
//*********************************************************



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char ImagedataOut[100000000];
extern unsigned char Imagedataori[100000000];
extern unsigned char Imagedata1[100000000];

double itoy(double i, int Size2)//change the i in the i-j coordinate to be y in x-y coordinate
{
	double y;
	y = Size2 - i - 1 + 0.5;
	return y;
}

double jtox(double j)//change the j in the i-j coordinate to be x in x-y coordinate
{
	double x;
	x = j + 1 - 0.5;
	return x;
}

double Returny(double y, int Size2)//change y in x-y coordinate to be the i in the i-j coordinate 
{
	double i;
	i = Size2 + 0.5 - y - 1;
	return i;
}

double Returnx(double x)//change x in x-y coordinate to be the j in the i-j coordinate 
{
	double j;
	j = x + 0.5 - 1;
	return j;
}

void Warp(double a, double b, double c, double d, double e, double f, unsigned char *Imagedata, unsigned char *ImagedataOut, int Size1, int Size2, double *x1, double *x2, double *x3)
//warp operation given the A matrix and the output control points
//the output control points should be ordered clockwise
//the size of the input image should be equal to the one of the output image
{
	double x1a[2], x2a[2], x3a[2], x1v[2], x2v[2], x3v[2];
	x1a[0] = x2[0] - x1[0]; x2a[0] = x3[0] - x2[0]; x3a[0] = x1[0] - x3[0]; // get the vector on the edge:(clockwise)
	x1a[1] = x2[1] - x1[1]; x2a[1] = x3[1] - x2[1]; x3a[1] = x1[1] - x3[1];
	x1v[1] = -x1a[0]; x1v[0] = x1a[1];// get the vector orthogonal to the edge
	x2v[1] = -x2a[0]; x2v[0] = x2a[1];
	x3v[1] = -x3a[0]; x3v[0] = x3a[1];
	for (int i = 0; i<Size2; i++)
	{
		for (int j = 0; j<Size1; j++)
		{
			double x, y, temp1, temp2, temp3;
			x = jtox(j);
			y = itoy(i, Size2);
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
				di = (i0 - (int)i0); dj = (j0 - (int)j0);//Bilinear interpolation to get the pixel in the output image from the input pixel
				i00 = (int)i0; j00 = (int)j0;
				i01 = (int)i0; j01 = (int)j0 + 1;
				i10 = (int)i0 + 1; j10 = (int)j0;
				i11 = (int)i0 + 1; j11 = (int)j0 + 1;
				temp = (1 - di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i00 + j00) + 0] + (di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i10 + j10) + 0] + (1 - di)*(dj)*(float)Imagedata[3 * (Size1 * i01 + j01) + 0] + (di)*(dj)*(float)Imagedata[3 * (Size1 * i11 + j11) + 0];
				ImagedataOut[3 * (Size1 * i + j) + 0] = temp;
				temp = (1 - di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i00 + j00) + 1] + (di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i10 + j10) + 1] + (1 - di)*(dj)*(float)Imagedata[3 * (Size1 * i01 + j01) + 1] + (di)*(dj)*(float)Imagedata[3 * (Size1 * i11 + j11) + 1];
				ImagedataOut[3 * (Size1 * i + j) + 1] = temp;
				temp = (1 - di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i00 + j00) + 2] + (di)*(1 - dj)*(float)Imagedata[3 * (Size1 * i10 + j10) + 2] + (1 - di)*(dj)*(float)Imagedata[3 * (Size1 * i01 + j01) + 2] + (di)*(dj)*(float)Imagedata[3 * (Size1 * i11 + j11) + 2];
				ImagedataOut[3 * (Size1 * i + j) + 2] = temp;
				//cout << temp << endl;
			}
		}
	}
}

void P1_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;


	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	double x1[2], x2[2], x3[2];

	x1[0] = 125.0; x2[0] = 249.5; x3[0] = 249.5;//the output control points of the first triangle (order of clockwise)
	x1[1] = 375.0; x2[1] = 499.5; x3[1] = 250.5;
	Warp(2.0, 0.0, -249.5, -1.0, 1.0, 249.5, Imagedata, ImagedataOut, Size1, Size2, x1, x2, x3);
	x1[0] = 125.0; x2[0] = 249.5; x3[0] = 0.5;//the output control points of the second triangle (order of clockwise)
	x1[1] = 375.0; x2[1] = 250.5; x3[1] = 250.5;
	Warp(1.0, -1.0, 250.0, 0.0, 2.0, -250.5, Imagedata, ImagedataOut, Size1, Size2, x1, x2, x3);
	x1[0] = 0.5; x2[0] = 249.5; x3[0] = 125.0;//the output control points of the Third triangle (order of clockwise)
	x1[1] = 250.5; x2[1] = 250.5; x3[1] = 125.5;
	Warp(1, 0.996, -249.498, 0.0, 2.0, -250.5, Imagedata, ImagedataOut, Size1, Size2, x1, x2, x3);
	x1[0] = 125.0; x2[0] = 249.5; x3[0] = 249.5;//the output control points of the forth triangle (order of clockwise)
	x1[1] = 125.5; x2[1] = 250.5; x3[1] = 0.5;
	Warp(2.0, 0.0, -249.5, 1.004, 1.0, -250.502, Imagedata, ImagedataOut, Size1, Size2, x1, x2, x3);
	x1[0] = 250.5; x2[0] = 375.0; x3[0] = 250.5;//the output control points of the fifth triangle (order of clockwise)
	x1[1] = 499.5; x2[1] = 375.0; x3[1] = 250.5;
	Warp(2.0, 0.0, -250.5, 1.0, 1.0, -250.5, Imagedata, ImagedataOut, Size1, Size2, x1, x2, x3);
	x1[0] = 375.0; x2[0] = 499.5; x3[0] = 250.5;//the output control points of the sixth triangle (order of clockwise)
	x1[1] = 375.0; x2[1] = 250.5; x3[1] = 250.5;
	Warp(1.0, 1.0, -250.5, 0.0, 2.0, -250.5, Imagedata, ImagedataOut, Size1, Size2, x1, x2, x3);
	x1[0] = 250.5; x2[0] = 499.5; x3[0] = 375.0;//the output control points of the seventh triangle (order of clockwise)
	x1[1] = 249.5; x2[1] = 249.5; x3[1] = 125.0;
	Warp(1.0, -1.0, 249.5, 0.0, 2.0, -249.5, Imagedata, ImagedataOut, Size1, Size2, x1, x2, x3);
	x1[0] = 250.5; x2[0] = 375.0; x3[0] = 250.5;//the output control points of the eighth triangle (order of clockwise)
	x1[1] = 249.5; x2[1] = 125.0; x3[1] = 0.5;
	Warp(2.0, 0.0, -250.5, -1.0, 1.0, 250.5, Imagedata, ImagedataOut, Size1, Size2, x1, x2, x3);



	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(ImagedataOut, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);
	system("pause");
}