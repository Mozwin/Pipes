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
    QList<GameObject*> getFields();
    QStringList* getPhases();

    void clearGameObjects();
    void addGameObject(GameObject* gameObject);
    GameObject* getGameObjectAt(int x, int y);
    GameObject *getFixedGameObjectAt(int x, int y);
    void resetLevel();
    void resetNextColor();
    void applyNextColor();

    int getWidth();
    int getHeight();

private:
    int min(int a, int b);
    void setSize(int width, int height);
    GameObject *createObjectByType(const QString &type);
};

#endif // LEVEL_H
