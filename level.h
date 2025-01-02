#ifndef LEVEL_H
#define LEVEL_H

#include <QList>

#include "gameobject.h"

class Level
{
    int width = 0;
    int height = 0;

    QList<GameObject*> fields;              // A pályán felhasználható mezők
    QList<GameObject*> fixedFields;         // A pályán fixen fent levő mezők

    QList<GameObject*> gameObjects;

    QStringList phases;

public:
    Level();

    Level* clone();

    bool loadFromXML(QString filename);
    bool saveToXML(QString filename);
    bool saveToPNG(QString filename);

    QList<GameObject*> getFixedFields();

    void addGameObject(GameObject* gameObject);
    GameObject* getGameObjectAt(int x, int y);
    void resetLevel();
    void resetNextColor();
    void applyNextColor();

    int getWidth();
    int getHeight();

private:
    void setSize(int width, int height);
    GameObject *createObjectByType(const QString &type);
};

#endif // LEVEL_H
