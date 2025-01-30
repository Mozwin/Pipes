#ifndef CONSUMER_H
#define CONSUMER_H

#include "gameobject.h"
#include "alphaomega.h"

class Consumer : public AlphaOmega
{

public:
    Consumer();

    GameObject *clone() override;
};

#endif // CONSUMER_H
