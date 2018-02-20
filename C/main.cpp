// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

// Compiled on WINDOWS 10 with Visual C++
// solution for all questions in  Problem 1, Problem 2 and Problem 3
// Use the DOS command to open the program and run it by the README.txt

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

unsigned char Imagedata[100000000] = { 0 };
unsigned char ImagedataOut[100000000] = { 0 };
unsigned char Imagedataori[100000000] = { 0 };
unsigned char Imagedata1[100000000] = { 0 };
unsigned char Imagedata2[100000000] = { 0 };
unsigned char Imagedataexp[100000000] = { 0 };
unsigned char Imagedataexp1[100000000] = { 0 };
unsigned char ImagedataPex[100000000] = { 0 };
unsigned char ImagedataPexM[100000000] = { 0 };
unsigned char ImagedataPOut[100000000] = { 0 };
unsigned char ImagedataP[100000000] = { 0 };

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	int BytesPerPixel;
	int Size1 = 256, Size2 = 256, Size3 = 300, Size4 = 300;
	int Problem;
	char Part;

	// Check for proper syntax
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size1 = 256] [Size2 = 256]" << endl;
		return 0;
	}

	cout << "Solve which problems: ";
	cin >> Problem;
	cout << "solve which part: ";
	cin >> Part;

	// Check if image is grayscale or color
	if (argc < 4) {
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5) {
			Size1 = atoi(argv[4]);
			Size2 = atoi(argv[5]);
		}
	}

	void P1_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P1_b(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P1_c(int BytesPerPixel, char *a1, char *a2, char *a3, int Size1, int Size2);
	void P2_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P2_b(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P3_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P3_b(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P3_c(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P3_d(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P1_a_1(int BytesPerPixel, char *a1, char *a2, char *a3, int Size1, int Size2);

	if (Problem == 1)//problem 1
	{
		if (Part == 'A' || Part == 'a')//a
		{
			int choose;
			cout << "Choose the method 1) Professor's method 2) Diamond: ";
			cin >> choose;
			if (choose == 1)
			{
				P1_a(BytesPerPixel, argv[1], argv[2], Size1, Size2);
			}
			else
			{
				P1_a_1(BytesPerPixel, argv[1], argv[2], argv[6], Size1, Size2);
			}
		}
		if (Part == 'B' || Part == 'b')//b
		{
			P1_b(BytesPerPixel, argv[1], argv[2], Size1, Size2);
		}
		if (Part == 'C' || Part == 'c')//c
		{
			P1_c(BytesPerPixel, argv[1], argv[2], argv[6], Size1, Size2);
		}
	}
	if (Problem == 2)//Problem 2
	{
		if (Part == 'A' || Part == 'a')//a
		{
			P2_a(BytesPerPixel, argv[1], argv[2], Size1, Size2);
		}
		if (Part == 'b' || Part == 'B')//b
		{
			P2_b(BytesPerPixel, argv[1], argv[2], Size1, Size2);
		}
	}
	if (Problem == 3)//Problem 3
	{
		if (Part == 'A' || Part == 'a')//a
		{
			P3_a(BytesPerPixel, argv[1], argv[2], Size1, Size2);
		}
		if (Part == 'B' || Part == 'b')//b
		{
			P3_b(BytesPerPixel, argv[1], argv[2], Size1, Size2);
		}
		if (Part == 'C' || Part == 'c')//c
		{
			P3_c(BytesPerPixel, argv[1], argv[2], Size1, Size2);
		}
		if (Part == 'D' || Part == 'd')//d
		{
			P3_d(BytesPerPixel, argv[1], argv[2], Size1, Size2);
		}
	}
}