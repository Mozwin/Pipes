#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>

enum FieldType {
    UNUSED = 0,
    SOURCE = 1,
    CONSUMER = 2,
    PIPE = 3,
    TAP = 4,
    DOUBLE = 5,
};

enum Rotation {
    CW_0 = 0,
    CW_90 = 1,
    CW_180 = 2,
    CW_270 = 3,
};

enum Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
};

class GameObject
{
protected:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    int x = -1;
    int y = -1;

    int originalX = -1;
    int originalY = -1;

    QString type = "";
    QString originalColor = ""; // Ez az eredeti szine, ebből állítódik vissza a color
    QString color = "";
    QString nextColor = "";     // A folyadék szimulációhoz, ez lesz a következő állapot szine...

    int rotation = CW_0;
    int originalRotation = CW_0;

public:
    GameObject();
    virtual GameObject* clone();

    QString getType();
    void reset();           // Visszaállítjuk az alap állapotot
    void setRotation(Rotation rotation);
    void setColor(const QString& color);
    void setOriginalColor(const QString& color);
    void setNextColor(const QString& color);
    void applyNextColor();
    void setConnections(bool up, bool down, bool left, bool right);
    void setXY(int x, int y);
    void setOriginalXY(int x, int y);
    int getX();
    int getY();
    QString getColor();
    QString getNextColor();

    bool hasUpConnection();
    bool hasDownConnection();
    bool hasLeftConnection();
    bool hasRightConnection();

    virtual bool hasFlow(Direction in, Direction out);
};

#endif // GAMEOBJECT_H
