// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Skeletonizing for P3_b
//*********************************************************



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedataori[100000000];
extern unsigned char ImagedataPex[100000000];
extern unsigned char ImagedataPexM[100000000];
extern unsigned char ImagedataPOut[100000000];
extern unsigned char ImagedataP[100000000];
unsigned char ImagedataPro[100000000] = { 0 };
unsigned char ImagedataProEdg[100000000] = { 0 };
unsigned char ImagedataProEdg1[100000000] = { 0 };

const int L = 30;
const double Pi = 3.1415926;

extern double abso(double a);
extern void Ext_i(int BytesPerPixel, int Size1, int Size2, unsigned char *ImagedataP, unsigned char *ImagedataPex);
extern int Bond(int *a);
extern int St2I(int *a);
extern void Pixelto1(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *ImagedataP);

void Shrink_d(int BytesPerPixel, int Size1, int Size2, unsigned char *ImagedataP, unsigned char *Imagedata)
//shrink the image to get the simple points which means the number of objects
//the basic function is similar with the one in the P3_a
{
	Ext_i(BytesPerPixel, Size1, Size2, ImagedataP, ImagedataPex);
	int dist = 1;
	int k0 = 1;
	do//for (int g = 0; g < 1; g++)//
	{
		dist = 0;
		for (int s = 0; s < BytesPerPixel; s++)
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
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
				for (int j = 0; j < Size1; j++)
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
						if (ind == 32 || ind == 128 || ind == 2 || ind == 8)
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
						else
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
					double temp;
					temp = abso(ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] - ImagedataPex[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s]);
					//cout << temp << endl;
					dist = dist + temp;
				}
			}
		}
		Ext_i(BytesPerPixel, Size1, Size2, ImagedataPOut, ImagedataPex);
		k0++;
	} while (dist > 0);//

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

void WNoCo(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *ImagedataPro, int ind)
{
	int white = 0;
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				ImagedataPro[BytesPerPixel * ((Size1) * (i)+(j)) + s] = Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
			}
		}
	}
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2 - L/2; i++)
		{
			for (int j = 0; j < Size1 - L; j++)
			{
				int a[5] = {0};
				a[0] = Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
				a[1] = Imagedata[BytesPerPixel * ((Size1) * (i)+(j + L)) + s];
				a[2] = Imagedata[BytesPerPixel * ((Size1) * (i + L / 2)+(j + L / 2)) + s];
				a[3] = Imagedata[BytesPerPixel * ((Size1) * (i - L / 2)+(j + L / 2)) + s];
				a[4] = Imagedata[BytesPerPixel * ((Size1) * (i)+(j + L / 2)) + s];
				if (a[0] == 255 && a[1] == 255 && a[2] == 255 && a[3] == 255 && a[4] == 0)//detect the holes in the image
				{
					for (int is = i - L / 2; is < i + L / 2; is++)
					{
						if (Imagedata[BytesPerPixel * ((Size1) * (is)+(j)) + s] == 255 && Imagedata[BytesPerPixel * ((Size1) * (is)+(j + L)) + s] == 255)
						{
							for (int js = j; js < j + L; js++)
							{
								if (Imagedata[BytesPerPixel * ((Size1) * (is)+(js)) + s] == 0)
								{
									ImagedataPro[BytesPerPixel * ((Size1) * (is)+(js)) + s] = 255;//fill the holes in the image
									Imagedata[BytesPerPixel * ((Size1) * (is)+(js)) + s] = 255;
								}
							}
						}
					}
				}
			}
		}
		Pixelto1(BytesPerPixel, Size1, Size2, ImagedataPro, ImagedataP);
		Shrink_d(BytesPerPixel, Size1, Size2, ImagedataP, ImagedataPOut);//count the number of the pattern in the image filter the holes
		for (int s = 0; s < BytesPerPixel; s++)
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					if (ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] == 255)
					{
						white++;
					}
				}
			}
		}
	}
	if (ind == 1)
	{
		cout << "The number of white object is: ";
		cout << white << endl;
	}
	
}

