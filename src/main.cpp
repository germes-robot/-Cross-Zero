#include <cstring>
#include "Board.h"
#include "StdioBoardView.h"
#include <NCursesBoardView.h>

static bool isContain(size_t argc, char ** argv, const char *needle)
{
    for (size_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], needle) == 0)
            return true;
    }
    return false;
}

void runNCursesMode()
{
    Board board(10, 10);
    NCursesBoardView boardView(board);

    while (board.gameState() == IN_PROGRESS)
    {
        boardView.doGameCycle();
    }

    if (board.gameState() == INTERRUPTED)
    {
        endwin();
    }
    else
    {
        boardView.printGameResult();
        getch();
        boardView.showEndAnimation();
        endwin();
    }
}

void runStdioMode(bool silence)
{
    Board board(10, 10);

    StdioBoardView boardView(board, silence);

    while (board.gameState() == IN_PROGRESS)
    {
        boardView.doGameCycle();
    }

    if (board.gameState() != INTERRUPTED)
        boardView.printGameResult();
}

int main(int argc, char ** argv)
{


    if (isContain(argc, argv, "curses"))
    {
        runNCursesMode();
    }
    else
    {
        runStdioMode(isContain(argc, argv, "silent"));
    }


    return 0;
}