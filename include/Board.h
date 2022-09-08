#ifndef HW_02_BOARD_H
#define HW_02_BOARD_H

#include <cstddef>

enum GAME_STATE {
    IN_PROGRESS,
    X_WIN,
    O_WIN,
    DRAW,
    INTERRUPTED
};

enum POSITION_STATE {
    X_SIGN = 'X',
    O_SIGN = 'O',
    EMPTY = '.'
};

class Board
{
public:
    int getTurnNumber() const;

    Board(size_t height_, size_t width_);

    void makeMove(size_t x, size_t y, char sign);

    bool canMove(size_t x, size_t y) const;

    GAME_STATE gameState() const;

    POSITION_STATE get(size_t x, size_t y) const;

    size_t getWidth() const;

    size_t getHeight() const;

    ~Board();

private:

    void interruptGame();
    void initData();
    void checkIfStateChanged(size_t x, size_t y);
    int countElements(size_t x, size_t y, const POSITION_STATE state, const int X_DELTA, const int Y_DELTA);

private:

    size_t width;
    size_t height;
    POSITION_STATE ** data;

    GAME_STATE currentState;
    size_t turnNumber = 1;

};


#endif //HW_02_BOARD_H
