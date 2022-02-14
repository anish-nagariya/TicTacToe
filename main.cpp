#include <iostream>

struct move{
    int r, c, score;
};

struct TicTacToe{
    char player, computer, grid[3][3];
    // constructor for struct TicTacToe
    TicTacToe(){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                grid[i][j] = ' ';
            }
        }
    }
    

    // checks if someone has won the game
    bool win(){
        // stores all winning states
        int win_states[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
        // iterating through every winning state
        for (int i = 0; i < 8; i++){
            bool win = true;
            // calculating row and columbn for board
            int first_r = win_states[i][0]/3;
            int first_c = win_states[i][0] % 3;

            // checks if the state is currently winning for anyone
            for (int j = 0; j < 3; j++){
                int r = win_states[i][j] / 3;
                int c = win_states[i][j] % 3;
                if (grid[first_r][first_c] == ' ' || grid[first_r][first_c] != grid[r][c]){
                    win = false;
                }
            }
            if (win){
                return true;
            }
        }
        return false;
    }

    // checks tie
    bool tie(){
        if (win()){
            return false;
        }
        // if all cells are covered and there is no win then it returns a tie
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (grid[i][j] == ' '){
                    return false;
                }
            }
        }
        return true;
    }

    // takes cell for human to mark
    void player_move(){
        while (true){
            std::cout << "Enter cell number (1 - 9): ";
            int cell;
            std::cin >> cell;
            int r = (cell - 1)/3, c = (cell - 1) % 3;
            if (cell >= 1 && cell <= 9 & grid[r][c] == ' '){
                grid[r][c] = player;
                break;
            }else{
                // if player sends invalid cell, it tries again
                std::cout << "Invalid cell, try again";
            }
        }
    }

    // the computer makes a move
    void computer_move(){
        move best_move = minimax();
        grid[best_move.r][best_move.c] = computer;
    }

    // minimax algorithm
    // checks if we are trying to maximize or minimize
    move minimax(bool maximizing = true){
        move best_move;
        // decides score if there is a win in the current state
        if (win()){
            if (maximizing){
                best_move.score = -1;
            }else{
                best_move.score = 1;
            }
            return best_move;
        }else if (tie()){
            best_move.score = 0;
            return best_move;
        }
        best_move.score = maximizing ? -2 : 2;
        /* checks all future states for every possible move
        maximize means its playing as computer, minimize as player
        It will decide the best move by playing optimally as the compuer and human
        */
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (grid[i][j] == ' '){
                    grid[i][j] = maximizing ? computer: player;
                    move board_state = minimax(!maximizing);
                    if (maximizing){
                        if (board_state.score > best_move.score){
                            best_move.score = board_state.score;
                            best_move.r = i;
                            best_move.c = j;
                        }
                    }else{
                        if (board_state.score < best_move.score){
                            best_move.score = board_state.score;
                            best_move.r = i;
                            best_move.c = j;
                        }
                    }
                    grid[i][j] = ' ';
                }
            }
        }
        return best_move;
    }

    // takes in human symbol
    void play(){
        // asking human for symbol input
        while (true){
            std::cout << "Enter Symbol (X or O): ";
            std::cin >> player;
            if (player == 'X' || player == 'O'){
                break;
            }else{
                std::cout << "Invalid symbol entered, try again\n";
            }
        }
        computer = player == 'X' ? 'O' : 'X';
        if (player == 'O'){
            computer_move();
        }
        print();
        while (true){
            // taking player move
            player_move();
            print();
            // checking if there is a result
            if (win()){
                std::cout << "Player Wins!\n";
                return;
            }else if (tie()){
                std::cout << "Tie!\n";
                return;
            }
            std::cout << "Computer is thinking...\n";
            computer_move();
            print();
            if (win()){
                std::cout << "Computer Wins!\n";
                return;
            }else if (tie()){
                std::cout << "Tie!\n";
                return;
            }
        }
    }

    // prints board
    void print(){
        for (int i = 0; i < 3; i++){
            if (i){
                std::cout << "-----------\n";
            }
            for (int j = 0; j < 3; j++){
                std::cout << "|";
                if (grid[i][j] == ' '){
                    std::cout << 3*i + j + 1;
                }else{
                    std::cout << grid[i][j];
                }
                std::cout << ' ';
            }
            std::cout << '\n';
        }
    }
};

int main(){
    TicTacToe game;
    game.play();
}
