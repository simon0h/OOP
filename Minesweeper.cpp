//Minesweeper game

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Minesweeper {
public:

	Minesweeper() {
		cout << "Welcome to minesweeper. \n+ represents tile that has not been checked yet. \n* represents bomb. \nNumber represents the number of bombs around that tile. \nEnjoy.\n \n";
		fillBoard(board);
    }

    struct Tile {
        int value = 0;//Amount of bombs around the tile
        bool visible = false;
    };

	void display(bool showAll) {
        if (showAll == false) {//Prints out string representation of the board
            for (int i = 1; i < board.size() - 1; ++i) {                      
                for (int j = 1; j < board[0].size() - 1; ++j) {
                    if (board[i][j].visible == false) {
                        cout << "+" << " "; 
                    }
                    else {
                        cout << board[i][j].value << " "; 
                    }
                }
                cout << "\n";
            }
        }
        else {
            for (int i = 1; i < board.size() - 1; ++i) {                      
                for (int j = 1; j < board[0].size() - 1; ++j) {
                    if (board[i][j].value == 9) {
                        cout << "*" << " "; 
                    }
                    else {
                        cout << board[i][j].value << " "; 
                    }
                }
                cout << "\n";
            }
        }
        cout <<"\n";
    }

	bool done() {
		if (visibleTiles == (100 - bombLoc.size())) {//Because there are 100 tiles and bombLoc is a vector whose size represents the total number of bombs, 100 - number of bombs is the total number of tiles that would have to be visible in order for the game to be completed.
			return true;
		}
		else {
			return false;
		}
	}

	bool validRow(int r) {
		if (r > 0 && r < 11){
			return true;
		}
		else {
			return false;
		}
	}

	bool validCol(int c) {
		if (c > 0 && c < 11) {
			return true;
		}
		else {
			return false;
		}
	}

	bool isVisible(int r, int c) {
		bool shown = false;
		if (board[r][c].visible == true) {
			shown = true;
		}
		return shown;
	}

	 bool play(int r, int c) {
        bool explosion = true;
        if (board[r][c].value == 9) {
            explosion = false;
        }
        else {
            checkAround(r, c, board, visibleTiles);
        }
        return explosion;
    }

private:

	vector<vector<Tile>> board;

	int visibleTiles = 0;//Keeps count of the total number of tiles that have been made visible

	vector<int> bombLoc = bombLocation();//A vector containing bomb location

	vector<int> bombLocation() {
		srand(time(NULL));
		vector<int> location;
	    int n = 0;
	    for (int j = 0; j < 10; j ++) {
	        int random = rand() % 10;
	        location.push_back(random);
	    }
	    for (int i = 0; i < location.size(); i ++) {
        	cout << location[i] << "\n";
    	}
	    return location;
	}

	void fillBoard(vector<vector<Tile>>& board) {//Creates a 12 by 12 board and fills it with -1 so the edges are all -1 and the middle 10 by 10 board can be filled in later
        for (int r = 0; r < 12; ++r) {                      
            vector<Tile> row;  
            for (int c = 0; c < 12; ++c) {
                Tile tile;
                tile.value = -1;
                row.push_back(tile); 
            }
            board.push_back(row);
        }
        //Fills the 10 by 10 board
        int counter = 0;
        for (int row = 1; row < 11; ++row) {   
        	counter ++;                   
            for (int col = 1; col < 11; ++col) {
                if (bombLoc[counter]== col) {
                    board[row][col].value = 9;
                }
                else {
                    board[row][col].value = 0;
                } 
            }
        }
        //Gets the number of bombs surrounding the tile
        for (int a = 1; a < 11; ++a) {                      
            for (int b = 1; b < 11; ++b) {
                tileValue(a, b, board);
            }
        }
    }

    void tileValue(int r, int c, vector<vector<Tile>>& board) {
        int tileNum = 0;
        if (board[r][c].value != 9) {
            for (int row = r - 1; row < r + 2; ++row) {                      
                if (board[row][c - 1].value == 9) {
                    tileNum ++;
                }
                if (board[row][c].value == 9) {
                    tileNum ++;
                }
                if (board[row][c + 1].value == 9) {
                    tileNum ++;
                }
            }
            board[r][c].value = tileNum;
        }
    }

    void checkAround(int r, int c, vector<vector<Tile>>& board, int& visibleTiles){ //Checks around the tile in [r][c] to find if there are any bombs around it
    	visibleTiles ++;
        board[r][c].visible = true;
        for (int row = r - 1; row < r + 2; ++row) {                      
            if (board[row][c - 1].value == 0) {
                if (board[row][c - 1].visible == false) {
                    checkAround(row, c - 1, board, visibleTiles);
                }
            }
            if (board[row][c].value == 0) {
                if (board[row][c].visible == false) {
                    checkAround(row, c, board, visibleTiles);
                }
            }
            if (board[row][c + 1].value == 0) {
                if (board[row][c + 1].visible == false) {
                    checkAround(row, c + 1, board, visibleTiles);
                }
            }
        }
    }

};

int main() {
    Minesweeper sweeper;
    //Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); //Display board without bombs

        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            //Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validCol(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        //Set selected square to be visible. May affect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); //Final board with bombs shown
            exit(0);
        }
    }
    //Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); //Final board with bombs shown
}
