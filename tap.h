#ifndef TAP_H
#define TAP_H

#include "gameobject.h"

class Tap : public GameObject
{
    bool closed = false;
public:
    Tap();

    void setClosed(bool closed);
    bool isClosed();

    GameObject *clone() override;
};

#endif // TAP_H
