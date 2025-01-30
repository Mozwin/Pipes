#include "tester.h"
#include "tap.h"
#include "alphaomega.h"

Tester::Tester()
{

}

bool Tester::test(Level *level, const QString& phaseColor)
{
    if (level == nullptr)
        return false;

    if (level->getWidth() <= 0 || level->getHeight() <= 0)
        return false;

    // Zárt-e a pálya...
    for (int y = 0; y < level->getHeight(); y++) {
        for (int x = 0; x < level->getWidth(); x++) {
            GameObject *go = level->getGameObjectAt(x, y);
            if (go == nullptr)
                continue;

            if (go->hasUpConnection()) {
                GameObject *ngo = level->getGameObjectAt(x, y - 1);
                if (ngo == nullptr) {
                    return false;
                } else {
                    if (!ngo->hasDownConnection())
                        return false;
                }
            }

            if (go->hasDownConnection()) {
                GameObject *ngo = level->getGameObjectAt(x, y + 1);
                if (ngo == nullptr) {
                    return false;
                } else {
                    if (!ngo->hasUpConnection())
                        return false;
                }
            }


            if (go->hasLeftConnection()) {
                GameObject *ngo = level->getGameObjectAt(x - 1, y);
                if (ngo == nullptr) {
                    return false;
                } else {
                    if (!ngo->hasRightConnection())
                        return false;
                }
            }

            if (go->hasRightConnection()) {
                GameObject *ngo = level->getGameObjectAt(x + 1, y);
                if (ngo == nullptr) {
                    return false;
                } else {
                    if (!ngo->hasLeftConnection())
                        return false;
                }
            }
        }
    }

    // Folyadék szimuláció...
//    level->resetNextColor();
    bool flow = true;

    while (flow) {
        flow = false;
        for (int y = 0; y < level->getHeight(); y++) {
            for (int x = 0; x < level->getWidth(); x++) {
                GameObject *go = level->getGameObjectAt(x, y);
                if (go == nullptr)
                    continue;

//                if (go->getColor() != "")
//                    continue;

                QString goType = go->getType();

                // Zárt csap?
                if (goType == "tap") {
                    if (((Tap*)go)->isClosed()) {
                        continue;
                    }
                }

                if (goType == "source" || goType == "consumer") {
                    if (((AlphaOmega*)go)->isActive()) {
                        go->setNextColor(go->getColor());   // A következő szine a sajátja marad!
                        continue;
                    }
                }

                if (go->hasUpConnection()) {
                    GameObject *ngo = level->getGameObjectAt(x, y - 1);
                    if (ngo->getColor() != "" && ngo->getType() != "consumer") {
                        if (go->getNextColor() != "") {
                            if (ngo->getColor() != go->getNextColor()) {
                                return false;
                            }
                        } else {
                            go->setNextColor(ngo->getColor());
                            flow = true;
                        }
                    }
                }

                if (go->hasDownConnection()) {
                    GameObject *ngo = level->getGameObjectAt(x, y + 1);
                    if (ngo->getColor() != "" && ngo->getType() != "consumer") {
                        if (go->getNextColor() != "") {
                            if (ngo->getColor() != go->getNextColor()) {
                                return false;
                            }
                        } else {
                            go->setNextColor(ngo->getColor());
                            flow = true;
                        }
                    }
                }

                if (go->hasLeftConnection()) {
                    GameObject *ngo = level->getGameObjectAt(x - 1, y);
                    if (ngo->getColor() != "" && ngo->getType() != "consumer") {
                        if (go->getNextColor() != "") {
                            if (ngo->getColor() != go->getNextColor()) {
                                return false;
                            }
                        } else {
                            go->setNextColor(ngo->getColor());
                            flow = true;
                        }
                    }
                }

                if (go->hasRightConnection()) {
                    GameObject *ngo = level->getGameObjectAt(x + 1, y);
                    if (ngo->getColor() != "" && ngo->getType() != "consumer") {
                        if (go->getNextColor() != "") {
                            if (ngo->getColor() != go->getNextColor()) {
                                return false;
                            }
                        } else {
                            go->setNextColor(ngo->getColor());
                            flow = true;
                        }
                    }
                }
            }
        }

        level->applyNextColor();
    }

    // Végső ellenőrzés...
    for (int y = 0; y < level->getHeight(); y++) {
        for (int x = 0; x < level->getWidth(); x++) {
            GameObject *go = level->getGameObjectAt(x, y);
            if (go == nullptr)
                continue;

            QString goType = go->getType();

            if (goType != "consumer")
                continue;

            if (go->getColor() != phaseColor)
                continue;

            if (go->hasUpConnection()) {
                GameObject *ngo = level->getGameObjectAt(x, y - 1);
                if (go->getColor() != ngo->getColor())
                    return false;
            }

            if (go->hasDownConnection()) {
                GameObject *ngo = level->getGameObjectAt(x, y + 1);
                if (go->getColor() != ngo->getColor())
                    return false;
            }

            if (go->hasLeftConnection()) {
                GameObject *ngo = level->getGameObjectAt(x - 1, y);
                if (go->getColor() != ngo->getColor())
                    return false;
            }

            if (go->hasRightConnection()) {
                GameObject *ngo = level->getGameObjectAt(x + 1, y);
                if (go->getColor() != ngo->getColor())
                    return false;
            }
        }
    }

    return true;
}
