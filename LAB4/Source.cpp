#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 8;
enum PieceType { Rook, Pawn, Bishop, Queen, King, Knight };

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) cout << cell << " ";
        cout << endl;
    }
}

vector<vector<int>> getRookMoves(int row, int col) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (i != row) board[i][col] = 1;
        if (i != col) board[row][i] = 1;
    }
    return board;
}

vector<vector<int>> getPawnMoves(int row, int col, bool isWhite = true) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    int direction = isWhite ? -1 : 1;
    if (row + direction >= 0 && row + direction < BOARD_SIZE) {
        if (col - 1 >= 0) board[row + direction][col - 1] = 1;
        if (col + 1 < BOARD_SIZE) board[row + direction][col + 1] = 1;
        if (board[row][col] == 0) board[row + direction][col] = 1;
    }
    return board;
}

vector<vector<int>> getBishopMoves(int row, int col) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    for (int i = 1; i < BOARD_SIZE; ++i) {
        if (row + i < BOARD_SIZE && col + i < BOARD_SIZE) board[row + i][col + i] = 1;
        if (row + i < BOARD_SIZE && col - i >= 0) board[row + i][col - i] = 1;
        if (row - i >= 0 && col + i < BOARD_SIZE) board[row - i][col + i] = 1;
        if (row - i >= 0 && col - i >= 0) board[row - i][col - i] = 1;
    }
    return board;
}

vector<vector<int>> getQueenMoves(int row, int col) {
    vector<vector<int>> board = getRookMoves(row, col);
    vector<vector<int>> bishopMoves = getBishopMoves(row, col);
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (bishopMoves[i][j] == 1) board[i][j] = 1;
    return board;
}

vector<vector<int>> getKingMoves(int row, int col) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if ((i || j) && row + i >= 0 && row + i < BOARD_SIZE && col + j >= 0 && col + j < BOARD_SIZE)
                board[row + i][col + j] = 1;
    return board;
}

vector<vector<int>> getKnightMoves(int row, int col) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    vector<pair<int, int>> moves = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };
    for (auto move : moves) {
        int newRow = row + move.first, newCol = col + move.second;
        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
            board[newRow][newCol] = 1;
    }
    return board;
}

void displayMoves(PieceType piece, int row, int col, bool isWhite = true) {
    vector<vector<int>> moves;
    switch (piece) {
    case Rook: moves = getRookMoves(row, col); break;
    case Pawn: moves = getPawnMoves(row, col, isWhite); break;
    case Bishop: moves = getBishopMoves(row, col); break;
    case Queen: moves = getQueenMoves(row, col); break;
    case King: moves = getKingMoves(row, col); break;
    case Knight: moves = getKnightMoves(row, col); break;
    default: cout << "Неизвестный тип фигуры." << endl; return;
    }
    printBoard(moves);
}

int main() {
    setlocale(LC_ALL, "ru");
    int row = 3, col = 3;
    PieceType piece = Queen; 
    displayMoves(piece, row, col);
    return 0;
}
