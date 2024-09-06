#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;

const int ArraySize = 8; // The # indicates how big the SQUARE array is
int CorrectWords;

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
bool WordSearch(const char table[ArraySize][ArraySize], const string& word, int CorrectWords) {
    // X = rows
    // Y = Columns 
    // +1 is down/right, -1 is up/left

    for (int x = 0; x < ArraySize; x++) {
        
        // Horizontal Search (2 directions)
        for (int y = 0; y <= ArraySize; y++) {
            for (int HorzDirection = -1; HorzDirection <= 1; HorzDirection += 2) {
                bool WordFoundNormHoriz = true;
                for (int i = 0; i < word.size(); i++) {
                    int HorzCol = y + i * HorzDirection; // calculating what column it is on
                    if (HorzCol < 0 || HorzCol >= ArraySize || table[x][HorzCol] != word[i]) { // Keeping search in bound and see if match
                        WordFoundNormHoriz = false;
                        break;
                    }
                }
                if (WordFoundNormHoriz) {
                    string HorzDirectionStr = (HorzDirection == 1) ? "left" : "right";
                    cout << word << " was found horizontally " << HorzDirectionStr << " at row " << x << " and column " << y << endl;
                    CorrectWords++;
                    return true;
                }
            }
        }

        // Vertical Search (2 directions)
        for (int y = 0; y < ArraySize; y++) {
            for (int VertDirection = -1; VertDirection <= 1; VertDirection += 2) {
                bool WordFoundVert = true;
                for (int i = 0; i < word.size(); i++) {
                    int VertRow = x + i * VertDirection; // calculate what row it is on
                    if (VertRow < 0 || VertRow >= ArraySize || table[VertRow][y] != word[i]) { // Keeping search in bound and see if match
                        WordFoundVert = false;
                        break;
                    }
                }
                if (WordFoundVert) {
                    string VertDirectionStr = (VertDirection == 1) ? "right" : "left";
                    cout << word << " was found vertically " << VertDirectionStr << " at row " << x << " and column " << y << endl;
                    CorrectWords++;
                    return true;
                }
            }
        }

        // Diagonal Search (4 directions)
        for (int y = 0; y < ArraySize; y++) {
            for (int DiagDirection = 0; DiagDirection < 4; DiagDirection++) {
                // 0 is top left to bottom right
                // 1 is top right to bottom left 
                // 2 is bottom right to top left
                // 3 is bottom left to top right 
                bool WordFoundDiag = true;
                for (int i = 0; i < word.size(); i++) {
                    int DiagRow = x + i * (DiagDirection == 0 ? 1 : (DiagDirection == 1 ? 1 : (DiagDirection == 2 ? -1 : -1)));  // Calculating movement for row
                    int DiagCol = y + i * (DiagDirection == 0 ? 1 : (DiagDirection == 1 ? -1 : (DiagDirection == 2 ? -1 : 1))); // Calculating movement for col
                    if (DiagCol < 0 || DiagRow < 0 || DiagCol >= ArraySize || DiagRow >= ArraySize || table[DiagRow][DiagCol] != word[i]) { // Keeping search in bound and see if match
                        WordFoundDiag = false;
                        break;
                    }
                }
                if (WordFoundDiag) {
                    string DiagDirectionStr = (DiagDirection == 0 ? "down-right" : (DiagDirection == 1 ? "down-left" : (DiagDirection == 2 ? "up-left" : "up-right")));
                    cout << word << " was found diagonally " << DiagDirectionStr << " at row " << x << " and column " << y << endl;
                    CorrectWords++;
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

    cout << "Found Words" << endl;

    // Searching Word + Output 
    for (const string& word : ArrayedWords) {

        WordSearch(table, word, CorrectWords);
        TotalWords++;
    }

    //cout << endl << "Total Words: " << TotalWords << endl;
    //cout << "Correct Words: " << CorrectWords << endl; // Fix Later

    return 0;
}
