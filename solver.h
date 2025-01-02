#ifndef SOLVER_H
#define SOLVER_H

#include "level.h"

class Solver
{
    Level* level;
    Level* workLevel;

public:
    Solver();

    void setLevel(Level* level);
    Level* getNextSolution();
};

#endif // SOLVER_H
