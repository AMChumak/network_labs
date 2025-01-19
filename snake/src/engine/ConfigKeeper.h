#ifndef CONFIGKEEPER_H
#define CONFIGKEEPER_H
#include "proto/snakes.pb.h"

namespace engine
{
    class ConfigKeeper
    {
    public:
        void read_from_file();
        void read_from_msg(const GameConfig& config);
        void write_to_file();

        int get_width();
        int get_height();
        int get_food_static();
        int get_state_delay_ms();

    private:
        std::mutex config_mutex;
        int width = 40;
        int height = 30;
        int food_static = 1;
        int state_delay_ms = 1000;
    };
} // engine

#endif //CONFIGKEEPER_H
