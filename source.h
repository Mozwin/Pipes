#ifndef SOURCE_H
#define SOURCE_H

#include "gameobject.h"
#include "alphaomega.h"

class Source : public AlphaOmega
{

public:
    Source();

    GameObject *clone() override;
};

#endif // SOURCE_H
