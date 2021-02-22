#include <bits/stdc++.h>
using namespace std;

const int N = 9;
const int root_N = sqrt(N);
int grid[N][N];
int cpy_grid[N][N];

//This function prints the grid of Sudoku Game as the game progresses
void print_grid() {
    int dd_len = to_string(N).size();
    for (int i = 0; i < N*(dd_len+2); cout << "-", i++);
    for (int i = 0; i < root_N; cout << "---", i++);
    cout << "-\n";
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
		cout << "|\n";
        if (i % root_N == root_N - 1) {
			for (int i = 0; i < N*(dd_len+2); cout << "-", i++);
			for (int i = 0; i < root_N; cout << "---", i++);
			cout << "-\n";
		}
	}
}
//This function checks if all rows and columns and boxes is full with all numbers
bool check_win() {
    //If row is not full with all numbers, the game is still running
    for (int i = 0; i < N; i++) {
        int s[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		for (int j = 0; j < N; j++) {
            s[grid[i][j]] ++;
			if (s[grid[i][j]] != 1 || grid[i][j] == 0)
				return false;
		}
	}
    //If column is not full with all numbers, the game is still running
    for (int i = 0; i < N; i++) {
        int s[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		for (int j = 0; j < N; j++) {
            s[grid[j][i]] ++;
			if (s[grid[j][i]] != 1 || grid[j][i] == 0)
				return false;
		}
	}
    //If box is not full with all numbers, the game is still running
    for (int i = 0; i < N; i+=root_N) {
		for (int j = 0; j < N; j+=root_N) {
			int s[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			for (int k = i; k < i+root_N; k++) {
				for (int w = j; w < j+root_N; w++) {
					s[grid[k][w]] ++;
					if (s[grid[k][w]] != 1 || grid[k][w] == 0)
						return false;
				}
			}
		}
	}
    //Otherwise, there is a win state in the game, 
    //if all cases above not reached		
    return true;
}
//This function checks if given position is valid or not 
bool check_valid_position(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < N;
}
//This function checks if given cell is empty or not 
bool check_empty_cell(int i, int j) {
    return grid[i][j] == 0;
}
//This function checks if given cell is original or not
bool check_original_cell(int i, int j) {
    return cpy_grid[i][j] != 0;
}
//This function checks if the given cell is valid with the given numbers
bool check_valid_value(int i, int j, int v) {
	//Check delete case
    if (v == 0)
        return true;
	//Check invalid value
    if (v < 0 || v > N)
        return false;
	//Check duplicate in all rows
    for (int k = 0; k < N; k++)
        if (grid[i][k] == v)
            return false;
	//Check duplicate in all columns
    for (int k = 0; k < N; k++)
        if (grid[k][j] == v)
            return false;
	//Check duplicate in all boxes
    int b = i/root_N*root_N;
	int e = j/root_N*root_N;
    for (int k = b; k < b+root_N; k++)
		for (int w = e; w < e+root_N; w++)
            if (grid[k][w] == v)
                return false;
    //Otherwise, the given value is valid,
    //if all cases above not reached		
    return true;
}
//This function sets a value to a cell
void set_cell(int i, int j, int v) {
	grid[i][j] = v;
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
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			grid[i][j] = 0;
			cpy_grid[i][j] = 0;
		}
	}
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
