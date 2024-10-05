#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;
const int ArraySize = 8; // The # indicates how big the SQUARE array is
int TotalFoundWords = 0;


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
    // X = rows
    // Y = Columns 
    // +1 is down/right, -1 is up/left

    for (int x = 0; x < ArraySize; x++) {
        for (int y = 0; y < ArraySize; y++) {
    for (int DiagDirection = 0; DiagDirection < 8; DiagDirection++) {
        // 0 is top left to bottom right (diagonal down-right)
        // 1 is top right to bottom left (diagonal down-left)
        // 2 is bottom right to top left (diagonal up-left)
        // 3 is bottom left to top right (diagonal up-right)
        // 4 is horizontal left to right
        // 5 is horizontal right to left
        // 6 is vertical top to bottom
        // 7 is vertical bottom to top
        
        bool WordFoundDiag = true;

        for (int i = 0; i < word.size(); i++) {
            int DiagRow = x + i * ((DiagDirection == 0 || DiagDirection == 1 || DiagDirection == 6) ? 1 : (DiagDirection == 2 || DiagDirection == 3 || DiagDirection == 7) ? -1 : 0);
            int DiagCol = y + i * ((DiagDirection == 0 || DiagDirection == 3 || DiagDirection == 4) ? 1 :  (DiagDirection == 1 || DiagDirection == 2 || DiagDirection == 5) ? -1 : 0);
            if (DiagCol < 0 || DiagRow < 0 || DiagCol >= ArraySize || DiagRow >= ArraySize || table[DiagRow][DiagCol] != word[i]) {
                WordFoundDiag = false;
                break;
            }
        }
        if (WordFoundDiag) {
            string DiagDirectionStr = (DiagDirection == 0 ? "down-right" : 
                                       DiagDirection == 1 ? "down-left" : 
                                       DiagDirection == 2 ? "up-left" : 
                                       DiagDirection == 3 ? "up-right" : 
                                       DiagDirection == 4 ? "right" : 
                                       DiagDirection == 5 ? "left" : 
                                       DiagDirection == 6 ? "down" :
                                       DiagDirection == 7 ? "up" : "unknown");

            cout << word << " was found " << DiagDirectionStr << " at row " << x << " and column " << y << endl;
            FoundWords++;
            return true;
        }
    }
}
    }
    return false;
}

int main() {
    char table[ArraySize][ArraySize];
    vector<string> ArrayedWords; // Replace static array with dynamic list
    int TotalWords = 0;

    // Finds and reads file. If not found, it gives error
    if (!readInputFile("Input File.txt", table)) {
        return 0;
    }

    // Read words from words.txt
    unordered_set<string> dictionary = readDictionary("words.txt");
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
