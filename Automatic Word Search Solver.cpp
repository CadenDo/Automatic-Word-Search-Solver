#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;


// Function 1 - Opens and read file (gives error if file isn't found)
bool readInputFile(const string& filename, char table[ArraySize][ArraySize]) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {// Failed to read file 
        cout << "File " << filename << " not found.";
        return false;
    }

    // Reads table
    for (int ReadTemp1 = 0; ReadTemp1 < ArraySize; ReadTemp1++) {
        for (int ReadTemp2 = 0; ReadTemp2 < ArraySize; ReadTemp2++) {
            inputFile >> table[ReadTemp1][ReadTemp2];
        }
    }
    inputFile.close();// Reading file was successful
    return true;
}

// Function 1.5 - Reads the Dictionary file 
unordered_set<string> readDictionary(const string& filename) {
    ifstream inputFile(filename);
    unordered_set<string> dictionary;
    string ReadWord;

    if (inputFile.is_open()) {
        while (getline(inputFile, ReadWord)) {
            dictionary.insert(ReadWord);
        }
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
    inputFile.close();// Stop reading of file 
    return dictionary;
}

// Function 2 - Prints the table 
void printTable(const char table[ArraySize][ArraySize]) {
    for (int PrintTemp1 = 0; PrintTemp1 < ArraySize; PrintTemp1++) {
        for (int PrintTemp2 = 0; PrintTemp2 < ArraySize; PrintTemp2++) {
            cout << table[PrintTemp1][PrintTemp2] << '\t';
        }
        cout << endl;
    }
}

// Function 3 - Word Searching (8 directions)
bool WordSearch(const char table[ArraySize][ArraySize], const string& word, int& FoundWords) {

    for (int n = 0; n < ArraySize; n++) {
        for (int m = 0; m < ArraySize; m++) {
            for (int DiagDirection = 0; DiagDirection < 8; DiagDirection++) {
                /* 0 is top left to bottom right (diagonal down-right)
                   1 is top right to bottom left (diagonal down-left)
                   2 is bottom right to top left (diagonal up-left)
                   3 is bottom left to top right (diagonal up-right)
                   4 is left to right
                   5 is right to left
                   6 is top to bottom
                   7 is bottom to top  */
                bool WordFoundDiag = true;
        
                for (int i = 0; i < word.size(); i++) {
                    int DiagRow;
                    if (DiagDirection == 0 || DiagDirection == 1 || DiagDirection == 6) {
                        DiagRow = n + i;
                    } else if (DiagDirection == 2 || DiagDirection == 3 || DiagDirection == 7) {
                        DiagRow = n - i;
                    } else {
                        DiagRow = n;
                    }
                
                    int DiagCol;
                    if (DiagDirection == 0 || DiagDirection == 3 || DiagDirection == 4) {
                        DiagCol = m + i;
                    } else if (DiagDirection == 1 || DiagDirection == 2 || DiagDirection == 5) {
                        DiagCol = m - i;
                    } else {
                        DiagCol = m;
                    }
                
                    if (DiagCol < 0 || DiagRow < 0 || DiagCol >= ArraySize || DiagRow >= ArraySize || table[DiagRow][DiagCol] != word[i]) {
                        WordFoundDiag = false;
                        break;
                    }
                }
                
                if (WordFoundDiag) {
                    string DiagDirectionStr;
                    if (DiagDirection == 0) {
                        DiagDirectionStr = "down-right";
                    } else if (DiagDirection == 1) {
                        DiagDirectionStr = "down-left";
                    } else if (DiagDirection == 2) {
                        DiagDirectionStr = "up-left";
                    } else if (DiagDirection == 3) {
                        DiagDirectionStr = "up-right";
                    } else if (DiagDirection == 4) {
                        DiagDirectionStr = "right";
                    } else if (DiagDirection == 5) {
                        DiagDirectionStr = "left";
                    } else if (DiagDirection == 6) {
                        DiagDirectionStr = "down";
                    } else if (DiagDirection == 7) {
                        DiagDirectionStr = "up";
                    } else {
                        DiagDirectionStr = "unknown";
                    }
                
                    cout << word << " was found " << DiagDirectionStr << " at row " << n << " and column " << m << endl;
                    FoundWords++;
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    const int ArraySize = 8; // The # indicates how big the SQUARE array 
    int TotalFoundWords = 0;
    char table[ArraySize][ArraySize];
    vector<string> ArrayedWords;
    int TotalWords = 0;

    // Finds and reads file. If not found, it gives error
    if (!readInputFile("Input File.txt", table)) {
        return 0;
    }

    // Read words from words.txt
    unordered_set<string> dictionary = readDictionary("words.txt"); // Initial file reading, removes duplicates, increase reading speed (sources online)
    ArrayedWords.assign(dictionary.begin(), dictionary.end()); // Convert set to vector

    // Printing Table
    printTable(table);
    cout << endl;

    // Searching Word + Output 
    cout << "Found Words" << endl;
    for (const string& word : ArrayedWords) {
        WordSearch(table, word, TotalFoundWords);
        TotalWords++;
    }

    cout << "Found Words: " << TotalFoundWords << endl; 

    return 0;
}
