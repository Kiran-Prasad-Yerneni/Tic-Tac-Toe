#include "tictactoe.h"

tictactoe::tictactoe()
{
    clearBoard();
}

void tictactoe::clearBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

gamestate tictactoe::gameStatus()
{
    for(int i = 0; i < 3; i++)
    {
        if((board[i][0] != ' ') && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return gamestate::COMPLETED;
        if((board[0][i] != ' ') && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return gamestate::COMPLETED;
    }

    if(board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return gamestate::COMPLETED;

    if(board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return gamestate::COMPLETED;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
                return gamestate::ONGOING;
        }
    }

    return gamestate::TIE;
}
