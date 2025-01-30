#include "alphaomega.h"

AlphaOmega::AlphaOmega()
{

}

void AlphaOmega::setActive(bool active)
{
    this->active = active;
}

bool AlphaOmega::isActive()
{
    return this->active;
}

GameObject *AlphaOmega::clone()
{
//    AlphaOmega* result = new AlphaOmega();
//    result->x = this->x;
//    result->y = this->y;
//    result->rotation = this->rotation;
//    result->color = this->color;
//    result->up = this->up;
//    result->down = this->down;
//    result->left = this->left;
//    result->right = this->right;
//    result->active = this->active;
//    return result;
    return nullptr;
}


