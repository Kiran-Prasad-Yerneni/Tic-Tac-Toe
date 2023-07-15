#ifndef TICTACTOE_H
#define TICTACTOE_H

enum class gamestate
{
    COMPLETED,
    TIE,
    ONGOING
};

class tictactoe
{
public:
    char board[3][3];
    tictactoe();
    void clearBoard();
    gamestate gameStatus();
};

#endif // TICTACTOE_H
