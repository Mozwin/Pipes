#include "gameobject.h"

GameObject::GameObject()
{

}

GameObject *GameObject::clone()
{
//    GameObject* result = new GameObject();
//    result->x = this->x;
//    result->y = this->y;
//    result->rotation = this->rotation;
//    result->color = this->color;
//    result->up = this->up;
//    result->down = this->down;
//    result->left = this->left;
//    result->right = this->right;
//    return result;

    return nullptr;
}

QString GameObject::getType()
{
    return this->type;
}

void GameObject::reset()
{
    this->x = -1;
    this->y = -1;
    this->rotation = Rotation::CW_0;
}

void GameObject::setRotation(Rotation rotation)
{
    this->rotation = rotation;
}

void GameObject::setConnections(bool up, bool down, bool left, bool right)
{
    this->up = up;
    this->down = down;
    this->left = left;
    this->right = right;
}

void GameObject::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
}

int GameObject::getX()
{
    return this->x;
}

int GameObject::getY()
{
    return this->y;
}

QString GameObject::getColor()
{
    return this->color;
}

QString GameObject::getNextColor()
{
    return this->nextColor;
}

bool GameObject::hasUpConnection()
{
    switch(this->rotation) {
    case CW_0: return up;
    case CW_90: return left;
    case CW_180: return down;
    case CW_270: return right;
    default: return false;
    }
}

bool GameObject::hasDownConnection()
{
    switch(this->rotation) {
    case CW_0: return down;
    case CW_90: return right;
    case CW_180: return up;
    case CW_270: return left;
    default: return false;
    }
}

bool GameObject::hasLeftConnection()
{
    switch(this->rotation) {
    case CW_0: return left;
    case CW_90: return down;
    case CW_180: return right;
    case CW_270: return up;
    default: return false;
    }
}

bool GameObject::hasRightConnection()
{
    switch(this->rotation) {
    case CW_0: return right;
    case CW_90: return up;
    case CW_180: return left;
    case CW_270: return down;
    default: return false;
    }
}

bool GameObject::hasFlow(Direction in, Direction out)
{
    return false;
}

void GameObject::setColor(const QString& color)
{
    this->color = color;
}

void GameObject::setNextColor(const QString &color)
{
    this->nextColor = color;
}

void GameObject::applyNextColor()
{
    this->color = this->nextColor;
}