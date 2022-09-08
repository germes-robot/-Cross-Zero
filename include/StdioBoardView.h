#ifndef HW_02_STDIOBOARDVIEW_H
#define HW_02_STDIOBOARDVIEW_H


#include "Board.h"

class StdioBoardView
{
public:
    explicit StdioBoardView(Board &board_, bool isSilent);
    void doGameCycle();
    void showBoard() const;
    void printGameResult();

private:

    void readCoordinates(size_t &x, size_t &y, char currentSign);

    Board& board;
    const bool SILENCE;
};


#endif //HW_02_STDIOBOARDVIEW_H
