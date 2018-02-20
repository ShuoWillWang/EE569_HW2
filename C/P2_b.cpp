// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
//Error Diffusion for P2_b
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

void Ext(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, short *Imagedataex)//extend the image from x*y to (x+2)*(y+2)(input is char output is short int)
{
	if (BytesPerPixel == 3)
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = Imagedata[3 * (Size1 * i + j) + 0];
				Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 1] = Imagedata[3 * (Size1 * i + j) + 1];
				Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 2] = Imagedata[3 * (Size1 * i + j) + 2];
			}
		}
		for (int j = 0; j < Size1; j++)
		{
			Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 0] = Imagedata[3 * (Size1 * 0 + j) + 0];
			Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 1] = Imagedata[3 * (Size1 * 0 + j) + 1];
			Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 2] = Imagedata[3 * (Size1 * 0 + j) + 2];
			Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 0];
			Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 1] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 1];
			Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 2] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 2];
		}
		for (int i = 0; i < (Size2 + 2); i++)
		{
			Imagedataex[3 * ((Size1 + 2) * i + 0) + 0] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 0];
			Imagedataex[3 * ((Size1 + 2) * i + 0) + 1] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 1];
			Imagedataex[3 * ((Size1 + 2) * i + 0) + 2] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 2];
			Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 0] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 0];
			Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 1] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 1];
			Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 2] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 2];
		}
	}
	else if (BytesPerPixel == 1)
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedataex[1 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = Imagedata[1 * (Size1 * i + j) + 0];
			}
		}
		for (int j = 0; j < Size1; j++)
		{
			Imagedataex[1 * ((Size1 + 2) * 0 + j + 1) + 0] = Imagedata[1 * (Size1 * 0 + j) + 0];
			Imagedataex[1 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = Imagedata[1 * (Size1 * (Size2 - 1) + j) + 0];
		}
		for (int i = 0; i < (Size2 + 2); i++)
		{
			Imagedataex[1 * ((Size1 + 2) * i + 0) + 0] = Imagedataex[1 * ((Size1 + 2) * i + 1) + 0];
			Imagedataex[1 * ((Size1 + 2) * i + (Size2 + 1)) + 0] = Imagedataex[1 * ((Size1 + 2) * i + Size2) + 0];
		}
	}
}

void Ext_c(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedataex)//extend the image from x*y to (x+2)*(y+2)(input is char output is char)
{
	if (BytesPerPixel == 3)
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = Imagedata[3 * (Size1 * i + j) + 0];
				Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 1] = Imagedata[3 * (Size1 * i + j) + 1];
				Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 2] = Imagedata[3 * (Size1 * i + j) + 2];
			}
		}
		for (int j = 0; j < Size1; j++)
		{
			Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 0] = Imagedata[3 * (Size1 * 0 + j) + 0];
			Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 1] = Imagedata[3 * (Size1 * 0 + j) + 1];
			Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 2] = Imagedata[3 * (Size1 * 0 + j) + 2];
			Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 0];
			Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 1] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 1];
			Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 2] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 2];
		}
		for (int i = 0; i < (Size2 + 2); i++)
		{
			Imagedataex[3 * ((Size1 + 2) * i + 0) + 0] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 0];
			Imagedataex[3 * ((Size1 + 2) * i + 0) + 1] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 1];
			Imagedataex[3 * ((Size1 + 2) * i + 0) + 2] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 2];
			Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 0] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 0];
			Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 1] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 1];
			Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 2] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 2];
		}
	}
	else if (BytesPerPixel == 1)
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedataex[1 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = Imagedata[1 * (Size1 * i + j) + 0];
			}
		}
		for (int j = 0; j < Size1; j++)
		{
			Imagedataex[1 * ((Size1 + 2) * 0 + j + 1) + 0] = Imagedata[1 * (Size1 * 0 + j) + 0];
			Imagedataex[1 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = Imagedata[1 * (Size1 * (Size2 - 1) + j) + 0];
		}
		for (int i = 0; i < (Size2 + 2); i++)
		{
			Imagedataex[1 * ((Size1 + 2) * i + 0) + 0] = Imagedataex[1 * ((Size1 + 2) * i + 1) + 0];
			Imagedataex[1 * ((Size1 + 2) * i + (Size2 + 1)) + 0] = Imagedataex[1 * ((Size1 + 2) * i + Size2) + 0];
		}
	}
}

