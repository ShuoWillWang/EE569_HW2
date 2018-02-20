% EE 569 Homework #2
% date:		Feb. 24th, 2017
% Name:		Shuo Wang
% ID:		8749390300
% email:	wang133@usc.edu
%************************************************************************************************************************************
% solution for Problem1(a)	Geometrical Warping
% objective:                Get the parameters of warping matrix to warp each triangle image
%                           from one form to another one. Warpping eight trignales, we can 
%                           get the diamond shape
% M-file name:              P1_a_1.m
% Usage                     P1_a_1
% Application Name: 		Image_Processing_HW2.exe
%************************************************************************************************************************************
% The usage method:
% 1) we do not have to extract the coordinate from the excel form
% 2) in the intruction, the first input triangle is (for i-j coordinate) (0 0)
% , (0 249) and (249, 249). Other input triangle will be ordered clockwise
% 3) in the intruction, the first input triangle is (for i-j coordinate) (124 124)
% , (0 249) and (249, 249). Other input triangle will be ordered clockwise
% 4) we should set other oarameters according to the triangle you want to input:
% if we want to get the matrix of 1st triangle
% y1 = [aS3Ox(1); aS3Ox(2); aS3Ox(9)];
% A1 = [aS3Nx(1), aS3Ny(1), 1; aS3Nx(2), aS3Ny(2), 1; aS3Nx(9), aS3Ny(9), 1];
% y2 = [aS3Oy(1); aS3Oy(2); aS3Oy(9)];
% A2 = [aS3Nx(1), aS3Ny(1), 1; aS3Nx(2), aS3Ny(2), 1; aS3Nx(9), aS3Ny(9), 1];
% if we want to get the matrix of 2nd triangle
% y1 = [aS3Ox(2); aS3Ox(3); aS3Ox(9)];
% A1 = [aS3Nx(2), aS3Ny(2), 1; aS3Nx(3), aS3Ny(3), 1; aS3Nx(9), aS3Ny(9), 1];
% y2 = [aS3Oy(2); aS3Oy(3); aS3Oy(9)];
% A2 = [aS3Nx(2), aS3Ny(2), 1; aS3Nx(3), aS3Ny(3), 1; aS3Nx(9), aS3Ny(9), 1];
% if we want to get the matrix of 3rd triangle
% y1 = [aS3Ox(3); aS3Ox(4); aS3Ox(9)];
% A1 = [aS3Nx(3), aS3Ny(3), 1; aS3Nx(4), aS3Ny(4), 1; aS3Nx(9), aS3Ny(9), 1];
% y2 = [aS3Oy(3); aS3Oy(4); aS3Oy(9)];
% A2 = [aS3Nx(3), aS3Ny(3), 1; aS3Nx(4), aS3Ny(4), 1; aS3Nx(9), aS3Ny(9), 1];
% if we want to get the matrix of 4th triangle
% y1 = [aS3Ox(4); aS3Ox(5); aS3Ox(9)];
% A1 = [aS3Nx(4), aS3Ny(4), 1; aS3Nx(5), aS3Ny(5), 1; aS3Nx(9), aS3Ny(9), 1];
% y2 = [aS3Oy(4); aS3Oy(5); aS3Oy(9)];
% A2 = [aS3Nx(4), aS3Ny(4), 1; aS3Nx(5), aS3Ny(5), 1; aS3Nx(9), aS3Ny(9), 1];
% if we want to get the matrix of 5th triangle
% y1 = [aS3Ox(5); aS3Ox(6); aS3Ox(9)];
% A1 = [aS3Nx(5), aS3Ny(5), 1; aS3Nx(6), aS3Ny(6), 1; aS3Nx(9), aS3Ny(9), 1];
% y2 = [aS3Oy(5); aS3Oy(6); aS3Oy(9)];
% A2 = [aS3Nx(5), aS3Ny(5), 1; aS3Nx(6), aS3Ny(6), 1; aS3Nx(9), aS3Ny(9), 1];
% if we want to get the matrix of 6th triangle
% y1 = [aS3Ox(6); aS3Ox(7); aS3Ox(9)];
% A1 = [aS3Nx(6), aS3Ny(6), 1; aS3Nx(7), aS3Ny(7), 1; aS3Nx(9), aS3Ny(9), 1];
% y2 = [aS3Oy(6); aS3Oy(7); aS3Oy(9)];
% A2 = [aS3Nx(6), aS3Ny(6), 1; aS3Nx(7), aS3Ny(7), 1; aS3Nx(9), aS3Ny(9), 1];
% if we want to get the matrix of 7th triangle
% y1 = [aS3Ox(7); aS3Ox(8); aS3Ox(9)];
% A1 = [aS3Nx(7), aS3Ny(7), 1; aS3Nx(8), aS3Ny(8), 1; aS3Nx(9), aS3Ny(9), 1];
% y2 = [aS3Oy(7); aS3Oy(8); aS3Oy(9)];
% A2 = [aS3Nx(7), aS3Ny(7), 1; aS3Nx(8), aS3Ny(8), 1; aS3Nx(9), aS3Ny(9), 1];
% if we want to get the matrix of 8th triangle
% y1 = [aS3Ox(8); aS3Ox(1); aS3Ox(9)];
% A1 = [aS3Nx(8), aS3Ny(8), 1; aS3Nx(1), aS3Ny(1), 1; aS3Nx(9), aS3Ny(9), 1];
% y2 = [aS3Oy(8); aS3Oy(1); aS3Oy(9)];
% A2 = [aS3Nx(8), aS3Ny(8), 1; aS3Nx(1), aS3Ny(1), 1; aS3Nx(9), aS3Ny(9), 1];

Size1 = 500; Size2 = 500; % set the size of image

aS3Oi = [0 0 0 Size2/2 - 1 Size2 - 1 Size2 - 1 Size2 - 1 Size2/2 - 1 Size2/2 - 1]; % the i of the control point in the input image
aS3Oj = [0 Size1/2 - 1 Size1 - 1 Size1 - 1 Size1 - 1 Size1/2 - 1 0 0 Size1/2 - 1]; % the j of the control point in the input image
aS3Ni = [Size2/4 - 1 0 Size2/4 - 1 Size2/2 - 1 3*Size2/4 - 1 Size2 - 1 3*Size2/4 - 1 Size2/2 - 1 Size2/2 - 1];  % the i of the control point in the output image
aS3Nj = [Size1/4 - 1 Size1/2 - 1 3*Size1/4 - 1 Size1 - 1 3*Size1/4 - 1 Size1/2 - 1 Size1/4 - 1 0 Size1/2 - 1];  % the j of the control point in the output image

aS3Oy = 500 - aS3Oi - 1 + 0.5;
aS3Ox = aS3Oj + 0.5;
aS3Ny = 500 - aS3Ni - 1 + 0.5;
aS3Nx = aS3Nj + 0.5;

y1 = [aS3Ox(1); aS3Ox(2); aS3Ox(9)];
A1 = [aS3Nx(1), aS3Ny(1), 1; aS3Nx(2), aS3Ny(2), 1; aS3Nx(9), aS3Ny(9), 1];
a1 = A1\y1;
y2 = [aS3Oy(1); aS3Oy(2); aS3Oy(9)];
A2 = [aS3Nx(1), aS3Ny(1), 1; aS3Nx(2), aS3Ny(2), 1; aS3Nx(9), aS3Ny(9), 1];
a2 = A2\y2;
a = [a1';a2']
