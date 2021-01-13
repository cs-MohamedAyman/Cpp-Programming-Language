#include <bits/stdc++.h>
using namespace std;

/*
Assigning values to the grid
The grid will look like this:
  0,0 | 0,1 | 0,2 | 0,3 | 0,4 | 0,5 | 0,6
  1,0 | 1,1 | 1,2 | 1,3 | 1,4 | 1,5 | 1,6
  2,0 | 2,1 | 2,2 | 2,3 | 2,4 | 2,5 | 2,6
  3,0 | 3,1 | 3,2 | 3,3 | 3,4 | 3,5 | 3,6
  4,0 | 4,1 | 4,2 | 4,3 | 4,4 | 4,5 | 4,6
  5,0 | 5,1 | 5,2 | 5,3 | 5,4 | 5,5 | 5,6
*/
const int N = 6;
const int M = 7;
char grid[N][M];

//This function prints the grid of Connect Four Game as the game progresses
void print_grid() {
    cout << "Player 1: X  vs  Player 2: O\n";
    cout << "--";
    for (int i = 0; i < M; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
        for (int j = 0; j < M; j++)
            cout << grid[i][j] << "  ";
        cout << "|\n";
        cout << "--";
        for (int i = 0; i < M; cout << "---", i++);
        cout << "--\n";
    }
}
//This function checks if row or column or diagonal is full with same characters
bool check_win() {

}
//This function checks if row or column or diagonal is full with same characters
bool check_tie(char mark) {

}
//This function checks if given cell is empty or not 
bool check_empty(int i) {

}
//This function checks if given position is valid or not 
bool check_valid_column(int i) {

}
//This function sets a value to a cell
void set_cell(int i, char mark) {

}
//This function clears the grid
void grid_clear() {

}

//MAIN FUNCTION
void play_game() {
    cout << "Connect Four Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    bool player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Set mark value based on the player
        char mark = (player == 0? 'X' : 'O');
        //Takes input from the user to fill in the grid
        cout << "Player " << mark << '\n';
        int i;
        cout << "Enter the column index: ";
        cin >> i;
        while (!check_valid_column(i) || !check_empty(i)) {
            cout << "Enter a valid column index: ";
            cin >> i;
        }
        //Set the input position with the mark
        set_cell(i, mark);
        //Check if the state of the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
            cout << "Congrats, Player " << mark << " is won!\n";
            break;
        }
        //Check if the state of the grid has a tie state
        if (check_tie(mark)) {
            //Prints the grid
            print_grid();
            cout << "Woah! That's a tie!\n";
            break;
        }
        //Player number changes after each turn
        player = 1 - player;
    }
}
int main() {
    while (true) {
    	grid_clear();
    	play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
    }
}
