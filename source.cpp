#include "source.h"

Source::Source()
{
    this->type = "source";
}

GameObject *Source::clone()
{
    Source* result = new Source();
    result->x = this->x;
    result->y = this->y;
    result->rotation = this->rotation;
    result->color = this->color;
    result->up = this->up;
    result->down = this->down;
    result->left = this->left;
    result->right = this->right;
    result->active = this->active;
    return result;
}
