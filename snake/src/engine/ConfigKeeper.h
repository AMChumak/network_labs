#ifndef CONFIGKEEPER_H
#define CONFIGKEEPER_H
#include "proto/snakes.pb.h"

namespace engine
{
    class ConfigKeeper
    {
    public:
        static void read_from_file();
        static void read_from_msg(const GameConfig& config);
        static void write_to_file();

        static int get_width();
        static int get_height();
        static int get_food_static();
        static int get_state_delay_ms();

    private:
        static int width;
        static int height;
        static int food_static;
        static int state_delay_ms;
    };
} // engine

#endif //CONFIGKEEPER_H
