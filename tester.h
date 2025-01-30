#ifndef TESTER_H
#define TESTER_H

#include "level.h"

class Tester
{
public:
    Tester();

    bool test(Level* level, const QString& color);
};

#endif // TESTER_H