void HNoCo(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *ImagedataPro)
{
	int hole = 0;
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				ImagedataPro[BytesPerPixel * ((Size1) * (i)+(j)) + s] = Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
			}
		}
	}
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2 - L / 2; i++)
		{
			for (int j = 0; j < Size1 - L; j++)
			{
				int a[5] = { 0 };
				a[0] = Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
				a[1] = Imagedata[BytesPerPixel * ((Size1) * (i)+(j + L)) + s];
				a[2] = Imagedata[BytesPerPixel * ((Size1) * (i + L / 2) + (j + L / 2)) + s];
				a[3] = Imagedata[BytesPerPixel * ((Size1) * (i - L / 2) + (j + L / 2)) + s];
				a[4] = Imagedata[BytesPerPixel * ((Size1) * (i)+(j + L / 2)) + s];
				if (a[0] == 255 && a[1] == 255 && a[2] == 255 && a[3] == 255 && a[4] == 0)//detect the holes in the image
				{
					for (int is = i - L / 2; is < i + L / 2; is++)
					{
						if (Imagedata[BytesPerPixel * ((Size1) * (is)+(j)) + s] == 255 && Imagedata[BytesPerPixel * ((Size1) * (is)+(j + L)) + s] == 255)
						{
							for (int js = j; js < j + L; js++)
							{
								if (Imagedata[BytesPerPixel * ((Size1) * (is)+(js)) + s] == 0)
								{
									ImagedataPro[BytesPerPixel * ((Size1) * (is)+(js)) + s] = 128;//mark the holes in the image
									Imagedata[BytesPerPixel * ((Size1) * (is)+(js)) + s] = 128;
								}
							}
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
					if (Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] == 128)//plot the holes in the image
					{
						ImagedataPro[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					else
					{
						ImagedataPro[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
				}
			}
		}
		Pixelto1(BytesPerPixel, Size1, Size2, ImagedataPro, ImagedataP);
		Shrink_d(BytesPerPixel, Size1, Size2, ImagedataP, ImagedataPOut);
		for (int s = 0; s < BytesPerPixel; s++)
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					if (ImagedataPOut[BytesPerPixel * ((Size1) * (i)+(j)) + s] == 255)
					{
						hole++;
					}
				}
			}
		}
	}
	cout << "The number of holes is: ";
	cout << hole << endl;
}

