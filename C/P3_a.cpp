// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Shrinking for P3_a
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
extern unsigned char ImagedataPex[100000000];
extern unsigned char ImagedataPexM[100000000];
extern unsigned char ImagedataPOut[100000000];
extern unsigned char ImagedataP[100000000];

extern double abso(double a);

void Ext_i(int BytesPerPixel, int Size1, int Size2, unsigned char *ImagedataP, unsigned char *ImagedataPex)//extend the image from x * y to be (x + 2) * (y * 2)
{
	if (BytesPerPixel == 3)
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				ImagedataPex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = ImagedataP[3 * (Size1 * i + j) + 0];
				ImagedataPex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 1] = ImagedataP[3 * (Size1 * i + j) + 1];
				ImagedataPex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 2] = ImagedataP[3 * (Size1 * i + j) + 2];
			}
		}
		for (int j = 0; j < Size1; j++)
		{
			ImagedataPex[3 * ((Size1 + 2) * 0 + j + 1) + 0] = ImagedataP[3 * (Size1 * 0 + j) + 0];
			ImagedataPex[3 * ((Size1 + 2) * 0 + j + 1) + 1] = ImagedataP[3 * (Size1 * 0 + j) + 1];
			ImagedataPex[3 * ((Size1 + 2) * 0 + j + 1) + 2] = ImagedataP[3 * (Size1 * 0 + j) + 2];
			ImagedataPex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = ImagedataP[3 * (Size1 * (Size2 - 1) + j) + 0];
			ImagedataPex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 1] = ImagedataP[3 * (Size1 * (Size2 - 1) + j) + 1];
			ImagedataPex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 2] = ImagedataP[3 * (Size1 * (Size2 - 1) + j) + 2];
		}
		for (int i = 0; i < (Size2 + 2); i++)
		{
			ImagedataPex[3 * ((Size1 + 2) * i + 0) + 0] = ImagedataPex[3 * ((Size1 + 2) * i + 1) + 0];
			ImagedataPex[3 * ((Size1 + 2) * i + 0) + 1] = ImagedataPex[3 * ((Size1 + 2) * i + 1) + 1];
			ImagedataPex[3 * ((Size1 + 2) * i + 0) + 2] = ImagedataPex[3 * ((Size1 + 2) * i + 1) + 2];
			ImagedataPex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 0] = ImagedataPex[3 * ((Size1 + 2) * i + Size2) + 0];
			ImagedataPex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 1] = ImagedataPex[3 * ((Size1 + 2) * i + Size2) + 1];
			ImagedataPex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 2] = ImagedataPex[3 * ((Size1 + 2) * i + Size2) + 2];
		}
	}
	else if (BytesPerPixel == 1)
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				ImagedataPex[1 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = ImagedataP[1 * (Size1 * i + j) + 0];
			}
		}
		for (int j = 0; j < Size1; j++)
		{
			ImagedataPex[1 * ((Size1 + 2) * 0 + j + 1) + 0] = ImagedataP[1 * (Size1 * 0 + j) + 0];
			ImagedataPex[1 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = ImagedataP[1 * (Size1 * (Size2 - 1) + j) + 0];
		}
		for (int i = 0; i < (Size2 + 2); i++)
		{
			ImagedataPex[1 * ((Size1 + 2) * i + 0) + 0] = ImagedataPex[1 * ((Size1 + 2) * i + 1) + 0];
			ImagedataPex[1 * ((Size1 + 2) * i + (Size2 + 1)) + 0] = ImagedataPex[1 * ((Size1 + 2) * i + Size2) + 0];
		}
	}
}

int Bond(int *a)//calculate the bond of the pixel if the pixel is 1
{
	int sum = 0, sum1 = 0, sum2 = 0;
	sum1 = a[0] + a[2] + a[5] + a[7];
	sum2 = 2 * (a[1] + a[3] + a[4] + a[6]);
	sum = sum1 + sum2;
	return sum;
}

int St2I(int *a)//calculate the number constructed by pixels around a pixel
{
	int sum = 0;
	for (int i = 0; i < 8; i++)
	{
		sum = (sum << 1) + a[i];
	}
	return sum;
}

void Pixelto1(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *ImagedataP)// turn the pixels value from 255 to 1
{
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				if (Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] >= 128)
				{
					ImagedataP[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
				}
				else
				{
					ImagedataP[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
				}
			}
		}
	}
}

