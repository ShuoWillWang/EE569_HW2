// EE 569 Homework #2
// date:	Feb. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu
//****************************************************************************************
// Compiled on WINDOWS 10 with Visual C++
// solution for all questions in  Problem 1, Problem 2 and Problem 3
// Use the DOS command to open the program and run it by the README.txt
//****************************************************************************************

Problem 1:	Geometric Image Modification
(a) 	Geometrical Warping
Relevant file: P1_a.cpp, P1_a_1.cpp
Open Method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\cup1.raw D:\EE569_Assignment\2\cup1_warp.raw 3 500 500
Solve which problems: 1
solve which part: a
Choose the method 1) Professor's method 2) Diamond: 1
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\cup1.raw D:\EE569_Assignment\2\cup1_warp1.raw 3 500 500
Solve which problems: 1
solve which part: a
Choose the method 1) Professor's method 2) Diamond: 2
Press any key to continue . . .

(b) 	Puzzle Matching
Relevant file: P1_b.cpp
Open Method: {path_of_program_name path_of_input_image.raw(piece.raw) path_of_edge_image.raw(for piece.raw) BytesPerPixel Size1(Width of piece.raw) Size2(Height of piece.raw)}
//The path of input and final output image (Hillary and Trump) is set in the C++ code, if you want to change the path, please change the C++ code
//The Size of input and final output image (Hillary and Trump) is set in the C++ code, if you want to change the path, please change the C++ code
//The Final output image is Hillary_Complete.raw and Trump_Complete.raw
D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\piece.raw D:\EE569_Assignment\2\test.raw 3 500 500
Solve which problems: 1
solve which part: b
The origin Cordinate for Hillary is:
The X:
96.5
241.5
202.5
57.5

The Y:
442.5
403.5
259.5
297.5
The origin Cordinate for Trump is:
The X:
377.5
383.5
308.5
302.5

The Y:
209.5
135.5
128.5
203.5
The new Cordinate for Hillary is:
The X:
173.5
272.5
272.5
173.5

The Y:
376.5
376.5
277.5
277.5
The new Cordinate for Trump is:
The X:
163.5
262.5
262.5
163.5

The Y:
275.5
275.5
176.5
176.5
INPUT THE STATISTIC INTO MATLAB:
Press any key to continue . . .

the used coordinate of input (x) is 1st, 2nd and 3rd
Input the parameters of matrix a, b, c, d, e and f: 1.4646 0.3939 -305.9343 -0.3939 1.4545 -36.7879

the used coordinate of input (x) is 3rd, 4th and 1st
Input the parameters of matrix a, b, c, d, e and f: -0.0606 -0.7576 527.1212 0.7576 -0.0606 21.3333

Press any key to continue . . .


(c) 	Homographic Transformation and Image Overlay
Relevant file: P1_c.cpp
Open Method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height) path_of_plus_input_image.raw}
//The Size of plus input image (Trojans) is set in the C++ code, if you want to change the Size, please change the C++ code
//we should input the corners of output corresponding to the plus input image as the order of left top, right top, right bottom and left bottom
D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\field.raw D:\EE569_Assignment\2\field_trojans.raw 3 972 648 D:\EE569_Assignment\2\trojans.raw
Solve which problems: 1
solve which part: c
The origin Cordinate is:
The X is:
0.5
349.5
349.5
0.5

The Y is:
196.5
196.5
0.5
0.5
Input the pixel coordinate of four points (for each point, i first, then j):
the No.1 point is: 594 325
the No.2 point is: 430 541
the No.3 point is: 434 713
the No.4 point is: 615 651
The new Cordinate is:
The X is:
325.5
541.5
713.5
651.5

The Y is:
53.5
217.5
213.5
32.5
INPUT THE STATISTIC INTO MATLAB:
Press any key to continue . . .
Input the 8 parameters: a,b,c,d,e,f,g and h:
0.0575 0.8913 -65.9687 -0.5144 0.1749 329.9161 0.0000 -0.0026
Press any key to continue . . .



