#ifndef PIPE_H
#define PIPE_H

#include "gameobject.h"

class Pipe : public GameObject
{
public:
    Pipe();

    GameObject *clone() override;
};

#endif // PIPE_H