void TD2(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata)//Four-output Floyd-Steinberg¡¯s error diffusion
{
	int bk;
	cout << "If use the extension 1)NO 2)YES: ";
	cin >> bk;//if we use the extension, if so, it is 2; else, it is 1
	short *Imagedataexp;
	Imagedataexp = new short[(Size1 + 2) * (Size2 + 2)];
	Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataexp);
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			int ak;
			ak = i % 2;//justify if the row is odd or even, if even, go from the left to right; else, go from the right to left
			if (ak == 0)
			{
				for (int j = 0; j < Size1; j++)
				{
					double dev, temp;
					if (Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] <= 85/2)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					else if (Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] > (85 / 2) && Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] <= (85 / 2 + 85))
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 85;
					}
					else if (Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] > (85 / 2 + 85) && Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] <= (85 / 2 + 85 * 2))
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 170;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					dev = Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)7 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] = temp;
						temp = (double)3 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = temp;
						temp = (double)5 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = temp;
						temp = (double)1 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = temp;
					}
					else
					{
						temp = (double)7 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] = temp;
						}
						temp = (double)3 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = temp;
						}
						temp = (double)5 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = temp;
						}
						temp = (double)1 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = temp;
						}
					}
				}
			}
			else
			{
				for (int j = Size1 - 1; j >= 0; j--)
				{
					double dev, temp;
					if (Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] <= 85 / 2)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					else if (Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] > (85 / 2) && Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] <= (85 / 2 + 85))
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 85;
					}
					else if (Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] > (85 / 2 + 85) && Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] <= (85 / 2 + 85 * 2))
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 170;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					dev = Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)7 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s] = temp;
						temp = (double)3 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = temp;
						temp = (double)5 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = temp;
						temp = (double)1 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = temp;
					}
					else
					{
						temp = (double)7 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s] = temp;
						}
						temp = (double)3 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = temp;
						}
						temp = (double)5 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = temp;
						}
						temp = (double)1 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = temp;
						}
					}
				}
			}
		}
	}
}

void FS(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata)//Floyd-Steinberg¡¯s error diffusion
{
	int bk;
	cout << "If use the extension 1)NO 2)YES: ";
	cin >> bk;//if we use the extension, if so, it is 2; else, it is 1
	short *Imagedataexp;
	Imagedataexp = new short[(Size1 + 2) * (Size2 + 2)];
	Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataexp);
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			int ak;
			ak = i % 2;//justify if the row is odd or even, if even, go from the left to right; else, go from the right to left
			if (ak == 0)
			{
				for (int j = 0; j < Size1; j++)
				{
					double dev, temp;
					if (Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] >= 127.5)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					dev = Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)7 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] = temp;
						temp = (double)3 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = temp;
						temp = (double)5 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = temp;
						temp = (double)1 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = temp;
					}
					else
					{
						temp = (double)7 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] = 0;
						}
						else
						{
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 2)) + s] = temp;
						}
						temp = (double)3 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = 0;
						}
						else
						{
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = temp;
						}
						temp = (double)5 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = temp;
						}
						temp = (double)1 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = 0;
						}
						else
						{
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = temp;
						}
					}
				}
			}
			else
			{
				for (int j = Size1 - 1; j >= 0; j--)
				{
					double dev, temp;
					if (Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] >= 127.5)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					dev = Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 1)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)7 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s] = temp;
						temp = (double)3 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = temp;
						temp = (double)5 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = temp;
						temp = (double)1 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = temp;
					}
					else
					{
						temp = (double)7 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 1) + (j + 0)) + s] = temp;
						}
						temp = (double)3 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 2)) + s] = temp;
						}
						temp = (double)5 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 1)) + s] = temp;
						}
						temp = (double)1 / 16 * dev + (double)Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp[BytesPerPixel * ((Size1 + 2) * (i + 2) + (j + 0)) + s] = temp;
						}
					}
				}
			}
		}
	}
}

