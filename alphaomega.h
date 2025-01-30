#ifndef ALPHAOMEGA_H
#define ALPHAOMEGA_H

#include "gameobject.h"

class AlphaOmega : public GameObject
{
protected:
    bool active = true;

public:
    AlphaOmega();

    void setActive(bool active);
    bool isActive();

    GameObject *clone() override;
};

#endif // ALPHAOMEGA_H