void Shrink(int BytesPerPixel, int Size1, int Size2, unsigned char *ImagedataP, unsigned char *Imagedata)
{
	Ext_i(BytesPerPixel, Size1, Size2, ImagedataP, ImagedataPex);
	int dist = 1, sinsea = 0, dusea = 0, num = 0;
	int b[480] = { 0 }, b1[480] = { 0 };
	int k0 = 1;
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				if (ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] == 1)
				{
					int ind, ind1;
					int a[8] = { 0 }, a1[8] = { 0 };
					a[0] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 0) + (j + 0)) + s];
					a[1] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 0) + (j + 1)) + s];
					a[2] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 0) + (j + 2)) + s];
					a[3] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s];
					a[4] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s];
					a[5] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
					a[6] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
					a[7] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
					a1[0] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s];
					a1[1] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s];
					a1[2] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 3)) + s];
					a1[3] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
					a1[4] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 3)) + s];
					a1[5] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 3) + (j + 1)) + s];
					a1[6] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 3) + (j + 2)) + s];
					a1[7] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 3) + (j + 3)) + s];
					ind = St2I(a);
					ind1 = St2I(a1);
					//cout << ind << endl;
					if (ind == 0)//calculate the number of the single point
					{
						sinsea++;
					}
					else if (ind == 11 && ind1 == 208)
					{
						dusea++;//calculate the number of the 2x2 square
					}
				}
			}
		}
	}
	b[0] = sinsea;
	b1[0] = dusea;
	do//for (int g = 0; g < 1; g++)//
	{
		sinsea = 0;
		dusea = 0;
		dist = 0;
		for (int s = 0; s < BytesPerPixel; s++)
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)//check if a pixel can be the candidate of the delete
				{
					if (ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] == 0)
					{
						ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
						ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					else
					{
						int bo, ind;
						int a[8] = { 0 };
						a[0] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 0) + (j + 0)) + s];
						a[1] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 0) + (j + 1)) + s];
						a[2] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 0) + (j + 2)) + s];
						a[3] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s];
						a[4] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s];
						a[5] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						a[6] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						a[7] = ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						bo = Bond(a);
						//cout << bo << endl;
						ind = St2I(a);
						//cout << ind << endl;
						if (bo == 1)
						{
							if (ind == 1 || ind == 4 || ind == 32 || ind == 128)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else if (bo == 2)
						{
							if (ind == 2 || ind == 8 || ind == 16 || ind == 64)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else if (bo == 3)
						{
							if (ind == 40 || ind == 96 || ind == 192 || ind == 144 || ind == 20 || ind == 6 || ind == 3 || ind == 9)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else if (bo == 4)
						{
							if (ind == 41 || ind == 224 || ind == 148 || ind == 7)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else if (bo == 5)
						{
							if (ind == 200 || ind == 73 || ind == 112 || ind == 42 || ind == 104 || ind == 208 || ind == 22 || ind == 11)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else if (bo == 6)
						{
							if (ind == 201 || ind == 116 || ind == 232 || ind == 105 || ind == 240 || ind == 212 || ind == 150 || ind == 23 || ind == 15 || ind == 43)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else if (bo == 7)
						{
							if (ind == 233 || ind == 244 || ind == 151 || ind == 47)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else if (bo == 8)
						{
							if (ind == 107 || ind == 248 || ind == 214 || ind == 31)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else if (bo == 9)
						{
							if (ind == 235 || ind == 111 || ind == 252 || ind == 249 || ind == 246 || ind == 215 || ind == 159 || ind == 63)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else if (bo == 10)
						{
							if (ind == 239 || ind == 253 || ind == 247 || ind == 191)
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 1;
							}
							else
							{
								ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
								ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
							}
						}
						else
						{
							ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] = 0;
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
					}
				}
			}
		}

		for (int s = 0; s < BytesPerPixel; s++)
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)//check if a candidate pixel should be deleted
				{
					if (ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] == 0)
					{

					}
					else
					{
						int ind;
						int a[8];
						a[0] = ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 0) + (j + 0)) + s];
						a[1] = ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 0) + (j + 1)) + s];
						a[2] = ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 0) + (j + 2)) + s];
						a[3] = ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s];
						a[4] = ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s];
						a[5] = ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						a[6] = ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						a[7] = ImagedataPexM[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						ind = St2I(a);
						//cout << ind << endl;
						if (ind == 32 || ind == 128 || ind == 2 || ind == 8)//if hit, do not delete
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (ind == 112 || ind == 200 || ind == 73 || ind == 42)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 0 && a[3] == 0 && a[6] == 0 && a[7] == 0 && a[2] == 1 && a[5] == 1 && (a[1] == 1 || a[4] == 1))
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[2] == 0 && a[4] == 0 && a[5] == 0 && a[6] == 0 && a[0] == 1 && a[7] == 1 && (a[1] == 1 || a[3] == 1))
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 0 && a[1] == 0 && a[4] == 0 && a[7] == 0 && a[2] == 1 && a[5] == 1 && (a[3] == 1 || a[6] == 1))
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[1] == 0 && a[2] == 0 && a[3] == 0 && a[5] == 0 && a[0] == 1 && a[7] == 1 && (a[4] == 1 || a[6] == 1))
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 1 && a[1] == 1 && a[3] == 1)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[2] == 0 && a[6] == 0 && a[7] == 0 && a[1] == 1 && a[3] == 1 && a[4] == 1)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 0 && a[5] == 0 && a[6] == 0 && a[1] == 1 && a[3] == 1 && a[4] == 1)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 0 && a[1] == 0 && a[5] == 0 && a[6] == 1 && a[3] == 1 && a[4] == 1)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[1] == 0 && a[2] == 0 && a[7] == 0 && a[6] == 1 && a[3] == 1 && a[4] == 1)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[4] == 0 && a[5] == 0 && a[7] == 0 && a[1] == 1 && a[3] == 1 && a[6] == 1)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 0 && a[2] == 0 && a[4] == 0 && a[1] == 1 && a[3] == 1 && a[6] == 1)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 0 && a[2] == 0 && a[3] == 0 && a[1] == 1 && a[4] == 1 && a[6] == 1)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[3] == 0 && a[5] == 0 && a[7] == 0 && a[1] == 1 && a[4] == 1 && a[6] == 1)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 1 && a[2] == 1 && (a[5] == 1 || a[6] == 1 || a[7] == 1))
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 1 && a[5] == 1 && (a[2] == 1 || a[4] == 1 || a[7] == 1))
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[5] == 1 && a[7] == 1 && (a[0] == 1 || a[1] == 1 || a[2] == 1))
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[2] == 1 && a[7] == 1 && (a[0] == 1 || a[3] == 1 || a[5] == 1))
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[1] == 1 && a[4] == 1 && a[5] == 1 && a[2] == 0 && a[3] == 0 && a[6] == 0)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[1] == 1 && a[3] == 1 && a[7] == 1 && a[0] == 0 && a[4] == 0 && a[6] == 0)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[2] == 1 && a[3] == 1 && a[6] == 1 && a[1] == 0 && a[4] == 0 && a[5] == 0)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else if (a[0] == 1 && a[4] == 1 && a[6] == 1 && a[1] == 0 && a[3] == 0 && a[7] == 0)
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 1;
						}
						else//if not hit, delete
						{
							ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
						}
					}
				}
			}
		}
		for (int s = 0; s < BytesPerPixel; s++)
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					if (ImagedataPOut[BytesPerPixel * ((Size1) * (i) + (j)) + s] == 0)
					{

					}
					else
					{
						int ind, ind1;
						int a[8] = { 0 }, a1[8] = { 0 };
						a[0] = ImagedataPOut[BytesPerPixel * ((Size1) * (i - 1) + (j - 1)) + s];
						a[1] = ImagedataPOut[BytesPerPixel * ((Size1) * (i - 1) + (j + 0)) + s];
						a[2] = ImagedataPOut[BytesPerPixel * ((Size1) * (i - 1) + (j + 1)) + s];
						a[3] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 0) + (j - 1)) + s];
						a[4] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 0) + (j + 1)) + s];
						a[5] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 1) + (j - 1)) + s];
						a[6] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 1) + (j + 0)) + s];
						a[7] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 1) + (j + 1)) + s];
						a1[0] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 0) + (j + 0)) + s];
						a1[1] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 0) + (j + 1)) + s];
						a1[2] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 0) + (j + 2)) + s];
						a1[3] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 1) + (j + 0)) + s];
						a1[4] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 1) + (j + 2)) + s];
						a1[5] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 2) + (j + 0)) + s];
						a1[6] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 2) + (j + 1)) + s];
						a1[7] = ImagedataPOut[BytesPerPixel * ((Size1) * (i + 2) + (j + 2)) + s];
						ind = St2I(a);
						ind1 = St2I(a1);
						if (ind == 0)//calculate the number of the single points
						{
							sinsea++;
						}
						else if (ind == 11 && ind1 == 208)//calculate the number of the 2x2 squares
						{
							dusea++;
						}
					}
				}
			}
		}
		for (int s = 0; s < BytesPerPixel; s++)//get the difference between the image before shrink and the one after shrink
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					double temp;
					temp = abso(ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] - ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s]);
					//cout << temp << endl;
					dist = dist + temp;
				}
			}
		}
		//cout << dist << endl;
		b[k0] = sinsea;
		b1[k0] = dusea;
		Ext_i(BytesPerPixel, Size1, Size2, ImagedataPOut, ImagedataPex);
		k0++;
		
	}while (dist > 0);//when there is no difference, stop the loop

	cout << "The total number is " << b[k0 - 1] << endl;

	for (int i = 0; i < k0; i++)
	{
		if (i == 0)
		{
			cout << "The number of " << 1 << "x" << 1 << " size is " << b[i] << endl;
			cout << "The number of " << 2 << "x" << 2 << " size is " << b1[i] << endl;
		}
		else
		{
			cout << "The number of " << 2 * i + 1 << "x" << 2 * i + 1 << " size is " << b[i] - b[i - 1] - b1[i - 1] << endl;
			cout << "The number of " << 2 * (i + 1) << "x" << 2 * (i + 1) << " size is " << b1[i] << endl;
		}
	}
	
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				if (ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] == 0)
				{
					Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
				}
				else
				{
					Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
				}
			}
		}
	}
}

void P3_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		system("pause");
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	Pixelto1(BytesPerPixel, Size1, Size2, Imagedata, ImagedataP);

	Shrink(BytesPerPixel, Size1, Size2, ImagedataP, Imagedata);

	//Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataexp);

	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		system("pause");
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), (Size2)*(Size1)*BytesPerPixel, file);
	fclose(file);
	system("pause");
}