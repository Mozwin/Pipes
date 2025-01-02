#include "pipe.h"

Pipe::Pipe()
{
    this->type = "pipe";
}

GameObject *Pipe::clone()
{
    Pipe* result = new Pipe();
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
