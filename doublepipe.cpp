#include "doublepipe.h"

DoublePipe::DoublePipe()
{
    this->type = "double";
    this->setConnections(true, true, true, true);
}

GameObject *DoublePipe::clone()
{
    DoublePipe* result = new DoublePipe();
    result->x = this->x;
    result->y = this->y;
    result->rotation = this->rotation;
    result->color = this->color;
    result->up = this->up;
    result->down = this->down;
    result->left = this->left;
    result->right = this->right;
    return result;
}
