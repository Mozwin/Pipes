#include "level.h"
#include "pipe.h"
#include "source.h"
#include "consumer.h"
#include "tap.h"
#include "doublepipe.h"

#include "tinyxml/tinyxml2.h"

#include <QBitmap>

using namespace tinyxml2;

Level::Level()
{
}

Level *Level::clone()
{
    Level* result = new Level();
    result->setSize(this->width, this->height);

    // Fázisok lemásolása...
    for (int i = 0; i < phases.length(); i++) {
        result->phases.append(phases.at(i));
    }

    // Fields lemásolása
    for (int i = 0; i < fields.length(); i++) {
        result->fields.append(fields.at(i)->clone());
    }

    // Fixed Fields lemásolása
    for (int i = 0; i < fixedFields.length(); i++) {
        result->fixedFields.append(fixedFields.at(i)->clone());
    }

    // Game Objects lemásolása
    for (int i = 0; i < gameObjects.length(); i++) {
        result->gameObjects.append(gameObjects.at(i)->clone());
    }

    return result;
}

bool Level::loadFromXML(QString filename)
{
    XMLDocument xml;

    if (xml.LoadFile(filename.toLocal8Bit().data()) != XMLError::XML_SUCCESS)
        return false;

    XMLElement* root_element = xml.FirstChildElement();
    if (root_element == nullptr)
        return false;

    int width = QString(root_element->Attribute("width")).toInt();
    int height = QString(root_element->Attribute("height")).toInt();

    this->setSize(width, height);

    // Mezők beolvasása
    XMLElement* fields_element = root_element->FirstChildElement("fields");
    if (fields_element != nullptr) {
        XMLElement* field_element = fields_element->FirstChildElement("field");
        while (field_element != nullptr) {
            int count = QString(field_element->Attribute("count")).toInt();
            bool up = QString(field_element->Attribute("up")) == "true";
            bool down = QString(field_element->Attribute("down")) == "true";
            bool left = QString(field_element->Attribute("left")) == "true";
            bool right = QString(field_element->Attribute("right")) == "true";
            QString type = field_element->Attribute("type");
            type = type.toLower();

            GameObject* go = nullptr;

            for (int i = 0; i < count; i++) {
                go = createObjectByType(type);

                if (go != nullptr) {
                    go->setConnections(up, down, left, right);
                    fields.append(go);
                }
            }

            field_element = field_element->NextSiblingElement("field");
        }
    }

    // Pálya beolvasása
    XMLElement* gameobjects_element = root_element->FirstChildElement("gameobjects");
    if (gameobjects_element != nullptr) {
        XMLElement* gameobject_element = gameobjects_element->FirstChildElement("gameobject");
        while (gameobject_element != nullptr) {
            int x = QString(gameobject_element->Attribute("x")).toInt();
            int y = QString(gameobject_element->Attribute("y")).toInt();
            bool up = QString(gameobject_element->Attribute("up")) == "true";
            bool down = QString(gameobject_element->Attribute("down")) == "true";
            bool left = QString(gameobject_element->Attribute("left")) == "true";
            bool right = QString(gameobject_element->Attribute("right")) == "true";
            QString type = gameobject_element->Attribute("type");
            QString color = gameobject_element->Attribute("color");
            type = type.toLower();
            color = color.toLower();

            GameObject* go = createObjectByType(type);

            if (go != nullptr) {
                go->setXY(x, y);
                go->setConnections(up, down, left, right);
                go->setColor(color);

                if (type == "tap") {
                    bool closed = QString(gameobject_element->Attribute("closed")) == "true";
                    ((Tap*)go)->setClosed(closed);
                }


                fixedFields.append(go);
            }

            gameobject_element = gameobject_element->NextSiblingElement("gameobject");
        }
    }

    // Fázisok beolvasása
    XMLElement* phases_element = root_element->FirstChildElement("phases");
    if (phases_element != nullptr) {
        XMLElement* phase_element = phases_element->FirstChildElement("phase");
        while (phase_element != nullptr) {
            QString color = phase_element->Attribute("color");
            this->phases.append(color);

            phase_element = phase_element->NextSiblingElement("phase");
        }
    }

    return true;
}

GameObject* Level::createObjectByType(const QString& type) {
    if (type == "pipe") {
        return new Pipe();
    } else if (type == "source") {
        return new Source();
    } else if (type == "consumer") {
        return new Consumer();
    } else if (type == "tap") {
        return new Tap();
    } else if (type == "double") {
        return new DoublePipe();
    }

    return nullptr;
}


bool Level::saveToXML(QString filename)
{
    return false;
}

bool Level::saveToPNG(QString filename)
{
    int size = 64;

    QImage image(width * size, height * size, QImage::Format_RGB888);
    image.fill(QColorConstants::White);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < height; x++) {

        }
    }

    image.save(filename);

    return true;
}

QList<GameObject *> Level::getFixedFields()
{
    return this->fixedFields;
}

void Level::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Level::addGameObject(GameObject *gameObject)
{
    if (gameObject == nullptr)
        return;

    int x = gameObject->getX();
    int y = gameObject->getY();

    if (x < 0 || y < 0 || x >= this->width || y >= this->height) {
        // TODO: hibakezelés!
        return;
    }

    if (getGameObjectAt(x, y)) {
        // TODO: hibakezelés!
        return;
    }

    gameObjects.append(gameObject);
}

GameObject *Level::getGameObjectAt(int x, int y)
{
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
        return nullptr;

    for (int i = 0; i < gameObjects.length(); i++) {
        GameObject* go = gameObjects.at(i);
        if (go == nullptr)
            continue;

        if (go->getX() == x && go->getY() == y)
            return go;
    }

    return nullptr;
}

void Level::resetLevel()
{
    this->gameObjects.clear();

    for (int i = 0; i < fields.length(); i++) {
        fields.at(i)->reset();
    }
}

void Level::resetNextColor()
{
    for (int i = 0; i < gameObjects.length(); i++) {
        gameObjects.at(i)->setNextColor("");
    }
}

void Level::applyNextColor()
{
    for (int i = 0; i < gameObjects.length(); i++) {
        gameObjects.at(i)->applyNextColor();
    }
}

int Level::getWidth()
{
    return this->width;
}

int Level::getHeight()
{
    return this->height;
}
