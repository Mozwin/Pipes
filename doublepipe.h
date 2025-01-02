#ifndef DOUBLEPIPE_H
#define DOUBLEPIPE_H

#include "pipe.h"

class DoublePipe : public Pipe
{
public:
    DoublePipe();

    GameObject *clone() override;
};

#endif // DOUBLEPIPE_H
