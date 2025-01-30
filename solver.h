#ifndef SOLVER_H
#define SOLVER_H

#include "level.h"

#include <QList>

#include <QPoint>

class Position {
public:
    int posIndex = -1;      // Nincs a táblán, illetve az emptyFields index-et jelöli
    int closed = 0;         // tap
    int rotation = 0;       // 0-1-2-3
    bool isTap = false;

    bool step(int maxPosition) {        // emptyFields.length - 1
        if (posIndex != -1) {
            rotation++;
            if (rotation > 3) {
                rotation = 0;

                if (isTap) {
                     closed++;
                     if (closed > 1) {
                         closed = 0;

                         posIndex++;
                         if (posIndex > maxPosition) {
                            posIndex = -1;

                            return true;
                         }
                     }
                } else {
                    posIndex++;
                    if (posIndex > maxPosition) {
                       posIndex = -1;

                       return true;
                    }
                }
            }
        } else {
            // Tuti -1 a posIndex
            posIndex++;
            if (posIndex > maxPosition) {
               posIndex = -1;

               return true;
            }

//            if (isTap) {
//                 closed++;
//                 if (closed > 1) {
//                     closed = 0;

//                     posIndex++;
//                     if (posIndex > maxPosition) {
//                        posIndex = -1;

//                        return true;
//                     }
//                 }
//            } else {
//                posIndex++;
//                if (posIndex > maxPosition) {
//                   posIndex = -1;

//                   return true;
//                }
//            }
        }

        return false;
    }
};

class Solver
{
    bool finished = false;
    Level* level;

    QList<QPoint> emptyFields;
    QList<Position*> positions;

    void collectEmptyFields();
    void createPositions();
    void optimizeFields();

public:
    Solver();
    virtual ~Solver();

    void init(Level* level);
    Level* getNextSolution();
    bool isFinished();
};

#endif // SOLVER_H
