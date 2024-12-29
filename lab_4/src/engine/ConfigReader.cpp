//
// Created by anton on 12/12/24.
//

#include "ConfigReader.h"

#include <fstream>

namespace gameEngine {

    int ConfigReader::width = 40;
    int ConfigReader::height = 30;
    int ConfigReader::foodStatic = 1;
    int ConfigReader::stateDelayMs = 1000;

    void ConfigReader::readFromFile()
    {
        std::ifstream confFile{"snakes.conf"};
        if(confFile.is_open())
        {
            std::string confLine;
            while (getline(confFile, confLine))
            {
                std::string key, value;

                int pos = confLine.find('=');

                if (pos != std::string::npos)
                {
                    if(confLine.substr(0, pos) == "width")
                    {
                        try
                        {
                            int widthResource = stoi(confLine.substr(pos+1, confLine.size() - (pos + 1)));
                            width = widthResource;
                        } catch (const std::invalid_argument & e) {
                            std::cout << e.what() << "\n";
                        }
                        catch (const std::out_of_range & e) {
                            std::cout << e.what() << "\n";
                        }
                    } else if(confLine.substr(0, pos) == "height")
                    {
                        try
                        {
                            int heightResource = stoi(confLine.substr(pos+1, confLine.size() - (pos + 1)));
                            height = heightResource;
                        } catch (const std::invalid_argument & e) {
                            std::cout << e.what() << "\n";
                        }
                        catch (const std::out_of_range & e) {
                            std::cout << e.what() << "\n";
                        }
                    } else if(confLine.substr(0, pos) == "food_static")
                    {
                        try
                        {
                            int foodStaticResource = stoi(confLine.substr(pos+1, confLine.size() - (pos + 1)));
                            foodStatic = foodStaticResource;
                        } catch (const std::invalid_argument & e) {
                            std::cout << e.what() << "\n";
                        }
                        catch (const std::out_of_range & e) {
                            std::cout << e.what() << "\n";
                        }
                    } else if(confLine.substr(0, pos) == "state_delay_ms")
                    {
                        try
                        {
                            int StateDelayResource = stoi(confLine.substr(pos+1, confLine.size() - (pos + 1)));
                            stateDelayMs = StateDelayResource;
                        } catch (const std::invalid_argument & e) {
                            std::cout << e.what() << "\n";
                        }
                        catch (const std::out_of_range & e) {
                            std::cout << e.what() << "\n";
                        }
                    }
                }
            }
            confFile.close();
        }
    }

    void ConfigReader::readFromMsg(const GameAnnouncement& announcement)
    {

        width = (announcement.config().has_width()) ? announcement.config().width() : 40;
        height = (announcement.config().has_height()) ? announcement.config().height() : 30;
        foodStatic = (announcement.config().has_food_static()) ? announcement.config().food_static() : 1;
        stateDelayMs = (announcement.config().has_width()) ? announcement.config().state_delay_ms() : 1000;
    }

    int ConfigReader::getWidth()
    {
        return width;
    }

    int ConfigReader::getHeight()
    {
        return height;
    }

    int ConfigReader::getFoodStatic()
    {
        return foodStatic;
    }

    int ConfigReader::getStateDelayMs()
    {
        return stateDelayMs;
    }
} // gameEngine