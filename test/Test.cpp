#include <cstdio>
#include "Test.h"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum)
{
    totalNum++;
    if (!expr)
    {
        printf("Failed test %s in %s on line %zu \n", func, filename, lineNum);
        failedNum++;
    }
}

static void printSeparator()
{
    printf("|==============|=============|=============|\n");
}

void Test::showFinalResult()
{
    printSeparator();
    printf("| Total Number | Test passed | Test failed |\n");
    printSeparator();
    printf("| %12d | %11d | %11d |\n", Test::totalNum, Test::totalNum - Test::failedNum, Test::failedNum);
    printSeparator();
}

