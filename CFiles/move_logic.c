#include <stdio.h>
#include <stdlib.h>
#include "game.h"
// #include <emscripten/emscripten.h>

int isPathClear(Position from, Position to);
int rook(Position to, Piece piece);
int knight(Position to, Piece piece);
int bishop(Position to, Piece piece);
int queen(Position to, Piece piece);
int king(Position to, Piece piece);
int pawn(Position to, Piece piece);
int isValidMove(Piece board[BOARD_SIZE][BOARD_SIZE], Position start, Position end);
int moveKing(Position from, Position to);
int moveRook(Position from, Position to);
int movePawn(Position from, Position to);


Position enPassasntSquare;
int enPassasnt = 0;
int castling = 15;
int whiteTurn = 1;

int movePiece(Position from, Position to){
    Piece piece = board[from.x][from.y];
    // printf("%c\n", piece.piece);
    if((piece.color == BLACK) & whiteTurn){
        return 0;
    }else if((piece.color == WHITE) & !whiteTurn){
        return 0;
    }
    if(isValidMove(board, from, to)){
        if(board[from.x][from.y].piece == 'K'){
            moveKing(from, to);
        }else if(board[from.x][from.y].piece == 'R'){
            moveRook(from, to);
        }else if(board[from.x][from.y].piece == 'P'){
            movePawn(from, to);
        }
        board[to.x][to.y].color = board[from.x][from.y].color;
        board[to.x][to.y].piece = board[from.x][from.y].piece;
        board[from.x][from.y].color = NONE;
        board[from.x][from.y].piece = ' ';
        board[from.x][from.y].hasMoved = 0;

        whiteTurn = !whiteTurn;
    }
    return 1;
}

int moveKing(Position from, Position to){
    Piece piece = board[from.x][to.x];
    int side;
    if(piece.color == WHITE && abs(piece.position.y - to.y) == 2){
        if(to.y == 2 && (castling & 8) > 0){
            side = 0;
        }else if(to.y == 6 && (castling & 4) > 0){
            side = 7;
        }else{
            return 0;
        }
        to.y = side;
        if(isPathClear(piece.position, to)){
            board[from.x][side].piece = ' ';
            board[from.x][side].color = NONE;

            board[from.x][side == 0 ? 3 : 5].color = WHITE;
            board[from.x][side == 0 ? 3 : 5].piece = 'K';
            castling &= 3;
            return 1;
        }
    }else if(piece.color == BLACK && abs(piece.position.y - to.y) == 2){
        if(to.y == 2 && (castling & 2) > 0){
            side = 0;
        }else if(to.y == 6 && (castling & 1) > 0){
            side = 7;
        }else{
            return 0;
        }
        to.y = side;
        if(isPathClear(piece.position, to)){
            board[from.x][side].piece = ' ';
            board[from.x][side].color = NONE;

            board[from.x][side == 0 ? 3 : 5].color = BLACK;
            board[from.x][side == 0 ? 3 : 5].piece = 'K';
            castling &= 12;
            return 1;
        }
    }
    int move1 = (piece.position.x == to.x || piece.position.y == to.y);
    int move2 = (abs(piece.position.x - to.x) == abs(piece.position.y - to.y));
    int oneSquare = ((abs(piece.position.x - to.x) == 1) || abs(piece.position.x - to.x) == 0) && ((abs(piece.position.y - to.y) == 1) || abs(piece.position.y - to.y) == 0);
    return ((move1 || move2) && oneSquare); 
}

int moveRook(Position from, Position to){
    Piece piece = board[from.x][from.y];
    int move = (piece.position.x == to.x || piece.position.y == to.y);
    if(move & isPathClear(from, to)){
        if(piece.color == WHITE & from.y == 0){
            castling &= 7;
        }else if(piece.color == WHITE & from.y == 7){
            castling &= 11;
        }else if(piece.color == BLACK & from.y == 0){
            castling &= 13;
        }else if(piece.color == BLACK & from.y == 7){
            castling &= 14;
        }
        return 1;
    }

}

int movePawn(Position from, Position to){
    Piece piece = board[from.x][from.y];
    if(piece.color == WHITE){ // White can't move backwards
        if(piece.position.x - to.x < 0){
            return 0;
        }
    }else if(piece.color == BLACK){ // Black can't move backwards
        if(to.x - piece.position.x < 0){
            return 0;
        }
    }
    int push = (abs(to.x - piece.position.x) == 1 && piece.position.y == to.y && board[to.x][to.y].piece == ' ');
    int capture = (abs(to.x - piece.position.x) == 1 && abs(to.y - piece.position.y) == 1 && board[to.x][to.y].piece != ' ');
    int twoPush = (abs(to.x - piece.position.x) == 2 && ((piece.position.x == 6) || (piece.position.x == 1)) && piece.position.y == to.y && board[to.x][to.y].piece == ' ');
    if(enPassasnt && (to.x == enPassasntSquare.x) && (to.y == enPassasntSquare.y) && abs(to.x - piece.position.x) == 1 && abs(to.y - piece.position.y) == 1){
        if(piece.color == WHITE){
            board[to.x + 1][to.y].color = NONE;
            board[to.x + 1][to.y].piece = ' ';
        }else{
            board[to.x - 1][to.y].color = NONE;
            board[to.x - 1][to.y].piece = ' ';
        }
        return 1;
    }
    if(twoPush){
        if(piece.position.x == 6){
            if(board[5][to.y].piece != ' '){
                twoPush = !twoPush;
            }
        }else if(piece.position.x == 1){
            if(board[2][to.y].piece != ' '){
                twoPush = !twoPush;
            }
        }
        enPassasnt = 1;
        enPassasntSquare = (Position){(from.x + to.x) / 2, from.y};
    }else{
        enPassasnt = 0;
        enPassasntSquare = (Position){-1, -1};
    }
    return push || capture || twoPush;
}