void Edg(int BytesPerPixel, int Size1, int Size2, unsigned char *ImagedataPro, unsigned char *ImagedataProEdg)
//get the edge of the patterns
{
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 1; i < Size2 - 1; i++)
		{
			for (int j = 1; j < Size1 - 1; j++)
			{
				if (ImagedataPro[BytesPerPixel * ((Size1) * (i)+(j)) + s] == 0)
				{
					ImagedataProEdg[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
				}
				else
				{
					int a[8] = { 0 };
					a[0] = ImagedataPro[BytesPerPixel * ((Size1) * (i - 1) + (j - 1)) + s];
					a[1] = ImagedataPro[BytesPerPixel * ((Size1) * (i - 1) + (j + 0)) + s];
					a[2] = ImagedataPro[BytesPerPixel * ((Size1) * (i - 1) + (j + 1)) + s];
					a[3] = ImagedataPro[BytesPerPixel * ((Size1) * (i + 0) + (j - 1)) + s];
					a[4] = ImagedataPro[BytesPerPixel * ((Size1) * (i + 0) + (j + 1)) + s];
					a[5] = ImagedataPro[BytesPerPixel * ((Size1) * (i + 1) + (j - 1)) + s];
					a[6] = ImagedataPro[BytesPerPixel * ((Size1) * (i + 1) + (j + 0)) + s];
					a[7] = ImagedataPro[BytesPerPixel * ((Size1) * (i + 1) + (j + 1)) + s];
					if (a[1] == 255 && a[3] == 255 && a[4] == 255 && a[6] == 255)
					{
						ImagedataProEdg[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					else
					{
						ImagedataProEdg[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
				}
			}
		}
	}

}

void Class(int BytesPerPixel, int Size1, int Size2, unsigned char *ImagedataPro, unsigned char *ImagedataProEdg)
{
	int ie[20][960] = { 0 }, je[20][960] = { 0 };
	int k = 0;
	int dist = 1;
	int index1[20] = { 0 };
	int index2 = 0;
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				ImagedataProEdg1[BytesPerPixel * ((Size1) * (i)+(j)) + s] = ImagedataProEdg[BytesPerPixel * ((Size1) * (i)+(j)) + s];
			}
		}
	}
	while (dist != 0)
	{
		dist = 0;
		int a0 = 0;
		for (int s = 0; s < BytesPerPixel; s++)
		{
			for (int i = 1; i < Size2 - 1; i++)
			{
				for (int j = 1; j < Size1 - 1; j++)//get the coordinates of each edges
				{
					if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i)+(j)) + s] == 255)
					{
						a0 = 1;
						//cout << i << '\t' << j << endl;
						int ind = 1, l = 0;
						int i0 = i, j0 = j;
						do
						{
							ie[k][l] = i0;
							je[k][l] = j0;
							ImagedataProEdg1[BytesPerPixel * ((Size1) * (i0)+(j0)) + s] = 0;
							if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i0)+(j0 + 1)) + s] == 255)//justify if the pixel is belong to the edge of image
							{
								i0 = i0;
								j0 = j0 + 1;
								l++;
							}
							else if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i0 + 1)+(j0 + 1)) + s] == 255)
							{
								i0 = i0 + 1;
								j0 = j0 + 1;
								l++;
							}
							else if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i0 + 1)+(j0)) + s] == 255)
							{
								i0 = i0 + 1;
								j0 = j0;
								l++;
							}
							else if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i0 + 1)+(j0 - 1)) + s] == 255)
							{
								i0 = i0 + 1;
								j0 = j0 - 1;
								l++;
							}
							else if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i0)+(j0 - 1)) + s] == 255)
							{
								i0 = i0;
								j0 = j0 - 1;
								l++;
							}
							else if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i0 - 1)+(j0 - 1)) + s] == 255)
							{
								i0 = i0 - 1;
								j0 = j0 - 1;
								l++;
							}
							else if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i0 - 1)+(j0)) + s] == 255)
							{
								i0 = i0 - 1;
								j0 = j0;
								l++;
							}
							else if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i0 - 1)+(j0 + 1)) + s] == 255)
							{
								i0 = i0 - 1;
								j0 = j0 + 1;
								l++;
							}
							else
							{
								ind = 0;
								l++;
							}
						} while (ind == 1);
						index1[k] = l;
						//cout << l << endl;
						break;
					}
				}
				if (a0)
				{
					break;
				}
			}
			if (a0)
			{
				break;
			}
		}

		for (int s = 0; s < BytesPerPixel; s++)
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)//detect if the images has been checked completely
				{
					if (ImagedataProEdg1[BytesPerPixel * ((Size1) * (i)+(j)) + s] != 0)
					{
						dist++;
					}
				}
			}
		}
		//cout << dist << endl;
		k++;
	} 
	index2 = k;
	int iem[20][2] = { 0 };
	for (int k0 = 0; k0 < index2; k0++)
	{
		int imax = 0, imim = 480;
		for (int k1 = 0; k1 < index1[k0]; k1++)//get the maxomum of the i for each pattern
		{
			if (imax < ie[k0][k1])
			{
				imax = ie[k0][k1];
			}
			if (imim > ie[k0][k1])
			{
				imim = ie[k0][k1];
			}
		}
		iem[k0][0] = imim;
		iem[k0][1] = imax;
		//cout << iem[k0][0] << '\t' << iem[k0][1] << endl;
	}
	int area[20] = { 0 };
	for (int k0 = 0; k0 < index2; k0++)//calculate the area value for each pattern
	{
		int areatemp = 0;
		int jmax = 0, jmim = 480;
		for (int i = iem[k0][0]; i <= iem[k0][1]; i++)
		{
			for (int k1 = 0; k1 < index1[k0]; k1++)
			{
				if (ie[k0][k1] == i)
				{
					if (jmax < je[k0][k1])
					{
						jmax = je[k0][k1];
					}
					if (jmim > je[k0][k1])
					{
						jmim = je[k0][k1];
					}
				}
			}
			areatemp = areatemp + jmax - jmim;
		}
		area[k0] = areatemp;
		//cout << area[k0] << endl;
	}
	int len[20] = { 0 };
	for (int s = 0; s < BytesPerPixel; s++)//calculate the length for each pattern
	{
		for (int k0 = 0; k0 < index2; k0++)
		{
			int lentemp = 0;
			for (int k1 = 0; k1 < index1[k0]; k1++)
			{
				int i0, j0;
				int a0 = 0;
				i0 = ie[k0][k1];
				j0 = je[k0][k1];
				int a[8] = { 0 };
				a[0] = (int)ImagedataPro[BytesPerPixel * ((Size1) * (i0 - 1)+(j0 - 1)) + s] / 255;
				a[1] = (int)ImagedataPro[BytesPerPixel * ((Size1) * (i0 - 1)+(j0)) + s] / 255;
				a[2] = (int)ImagedataPro[BytesPerPixel * ((Size1) * (i0 - 1)+(j0 + 1)) + s] / 255;
				a[3] = (int)ImagedataPro[BytesPerPixel * ((Size1) * (i0)+(j0 - 1)) + s] / 255;
				a[4] = (int)ImagedataPro[BytesPerPixel * ((Size1) * (i0)+(j0 + 1)) + s] / 255;
				a[5] = (int)ImagedataPro[BytesPerPixel * ((Size1) * (i0 + 1)+(j0 - 1)) + s] / 255;
				a[6] = (int)ImagedataPro[BytesPerPixel * ((Size1) * (i0 + 1)+(j0)) + s] / 255;
				a[7] = (int)ImagedataPro[BytesPerPixel * ((Size1) * (i0 + 1)+(j0 + 1)) + s] / 255;
				a0 = St2I(a);
				if (a0 == 107 || a0 == 248 || a0 == 214 || a0 == 31)
				{
					lentemp = lentemp + 1;
				}
				else if (a[1] == 1 && a[2] == 1 && a[4] == 1 && a[3] == 0 && a[5] == 0 && a[6] == 0)
				{
					lentemp = lentemp + 2;
				}
				else if (a[1] == 0 && a[2] == 0 && a[4] == 0 && a[3] == 1 && a[5] == 1 && a[6] == 1)
				{
					lentemp = lentemp + 2;
				}
				else if (a[0] == 1 && a[1] == 1 && a[3] == 1 && a[4] == 0 && a[6] == 0 && a[7] == 0)
				{
					lentemp = lentemp + 2;
				}
				else if (a[0] == 0 && a[1] == 0 && a[3] == 0 && a[4] == 1 && a[6] == 1 && a[7] == 1)
				{
					lentemp = lentemp + 2;
				}
			}
			len[k0] = lentemp;
			//cout << len[k0] << endl;
		}
	}
	double c[20] = { 0 };
	for (int s = 0; s < BytesPerPixel; s++)//calculate the C
	{
		for (int k0 = 0; k0 < index2; k0++)
		{
			double ctemp = 0.0;
			ctemp = 4 * Pi * (double)(area[k0]) / ((double)len[k0] * (double)len[k0]);
			c[k0] = ctemp;
			//cout << c[k0] << endl;
		}
	}
	int circle = 0, rec = 0;
	for (int s = 0; s < BytesPerPixel; s++)//justify the shape of the patterns
	{
		for (int k0 = 0; k0 < index2; k0++)
		{
			if (c[k0] >= 0.8)
				circle++;
			else
				rec++;
		}
	}
	cout << "The number of white circles is: ";
	cout << circle << endl;
	cout << "The number of white squares is: ";
	cout << rec << endl;
}

void P3_d(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
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

	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedataori[BytesPerPixel * ((Size1) * (i)+(j)) + s] = Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
			}
		}
	}

	//Pixelto1(BytesPerPixel, Size1, Size2, Imagedata, ImagedataP);
	int sub = 1;
	cout << "Input the subquestion want to solve" << endl;
	cout << " 1) The number of the white objects " << endl;
	cout << " 2) The number of holes " << endl;
	cout << " 3) The number of squares and cicles: " << endl;
	cin >> sub;
	if (sub == 1)
	{
		WNoCo(BytesPerPixel, Size1, Size2, Imagedata, ImagedataPro, 1);
	}
	else if (sub == 2)
	{
		HNoCo(BytesPerPixel, Size1, Size2, Imagedata, ImagedataPro);
	}
	else if (sub == 3)
	{
		WNoCo(BytesPerPixel, Size1, Size2, Imagedata, ImagedataPro, 0);
		Edg(BytesPerPixel, Size1, Size2, ImagedataPro, ImagedataProEdg);
		Class(BytesPerPixel, Size1, Size2, ImagedataPro, ImagedataProEdg);
	}



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