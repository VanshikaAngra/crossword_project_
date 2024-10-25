#include <bits/stdc++.h>
using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

void placeHorizontally(vector<vector<string>>& grid, const string& word, int row, int col) {
    for (int j = 0; j < word.size(); j++) {
        grid[row][col + j] = string(1, word[j]);
    }
}

void placeVertically(vector<vector<string>>& grid, const string& word, int row, int col) {
    for (int i = 0; i < word.size(); i++) {
        grid[row + i][col] = string(1, word[i]);
    }
}

void placeDiagonally(vector<vector<string>>& grid, const string& word, int row, int col) {
    for (int i = 0; i < word.size(); i++) {
        grid[row + i][col + i] = string(1, word[i]);
    }
}

bool canPlaceHorizontally(const vector<vector<string>>& grid, const string& word, int row, int col) {
    if (col + word.size() > grid[0].size()) return false;
    for (int j = 0; j < word.size(); j++) {
        if (grid[row][col + j] != "*" && grid[row][col + j] != string(1, word[j])) return false;
    }
    return true;
}

bool canPlaceVertically(const vector<vector<string>>& grid, const string& word, int row, int col) {
    if (row + word.size() > grid.size()) return false;
    for (int i = 0; i < word.size(); i++) {
        if (grid[row + i][col] != "*" && grid[row + i][col] != string(1, word[i])) return false;
    }
    return true;
}

bool canPlaceDiagonally(const vector<vector<string>>& grid, const string& word, int row, int col) {
    if (row + word.size() > grid.size() || col + word.size() > grid[0].size()) return false;
    for (int i = 0; i < word.size(); i++) {
        if (grid[row + i][col + i] != "*" && grid[row + i][col + i] != string(1, word[i])) return false;
    }
    return true;
}

void displayGrid(const vector<vector<string>>& grid) {
    int rowCount = grid.size();
    int colCount = grid[0].size();

    cout << "---------------------" << endl;
    for (int i = 0; i < rowCount; i++) {
        cout << "| ";
        for (int j = 0; j < colCount; j++) {
            if (grid[i][j] == "*") {
                cout << WHITE << grid[i][j] << RESET << " ";
            } else {
                if ((i + j) % 2 == 0) {
                    cout << RED << grid[i][j] << RESET << " ";
                } else {
                    cout << GREEN << grid[i][j] << RESET << " ";
                }
            }
        }
        cout << "|" << endl;
    }
    cout << "---------------------" << endl;
}

int main() {
    int wordCount;
    cout << "Enter the number of words in Crossworld: ";
    cin >> wordCount;
    cout << "Enter the words to be added to the Crossworld:" << endl;

    vector<string> wordList(wordCount);
    for (int i = 0; i < wordCount; i++) {
        cin >> wordList[i];
    }

    int rows = wordCount * 2, cols = wordCount * 2;
    vector<vector<string>> crossword(rows, vector<string>(cols, "*"));

    for (int i = 0; i < wordCount; i++) {
        bool placed = false;

        for (int r = 0; r < rows && !placed; r++) {
            for (int c = 0; c < cols && !placed; c++) {
                if (i % 3 == 0 && canPlaceHorizontally(crossword, wordList[i], r, c)) {
                    placeHorizontally(crossword, wordList[i], r, c);
                    placed = true;
                } else if (i % 3 == 1 && canPlaceVertically(crossword, wordList[i], r, c)) {
                    placeVertically(crossword, wordList[i], r, c);
                    placed = true;
                } else if (i % 3 == 2 && canPlaceDiagonally(crossword, wordList[i], r, c)) {
                    placeDiagonally(crossword, wordList[i], r, c);
                    placed = true;
                }
            }
        }

        if (!placed) {
            cout << "Could not place the word: " << wordList[i] << endl;
        }
    }

    displayGrid(crossword);
    
    return 0;
}