// EMSCRIPTEN_KEEPALIVE
int isPathClear(Position from, Position to){
    int x = to.x - from.x;
    int y = to.y - from.y;
    if(x == 0){
        int increment = y > 0 ? 1 : -1;
        for(int i = from.y + increment; i != to.y; i += increment){
            if(board[from.x][i].piece != ' '){
                return 0;
            }
        }
    }else if(y == 0){
        int increment = x > 0 ? 1 : -1;
        for(int i = from.x + increment; i != to.x; i += increment){
            if(board[i][from.y].piece != ' '){
                return 0;
            }
        }
    }else if(abs(x) == abs(y)){
        int incrementY = y > 0 ? 1: -1;
        int incrementX = x > 0 ? 1: -1;
        for(int i = from.x + incrementX, j = from.y + incrementY; i != to.x; i += incrementX, j += incrementY){
            if(board[i][j].piece != ' '){
                return 0;
            }
        }
    }else{
        return 0;
    }
    return 1;
}

// EMSCRIPTEN_KEEPALIVE
int rook(Position to, Piece piece){
    int move = (piece.position.x == to.x || piece.position.y == to.y);
    return move && isPathClear(piece.position, to);
}

// EMSCRIPTEN_KEEPALIVE
int knight(Position to, Piece piece){
    int move1 = (abs(piece.position.x - to.x) == 2) && (abs(piece.position.y - to.y) == 1);
    int move2 = (abs(piece.position.x - to.x) == 1) && (abs(piece.position.y - to.y) == 2);
    return move1 || move2;
}

// EMSCRIPTEN_KEEPALIVE
int bishop(Position to, Piece piece){
    int move = abs(piece.position.x - to.x) == abs(piece.position.y - to.y);
    return move && isPathClear(piece.position, to);
}

// EMSCRIPTEN_KEEPALIVE
int queen(Position to, Piece piece){
    int move1 = (piece.position.x == to.x || piece.position.y == to.y);
    int move2 = (abs(piece.position.x - to.x) == abs(piece.position.y - to.y));
    return (move1 || move2) && isPathClear(piece.position, to);
}

// EMSCRIPTEN_KEEPALIVE
int king(Position to, Piece piece){
    int side;
    if(piece.color == WHITE && abs(piece.position.y - to.y) == 2){
        if(to.y == 2 && (castling & 8) > 0){
            side = 0;
        }else if(to.y == 6 && (castling & 4) > 0){
            side = 7;
        }else{
            return 0;
        }
        to.y = side;
        return isPathClear(piece.position, to);
    }else if(piece.color == BLACK && abs(piece.position.y - to.y) == 2){
        if(to.y == 2 && (castling & 2) > 0){
            side = 0;
        }else if(to.y == 6 && (castling & 1) > 0){
            side = 7;
        }else{
            return 0;
        }
        to.y = side;
        return isPathClear(piece.position, to);
    }
    int move1 = (piece.position.x == to.x || piece.position.y == to.y);
    int move2 = (abs(piece.position.x - to.x) == abs(piece.position.y - to.y));
    int oneSquare = ((abs(piece.position.x - to.x) == 1) || abs(piece.position.x - to.x) == 0) && ((abs(piece.position.y - to.y) == 1) || abs(piece.position.y - to.y) == 0);
    return ((move1 || move2) && oneSquare);
}

// EMSCRIPTEN_KEEPALIVE
int pawn(Position to, Piece piece){
    if(piece.color == WHITE){ // White can't move backwards
        if(piece.position.x - to.x < 0){
            return 0;
        }
    }else if(piece.color == BLACK){ // Black can't move backwards
        if(to.x - piece.position.x < 0){
            return 0;
        }
    }
    int push = (abs(to.x - piece.position.x) == 1 && piece.position.y == to.y && board[to.x][to.y].piece == ' ');
    int capture = (abs(to.x - piece.position.x) == 1 && abs(to.y - piece.position.y) == 1 && board[to.x][to.y].piece != ' ');
    int twoPush = (abs(to.x - piece.position.x) == 2 && ((piece.position.x == 6) || (piece.position.x == 1)) && piece.position.y == to.y && board[to.x][to.y].piece == ' ');
    if(enPassasnt && (to.x == enPassasntSquare.x) && (to.y == enPassasntSquare.y) && abs(to.x - piece.position.x) == 1 && abs(to.y - piece.position.y) == 1){
        return 1;
    }
    if(twoPush){
        if(piece.position.x == 6){
            if(board[5][to.y].piece != ' '){
                twoPush = !twoPush;
            }
        }else if(piece.position.x == 1){
            if(board[2][to.y].piece != ' '){
                twoPush = !twoPush;
            }
        }
    }
    return push || capture || twoPush;
}

// EMSCRIPTEN_KEEPALIVE
int isValidMove(Piece board[BOARD_SIZE][BOARD_SIZE], Position start, Position end){
    Piece piece = board[start.x][start.y];
    if(start.x == end.x && start.y == end.y){ // Same square
        return 0;
    }
    if(piece.color == board[end.x][end.y].color){ // Same color
        return 0;
    }
    switch(piece.piece){
        case 'R':
            enPassasnt = 0;
            return rook(end, piece);
        case 'N':
            enPassasnt = 0;
            return knight(end, piece);
        case 'B':
            enPassasnt = 0;
            return bishop(end, piece);
        case 'Q':
            enPassasnt = 0;
            return queen(end, piece);
        case 'K':
            enPassasnt = 0;
            return king(end, piece);
        case 'P':
            return pawn(end, piece);
    }
    return 1;
}