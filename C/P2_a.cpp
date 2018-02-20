// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Dither Matrix for P2_a
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
unsigned char Imagedatasub1[100000000] = { 0 };
unsigned char Imagedatas1[100000000] = { 0 };

void Bayer(int N, double *a) // build the Bayer Matrix Size is 2^N x 2^N
{
	double N0, N1;
	N1 = 2 * N;
	N0 = 2 << N;
	a[0] = 0;
	double temp[1024] = { 0 };
	for (int n = 0; n < N; n++)
	{
		int Size = sqrt(1 << (2*n));
		//cout << Size << endl;
		for (int s = 0; s < Size;s++)
		{
			for (int t = 0; t < Size;t++)
			{
				a[Size * 2 * s + t] = 4 * temp[Size * s + t];
			}
		}
		for (int s = 0; s < Size;s++)
		{
			for (int t = 0; t < Size;t++)
			{
				a[Size * 2 * s + (t + Size)] = 4 * temp[Size * s + t] + 2;
			}
		}
		for (int s = 0; s < Size;s++)
		{
			for (int t = 0; t < Size;t++)
			{
				a[Size * 2 * (s + Size) + (t)] = 4 * temp[Size * s + t] + 3;
			}
		}
		for (int s = 0; s < Size;s++)
		{
			for (int t = 0; t < Size;t++)
			{
				a[Size * 2 * (s + Size) + (t + Size)] = 4 * temp[Size * s + t] + 1;
			}
		}
		for (int j = 0; j < 2 * 2 * Size * Size; j++)
		{
			temp[j] = a[j];
		}
	}
}

void P2_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	double a[1024] = { 0 };

	int c, c0;
	int aa;
	cout << "which Bayer Matrix use: 1)standard 2) different Matrix 3) 4-level: ";
	cin >> aa;
	if (aa == 1 || aa == 2)
	{
		if (aa == 1)//for the standard Bayer Matrix
		{
			cout << "Input the Size of Bayer Matrix: ";
			cin >> c0;
			c = log2(c0);
			Bayer(c, a);
		}
		else if (aa == 2)//for the different 4x4 Bayer Matrix
		{
			c = 2;
			c0 = 4;
			a[0] = 14; a[1] = 10; a[2] = 11; a[3] = 15;
			a[4] = 9; a[5] = 3; a[6] = 0; a[7] = 4;
			a[8] = 8; a[9] = 2; a[10] = 1; a[11] = 5;
			a[12] = 13; a[13] = 7; a[14] = 6; a[15] = 12;
		}


		cout << c << endl;



		for (int i = 0; i < c0; i++)
		{
			for (int j = 0; j < c0; j++)
			{
				cout << a[c0 * i + j] << '\t';
			}
			cout << endl;
		}

		for (int i = 0; i < (1 << (2 * c));i++)
		{
			a[i] = a[i] / (1 << (2 * c)) * 255;
		}

		//for (int i = 0; i < c0; i++)
		//{
		//	for (int j = 0; j < c0; j++)
		//	{
		//		cout << a[c0 * i + j] << '\t';
		//	}
		//	cout << endl;
		//}

		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				int a0 = i % (2 * c), b0 = j % (2 * c);
				if (Imagedata[1 * (Size1 * i + j) + 0] > a[c0 * a0 + b0])
				{
					Imagedata[1 * (Size1 * i + j) + 0] = 255;
				}
				else
				{
					Imagedata[1 * (Size1 * i + j) + 0] = 0;
				}
			}
		}
	}
	else if (aa == 3)//4-level outputs
	{
		c = 2;
		c0 = 4;
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				if (Imagedata[1 * (Size1 * i + j) + 0] == 0)//devide each pixel into three parts
				{
					Imagedatasub1[3 * (Size1 * i + j) + 0] = 0;
					Imagedatasub1[3 * (Size1 * i + j) + 1] = 0;
					Imagedatasub1[3 * (Size1 * i + j) + 2] = 0;
				}
				else if (Imagedata[1 * (Size1 * i + j) + 0] >= 1 && Imagedata[1 * (Size1 * i + j) + 0] <= 85)
				{
					Imagedatasub1[3 * (Size1 * i + j) + 0] = Imagedata[1 * (Size1 * i + j) + 0];
					Imagedatasub1[3 * (Size1 * i + j) + 1] = 0;
					Imagedatasub1[3 * (Size1 * i + j) + 2] = 0;
				}
				else if (Imagedata[1 * (Size1 * i + j) + 0] >= 86 && Imagedata[1 * (Size1 * i + j) + 0] <= 170)
				{
					Imagedatasub1[3 * (Size1 * i + j) + 0] = 85;
					Imagedatasub1[3 * (Size1 * i + j) + 1] = Imagedata[1 * (Size1 * i + j) + 0] - 85;
					Imagedatasub1[3 * (Size1 * i + j) + 2] = 0;
				}
				else if (Imagedata[1 * (Size1 * i + j) + 0] >= 171 && Imagedata[1 * (Size1 * i + j) + 0] <= 255)
				{
					Imagedatasub1[3 * (Size1 * i + j) + 0] = 85;
					Imagedatasub1[3 * (Size1 * i + j) + 1] = 85;
					Imagedatasub1[3 * (Size1 * i + j) + 2] = Imagedata[1 * (Size1 * i + j) + 0] - 85 - 85;
				}
			}
		}
		Bayer(c, a);//contruct the Bayer Matrix
		for (int i = 0; i < c0; i++)
		{
			for (int j = 0; j < c0; j++)
			{
				cout << a[c0 * i + j] << '\t';
			}
			cout << endl;
		}

		for (int i = 0; i < (1 << (2 * c));i++)
		{
			a[i] = a[i] / (1 << (2 * c)) * 85;
		}

		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)//do the halftone for each part
			{
				int a0 = i % (2 * c), b0 = j % (2 * c);
				if (Imagedatasub1[3 * (Size1 * i + j) + 0] > a[c0 * a0 + b0])
				{
					Imagedatas1[3 * (Size1 * i + j) + 0] = 85;
				}
				else
				{
					Imagedatas1[3 * (Size1 * i + j) + 0] = 0;
				}
			}
		}
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				int a0 = i % (2 * c), b0 = j % (2 * c);
				if (Imagedatasub1[3 * (Size1 * i + j) + 1] > a[c0 * a0 + b0])
				{
					Imagedatas1[3 * (Size1 * i + j) + 1] = 85;
				}
				else
				{
					Imagedatas1[3 * (Size1 * i + j) + 1] = 0;
				}
			}
		}
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				int a0 = i % (2 * c), b0 = j % (2 * c);
				if (Imagedatasub1[3 * (Size1 * i + j) + 2] > a[c0 * a0 + b0])
				{
					Imagedatas1[3 * (Size1 * i + j) + 2] = 85;
				}
				else
				{
					Imagedatas1[3 * (Size1 * i + j) + 2] = 0;
				}
			}
		}
		for (int i = 0; i < Size2; i++)//combine every parts together
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedata[1 * (Size1 * i + j) + 0] = Imagedatas1[3 * (Size1 * i + j) + 0] + Imagedatas1[3 * (Size1 * i + j) + 1] + Imagedatas1[3 * (Size1 * i + j) + 2];
			}
		}
	}



	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);
	system("pause");
}