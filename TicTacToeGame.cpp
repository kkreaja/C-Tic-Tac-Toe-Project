//Kre'aja Jackson
 //ITPRG-244 Project
 // Tic Tac Toe Game

    #include <iostream>
    #include <vector>
    #include <stdexcept>
    #include <cstdlib>
    #include <ctime>
    #include <limits> // for numeric_limits
    
    using namespace std;
    
    class TicTacToe {
    private:
        char board[3][3];
        bool player1Turn;
        
    public:
        TicTacToe() {
            // Initialize the board
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    board[i][j] = '-';
                }
            }
            player1Turn = true;
        }
        
        void displayBoard() {
            // Display the current state of the board
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
        }
        
        bool isValidMove(int row, int col) {
            // Check if the selected cell is within the board and not already marked
            return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '-');
        }
        
        bool checkWin(char mark) {
            // Check for winning combinations
            for (int i = 0; i < 3; ++i) {
                if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark)
                    return true;
                if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)
                    return true;
            }
            if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark)
                return true;
            if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)
                return true;
            return false;
        }
        
        bool isBoardFull() {
            // Check if the board is full
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == '-')
                        return false;
                }
            }
            return true;
        }
        
        void resetGame() {
            // Reset the game board and player turn
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    board[i][j] = '-';
                }
            }
            player1Turn = true;
        }
        
        void play() {
            char playAgain;
            do {
                resetGame(); // Reset the game before starting a new one
                int row, col;
                char mark;
                while (true) {
                    cout << "Player " << (player1Turn ? "1" : "2") << "'s turn. Enter row and column (0-2): ";
                    // Input validation for integers
                    while (!(cin >> row >> col) || row < 0 || row > 2 || col < 0 || col > 2 || !isValidMove(row, col)) {
                        cout << "Invalid input! Please enter row and column within range (0-2): ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    
                    // Mark the selected cell with the player's symbol
                    mark = (player1Turn ? 'X' : 'O');
                    board[row][col] = mark;
                    
                    // Display the updated board
                    displayBoard();
                    
                    // Check for win or draw
                    if (checkWin(mark)) {
                        cout << "Player " << (player1Turn ? "1" : "2") << " wins!" << endl;
                        break; // Exit the loop if there's a winner
                    } else if (isBoardFull()) {
                        cout << "It's a draw!" << endl;
                        break; // Exit the loop if it's a draw
                    }
                    
                    // Switch player
                    player1Turn = !player1Turn;
                }
                
                // Ask if players want to play again
                cout << "Do you want to play again? (y/n): ";
                cin >> playAgain;
            } while (playAgain == 'y' || playAgain == 'Y');
        }
        
        void playAgainstAI() {
            char playAgain;
            do {
                resetGame(); // Reset the game before starting a new one
                int row, col;
                char mark;
                while (true) {
                    if (player1Turn) {
                        cout << "Player 1's turn. Enter row and column (0-2): ";
                        // Input validation for integers
                        while (!(cin >> row >> col) || row < 0 || row > 2 || col < 0 || col > 2 || !isValidMove(row, col)) {
                            cout << "Invalid input! Please enter row and column within range (0-2): ";
                            cin.clear();
                            cin.ignore(numeric_limits <streamsize>::max(), '\n');
                        }
                    } else {
                        // AI's turn (random move)
                        cout << "AI's turn..." << endl;
                        srand(time(0));
                        row = rand() % 3;
                        col = rand() % 3;
                        
                        // Check if the selected cell is available
                        while (!isValidMove(row, col)) {
                            row = rand() % 3;
                            col = rand() % 3;
                        }
                    }
                    
                    // Mark the selected cell with the player's symbol
                    mark = (player1Turn ? 'X' : 'O');
                    board[row][col] = mark;
                    
                    // Display the updated board
                    displayBoard();
                    
                    // Check for win or draw
                    if (checkWin(mark)) {
                        if (player1Turn)
                            cout << "Player 1 wins!" << endl;
                        else
                            cout << "AI wins!" << endl;
                        break; // Exit the loop if there's a winner
                    } else if (isBoardFull()) {
                        cout << "It's a draw!" << endl;
                        break; // Exit the loop if it's a draw
                    }
                    
                    // Switch player
                    player1Turn = !player1Turn;
                }
                
                // Ask if players want to play again
                cout << "Do you want to play again? (y/n): ";
                cin >> playAgain;
            } while (playAgain == 'y' || playAgain == 'Y');
        }
    };
    
    int main() {
        TicTacToe game;
        char choice;
        cout << "Welcome to Tic-Tac-Toe!" << endl;
        cout << "Choose mode:" << endl;
        cout << "1. Two-player mode" << endl;
        cout << "2. Play against AI" << endl;
        cout << "Enter your choice (1/2): ";
        cin >> choice;
        if (choice == '1')
            game.play();
        else if (choice == '2')
            game.playAgainstAI();
        else
            cout << "Invalid choice. Exiting..." << endl;
        return 0;
    }