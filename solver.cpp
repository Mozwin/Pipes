#include "solver.h"
#include "tap.h"

#include <QPoint>

Solver::Solver()
{

}

Solver::~Solver()
{
    while (this->positions.length() > 0) {
        delete this->positions.at(0);
        this->positions.removeAt(0);
    }
}

void Solver::collectEmptyFields()
{
    for (int y = 0; y < this->level->getHeight(); y++) {
        for (int x = 0; x < this->level->getWidth(); x++) {
            GameObject* go = level->getFixedGameObjectAt(x, y);
            if (go == nullptr) {
                this->emptyFields.append(QPoint(x, y));
            }
        }
    }
}

void Solver::createPositions()
{
    for (int i = 0; i < level->getFields().length(); i++) {
        Position* p = new Position();

        // Csap típus kezelése...
        if (level->getFields().at(i)->getType() == "tap")
            p->isTap = true;

        this->positions.append(p);
    }
}

void Solver::init(Level *level)
{
    this->level = level;

    collectEmptyFields();
    createPositions();

    // Kidobja a felesleges szabad mezőket, ha túl sokan vannak...
    optimizeFields();
}

void Solver::optimizeFields()
{

}

Level *Solver::getNextSolution()
{
    // Early exit -> nincs mit csinálni...
    if (this->emptyFields.length() == 0)
        return this->level;

    QList<GameObject*> fixedFields = this->level->getFixedFields();
    QList<GameObject*> fields = this->level->getFields();

    // Törlünk mindent...
    level->resetLevel();
    level->clearGameObjects();

    // A fixed mezőket berakjuk a gameObjects listába, hogy legyen mit ellenőrizni...
    for (int i = 0; i < fixedFields.length(); i++) {
        level->addGameObject(fixedFields.at(i));
    }

    // Beállítjuk a dinamikus elemeket a Positions alapján...
    for (int i = 0; i < fields.length(); i++) {
        GameObject* go = fields.at(i);
        Position* pos = positions.at(i);

        if (pos->posIndex != -1) {
            QPoint xy = emptyFields.at(pos->posIndex);
            go->setXY(xy.x(), xy.y());
            go->setRotation((Rotation)pos->rotation);
            level->addGameObject(go);

            if (go->getType() == "tap") {
                ((Tap*)go)->setClosed(pos->closed);
            }
        }
    }

    // Majd megcsinálunk egy lépést...
    bool needStep = true;
    int items = positions.length();

    bool hasCollision = true;

    while (hasCollision) {
        for (int i = 0; i < items; i++) {
            if (needStep) {
                needStep = positions.at(i)->step(emptyFields.length() - 1);
            }
        }

        hasCollision = false;

        for (int i = 0; i < items; i++) {
            for (int j = 0; j < items; j++) {
                if (i == j)
                    continue;

                if (positions.at(i)->posIndex == -1 || positions.at(j)->posIndex == -1)
                    continue;

                if (positions.at(i)->posIndex == positions.at(j)->posIndex) {
                    hasCollision = true;
                    needStep = true;
                    break;
                }
            }
        }
    }

    if (needStep) {
        finished = true;
    }

    return this->level;
}

bool Solver::isFinished()
{
    return this->finished;
}
