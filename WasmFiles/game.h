#ifndef GAME_H
#define GAME_H

// Constants
#define BOARD_SIZE 8
#define BLACK 0
#define WHITE 1
#define NONE -1

// Structs
typedef struct{
    int x;
    int y;
} Position;

typedef struct{
    char piece; // Type of piece
    Position position; // x, y co-ordinate of the piece
    int color; // 1 if white 0 is black
    int hasMoved; // 1 if the piece has move, 0 if not
} Piece;

extern Piece board[BOARD_SIZE][BOARD_SIZE];

// Functions
void initBoard(Piece board[BOARD_SIZE][BOARD_SIZE]);
void displayLegalMoves(Piece board[BOARD_SIZE][BOARD_SIZE], Position position);
void printBoard(Piece board[BOARD_SIZE][BOARD_SIZE]);
int isGameOver(Piece board[BOARD_SIZE][BOARD_SIZE]);
int isCheck(Piece board[BOARD_SIZE][BOARD_SIZE], int color);
int isCheckmate(Piece board[BOARD_SIZE][BOARD_SIZE], int color);
int isStalemate(Piece board[BOARD_SIZE][BOARD_SIZE], int color);
int isThreeFoldRepetition(Piece board[BOARD_SIZE][BOARD_SIZE]);
int isValidMove(Piece board[BOARD_SIZE][BOARD_SIZE], Position start, Position end);

int movePiece(Position start, Position end);
int isPathClear(Position from, Position to);
int rook(Position to, Piece piece);
int knight(Position to, Piece piece);
int bishop(Position to, Piece piece);
int queen(Position to, Piece piece);
int king(Position to, Piece piece);
int pawn(Position to, Piece piece);

int moveKing(Position from, Position to);
int moveRook(Position from, Position to);
int movePawn(Position from, Position to);

#endif