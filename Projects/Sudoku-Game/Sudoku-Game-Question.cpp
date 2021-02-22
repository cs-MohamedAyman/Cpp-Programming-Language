#include <bits/stdc++.h>
using namespace std;

const int N = 9;
const int root_N = sqrt(N);
int grid[N][N];
int cpy_grid[N][N];

//This function prints the grid of Sudoku Game as the game progresses
void print_grid() {
    char symbols[17] = {'.', '1', '2', '3', '4', '5', '6', '7',
					    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    for (int i = 0; i < N*3; cout << "-", i++);
    for (int i = 0; i < root_N; cout << "---", i++);
    cout << "-\n";
    for (int i = 0; i < N; i++) {
        cout << "|  ";
		for (int j = 0; j < N; j++) {
            if (j % root_N == 0 && j > 0)
                cout << "|  ";
			cout << symbols[grid[i][j]] << "  ";
		}
		cout << "|\n";
        if (i % root_N == root_N - 1) {
			for (int i = 0; i < N*3; cout << "-", i++);
			for (int i = 0; i < root_N; cout << "---", i++);
			cout << "-\n";
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
                int n = rand() % N + 1;
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
        //Read an input from the player
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
