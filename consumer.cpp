#include "consumer.h"

Consumer::Consumer()
{
    this->type = "consumer";
}

GameObject *Consumer::clone()
{
    Consumer* result = new Consumer();
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
