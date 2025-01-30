#include "level.h"
#include "pipe.h"
#include "source.h"
#include "consumer.h"
#include "tap.h"
#include "doublepipe.h"

#include "tinyxml/tinyxml2.h"

#include <QBitmap>
#include <QPainter>

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

int Level::min(int a, int b)
{
    return a < b ? a : b;
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
                go->setOriginalXY(x, y);

                go->setConnections(up, down, left, right);

                go->setColor(color);
                go->setOriginalColor(color);

                if (type == "tap") {
                    bool closed = QString(gameobject_element->Attribute("closed")) == "true";
                    ((Tap*)go)->setClosed(closed);
                }

                fixedFields.append(go);
            }

            gameobject_element = gameobject_element->NextSiblingElement("gameobject");
        }
    }

    int ef = 0;

    // Megszámoljuk, hogy mennyi empty field van...
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            GameObject* go = this->getFixedGameObjectAt(x, y);
            if (go == nullptr) {
                ef++;
            }
        }
    }

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

            for (int i = 0; i < min(count, ef); i++) {
                go = createObjectByType(type);

                if (go != nullptr) {
                    go->setConnections(up, down, left, right);
                    fields.append(go);
                }
            }

            field_element = field_element->NextSiblingElement("field");
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
    int pipeSize = 16;
    int sourceSize = size / 2;

    QFont font;
    font.setPixelSize(16);

    QTextOption options;
    options.setAlignment(Qt::AlignCenter);

    QColor color;

    QImage image(width * size, height * size, QImage::Format_RGB888);
    image.fill(QColorConstants::White);
    QPainter painter;
    if (painter.begin(&image)) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {               
                // Háttér
                int xx = x * size;
                int yy = y * size;
                int hc = xx + size / 2;      // Horizontal Center
                int vc = yy + size / 2;      // Horizontal Center
                QRect rect(xx, yy, size - 2, size - 2);
                painter.setBrush(QBrush(QColor::fromRgb(192, 192, 192)));
                painter.fillRect(rect, QColor::fromRgb(192, 192, 192));
                painter.setPen(QColor::fromRgb(128, 128,128));
                painter.drawRect(rect);

                GameObject* go = getGameObjectAt(x, y);
                if (go == nullptr)
                    continue;

                if (go->getType() == "double") {
                    // TODO
                } else {
                    color.setNamedColor(go->getColor());
                    painter.setPen(Qt::PenStyle::NoPen);
                    painter.setBrush(QBrush(color));

                    if (go->hasUpConnection()) {
                        painter.fillRect(hc - pipeSize / 2, yy, pipeSize, size / 2, color);
                    }
                    if (go->hasDownConnection()) {
                        painter.fillRect(hc - pipeSize / 2, yy + size / 2, pipeSize, size / 2, color);
                    }
                    if (go->hasLeftConnection()) {
                        painter.fillRect(xx, vc - pipeSize / 2, size / 2, pipeSize, color);
                    }
                    if (go->hasRightConnection()) {
                        painter.fillRect(xx + size / 2, vc - pipeSize / 2, size / 2, pipeSize, color);
                    }
                    // Középre egy kör
                    if (go->hasUpConnection() || go->hasDownConnection() || go->hasLeftConnection() || go->hasRightConnection()) {
                        painter.setPen(Qt::PenStyle::NoPen);
                        painter.setBrush(color);
                        painter.drawEllipse(QPoint(hc, vc), pipeSize / 2, pipeSize / 2);
                    }
                }

                if (go->getType() == "source") {
                    color.setNamedColor(go->getColor());
                    painter.setPen(Qt::PenStyle::NoPen);
                    painter.setBrush(QBrush(color));
                    painter.drawEllipse(QPoint(hc, vc), sourceSize / 2, sourceSize / 2);

                    painter.setPen(QColor::fromRgb(0, 0, 0));
                    painter.setFont(font);
                    painter.drawText(rect, "S", options);
                }

                if (go->getType() == "consumer") {
                    QColor color;
                    color.setNamedColor(go->getColor());
                    painter.setPen(Qt::PenStyle::NoPen);
                    painter.setBrush(QBrush(color));
                    painter.drawEllipse(QPoint(hc, vc), sourceSize / 2, sourceSize / 2);

                    painter.setPen(QColor::fromRgb(0, 0, 0));
                    painter.setFont(font);
                    painter.drawText(rect, "C", options);
                }

                if (go->getType() == "tap") {
                    Tap* tap = (Tap*)go;
                    painter.setPen(tap->isClosed() ? QColor::fromRgb(0, 0, 0) : QColor::fromRgb(255, 255, 255));
                    painter.setBrush(Qt::BrushStyle::NoBrush);
                    painter.drawEllipse(QPoint(hc, vc), sourceSize / 2, sourceSize / 2);
                }
            }
        }

        painter.end();
    }
    image.save(filename);

    return true;
}

QList<GameObject *> Level::getFixedFields()
{
    return this->fixedFields;
}

QList<GameObject *> Level::getFields()
{
    return this->fields;
}

QStringList *Level::getPhases()
{
    return &this->phases;
}

void Level::clearGameObjects()
{
    this->gameObjects.clear();
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

GameObject *Level::getFixedGameObjectAt(int x, int y)
{
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
        return nullptr;

    for (int i = 0; i < fixedFields.length(); i++) {
        GameObject* go = fixedFields.at(i);
        if (go == nullptr)
            continue;

        if (go->getX() == x && go->getY() == y)
            return go;
    }

    return nullptr;
}

void Level::resetLevel()
{
    for (int i = 0; i < fixedFields.length(); i++) {
        fixedFields.at(i)->reset();
    }

    for (int i = 0; i < fields.length(); i++) {
        fields.at(i)->reset();
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
