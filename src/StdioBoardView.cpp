#include <cstdio>
#include "StdioBoardView.h"


StdioBoardView::StdioBoardView(Board &board_, bool isSilent) : board(board_), SILENCE(isSilent) {
}

void StdioBoardView::showBoard() const
{
    for (size_t i = 0; i < board.getHeight(); i++)
    {
        for (size_t j = 0; j < board.getWidth(); j++)
        {
            printf("%c", char(board.get(i, j)));
        }
        printf("\n");
    }
}

void StdioBoardView::doGameCycle()
{
    if (board.gameState() != IN_PROGRESS)
        return;

    if (!SILENCE)
        showBoard();

    char currentSign = (board.getTurnNumber() % 2)
                       ? 'O'
                       : 'X';

    size_t x, y;
    readCoordinates(x, y, currentSign);

    board.makeMove(x, y, currentSign);
}

void StdioBoardView::readCoordinates(size_t &x, size_t &y, char currentSign)
{
    printf("%c move: ", currentSign);
    fflush(stdout);
    scanf("%zu %zu", &x, &y);

    if (int(x) == -1 && int(y) == -1)
    {
        return;
    }
    if (!board.canMove(x, y))
    {
        printf("Bad move!\n");
        readCoordinates(x, y, currentSign);
        return;
    }
    printf("\n");

}

void StdioBoardView::printGameResult()
{
    showBoard();
    if (board.gameState() == X_WIN)
        printf("X wins!");
    else if (board.gameState() == O_WIN)
        printf("O wins!");
    else
        printf("Draw.");
}



