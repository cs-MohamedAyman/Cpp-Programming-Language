#include <bits/stdc++.h>
using namespace std;

/*
Assigning values to the grid
The grid will look like this:
  0,0 | 0,1 | 0,2 | 0,3 | 0,4 | 0,5 | 0,6 | 0,7 | 0,8
  1,0 | 1,1 | 1,2 | 1,3 | 1,4 | 1,5 | 1,6 | 1,7 | 1,8
  2,0 | 2,1 | 2,2 | 2,3 | 2,4 | 2,5 | 2,6 | 2,7 | 2,8
  3,0 | 3,1 | 3,2 | 3,3 | 3,4 | 3,5 | 3,6 | 3,7 | 3,8
  4,0 | 4,1 | 4,2 | 4,3 | 4,4 | 4,5 | 4,6 | 4,7 | 4,8
  5,0 | 5,1 | 5,2 | 5,3 | 5,4 | 5,5 | 5,6 | 5,7 | 5,8
  6,0 | 6,1 | 6,2 | 6,3 | 6,4 | 6,5 | 6,6 | 6,7 | 6,8
  7,0 | 7,1 | 7,2 | 7,3 | 7,4 | 7,5 | 7,6 | 7,7 | 7,8
  8,0 | 8,1 | 8,2 | 8,3 | 8,4 | 8,5 | 8,6 | 8,7 | 8,8
*/
const int N = 9;
const int root_N = 3;
int grid[N][N];
int cpy_grid[N][N];

//This function prints the grid of 2048 Game as the game progresses
void print_grid() {
    int dd_len = to_string(N).size();
    for (int i = 0; i < N*(dd_len+2); cout << "-", i++);
    for (int i = 0; i < root_N; cout << "---", i++);
	cout << "-";
	cout << '\n';
    for (int i = 0; i < N; i++) {
        cout << "|  ";
		for (int j = 0; j < N; j++) {
            if (j % root_N == 0 && j > 0)
                cout << "|  ";
            if (grid[i][j] == 0) {
				for (int k = 0; k < dd_len; cout << ".", k++);
				cout << "  ";
			}
            else {
				for (int k = 0; k < dd_len - to_string(grid[i][j]).size(); cout << "0", k++);
				cout << grid[i][j] << "  ";
			}
		}
		cout << "|";
		cout << '\n';
        if (i % root_N == root_N - 1) {
			for (int i = 0; i < N*(dd_len+2); cout << "-", i++);
			for (int i = 0; i < root_N; cout << "---", i++);
			cout << "-";
			cout << '\n';
		}
	}
}
//This function checks if all rows and columns and boxes is full with all numbers
bool check_win() {

}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {

}
//This function checks if given cell is empty or not 
bool check_empty_cell(int i, int j) {

}
//This function checks if given cell is original or not
bool check_original_cell(int i, int j) {

}
//This function checks if the given cell is valid with the given numbers
bool check_valid_value(int i, int j, int v) {

}
//This function sets a value to a cell
void set_cell(int i, int j, int v) {

}
//This function solve the grid
bool solve_grid(int i, int j) {
    if (j == N) {
        i += 1;
        j = 0;
	}
    if (i == N)
        return true;
    if (check_original_cell(i, j))
        return solve_grid(i, j + 1);
    for (int k = 1; k < N+1; k++) {
        if (check_valid_value(i, j, k)) {
            grid[i][j] = k;
            cpy_grid[i][j] = k;
            if (solve_grid(i, j + 1))
                return true;
		}
        grid[i][j] = 0;
        cpy_grid[i][j] = 0;
	}
    return false;
}
//This function generates cells in the grid
void generate_cells() {
    //Generate cells in the diagonal boxes of the grid
    for (int k = 0; k < N; k+=root_N) {
		for (int i = 0; i < root_N; i++) {
			for (int j = 0; j < root_N; j++) {
                int n = rand() % (N + 1) + 1;
                while (!check_valid_value(k+i, k+j, n) || check_original_cell(k+i, k+j))
					n = rand() % N + 1;
                grid[k+i][k+j] = n;
                cpy_grid[k+i][k+j] = n;
			}
		}
	}
    //Solve the complete grid
    solve_grid(0, 0);
    //Remove cells in the grid to be solved
    int prev_x = 0, prev_y = 0;
    for (int k = 0; k < N*N - N/2*N; k++) {
        int i = (rand() % N + prev_x + root_N) % N;
        int j = (rand() % N + prev_y + root_N) % N;
        while (!check_original_cell(i, j)) {
			i = (rand() % N + prev_x + root_N) % N;
			j = (rand() % N + prev_y + root_N) % N;
		}
        grid[i][j] = 0;
        cpy_grid[i][j] = 0;
        prev_x = i;
		prev_y = j;
	}
}
//This function clears the grid
void grid_clear() {

}


//MAIN FUNCTION
void play_game() {
    cout << "Sudoku Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    while (true) {
        //Prints the grid
        print_grid();
        int i, j, v;
        cout << "Enter the position and value: ";
        cin >> i >> j >> v;
        while (!check_valid_position(i, j) || !check_valid_value(i, j, v) || check_original_cell(i, j)) {
            cout << "Enter a valid position and value: ";
            cin >> i >> j >> v;
        }
        //Set the input position with the value
        set_cell(i, j, v);
        //Check if the state of the grid has a win state
        if (check_win()) {
            //Prints the grid
            print_grid();
            cout << "Congrats, You won!\n";
            break;
		}
	}
}
int main() {
	while (true) {
		grid_clear();
		generate_cells();
		play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
	}
}
