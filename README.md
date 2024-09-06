This is a program I started during the Winter of 2024 at Washtenaw Community College, and I am continuing to improve it as I gain more experience in C++.

My program currently uses a text file of English words (provided by https://github.com/dwyl/english-words) as the source of the correctly spelled words. Before starting the program, an input file, which contains the crossword puzzle, must be defined in the code for the program to run. The program will then read both the input and the English word text file (words.txt) and print the table into the terminal. 

Initially, the content of words.txt will be randomly read and assigned a random position in the hash table (unordered_set). Then, it's converted into a string vector for comparing words in the input file table. 
After the words.txt file has been turned into a vector, the program will search for correct matches in the table. The found words will be printed as "(Word) was found vertically/diagonally/horizontally (direction) at row X and column Y." The given row and column are the starting locations of the found word. 

Right now, I'm currently trying to solve a few issues with the code, attempting to optimize the code, and adding new features to this project. Additionally, I am trying to find a word file that has most of the English words in the English Language but doesn't have abbreviations.  
