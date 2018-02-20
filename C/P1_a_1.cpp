// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Warpping for P1_a (Diamond)
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

void Diamond(unsigned char *Imagedata, unsigned char *ImagedataOut, int Size1, int Size2, int type)
//the size of the input image should be equal to the one of the output image
{
	if (type == 1)//if it is the top-left part of the image
	{
		for (int i = 0; i<Size2 / 2; i++)
		{
			double delta;
			if (i == 0)
			{
				delta = 0;
			}
			else
			{
				delta = (double)((double)Size2 / 2 - 1) / i;//the sampling distance
			}
			int j0 = Size1 / 2 - 1;
			double j = Size1 / 2 - 1;
			if (delta == 0)//for the top point with only one pixel
			{
				ImagedataOut[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 0] = Imagedata[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 0];
				ImagedataOut[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 1] = Imagedata[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 1];
				ImagedataOut[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 2] = Imagedata[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 2];
			}
			else
			{
				while (j >= 0)//when j is in the range
				{
					double dj, temp01, temp02, temp03;
					int j00, j01;
					dj = (j - (int)j);//Linear interpolation
					j00 = (int)j;
					j01 = (int)j + 1;
					temp01 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 0] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 0];
					temp03 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 2] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 2];
					temp02 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 1] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 1];
					ImagedataOut[3 * (Size1 * i + j0) + 0] = temp01;
					ImagedataOut[3 * (Size1 * i + j0) + 1] = temp02;
					ImagedataOut[3 * (Size1 * i + j0) + 2] = temp03;
					j0--;
					j = j - delta;
				}
			}
		}
	}
	else if (type == 2)//if it is the top-right part of the image
	{
		for (int i = 0; i<Size2 / 2; i++)
		{
			double delta;
			if (i == 0)
			{
				delta = 0;
			}
			else
			{
				delta = (double)((double)Size2 / 2 - 1) / i;//the sampling distance
			}
			int j0 = Size1 / 2 - 1;
			double j = Size1 / 2 - 1;
			if (delta == 0)//for the top point with only one pixel
			{
				ImagedataOut[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 0] = Imagedata[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 0];
				ImagedataOut[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 1] = Imagedata[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 1];
				ImagedataOut[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 2] = Imagedata[3 * (Size1 * 0 + (Size1 / 2 - 1)) + 2];
			}
			else
			{
				while (j < Size1)//when j is in the range
				{
					double dj, temp01, temp02, temp03;
					int j00, j01;
					dj = (j - (int)j);
					j00 = (int)j;
					j01 = (int)j + 1;
					temp01 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 0] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 0];
					temp03 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 2] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 2];
					temp02 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 1] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 1];
					ImagedataOut[3 * (Size1 * i + j0) + 0] = temp01;
					ImagedataOut[3 * (Size1 * i + j0) + 1] = temp02;
					ImagedataOut[3 * (Size1 * i + j0) + 2] = temp03;
					j0++;
					j = j + delta;
				}
			}
		}
	}
	else if (type == 3)//if it is the bottom-left part of the image
	{
		for (int i = Size2 - 1; i >= Size2 / 2; i--)
		{
			double delta;
			if (i == Size2 - 1)
			{
				delta = 0;
			}
			else
			{
				delta = (double)((double)Size2 / 2 - 1) / (Size2 - 1 - i);//the sampling distance
			}
			int j0 = Size1 / 2 - 1;
			double j = Size1 / 2 - 1;
			if (delta == 0)//for the top point with only one pixel
			{
				ImagedataOut[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 0] = Imagedata[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 0];
				ImagedataOut[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 1] = Imagedata[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 1];
				ImagedataOut[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 2] = Imagedata[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 2];
			}
			else
			{
				while (j >= 0)//when j is in the range
				{
					double dj, temp01, temp02, temp03;
					int j00, j01;
					dj = (j - (int)j);
					j00 = (int)j;
					j01 = (int)j + 1;
					temp01 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 0] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 0];
					temp03 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 2] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 2];
					temp02 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 1] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 1];
					ImagedataOut[3 * (Size1 * i + j0) + 0] = temp01;
					ImagedataOut[3 * (Size1 * i + j0) + 1] = temp02;
					ImagedataOut[3 * (Size1 * i + j0) + 2] = temp03;
					j0--;
					j = j - delta;
				}
			}
		}
	}
	else if (type == 4)//if it is the bottom-right part of the image
	{
		for (int i = Size2 - 1; i >= Size2 / 2; i--)
		{
			double delta;
			if (i == Size2 - 1)
			{
				delta = 0;
			}
			else
			{
				delta = (double)((double)Size2 / 2 - 1) / (Size2 - 1 - i);//the sampling distance
			}
			int j0 = Size1 / 2 - 1;
			double j = Size1 / 2 - 1;
			if (delta == 0)//for the top point with only one pixel
			{
				ImagedataOut[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 0] = Imagedata[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 0];
				ImagedataOut[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 1] = Imagedata[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 1];
				ImagedataOut[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 2] = Imagedata[3 * (Size1 * (Size2 - 1) + (Size1 / 2 - 1)) + 2];
			}
			else
			{
				while (j < Size1)//when j is in the range
				{
					double dj, temp01, temp02, temp03;
					int j00, j01;
					dj = (j - (int)j);
					j00 = (int)j;
					j01 = (int)j + 1;
					temp01 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 0] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 0];
					temp03 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 2] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 2];
					temp02 = (1 - dj)*(float)Imagedata[3 * (Size1 * i + j00) + 1] + (dj)*(float)Imagedata[3 * (Size1 * i + j01) + 1];
					ImagedataOut[3 * (Size1 * i + j0) + 0] = temp01;
					ImagedataOut[3 * (Size1 * i + j0) + 1] = temp02;
					ImagedataOut[3 * (Size1 * i + j0) + 2] = temp03;
					j0++;
					j = j + delta;
				}
			}
		}
	}
}

void P1_a_1(int BytesPerPixel, char *a1, char *a2, char *a3, int Size1, int Size2)
{
	FILE *file;

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedataori, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	Diamond(Imagedataori, Imagedata, Size1, Size2, 1);
	Diamond(Imagedataori, Imagedata, Size1, Size2, 2);
	Diamond(Imagedataori, Imagedata, Size1, Size2, 3);
	Diamond(Imagedataori, Imagedata, Size1, Size2, 4);

	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);
	system("pause");
}
