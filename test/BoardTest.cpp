#include "BoardTest.h"
#include "Board.h"

void BoardTest::runAllTests()
{
    testGameWinX();
    testGameWinO();
    testGameDraw();
    testGameInterrupted();
    testGameInProgress();

    getTurnNumberAfterOperations1();
    getTurnNumberAfterOperations2();
    getTurnNumberFirstTurn();

    movingNegativeCoordinates();
    movingBigCoordinates();
    movingOnNonEmptyField();
    movingGoodMove();

    gettingEmpty();
    gettingSignX();
    gettingSignO();

    gameWinHorizontal();
    gameWinMainDiagonal();
    gameWinSideDiagonal();
    gameWinVertical();

    widthCorrect1();
    widthCorrect2();
    widthCorrect3();

    heightCorrect1();
    heightCorrect2();
    heightCorrect3();

    winLastTurn();

    showFinalResult();
}

void BoardTest::testGameWinO()
{
    Board board(5, 5);
    board.makeMove(0, 0, 'O');
    board.makeMove(0, 1, 'O');
    board.makeMove(0, 2, 'O');
    board.makeMove(0, 3, 'O');
    board.makeMove(0, 4, 'O');
    DO_CHECK(board.gameState() == O_WIN);
}

void BoardTest::testGameWinX()
{
    Board board(5,5);
    for (size_t i = 0; i < 5; i++)
        board.makeMove(i, i, 'X');
    DO_CHECK(board.gameState() == X_WIN);
}

void BoardTest::testGameDraw()
{
    size_t n = 3;
    Board board(n, n);

    int turn = 0;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            board.makeMove(i, j, (turn++) % 2 ? 'O' : 'X');

    DO_CHECK(board.gameState() == DRAW);
}

void BoardTest::testGameInterrupted()
{
    Board board(10, 10);
    board.makeMove(-1, -1, 'X');
    DO_CHECK(board.gameState() == INTERRUPTED);
}

void BoardTest::testGameInProgress()
{
    Board board(4, 5);
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            board.makeMove(i, j, 'X');
    DO_CHECK(board.gameState() == IN_PROGRESS);
}

void BoardTest::getTurnNumberAfterOperations1()
{
    Board board(10, 10);
    for (size_t i = 0; i < 4; i++)
    {
        board.makeMove(i, i, 'X');
    }

    DO_CHECK(board.getTurnNumber() == 5);
}

void BoardTest::getTurnNumberAfterOperations2()
{
    Board board(10, 10);
    for (size_t i = 2; i < 8; i += 2)
    {
        board.makeMove(i, i, 'X');
    }

    DO_CHECK(board.getTurnNumber() == 4);
}

void BoardTest::getTurnNumberFirstTurn()
{
    Board board(10, 10);
    DO_CHECK(board.getTurnNumber() == 1);
}

void BoardTest::movingNegativeCoordinates()
{
    Board board(10, 10);
    DO_CHECK(!board.canMove(-1, -1));
}

void BoardTest::movingBigCoordinates()
{
    Board board(10, 10);
    DO_CHECK(!board.canMove(10, 10));
}

void BoardTest::movingOnNonEmptyField()
{
    Board board(10, 10);
    board.makeMove(0, 0, 'X');
    DO_CHECK(!board.canMove(0, 0));
}

void BoardTest::movingGoodMove()
{
    Board board(10, 10);
    DO_CHECK(board.canMove(0, 0));
}

void BoardTest::gettingEmpty()
{
    Board board(10, 10);
    DO_CHECK(board.get(0, 0) == EMPTY);
}

void BoardTest::gettingSignX()
{
    Board board(10, 10);
    board.makeMove(0, 0, 'X');
    DO_CHECK(board.get(0, 0) == X_SIGN);
}

void BoardTest::gettingSignO()
{
    Board board(10, 10);
    board.makeMove(5, 5, 'O');
    DO_CHECK(board.get(5, 5) == O_SIGN);
}

void BoardTest::widthCorrect1()
{
    Board board(7, 3);
    DO_CHECK(board.getWidth() == 3);
}

void BoardTest::widthCorrect2()
{
    Board board(5, 18);
    DO_CHECK(board.getWidth() == 18);
}

void BoardTest::widthCorrect3()
{
    Board board(32, 14);
    DO_CHECK(board.getWidth() == 14);
}

void BoardTest::heightCorrect1()
{
    Board board(7, 3);
    DO_CHECK(board.getHeight() == 7);
}

void BoardTest::heightCorrect2()
{
    Board board(5, 18);
    DO_CHECK(board.getHeight() == 5);
}

void BoardTest::heightCorrect3()
{
    Board board(32, 14);
    DO_CHECK(board.getHeight() == 32);
}

void BoardTest::gameWinHorizontal()
{
    Board board(7, 7);

    for (size_t i = 1; i < 6; i++)
    {
        board.makeMove(2, i, 'X');
    }

    DO_CHECK(board.gameState() == X_WIN);
}

void BoardTest::gameWinMainDiagonal()
{
    Board board(7, 7);

    for (size_t i = 1; i < 6; i++)
    {
        board.makeMove(i, i, 'X');
    }

    DO_CHECK(board.gameState() == X_WIN);
}

void BoardTest::gameWinSideDiagonal()
{
    Board board(7, 7);

    for (size_t i = 0; i < 5; i++)
    {
        board.makeMove(5 - i, i, 'X');
    }

    DO_CHECK(board.gameState() == X_WIN);
}

void BoardTest::gameWinVertical()
{
    Board board(7, 7);

    for (size_t i = 1; i < 6; i++)
    {
        board.makeMove(i, 2, 'X');
    }

    DO_CHECK(board.gameState() == X_WIN);
}

void BoardTest::winLastTurn()
{
    Board board(5, 5);

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            board.makeMove(i, j, 'X');
        }
    }

    for (size_t i = 0; i < 4; i++)
    {
        board.makeMove(i, 4, 'O');
        board.makeMove(4, i, 'O');
    }

    board.makeMove(4, 4, 'X');

    DO_CHECK(board.gameState() == X_WIN);

    /*
        XXXXY
        XXXXY
        XXXXY
        XXXXY
        YYYYX
    */
}











