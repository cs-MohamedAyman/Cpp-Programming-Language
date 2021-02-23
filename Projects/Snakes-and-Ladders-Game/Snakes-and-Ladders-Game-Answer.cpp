#include <bits/stdc++.h>
using namespace std;

const int N = 10;
const int M = 10;
const int n_players = 2;
const int n_components = 6;
char ladder_symbol = 'L';
char snake_symbol = 'S';
char grid[N][M];
int player_position[n_players];
int snakes[n_components][n_players];
int ladders[n_components][n_players];

//This function converts the given indices into position
void convert_indices_to_position(int i, int j, int &p) {
    p = (N - i - 1) * M;
    if (i % 2 == N % 2)
        p += M - j;
    else
        p += j + 1;
}
//This function converts the given position into indices
void convert_position_to_indices(int p, int &i, int &j) {
    i = N - (p - 1) / M - 1;
    if (i % 2 == N % 2)
        j = (M - p % M) % M;
    else
        j = (p % M - 1 + M) % M;
}
//This function prints the grid of Snakes and Ladders as the game progresses
void print_grid() {
    cout << "Player 1: X  vs  Player 2: O\n";
	for (int i = 0; i < M; cout << "-------", i++);
	cout << "-\n";
	for (int i = 0; i < N; i++) {
		string row_res = "";
        row_res += "|";
		for (int j = 0; j < M; j++) {
            int p1, p2;
			convert_position_to_indices(player_position[0], p1, p2);
            row_res += (p1 == i && p2 == j)? "X  " : "   ";
			int p;
            convert_indices_to_position(i, j, p);
            row_res += (p < 10? "  " + to_string(p) : p < 100? " " + to_string(p) : to_string(p));
            row_res += "|";
		}
        row_res += "\n|";
		for (int j = 0; j < M; j++) {
            string symbol = "  ";
            int p;
			convert_indices_to_position(i, j, p);
            if (grid[i][j] == ladder_symbol)
				for (int k = 0; k < n_components; k++)
                    if (p == ladders[k][0] || p == ladders[k][1]) {
                        symbol = ladder_symbol+to_string(k+1);
                        break;
					}
            if (grid[i][j] == snake_symbol)
				for (int k = 0; k < n_components; k++)
                    if (p == snakes[k][0] || p == snakes[k][1]) {
                        symbol = snake_symbol+to_string(k+1);
                        break;
					}
            row_res += symbol + " ";
            int p1, p2;
			convert_position_to_indices(player_position[1], p1, p2);
            row_res += (p1 == i && p2 == j? "  O" : "   ");
            row_res += "|";
		}
		cout << row_res << '\n';
		for (int j = 0; j < M; cout << "-------", j++);
		cout << "-\n";
	}
    cout << "Player X in " << player_position[0] << '\n';
    cout << "Player O in " << player_position[1] << '\n';
	for (int i = 0; i < M; cout << "-------", i++);
	cout << "-\n";
}
//This function checks if the given player reach the end of the game or not 
bool check_win(int player) {
    return player_position[player] >= N * M;
}
//This function generate a random dice face
int generate_dice_face() {
	return rand() % 6 + 1;
}
//This function prints the given dice face
string print_dice_face(int i) {
    string s = "";
    if (i == 1) {
        s += " _____ \n";
        s += "|     |\n";
        s += "|  *  |\n";
        s += "|_____|\n";
	}
    if (i == 2) {
        s += " _____ \n";
        s += "|    *|\n";
        s += "|     |\n";
        s += "|*____|\n";
	}
    if (i == 3) {
        s += " _____ \n";
        s += "|    *|\n";
        s += "|  *  |\n";
        s += "|*____|\n";
	}
    if (i == 4) {
        s += " _____ \n";
        s += "|*   *|\n";
        s += "|     |\n";
        s += "|*___*|\n";
	}
    if (i == 5) {
        s += " _____ \n";
        s += "|*   *|\n";
        s += "|  *  |\n";
        s += "|*___*|\n";
	}
    if (i == 6) {
        s += " _____ \n";
        s += "|*   *|\n";
        s += "|*   *|\n";
        s += "|*___*|\n";
	}
    return s;
}
//This function checks if given face is valid or not 
bool check_valid_face(char i) {
	string s = "abcdef";
	return s.find(tolower(i)) != -1;
}
//This function moves the given player by the given value
void move_player(int player, int moves) {
    player_position[player] += moves;
    player_position[player] = min(N * M, player_position[player]);
}
//This function generates snakes and ladders in the grid
void generate_snakes_and_ladders(char symbol) {
    int n_mid = N/2, m_mid = M/2;
    int areas_beg[n_components][4] = {{1, 1, n_mid-1, m_mid-1},             {1, m_mid, n_mid-1, M-2}, 
									  {n_mid, 1, N-2, m_mid-1},             {n_mid, m_mid, N-2, M-2}, 
									  {n_mid-2, m_mid-2, n_mid-2, m_mid+1}, {0, m_mid-2, 0, m_mid+1}};
    int areas_end[n_components][4] = {{1, 1, n_mid-1, m_mid-1},             {1, m_mid, n_mid-1, M-2}, 
									  {n_mid, 1, N-2, m_mid-1},             {n_mid, m_mid, N-2, M-2}, 
									  {N-1, m_mid-2, N-1, m_mid+1},         {n_mid+1, m_mid-2, n_mid+1, m_mid+1}};
    for (int i = 0; i < n_components; i++) {
        int xb1 = areas_beg[i][0], yb1 = areas_beg[i][1];
		int	xe1 = areas_beg[i][2], ye1 = areas_beg[i][3];
        int xb2 = areas_end[i][0], yb2 = areas_end[i][1];
		int xe2 = areas_end[i][2], ye2 = areas_end[i][3];
        int x1 = rand() % (xe1 - xb1 + 1) + xb1;
        int y1 = rand() % (ye1 - yb1 + 1) + yb1;
        int x2 = rand() % (xe2 - xb2 + 1) + xb2;
        int y2 = rand() % (ye2 - yb2 + 1) + yb2;
        while (x1 == x2 || y1 == y2 || abs(x1 - x2) + abs(y1 - y2) <= int(min(sqrt(N), sqrt(M))) ||
               grid[x1][y1] != '.' || grid[x2][y2] != '.') {
			x1 = rand() % (xe1 - xb1 + 1) + xb1;
			y1 = rand() % (ye1 - yb1 + 1) + yb1;
			x2 = rand() % (xe2 - xb2 + 1) + xb2;
			y2 = rand() % (ye2 - yb2 + 1) + yb2;
		}
        grid[x1][y1] = symbol;
        grid[x2][y2] = symbol;
        int p1, p2;
		convert_indices_to_position(x1, y1, p1);
        convert_indices_to_position(x2, y2, p2);
        if (symbol == ladder_symbol) {
			ladders[i][0] = min(p1, p2); 
			ladders[i][1] = max(p1, p2);
		}
        if (symbol == snake_symbol) {
			snakes[i][0] = min(p1, p2);
			snakes[i][1] = max(p1, p2);
		}
	}
}
//This function gets the plus value of the given position
int get_ladder_plus_value(int p) {
    for (int i = 0; i < n_components; i++)
        if (p == ladders[i][0])
            return ladders[i][1] - ladders[i][0];
    return 0;
}    
//This function gets the minus value of the given position
int get_snake_minus_value(int p) {
    for (int i = 0; i < n_components; i++)
        if (p == snakes[i][1])
            return snakes[i][0] - snakes[i][1];
    return 0;
}
//This function clears the grid
void grid_clear() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			grid[i][j] = '.';
	for (int i = 0; i < n_players; i++)
		player_position[i] = 0;
    for (int i = 0; i < n_components; i++) {
		for (int j = 0; j < n_players; j++) {
			snakes[i][j] = 0;
			ladders[i][j] = 0;
		}
	}
}