void JJN(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata)
{
	int bk;
	cout << "If use the extension 1)NO 2)YES: ";
	cin >> bk;
	unsigned char *Imagedataexp1;
	Imagedataexp1 = new unsigned char[(Size1 + 2) * (Size2 + 2)];
	short *Imagedataexp2;
	Imagedataexp2 = new short[(Size1 + 4) * (Size2 + 4)];
	Ext_c(BytesPerPixel, Size1, Size2, Imagedata, Imagedataexp1);
	cout << Size2 << endl;
	Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataexp1, Imagedataexp2);
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			int ak;
			ak = i % 2;
			if (ak == 0)
			{
				for (int j = 0; j < Size1; j++)
				{
					double dev, temp;
					if (Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] >= 128)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					dev = Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)7 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = temp;
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = temp;
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						temp = (double)7 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						temp = (double)1 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;
						temp = (double)1 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
					}
					else
					{
						temp = (double)7 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = temp;
						}
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = temp;
						}
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						}
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						}
						temp = (double)7 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						}
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						}
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						}
						temp = (double)1 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
						}
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;
						}
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						}
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;

						}
						temp = (double)1 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
						}
					}
				}
			}
			else
			{
				for (int j = Size1 - 1; j >= 0; j--)
				{
					double dev, temp;
					if (Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] >= 128)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					dev = Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)7 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = temp;
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = temp;
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						temp = (double)7 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						temp = (double)1 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;
						temp = (double)1 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
					}
					else
					{
						temp = (double)7 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = temp;
						}
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = temp;
						}
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						}
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						}
						temp = (double)7 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						}
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						}
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						}
						temp = (double)1 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
						}
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;
						}
						temp = (double)5 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						}
						temp = (double)3 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;

						}
						temp = (double)1 / 48 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
						}
					}
				}
			}
		}
	}
}

void Stucki(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata)
{
	int bk;
	cout << "If use the extension 1)NO 2)YES: ";
	cin >> bk;
	unsigned char *Imagedataexp1;
	Imagedataexp1 = new unsigned char[(Size1 + 2) * (Size2 + 2)];
	short *Imagedataexp2;
	Imagedataexp2 = new short[(Size1 + 4) * (Size2 + 4)];
	Ext_c(BytesPerPixel, Size1, Size2, Imagedata, Imagedataexp1);
	cout << Size2 << endl;
	Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataexp1, Imagedataexp2);
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			int ak;
			ak = i % 2;
			if (ak == 0)
			{
				for (int j = 0; j < Size1; j++)
				{
					double dev, temp;
					if (Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] >= 128)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					dev = Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)8 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = temp;
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = temp;
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						temp = (double)8 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						temp = (double)1 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;
						temp = (double)1 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
					}
					else
					{
						temp = (double)8 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = temp;
						}
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = temp;
						}
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						}
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						}
						temp = (double)8 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						}
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						}
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						}
						temp = (double)1 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
						}
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;
						}
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						}
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;

						}
						temp = (double)1 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
						}
					}
				}
			}
			else
			{
				for (int j = Size1 - 1; j >= 0; j--)
				{
					double dev, temp;
					if (Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] >= 128)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					dev = Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)8 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = temp;
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = temp;
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						temp = (double)8 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						temp = (double)1 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;
						temp = (double)1 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
					}
					else
					{
						temp = (double)8 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = temp;
						}
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = temp;
						}
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						}
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						}
						temp = (double)8 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						}
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						}
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						}
						temp = (double)1 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
						}
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;
						}
						temp = (double)4 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						}
						temp = (double)2 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;

						}
						temp = (double)1 / 42 * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
						}
					}
				}
			}
		}
	}
}

