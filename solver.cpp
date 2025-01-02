#include "solver.h"

Solver::Solver()
{

}

void Solver::setLevel(Level *level)
{
    this->level = level;
}

Level *Solver::getNextSolution()
{
    QList<GameObject*> fixedFields = this->level->getFixedFields();

    // A fixed mezőket berakjuk a gameObjects listába, hogy legyen mit ellenőrizni...
    for (int i = 0; i < fixedFields.length(); i++) {
        level->addGameObject(fixedFields.at(i));
    }

    // TODO

    return this->level->clone();
}
