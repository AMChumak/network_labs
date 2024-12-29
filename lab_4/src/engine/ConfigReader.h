//
// Created by anton on 12/12/24.
//

#ifndef CONFIGREADER_H
#define CONFIGREADER_H
#include "../snakes.pb.h"

namespace gameEngine {

class ConfigReader {
public:
    static void readFromFile();
    static void readFromMsg(const GameAnnouncement& announcement);

    static int getWidth();
    static int getHeight();
    static int getFoodStatic();
    static int getStateDelayMs();
private:
    static int width;
    static int height;
    static int foodStatic;
    static int stateDelayMs;
};

} // gameEngine

#endif //CONFIGREADER_H
