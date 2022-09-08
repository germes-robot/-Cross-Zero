#include <unistd.h>
#include "NCursesBoardView.h"

NCursesBoardView::NCursesBoardView(Board &board_) : board(board_),
                                                    cursor(board.getHeight(),
                                                           board.getWidth(),
                                                           board)
{
    init();
    cursor.initCursorWindow();
    wmove(cursor.getWindow(), 0, 0);
}

void NCursesBoardView::showBoard() const
{
    printWhoseTurn();
    wmove(cursor.getWindow(), 0, 0);
    for (size_t i = 0; i < board.getHeight(); i++)
    {
        for (size_t j = 0; j < board.getWidth(); j++)
        {
            cursor.drawColored(i, j, false);
        }
    }
    cursor.draw();
    wrefresh(cursor.getWindow());
}



void NCursesBoardView::doGameCycle()
{
    if (board.gameState() != IN_PROGRESS)
        return;

    wmove(cursor.getWindow(), 0, 0 );

    showBoard();

    char currentSign = (board.getTurnNumber() % 2)
                       ? 'O'
                       : 'X';

    while (true)
    {
        int key = wgetch(cursor.getWindow());

        if (key == 'x')
        {
            board.makeMove(-1, -1, currentSign);
            break;
        }
        else if (key == ' ')
        {
            if (board.canMove(cursor.getX(), cursor.getY()))
            {
                board.makeMove(cursor.getX(), cursor.getY(), currentSign);
                break;
            }
        }
        else
        {
            cursor.moveCursor(key);
        }
    }
    cursor.draw();
}


void NCursesBoardView::printGameResult()
{
    showBoard();
    cursor.remove();
    move(1, board.getWidth() + 2);
    printw("      ");

    move(board.getHeight() + 2, 0);

    if (board.gameState() == X_WIN)
        printw("X wins!");
    else if (board.gameState() == O_WIN)
        printw("O wins!");
    else
        printw("Draw.");

    printw("\nPress any key to exit the game");
}

void NCursesBoardView::init()
{
    initscr();

    raw();
    noecho();
    keypad(stdscr, true);

    start_color();
    init_color(COLOR_BLUE, 0, 1000, 1000);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(BACKGROUND_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(CURSOR_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(X_COLOR, COLOR_BLUE, COLOR_BLACK);
    init_pair(O_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(EDGE_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(END_COLOR, COLOR_BLACK, COLOR_BLACK);

    attron(COLOR_PAIR(EDGE_COLOR));
    for (size_t i = 0; i < board.getWidth() + 2; i++)
    {
        mvprintw(0, i, "=");
        mvprintw(board.getHeight() + 1, i, "=");
    }

    for (size_t i = 0; i < board.getHeight() + 2; i++)
    {
        mvprintw(i, 0, "|");
        mvprintw(i, board.getWidth() + 1, "|");
    }
    attroff(COLOR_PAIR(EDGE_COLOR));
}

void NCursesBoardView::printWhoseTurn() const
{
    char symbol = board.getTurnNumber() % 2 ?
            'O':
            'X';

    int color = (symbol == 'X') ?
            X_COLOR:
            O_COLOR;

    attron(COLOR_PAIR(color));
    mvwprintw(stdscr, 1, board.getWidth() + 2, "%c TURN", symbol);
    refresh();
    attroff(COLOR_PAIR(color));


    cursor.draw();
    wrefresh(cursor.getWindow());

}

void NCursesBoardView::showEndAnimation()
{
    wattron(cursor.getWindow(), COLOR_PAIR(END_COLOR));
    attron(COLOR_PAIR(BACKGROUND_COLOR));
    wmove(cursor.getWindow(), 0, 0);

    const size_t diagonals = board.getHeight() + board.getWidth() - 1;

    for (size_t i = 0; i < diagonals / 4 + 2; i++)
    {
        const size_t diags[4] = {
                i,
                diagonals - 1 - i,
                diagonals / 2 - i,
                diagonals / 2 + i
        };

        for (unsigned long diag : diags)
        {
            for (int x = 0; int(diag) - x >= 0; x++)
            {
                int y = diag - x;
                refresh();
                mvwprintw(cursor.getWindow(), x, y, "/");
            }
        }

        sleep(1);
        wmove(cursor.getWindow(), 0, 0);
        wrefresh(cursor.getWindow());
    }
    wattroff(cursor.getWindow(), COLOR_PAIR(END_COLOR));
}

NCursesBoardView::Cursor::Cursor(size_t height_, size_t width_, Board &board_) : width(width_),
                                                                                    height(height_),
                                                                                    board(board_)
{
    currentX = currentY = 0;
}

size_t NCursesBoardView::Cursor::getX() const
{
    return currentX;
}

size_t NCursesBoardView::Cursor::getY() const
{
    return currentY;
}

void NCursesBoardView::Cursor::remove()
{
    wmove(window, getX(), getY());
    drawColored(getX(), getY());
    wmove(window, getX(), getY());
    wrefresh(window);
}

void NCursesBoardView::Cursor::draw()
{
    wmove(window, getX(), getY());
    drawColored(getX(), getY(), true);
    wmove(window, getX(), getY());
    wrefresh(window);
}

void NCursesBoardView::Cursor::moveCursor(int command)
{
    remove();
    switch (command)
    {
        case KEY_UP:
            moveUp();
            break;

        case KEY_LEFT:
            moveLeft();
            break;

        case KEY_RIGHT:
            moveRight();
            break;

        case KEY_DOWN:
            moveDown();
            break;
    }

    draw();
}

void NCursesBoardView::Cursor::moveUp()
{
    if (currentX > 0)
    {
        currentX--;
    }
}

void NCursesBoardView::Cursor::moveDown()
{
    if (currentX + 1 < height)
    {
        currentX++;
    }
}

void NCursesBoardView::Cursor::moveRight()
{
    if (currentY + 1 < width)
    {
        currentY++;
    }
}

void NCursesBoardView::Cursor::moveLeft()
{
    if (currentY > 0)
    {
        currentY--;
    }
}

void NCursesBoardView::Cursor::drawColored(size_t i, size_t j, bool underCursor) const
{
    POSITION_STATE current = board.get(i, j);
    int color;
    if (underCursor)
    {
        color = CURSOR_COLOR;
    }
    else
    {
        if (current == X_SIGN)
            color = X_COLOR;
        else if (current == O_SIGN)
            color = O_COLOR;
        else
            color = BACKGROUND_COLOR;
    }

    wattron(window, COLOR_PAIR(color));

    if (char(board.get(i, j)) == '.')
        wprintw(window, ".");
    else
        wprintw(window, "%c", char(board.get(i, j)));

    wattroff(window, COLOR_PAIR(color));
}

WINDOW *NCursesBoardView::Cursor::getWindow() const
{
    return window;
}

NCursesBoardView::Cursor::~Cursor()
{
    delwin(window);
}

void NCursesBoardView::Cursor::initCursorWindow()
{
    move(1, 1);
    window = newwin(board.getHeight(), board.getWidth(), 1, 1);

    keypad(window, true);

    wrefresh(window);
}


