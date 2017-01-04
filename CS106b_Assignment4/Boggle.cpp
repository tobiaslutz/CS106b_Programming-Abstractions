/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */
 
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "point.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const Lexicon english("EnglishWords.dat");

/* Function prototypes */

void welcome();
void giveInstructions();
int boardConfiguration();
void setupCubes(Grid<char> &board, bool testRun);
Vector<string> humanSearch(Grid<char> board);
void computerSearch(Grid<char> board, Point root, Vector<string> &words, string newWord);
void startComputerSearch(Grid<char> board, Vector<string> &words);
void exploreAllDirections (Grid<char> board, Point root, Vector<string> &words, string newWord);
bool existsOnBoard(Grid<char> board, string word, Vector<Point> &m);
Grid<char> generateTestBoard();
enum Direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST};
Direction operator++(Direction & dir, int);
Point adjacentPoint(Point start, Direction dir);

/* Main program */

int main() {
    int c = 1;
    bool anotherGame = true;
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    while(anotherGame) {
        if (c == 1) {
            welcome();
            giveInstructions();
        }
        else    {
            while (true)    {
                cout << "Do you want to see the instructions again (yes/no)?" << endl;
                string instructions = getLine();
                if (instructions == "yes")  {
                    giveInstructions();
                    break;
                }
                else if (instructions == "no")
                    break;
                else
                    cout << "I did not unterstand. " << endl;
            }
        }
        int numRows = boardConfiguration();
        Grid<char> board(numRows,numRows);
        bool testRun = false;
        if(testRun)
            board = generateTestBoard();
        setupCubes(board, testRun);
        Vector<string> foundWords = humanSearch(board);
        startComputerSearch(board, foundWords);
        c++;
        while (true)    {
            cout << "Are you ready for another game of Boogle (yes/no)?" << endl;
            string newGame = getLine();
            if (newGame == "no")    {
                anotherGame = false;
                break;
            }
            else if(newGame == "yes")   break;
            else    cout << "I did not unterstand. " << endl;
        }

    }
    cout << "Done. Thank you!" << endl;
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/*
 * Function: boardConfiguration
 * Usage: int numRows = boardConfiguration();
 * --------------------------
 * Let the user specify the number of rows and columns of the squared board and returns this value
 */
int boardConfiguration()   {
    while(true) {
        int numRows = getInteger("Side length of square board (4 or 5)?");
        if (numRows == 4 || numRows == 5)   {
            drawBoard(numRows, numRows);
            return numRows;
        }
        cout << "Please provide a positive integer!" << endl;
    }
}

/*
 * Function: setupCubes(Grid<char> &letters, bool testRun)
 * Usage: setupCubes(letters, testRun);
 * --------------------------
 * Functionality: Labels the cubes on the gui after having chosen a random character of each string in
 * STANDARD_CUBES or BIG_BOOGLE_CUBES, shuffling these random characters and showing them on the gui 
 * cubes
 *
 */
void setupCubes(Grid<char> &letters, bool testRun)   {
    
    int numRows = letters.numRows();
    if(testRun) {
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numRows; col++) {
                labelCube(row, col, letters.get(row, col));
            }
        }
    }
    else    {
        string cube;
        // Choose a random side of each cube in cubes and places the resulting characters in a 2D
        // array
        if (numRows == 4)   {
            for (int row = 0; row < numRows; row++) {
                for (int col = 0; col < numRows; col++) {
                        cube = STANDARD_CUBES[(row * (numRows)) + col];
                letters[row][col] = cube.at(randomInteger(0, 5));
                }
            }
        }
        else    {
            for (int row = 0; row < numRows; row++) {
                for (int col = 0; col < numRows; col++) {
                    cube = BIG_BOGGLE_CUBES[(row * (numRows)) + col];
                    letters[row][col] = cube.at(randomInteger(0, 5));
                }
            }
        }

        // Shuffles the 2D array and places each element of the array onto the cubes of the gui
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numRows; col++) {
                int rand_r = randomInteger(row, numRows-1);
                int rand_c = randomInteger(col, numRows-1);
                char temp = letters.get(row, col);
                letters[row][col] = letters.get(rand_r, rand_c);
                letters[rand_r][rand_c] = temp;
                labelCube(row, col, letters.get(row, col));
            }
        }
    }
}

/*
 * Function: humanSearch(Grid<char> &board)
 * Usage: humanSearch(board);
 * --------------------------
 * Functionality: Asks the user for words he spotted on the board and checks whether the words satisfy
 * the minimum requirements
 */
Vector<string> humanSearch(Grid<char> board)    {
    string word;
    bool wordIsNew;
    Vector<string> wordList;
    
    while(true) {
        Vector<Point> matchingCubes;
        cout << "Enter a word you found (or hit Enter to return): ";
        getline(cin, word);
        word = toUpperCase(word);
        wordIsNew = true;
        if (word == "") {
            cout << "You just finished your turn. " << endl;
            return wordList;
        }
        if (word.length() >= 4 && english.contains(word)) {
            for (int i = 0; i < wordList.size(); i++)   {
                if(wordList.get(i) == word) {
                    wordIsNew = false;
                    break;
                }
            }
            if (wordIsNew && existsOnBoard(board, word, matchingCubes)) {
                for (int l = matchingCubes.size() - 1; l >= 0; l--)  {
                    highlightCube(matchingCubes.get(l).getX(), matchingCubes.get(l).getY(), true);
                    pause(200);
                    highlightCube(matchingCubes.get(l).getX(), matchingCubes.get(l).getY(), false);
                }
                recordWordForPlayer(word,HUMAN);
                wordList.add(word);
                cout << "Congratulations! " + word + " is a valid choice." << endl;
            }
            else
                cout << "No valid choice. Try again! " << endl;
        }
        else
            cout << "No valid choice. Try again! " << endl;
    }
}

