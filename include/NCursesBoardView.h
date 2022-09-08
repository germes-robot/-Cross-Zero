#ifndef HW_02_NCURSESBOARDVIEW_H
#define HW_02_NCURSESBOARDVIEW_H

#include "Board.h"
#include <ncurses.h>


const size_t BACKGROUND_COLOR = 1;
const size_t CURSOR_COLOR = 2;
const size_t X_COLOR = 3;
const size_t O_COLOR = 4;
const size_t EDGE_COLOR = 5;
const size_t END_COLOR = 6;


class NCursesBoardView
{
public:
    explicit NCursesBoardView(Board &board_);
    void doGameCycle();
    void showBoard() const;
    void printGameResult();

    void init();

    void showEndAnimation();

private:

    void printWhoseTurn() const;


    class Cursor
    {

    public:

        Cursor(size_t height_, size_t width_, Board &board_);

        virtual ~Cursor();

        void initCursorWindow();

        size_t getX() const;
        size_t getY() const;

        void moveCursor(int command);

        void remove();
        void draw();

        void drawColored(size_t i, size_t j, bool underCursor = false) const;

        WINDOW *getWindow() const;

    private:

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        size_t currentX;
        size_t currentY;
        size_t width;
        size_t height;
        Board& board;

        WINDOW *window;
    };


    Board& board;
    mutable Cursor cursor;
};


#endif //HW_02_NCURSESBOARDVIEW_H
