% EE 569 Homework #2
% date:		Feb. 24th, 2017
% Name:		Shuo Wang
% ID:		8749390300
% email:	wang133@usc.edu
%************************************************************************************************************************************
% solution for Problem1(a)	Geometrical Warping (Professor's solution)
% M-file name:              	P1_a_1.m
% Usage                     	P1_a_1
% Application Name: 		Image_Processing_HW2.exe
% objective:                	Get the parameters of warping matrix to warp each triangle image
%                           	from one form to another one. Warpping eight trignales, we can 
%                          	get the diamond shape
% The usage method:
% 	1) we do not have to extract the coordinate from the excel form, just input the Size of the image (the size of input and output are same)
% 	2) in the intruction, the first input triangle is (for i-j coordinate) (0 0), (0 Size1 / 2 - 1) and (Size2 / 2 - 1, Size1 / 2 - 1). Other input triangle will be ordered clockwise
% 	3) in the intruction, the first output triangle is (for i-j coordinate) (Size2 / 4 - 1 Size1 / 4 - 1), (0 Size1 / 2 - 1) and (Size2 / 2 - 1, Size1 / 2 - 1). Other output triangle will be ordered clockwise
% 	4) we should set other oarameters according to the triangle you want to input:
% 	if we want to get the matrix of 1st triangle
% 		y1 = [aS3Ox(1); aS3Ox(2); aS3Ox(9)];
% 		A1 = [aS3Nx(1), aS3Ny(1), 1; aS3Nx(2), aS3Ny(2), 1; aS3Nx(9), aS3Ny(9), 1];
% 		y2 = [aS3Oy(1); aS3Oy(2); aS3Oy(9)];
% 		A2 = [aS3Nx(1), aS3Ny(1), 1; aS3Nx(2), aS3Ny(2), 1; aS3Nx(9), aS3Ny(9), 1];
% 	if we want to get the matrix of 2nd triangle
% 		y1 = [aS3Ox(2); aS3Ox(3); aS3Ox(9)];
% 		A1 = [aS3Nx(2), aS3Ny(2), 1; aS3Nx(3), aS3Ny(3), 1; aS3Nx(9), aS3Ny(9), 1];
% 		y2 = [aS3Oy(2); aS3Oy(3); aS3Oy(9)];
% 		A2 = [aS3Nx(2), aS3Ny(2), 1; aS3Nx(3), aS3Ny(3), 1; aS3Nx(9), aS3Ny(9), 1];
% 	if we want to get the matrix of 3rd triangle
% 		y1 = [aS3Ox(3); aS3Ox(4); aS3Ox(9)];
% 		A1 = [aS3Nx(3), aS3Ny(3), 1; aS3Nx(4), aS3Ny(4), 1; aS3Nx(9), aS3Ny(9), 1];
% 		y2 = [aS3Oy(3); aS3Oy(4); aS3Oy(9)];
%	 	A2 = [aS3Nx(3), aS3Ny(3), 1; aS3Nx(4), aS3Ny(4), 1; aS3Nx(9), aS3Ny(9), 1];
% 	if we want to get the matrix of 4th triangle
% 		y1 = [aS3Ox(4); aS3Ox(5); aS3Ox(9)];
% 		A1 = [aS3Nx(4), aS3Ny(4), 1; aS3Nx(5), aS3Ny(5), 1; aS3Nx(9), aS3Ny(9), 1];
% 		y2 = [aS3Oy(4); aS3Oy(5); aS3Oy(9)];
% 		A2 = [aS3Nx(4), aS3Ny(4), 1; aS3Nx(5), aS3Ny(5), 1; aS3Nx(9), aS3Ny(9), 1];
% 	if we want to get the matrix of 5th triangle
% 		y1 = [aS3Ox(5); aS3Ox(6); aS3Ox(9)];
% 		A1 = [aS3Nx(5), aS3Ny(5), 1; aS3Nx(6), aS3Ny(6), 1; aS3Nx(9), aS3Ny(9), 1];
% 		y2 = [aS3Oy(5); aS3Oy(6); aS3Oy(9)];
% 		A2 = [aS3Nx(5), aS3Ny(5), 1; aS3Nx(6), aS3Ny(6), 1; aS3Nx(9), aS3Ny(9), 1];
% 	if we want to get the matrix of 6th triangle
% 		y1 = [aS3Ox(6); aS3Ox(7); aS3Ox(9)];
% 		A1 = [aS3Nx(6), aS3Ny(6), 1; aS3Nx(7), aS3Ny(7), 1; aS3Nx(9), aS3Ny(9), 1];
% 		y2 = [aS3Oy(6); aS3Oy(7); aS3Oy(9)];
% 		A2 = [aS3Nx(6), aS3Ny(6), 1; aS3Nx(7), aS3Ny(7), 1; aS3Nx(9), aS3Ny(9), 1];
% 	if we want to get the matrix of 7th triangle
% 		y1 = [aS3Ox(7); aS3Ox(8); aS3Ox(9)];
% 		A1 = [aS3Nx(7), aS3Ny(7), 1; aS3Nx(8), aS3Ny(8), 1; aS3Nx(9), aS3Ny(9), 1];
% 		y2 = [aS3Oy(7); aS3Oy(8); aS3Oy(9)];
% 		A2 = [aS3Nx(7), aS3Ny(7), 1; aS3Nx(8), aS3Ny(8), 1; aS3Nx(9), aS3Ny(9), 1];
% 	if we want to get the matrix of 8th triangle
% 		y1 = [aS3Ox(8); aS3Ox(1); aS3Ox(9)];
% 		A1 = [aS3Nx(8), aS3Ny(8), 1; aS3Nx(1), aS3Ny(1), 1; aS3Nx(9), aS3Ny(9), 1];
% 		y2 = [aS3Oy(8); aS3Oy(1); aS3Oy(9)];
% 		A2 = [aS3Nx(8), aS3Ny(8), 1; aS3Nx(1), aS3Ny(1), 1; aS3Nx(9), aS3Ny(9), 1];
%	5) after calculation, input the six value of the a into the a b c d e f of void Warp(double a, double b, double c, double d, double e, double f, unsigned char *Imagedata, unsigned char *ImagedataOut, int Size1, int Size2, double *x1, double *x2, double *x3)
%		 according to the value of *x1, *x2, *x3 which can be seen in the A1 
%************************************************************************************************************************************
% solution for Problem1(a)	Puzzle Matching (Hillary)
% M-file name:              	P1_a_2_Hillary.m
% Usage                     	P1_a_2_Hillary
% Application Name: 		Image_Processing_HW2.exe
% objective:                	Get the parameters of warping matrix to complete the puzzle patch
% The usage method:
% 	1) save the origin patch coordinate x into the first column of the excel form
% 	2) save the origin patch coordinate y into the second column of the excel form
% 	3) save the hole coordinate x in the origin image into the forth column of the excel form
% 	4) save the hole coordinate y in the origin image into the fifth column of the excel form
% 	5) when we use the Image_Processing_HW2.exe and get the message "the used coordinate of input (x) is 1st, 2nd and 3rd (Hillary)"
%   		we can get the a, b and c of [aS3O(a,1); aS3O(b,1); aS3O(c,1)] is 1, 2 and 3
%   		we can get the a, b and c of [aS3O(a,2); aS3O(b,2); aS3O(c,2)] is 1, 2 and 3
% 	6) copy the value of the a and paste when there is a message " Input the parameters of matrix a, b, c, d, e and f: "
%************************************************************************************************************************************
% solution for Problem1(a)	Puzzle Matching (Trump)
% M-file name:              	P1_a_2_Trump.m
% Usage                     	P1_a_2_Trump
% Application Name: 		Image_Processing_HW2.exe
% objective:                	Get the parameters of warping matrix to complete the puzzle patch
% The usage method:
% 	1) save the origin patch coordinate x into the first column of the excel form
% 	2) save the origin patch coordinate y into the second column of the excel form
% 	3) save the hole coordinate x in the origin image into the forth column of the excel form
% 	4) save the hole coordinate y in the origin image into the fifth column of the excel form
% 	5) when we use the Image_Processing_HW2.exe and get the message "the used coordinate of input (x) is 1st, 2nd and 3rd (Hillary)"
%   		we can get the a, b and c of [aS3O(a,1); aS3O(b,1); aS3O(c,1)] is 1, 2 and 3
%   		we can get the a, b and c of [aS3O(a,2); aS3O(b,2); aS3O(c,2)] is 1, 2 and 3
% 	6) copy the value of the a and paste when there is a message " Input the parameters of matrix a, b, c, d, e and f: "
%************************************************************************************************************************************
% solution for Problem1(a)	Homographic Transformation and Image Overlay
% objective:                	Get the parameters of Homographic Transformation matrix to put the trojans into the field image
% M-file name:              	P1_a_3.m
% Usage                     	P1_a_3
% Application Name: 		Image_Processing_HW2.exe
% The usage method:
% 	1)according to the output value change the value of xyn1, xyn2, xyn3, xyn4 
%	following the order of the output in the C++ exe. for each xyn1, [0.5, 196.5] represent
% 	the x and y of the coordinates
% 	2)run the m file and get the output of k
%	3)paste the value of k when the program C++ shows " Input the 8 parameters: a,b,c,d,e,f,g and h: " 
%************************************************************************************************************************************