Problem 2:	Digital Halftoning
(a) 	Dithering Matrix
Relevant File: P2_a.cpp
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\man.raw D:\EE569_Assignment\2\man_Bayer_4.raw 1 512 512
Solve which problems: 2
solve which part: a
which Bayer Matrix use: 1)standard 2) different Matrix 3) 4-level: 1
Input the Size of Bayer Matrix: 4
0       8       2       10
12      4       14      6
3       11      1       9
15      7       13      5
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\man.raw D:\EE569_Assignment\2\man_Bayer_4_Sp.raw 1 512 512
Solve which problems: 2
solve which part: a
which Bayer Matrix use: 1)standard 2) different Matrix 3) 4-level: 2
14      10      11      15
9       3       0       4
8       2       1       5
13      7       6       12
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\man.raw D:\EE569_Assignment\2\man_Bayer_4_level_Sp.raw 1 512 512
Solve which problems: 2
solve which part: a
which Bayer Matrix use: 1)standard 2) different Matrix 3) 4-level: 3
0       8       2       10
12      4       14      6
3       11      1       9
15      7       13      5
Press any key to continue . . .


(b) 	Error Diffusion
Relevant File: P2_b.cpp
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}

D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\man.raw D:\EE569_Assignment\2\man_FS_4.raw 1 512 512
Solve which problems: 2
solve which part: b
Input the method number 1) Floyd-Steinberg 2) JJN 3) Stucki 4) TD: 1
If use the extension 1)NO 2)YES: 1
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\man.raw D:\EE569_Assignment\2\man_JJN.raw 1 512 512
Solve which problems: 2
solve which part: b
Input the method number 1) Floyd-Steinberg 2) JJN 3) Stucki 4) TD: 2
If use the extension 1)NO 2)YES: 1
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\man.raw D:\EE569_Assignment\2\man_Stucki.raw 1 512 512
Solve which problems: 2
solve which part: b
Input the method number 1) Floyd-Steinberg 2) JJN 3) Stucki 4) TD: 3
If use the extension 1)NO 2)YES: 1
Press any key to continue . . .


Problem 3
(a)	Shrinking
Relevant File: P3_a.cpp
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\squares.raw D:\EE569_Assignment\2\squares_S.raw 1 480 480
Solve which problems: 3
solve which part: a
The total number is 24
The number of 1x1 size is 4
The number of 2x2 size is 0
The number of 3x3 size is 0
The number of 4x4 size is 1
The number of 5x5 size is 0
The number of 6x6 size is 2
The number of 7x7 size is 0
The number of 8x8 size is 9
The number of 9x9 size is 0
The number of 10x10 size is 0
The number of 11x11 size is 0
The number of 12x12 size is 1
The number of 13x13 size is 0
The number of 14x14 size is 1
The number of 15x15 size is 0
The number of 16x16 size is 0
The number of 17x17 size is 0
The number of 18x18 size is 6
The number of 19x19 size is 0
The number of 20x20 size is 0
The number of 21x21 size is 0
The number of 22x22 size is 0
Press any key to continue . . .


(b)	Thinning
Relevant File: P3_b.cpp
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\squares.raw D:\EE569_Assignment\2\squares_Th.raw 1 480 480
Solve which problems: 3
solve which part: b
Press any key to continue . . .


(c)	Skeletonizing
Relevant File: P3_c.cpp
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\squares.raw D:\EE569_Assignment\2\squares_Sk.raw 1 480 480
Solve which problems: 3
solve which part: c
Press any key to continue . . .


(d)	Counting game
Relevant File: P3_d.cpp
Open method: {path_of_program_name path_of_input_image.raw path_of_output_image.raw BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\board.raw D:\EE569_Assignment\2\board_Edg.raw 1 480 480
Solve which problems: 3
solve which part: d
Input the subquestion want to solve
 1) The number of the white objects
 2) The number of holes
 3) The number of squares and cicles:
1
The number of white object is: 15
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\board.raw D:\EE569_Assignment\2\board_Edg.raw 1 480 480
Solve which problems: 3
solve which part: d
Input the subquestion want to solve
 1) The number of the white objects
 2) The number of holes
 3) The number of squares and cicles:
2
The number of holes is: 9
Press any key to continue . . .

D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug>D:\EE569_Assignment\1\C++\Image_Processing_HW2\Debug\Image_Processing_HW2.exe D:\EE569_Assignment\2\board.raw D:\EE569_Assignment\2\board_Edg.raw 1 480 480
Solve which problems: 3
solve which part: d
Input the subquestion want to solve
 1) The number of the white objects
 2) The number of holes
 3) The number of squares and cicles:
3
The number of white circles is: 7
The number of white squares is: 8
Press any key to continue . . .