//MAIN FUNCTION
void play_game() {
    cout << "Snakes and Ladders Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    bool player = 0;
    while (true) {
        //Prints the grid
        print_grid();
        //Set mark value based on the player
        char mark = (player == 0? 'X' : 'O');
        //Read an input from the player
        cout << "Player " << mark << '\n';
        char i;
        cout << "Choose the dice face [A B C D E F]: ";
        cin >> i;
        while (!check_valid_face(i)) {
            cout << "Choose a valid dice face [A B C D E F]: ";
            cin >> i;
        }
        //Generate a dice face
        int dice_face = generate_dice_face();
        cout << print_dice_face(dice_face) << '\n';
        //Move the player position
        move_player(player, dice_face);
        //Get the plus value if there is a ladder
        int plus_value = get_ladder_plus_value(player_position[player]);
        if (plus_value > 0) {
            //Prints the grid
            print_grid();
            cout << "Player " << mark << " face a ladder, there is a movement from " << 
				    player_position[player] << " to " << player_position[player]+plus_value << '\n';
			//Move the player position
            move_player(player, plus_value);
		}
        //Get the minus value if there is a snake
        int minus_value = get_snake_minus_value(player_position[player]);
        if (minus_value < 0) {
            //Prints the grid
            print_grid();
            cout << "Player " << mark << " face a snake, there is a movement from " << 
				    player_position[player] << " to " << player_position[player]+minus_value << '\n';
            //Move the player position
            move_player(player, minus_value);
		}
        //Check if the state of the grid has a win state
        if (check_win(player)) {
            //Prints the grid
            print_grid();
            cout << "Congrats, Player " << mark << " is won!\n";
            break;
		}
        //Player number changes after each turn
        player = 1 - player;
    }
}
int main() {
	while (true) {
		grid_clear();
		generate_snakes_and_ladders(ladder_symbol);
		generate_snakes_and_ladders(snake_symbol);
		play_game();
    	char c;
    	cout << "Play Again [Y/N] ";
    	cin >> c;
    	if (c != 'y' && c != 'Y')
    		break;
	}
}
