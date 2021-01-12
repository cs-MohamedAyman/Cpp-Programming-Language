#include <bits/stdc++.h>
using namespace std;

/*
Assigning values to the grid
The grid will look like this:
  0,0 | 0,1 | 0,2
  1,0 | 1,1 | 1,2
  2,0 | 2,1 | 2,2
*/
const int N = 3;
char grid[N][N];

//This function prints the grid of Tic-Tac-Toe as the game progresses
void print_grid() {
    cout << "Player 1: X  vs  Player 2: O\n";
    cout << "--";
    for (int i = 0; i < N; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << "  ";
        cout << "|\n";
        cout << "--";
        for (int i = 0; i < N; cout << "---", i++);
        cout << "--\n";
    }
}
//This function checks if row or column or diagonal is full with same characters
bool check_win() {
    //If row is full with same characters, 
	//the game is over and the player with that character has won

    //If column is full with same characters, 
	//the game is over and the player with that character has won

    //If diagonal 1 is full with same characters, 
	//the game is over and the player with that character has won

    //If diagonal 2 is full with same characters, 
	//the game is over and the player with that character has won

    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached	

}
//This function checks if row or column or diagonal is full with same characters
bool check_tie(char mark) {
    //If row a single type of characters

    //If column a single type of characters

    //If diagonal a single type of characters

    //If diagonal a single type of characters

    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached	

}
//This function checks if given cell is empty or not 
bool check_empty(int i, int j) {

}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {

}
//This function sets a value to a cell
void set_cell(int i, int j, char mark) {

}
//This function clears the grid
void grid_clear() {

}
//MAIN FUNCTION
void play_game() {
    cout << "Tic-Tac-Toe Game!\n";
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
        int i, j;
        cout << "Enter the row index and column index: ";
        cin >> i >> j;
        while (!check_valid_position(i, j) or !check_empty(i, j)) {
            cout << "Enter a valid row index and a valid column index: ";
            cin >> i >> j;
        }
        //Set the input position with the mark
        set_cell(i, j, mark);
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
