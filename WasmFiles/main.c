#include <stdio.h>
#include "game.h"
#include <emscripten.h>

Piece board[BOARD_SIZE][BOARD_SIZE];

EMSCRIPTEN_KEEPALIVE
void initBoard(Piece board[BOARD_SIZE][BOARD_SIZE]){
    board[0][0] = (Piece){'R', {0, 0}, BLACK, 0};
    board[0][1] = (Piece){'N', {0, 1}, BLACK, 0};
    board[0][2] = (Piece){'B', {0, 2}, BLACK, 0};
    board[0][3] = (Piece){'Q', {0, 3}, BLACK, 0};
    board[0][4] = (Piece){'K', {0, 4}, BLACK, 0};
    board[0][5] = (Piece){'B', {0, 5}, BLACK, 0};
    board[0][6] = (Piece){'N', {0, 6}, BLACK, 0};
    board[0][7] = (Piece){'R', {0, 7}, BLACK, 0};
    for(int i = 0; i < BOARD_SIZE; i++){
        board[1][i] = (Piece){'P', {1, i}, BLACK, 0};
        board[6][i] = (Piece){'P', {6, i}, WHITE, 0};
    }
    board[7][0] = (Piece){'R', {7, 0}, WHITE, 0};
    board[7][1] = (Piece){'N', {7, 1}, WHITE, 0};
    board[7][2] = (Piece){'B', {7, 2}, WHITE, 0};
    board[7][3] = (Piece){'Q', {7, 3}, WHITE, 0};
    board[7][4] = (Piece){'K', {7, 4}, WHITE, 0};
    board[7][5] = (Piece){'B', {7, 5}, WHITE, 0};
    board[7][6] = (Piece){'N', {7, 6}, WHITE, 0};
    board[7][7] = (Piece){'R', {7, 7}, WHITE, 0};

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = (Piece) {' ', {i, j}, NONE, 0};
        }
    }
}

EMSCRIPTEN_KEEPALIVE
void printBoard(Piece board[BOARD_SIZE][BOARD_SIZE]){
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            if(board[row][col].piece == '\0'){
                printf("[ ]");
            }else{
                printf("[%c]", board[row][col].piece);
            }
        }
        printf("\n");
    }
}

int testing(){

    // Position p1;
    // p1.x = 2;
    // p1.y = 2;
    // Position p2;
    // p2.x = 4;
    // p2.y = 4;
    // Position kingPos;
    // kingPos.x = 3;
    // kingPos.y = 2;
    // Position kingPos2;
    // kingPos2.x = 3;
    // kingPos2.y = 6;
    // printf("%d\n", rook(p4, board[4][0]));
    // printf("%d\n", rook(p4, board[0][4]));
    // printf("%d\n", rook(p4, board[4][4]));
    
    // printf("%d\n", bishop(p1, board[4][4]));
    // printf("%d\n", bishop(p1, board[2][4]));
    
    // printf("%d\n", knight(p1, board[3][4]));
    // printf("%d\n", knight(p1, board[4][3]));
    // printf("%d\n", knight(p1, board[4][4]));

    // printf("%d\n", queen(p1, board[4][4]));
    // printf("%d\n", queen(p1, board[4][2]));
    // printf("%d\n", queen(p1, board[2][4]));
    // printf("%d\n", queen(p1, board[4][3]));
    
    // printf("%d\n", king(p1, board[3][3]));
    // printf("%d\n", king(p1, board[2][3]));
    // printf("%d\n", king(p1, board[3][2]));
    // printf("%d\n", board[7][7].color);
    // printf("%d\n", king(kingPos2, board[3][4]));
    // printf("%d\n", king(kingPos, board[3][4]));
    
    // printf("%d\n", pawn(p3, board[1][4]));
    // printf("%d\n", pawn(p3, board[2][4]));

    // printf("%d\n", isValidMove(board, p3, board[1][4].position));
    // printf("%d\n", isValidMove(board, (Position){0, 0}, board[4][0].position));
    // printf("%d\n", isValidMove(board, (Position){0, 2}, board[3][5].position));
    // printf("%d\n", isValidMove(board, (Position){0, 1}, board[2][2].position));
    // printf("%d\n", isValidMove(board, (Position){0, 3}, board[7][3].position));
    // printf("%d\n", isValidMove(board, (Position){0, 3}, board[3][6].position));
    // printf("%d\n", isValidMove(board, (Position){0, 4}, board[1][4].position));
    // printf("%d\n", isValidMove(board, (Position){0, 4}, board[1][5].position));
    // printf("%d\n", isValidMove(board, (Position){0, 4}, board[1][3].position));
    // printf("%d\n", isValidMove(board, p4, board[0][4].position));

    printf("%d\n", movePiece((Position){6, 0}, (Position){4, 0}));
    printf("%d\n", movePiece((Position){1, 1}, (Position){3, 1}));
    printf("%d\n", movePiece((Position){4, 0}, (Position){3, 1}));
    // printf("%d\n", movePiece((Position){4, 0}, (Position){3, 1}));
    // printf("%d\n", movePiece((Position){3, 1}, (Position){4, 1}));
    // printf("%d\n", board[3][1].color);
    // printf("%d\n", board[4][0].color);
    printBoard(board);

    // printf("%d\n", isPathClear(p1, p2));
    return 0;
}

int main(){
    initBoard(board);
    // printBoard(board);
    // testing();
    return 0;
}