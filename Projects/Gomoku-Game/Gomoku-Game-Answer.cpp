#include <bits/stdc++.h>
using namespace std;

const int N = 15;
const int M = 15;
const int a_row = 5;
char grid[N][M];

//This function prints the grid of Gomoku as the game progresses
void print_grid() {
    cout << "Player 1: B  vs  Player 2: W\n";
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
    char s;
    int cnt;
    //If row is full with same characters, 
	//the game is over and the player with that character has won
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < M-a_row+1; j++) {
			s = grid[i][j];
			cnt = 0;
			for (int k = j; k < j+a_row; k++)
				if (s == grid[i][k])
					cnt ++;
			if (cnt == a_row && s != '.')
				return true;
		}
    }
    //If column is full with same characters, 
	//the game is over and the player with that character has won
    for (int i = 0; i < M; i++) {
		for (int j = 0; j < N-a_row+1; j++) {
			s = grid[j][i];
			cnt = 0;
			for (int k = j; k < j+a_row; k++)
				if (s == grid[k][i])
					cnt ++;
			if (cnt == a_row && s != '.')
				return true;
		}
    }
    //If diagonal 1 is full with same characters, 
	//the game is over and the player with that character has won
    for (int i = 0; i < N; i++) {
        if (i+a_row-1 >= N)
            continue;
        for (int j = 0; j < M; j++) {
            if (j+a_row-1 >= M)
                continue;
            s = grid[i][j];
			cnt = 0;
			for (int k = 0; k < a_row; k++) {
				if (s == grid[i+k][j+k])
					cnt ++;
			}
			if (cnt == a_row && s != '.')
				return true;
		}
	}
    //If diagonal 2 is full with same characters, 
	//the game is over and the player with that character has won
    for (int i = 0; i < N; i++) {
        if (i+a_row-1 >= N)
            continue;
        for (int j = 0; j < M; j++) {
            if (j-a_row+1 < 0)
                continue;
            s = grid[i][j];
			cnt = 0;
			for (int k = 0; k < a_row; k++) {
				if (s == grid[i+k][j-k])
					cnt ++;
			}
			if (cnt == a_row && s != '.')
				return true;
		}
	}
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached	
    return false;
}
//This function checks if row or column or diagonal is full with same characters
bool check_tie(char mark) {
    char s;
    int cnt;
    //If row a single type of characters
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < M-a_row+1; j++) {
			s = mark;
			cnt = 0;
			for (int k = j; k < j+a_row; k++)
				if (grid[i][k] != '.' && s != grid[i][k])
					cnt ++;
			if (cnt == 0)
				return false;
		}
    }
    //If column a single type of characters
    for (int i = 0; i < M; i++) {
		for (int j = 0; j < N-a_row+1; j++) {
			s = mark;
			cnt = 0;
			for (int k = j; k < j+a_row; k++)
				if (grid[k][i] != '.' && s != grid[k][i])
					cnt ++;
			if (cnt == 0)
				return false;
		}
    }
    //If diagonal a single type of characters
    for (int i = 0; i < N; i++) {
        if (i+a_row-1 >= N)
            continue;
        for (int j = 0; j < M; j++) {
            if (j+a_row-1 >= M)
                continue;
			s = mark;
			cnt = 0;
			for (int k = 0; k < a_row; k++) {
				if (grid[i+k][j+k] != '.' && s != grid[i+k][j+k])
					cnt ++;
			}
			if (cnt == 0)
				return true;
		}
	}
    //If diagonal a single type of characters
    for (int i = 0; i < N; i++) {
        if (i+a_row-1 >= N)
            continue;
        for (int j = 0; j < M; j++) {
            if (j-a_row+1 < 0)
                continue;
			s = mark;
			cnt = 0;
			for (int k = 0; k < a_row; k++) {
				if (grid[i+k][j-k] != '.' && s != grid[i+k][j-k])
					cnt ++;
			}
			if (cnt == 0)
				return true;
		}
	}
    //Otherwise, there isn't a win state in the game, 
    //if all cases above not reached	
	return true;
}
//This function checks if given cell is empty or not 
bool check_empty(int i, int j) {
	return grid[i][j] == '.';
}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {
	return 0 <= i && i < N && 0 <= j && j < M;
}
//This function sets a value to a cell
void set_cell(int i, int j, char mark) {
	grid[i][j] = mark;
}
//This function clears the grid
void grid_clear() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            grid[i][j] = '.';
}
//MAIN FUNCTION
void play_game() {
    cout << "Gomoku Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    bool player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Set mark value based on the player
        char mark = (player == 0? 'B' : 'W');
        //Read an input from the player
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