void TD1(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata)
{
	unsigned char *Imagedataexp1;
	Imagedataexp1 = new unsigned char[(Size1 + 2) * (Size2 + 2)];
	short *Imagedataexp2;
	Imagedataexp2 = new short[(Size1 + 4) * (Size2 + 4)];
	Ext_c(BytesPerPixel, Size1, Size2, Imagedata, Imagedataexp1);
	cout << Size2 << endl;
	Ext(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataexp1, Imagedataexp2);
	double a[5] = { 0 };
	double Sig = 1.0;
	cout << "input the Sigma: ";
	cin >> Sig;//Gaussian error diffusin matrix
	a[0] = exp(-(double)1 / (2 * Sig * Sig));
	a[1] = exp(-(double)2 / (2 * Sig * Sig));
	a[2] = exp(-(double)4 / (2 * Sig * Sig));
	a[3] = exp(-(double)5 / (2 * Sig * Sig));
	a[4] = exp(-(double)8 / (2 * Sig * Sig));
	double sum;
	int bk;
	cout << "If use the extension 1)NO 2)YES: ";
	cin >> bk;
	sum = 2 * a[0] + 2 * a[1] + 2 * a[2] + 4 * a[3] + 2 * a[4];
	for (int s = 0; s < BytesPerPixel; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			int ak;
			ak = i % 2;

			if (ak == 0)
			{
				for (int j = 0; j < Size1; j++)
				{
					double dev, temp;
					if (Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] >= 128)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					dev = Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)a[0] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = temp;
						temp = (double)a[2] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = temp;
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						temp = (double)a[1] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						temp = (double)a[0] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						temp = (double)a[1] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						temp = (double)a[4] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;
						temp = (double)a[2] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;
						temp = (double)a[4] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
					}
					else
					{
						temp = (double)a[0] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 3)) + s] = temp;
						}
						temp = (double)a[2] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 4)) + s] = temp;
						}
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						}
						temp = (double)a[1] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						}
						temp = (double)a[0] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						}
						temp = (double)a[1] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						}
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						}
						temp = (double)a[4] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
						}
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;
						}
						temp = (double)a[2] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						}
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;

						}
						temp = (double)a[4] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
						}
					}
				}
			}
			else
			{
				for (int j = Size1 - 1; j >= 0; j--)
				{
					double dev, temp;
					if (Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] >= 128)
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 255;
					}
					else
					{
						Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s] = 0;
					}
					dev = Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 2)) + s] - Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + s];
					if (bk == 1)
					{
						temp = (double)a[0] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = temp;
						temp = (double)a[2] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = temp;
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						temp = (double)a[1] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						temp = (double)a[0] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						temp = (double)a[1] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						temp = (double)a[4] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;
						temp = (double)a[2] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;
						temp = (double)a[4] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
					}
					else
					{
						temp = (double)a[0] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 1)) + s] = temp;
						}
						temp = (double)a[2] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 2) + (j + 0)) + s] = temp;
						}
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 4)) + s] = temp;
						}
						temp = (double)a[1] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 3)) + s] = temp;
						}
						temp = (double)a[0] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 2)) + s] = temp;
						}
						temp = (double)a[1] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 1)) + s] = temp;
						}
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 3) + (j + 0)) + s] = temp;
						}
						temp = (double)a[4] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 4)) + s] = temp;
						}
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 3)) + s] = temp;
						}
						temp = (double)a[2] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 2)) + s] = temp;
						}
						temp = (double)a[3] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 1)) + s] = temp;

						}
						temp = (double)a[4] / sum * dev + (double)Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s];
						if (temp >= 255)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 255;
						}
						else if (temp <= 0)
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = 0;
						}
						else
						{
							Imagedataexp2[BytesPerPixel * ((Size1 + 4) * (i + 4) + (j + 0)) + s] = temp;
						}
					}
				}
			}
		}
	}
}

void P2_b(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	int a;
	cout << "Input the method number 1) Floyd-Steinberg 2) JJN 3) Stucki 4) TD1 5) TD2: ";
	cin >> a;

	if (a == 1)
	{
		FS(BytesPerPixel, Size1, Size2, Imagedata);
	}
	else if (a == 2)
	{
		JJN(BytesPerPixel, Size1, Size2, Imagedata);
	}
	else if (a == 3)
	{
		Stucki(BytesPerPixel, Size1, Size2, Imagedata);
	}
	else if (a == 4)
	{
		TD1(BytesPerPixel, Size1, Size2, Imagedata);
	}
	else if (a == 5)
	{
		TD2(BytesPerPixel, Size1, Size2, Imagedata);
	}

	//Ext(BytesPerPixel, Size1, Size2, Imagedata, Imagedataexp);

	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), (Size2)*(Size1)*BytesPerPixel, file);
	fclose(file);
	system("pause");
}