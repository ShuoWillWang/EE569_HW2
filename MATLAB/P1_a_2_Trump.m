% EE 569 Homework #2
% date:		Feb. 24th, 2017
% Name:		Shuo Wang
% ID:		8749390300
% email:	wang133@usc.edu
%************************************************************************************************************************************
% solution for Problem1(a)	Puzzle Matching (Trump)
% objective:                Get the parameters of warping matrix to complete the puzzle patch
% M-file name:              P1_a_2_Trump.m
% Usage                     P1_a_2_Trump
% Application Name: 		Image_Processing_HW2.exe
%************************************************************************************************************************************
% The usage method:
% 1) save the origin patch coordinate x into the 8th column of the excel form
% 2) save the origin patch coordinate y into the 9th column of the excel form
% 3) save the hole coordinate x in the origin image into the 11th column of the excel form
% 4) save the hole coordinate y in the origin image into the 12th column of the excel form
% 5) when we use the Image_Processing_HW2.exe and get the the used coordinate of input (x) is 1st, 2nd and 3rd,
%   we can get the a, b and c of [aS3O(a,1); aS3O(b,1); aS3O(c,1)] is 1, 2 and 3
%   we can get the a, b and c of [aS3O(a,2); aS3O(b,2); aS3O(c,2)] is 1, 2 and 3
%when we get the the used coordinate of input (x) is 1st, 2nd and 3rd,
%we can get the a, b and c of [aS3O(a,1); aS3O(b,1); aS3O(c,1)] is 1, 2 and 3
%we can get the a, b and c of [aS3O(a,2); aS3O(b,2); aS3O(c,2)] is 1, 2 and 3

aS3O = [VarName8 VarName9];
aS3N = [VarName11 VarName12];

y1 = [aS3O(3,1); aS3O(4,1); aS3O(1,1)];
A1 = [aS3N(1,1), aS3N(1,2), 1; aS3N(2,1), aS3N(2,2), 1; aS3N(3,1), aS3N(3,2), 1];%it should not change
a1 = A1\y1;
y2 = [aS3O(3,2); aS3O(4,2); aS3O(1,2)];
A2 = [aS3N(1,1), aS3N(1,2), 1; aS3N(2,1), aS3N(2,2), 1; aS3N(3,1), aS3N(3,2), 1];%it should not change
a2 = A2\y2;
a = [a1';a2']
