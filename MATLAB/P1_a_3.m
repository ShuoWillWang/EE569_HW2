% EE 569 Homework #2
% date:		Feb. 24th, 2017
% Name:		Shuo Wang
% ID:		8749390300
% email:	wang133@usc.edu
%************************************************************************************************************************************
% solution for Problem1(a)	Homographic Transformation and Image Overlay
% objective:                Get the parameters of Homographic Transformation matrix to put the teojans into the field image
% M-file name:              P1_a_3.m
% Usage                     P1_a_3
% Application Name: 		Image_Processing_HW2.exe
%************************************************************************************************************************************
% The usage method:
% 1) according to the output value change the value of xyn1, xyn2, xyn3, xyn4, 
%   according to the order in the C++ exe. for each xyn1, [0.5, 196.5] represent
% 	the x and y of the coordinates

xy1 = [0.5, 196.5]; % the x-y coordinate of the trojan image
xy2 = [349.5, 196.5];
xy3 = [349.5, 0.5];
xy4 = [0.5, 0.5];

xyn1 = [325.5, 53.5];% the x-y coordinate in the field image the trojan will be placed
xyn2 = [541.5, 217.5];
xyn3 = [713.5, 213.5];
xyn4 = [651.5, 32.5];

A = [xyn1 1 0 0 0 -xy1(1)*xyn1;
    0 0 0 xyn1 1 -xy1(2)*xyn1;
    xyn2 1 0 0 0 -xy2(1)*xyn2;
    0 0 0 xyn2 1 -xy2(2)*xyn2;
    xyn3 1 0 0 0 -xy3(1)*xyn3;
    0 0 0 xyn3 1 -xy3(2)*xyn3;
    xyn4 1 0 0 0 -xy4(1)*xyn4;
    0 0 0 xyn4 1 -xy4(2)*xyn4];

a = [xy1';xy2';xy3';xy4'];

k = A\a;
k = k'%final transformation matrix