/*
 * Function: verifyWord(Grid<char> &board, string word, Point start)
 * Usage: bool wordExists = humanSearch(board);
 * --------------------------
 * Functionality: Checks whether word can be found on the board whereas the search starts from 
 * position start using recursive backtracking
 */

bool verifyWord(Grid<char> board, string word, Point start, Vector<Point> &m) {
    int numRows = board.numRows();
    if (word.size() == 0)   return true;
    if (word.at(0) != board.get(start.getX(), start.getY()) || board.get(start.getX(), start.getY()) == '%')   return false;
    for (Direction dir = NORTH; dir <= NORTHWEST; dir++)    {
        Point nextPoint = adjacentPoint(start, dir);
        if(nextPoint.getX() >= 0 && nextPoint.getX() < numRows && nextPoint.getY() >= 0
           && nextPoint.getY() < numRows)   {
            board[start.getX()][start.getY()] = '%';
            if(verifyWord(board, word.substr(1), nextPoint, m))    {
                m.add(start);
                return true;
            }
        }
    }
    return false;
}

/*
 * Function: operator++(Direction & dir, int)
 * Usage: for(Direction dir = NORTH; dir <= NORTHWEST; dir++)    { ...}
 * --------------------------
 * Functionality: Overloads the ++ operator for usage with the data type Direction 
 */
Direction operator++(Direction & dir, int) {
    Direction old = dir;
    dir = Direction(dir + 1);
    return old;
}

/*
 * Function: adjacentPoint(Point start, Direction dir)
 * Usage: Point nextPoint = adjacentPoint(currentPoint, NORTH)
 * --------------------------
 * Functionality: Moves a point on a 2D integer grid towards the specified direction, whereas each 
 * dimension is incremented or decremented at most by 1
 */
Point adjacentPoint(Point start, Direction dir) {
    switch(dir) {
        case NORTH: return Point(start.getX() - 1, start.getY());
        case NORTHEAST: return Point(start.getX() - 1, start.getY() + 1);
        case EAST:  return Point(start.getX(), start.getY() + 1);
        case SOUTHEAST: return Point(start.getX() + 1 , start.getY() + 1);
        case SOUTH: return Point(start.getX() + 1, start.getY());
        case SOUTHWEST: return Point(start.getX() + 1, start.getY() - 1);
        case WEST:  return Point(start.getX(), start.getY() - 1);
        case NORTHWEST: return Point(start.getX() - 1, start.getY() - 1);
    }
}

/*
 * Function: existsOnBoard(Grid<char> &board, string word)
 * Usage: bool wordExists = existsOnBoard(board, word)
 * --------------------------
 * Functionality: Parses each position of the board and applies recursive backtracking to each
 * position by means of the function verifyWord(Grid<char> &board, string word, Point start). As soon
 * as the word is found, the function returns true
 */
bool existsOnBoard(Grid<char> board, string word, Vector<Point> &m) {
    int numRows = board.numRows();
    for (int r = 0; r < numRows; r++)   {
        for (int c = 0; c < numRows; c++)   {
            Point root(r,c);
            if(verifyWord(board, word, root, m))
                return true;
        }
    }
    return false;
}

void startComputerSearch(Grid<char> board, Vector<string> &words)  {
    cout << "Now I, the super computer, will beat your ass!" << endl;
    cout << "Hit return when you're ready...";
    getLine();
    cout << "Computer Search starts..." << endl;
    int numRows = board.numRows();
    for (int r = 0; r < numRows; r++)   {
        for (int c = 0; c < numRows; c++)   {
            Point root(r,c);
            computerSearch(board, root, words, "");
        }
    }
}

void computerSearch(Grid<char> board, Point root, Vector<string> &words, string newWord)    {
    
    if (board.get(root.getX(), root.getY()) == '%')
        return;
    else    {
        newWord += board.get(root.getX(), root.getY());
        board[root.getX()][root.getY()] = '%';
        
        if (newWord.length() >= 4 && english.contains(newWord)) {
            bool wordIsNew = true;
            for (int i = 0; i < words.size(); i++)   {
                if(words.get(i) == newWord) {
                    wordIsNew = false;
                    break;
                }
            }
            if(wordIsNew)   {
                recordWordForPlayer(newWord,COMPUTER);
                words.add(newWord);
            }
            exploreAllDirections(board,root, words, newWord);
        }
        else
            exploreAllDirections(board,root, words, newWord);
    }
}

void exploreAllDirections (Grid<char> board, Point root, Vector<string> &words, string newWord) {
    int numRows = board.numRows();
    if (english.containsPrefix(newWord)) {
        for (Direction dir = NORTH; dir <= NORTHWEST; dir++)    {
            Point nextPoint = adjacentPoint(root, dir);
            if(nextPoint.getX() >= 0 && nextPoint.getX() < numRows && nextPoint.getY() >= 0
               && nextPoint.getY() < numRows)   {
                computerSearch(board, nextPoint, words, newWord);
            }
        }
    }
}

Grid<char> generateTestBoard()  {
    Grid<char> testBoard(4,4);
    testBoard[0][0] = 't';
    testBoard[0][1] = 'e';
    testBoard[0][2] = 's';
    testBoard[0][3] = 't';
    testBoard[1][0] = 't';
    testBoard[1][1] = 't';
    testBoard[1][2] = 'h';
    testBoard[1][3] = 't';
    testBoard[2][0] = 't';
    testBoard[2][1] = 'i';
    testBoard[2][2] = 's';
    testBoard[2][3] = 't';
    testBoard[3][0] = 't';
    testBoard[3][1] = 'e';
    testBoard[3][2] = 's';
    testBoard[3][3] = 't';
    
    return testBoard;
}


