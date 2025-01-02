#include "tap.h"

Tap::Tap()
{
    this->type = "tap";
}

void Tap::setClosed(bool closed)
{
    this->closed = closed;
}

bool Tap::isClosed()
{
    return closed;
}

GameObject *Tap::clone()
{
    Tap* result = new Tap();
    result->x = this->x;
    result->y = this->y;
    result->rotation = this->rotation;
    result->color = this->color;
    result->up = this->up;
    result->down = this->down;
    result->left = this->left;
    result->right = this->right;
    result->closed = this->closed;
    return result;
}
