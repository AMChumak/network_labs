#include "ConfigKeeper.h"

#include <fstream>

namespace engine {
    int ConfigKeeper::width = 40;
    int ConfigKeeper::height = 30;
    int ConfigKeeper::food_static = 1;
    int ConfigKeeper::state_delay_ms = 1000;

    void ConfigKeeper::read_from_file()
    {
        if(std::ifstream conf_file{"snakes.conf"}; conf_file.is_open())
        {
            std::string conf_line;
            while (getline(conf_file, conf_line))
            {
                std::string key, value;

                int pos = conf_line.find('=');

                if (pos != std::string::npos)
                {
                    std::string conf_key = conf_line.substr(0, pos);
                    auto no_space_key = std::remove_if(conf_key.begin(), conf_key.end(), isspace);
                    conf_key.erase(no_space_key, std::end(conf_key));


                    std::string conf_value = conf_line.substr(pos+1, conf_line.size() - (pos + 1));
                    auto no_space_value = std::remove_if(conf_value.begin(), conf_value.end(), isspace);
                    conf_value.erase(no_space_value, std::end(conf_value));

                    if(conf_key == "width")
                    {
                        try
                        {
                            int width_resource = stoi(conf_value);
                            width = width_resource;
                        } catch (const std::invalid_argument & e) {
                            std::cout << e.what() << "\n";
                        }
                        catch (const std::out_of_range & e) {
                            std::cout << e.what() << "\n";
                        }
                    } else if(conf_key == "height")
                    {
                        try
                        {
                            int height_resource = stoi(conf_value);
                            height = height_resource;
                        } catch (const std::invalid_argument & e) {
                            std::cout << e.what() << "\n";
                        }
                        catch (const std::out_of_range & e) {
                            std::cout << e.what() << "\n";
                        }
                    } else if(conf_key == "food_static")
                    {
                        try
                        {
                            int food_static_resource = stoi(conf_value);
                            food_static = food_static_resource;
                        } catch (const std::invalid_argument & e) {
                            std::cout << e.what() << "\n";
                        }
                        catch (const std::out_of_range & e) {
                            std::cout << e.what() << "\n";
                        }
                    } else if(conf_key == "state_delay_ms")
                    {
                        try
                        {
                            int state_delay_resource = stoi(conf_value);
                            state_delay_ms = state_delay_resource;
                        } catch (const std::invalid_argument & e) {
                            std::cout << e.what() << "\n";
                        }
                        catch (const std::out_of_range & e) {
                            std::cout << e.what() << "\n";
                        }
                    }
                }
            }
            conf_file.close();
        }
    }

    void ConfigKeeper::read_from_msg(const GameConfig& config)
    {

        width = (config.has_width()) ? config.width() : 40;
        height = (config.has_height()) ? config.height() : 30;
        food_static = (config.has_food_static()) ? config.food_static() : 1;
        state_delay_ms = (config.has_width()) ? config.state_delay_ms() : 1000;
    }

    void ConfigKeeper::write_to_file()
    {
        if (std::ofstream conf_file{"snakes.conf"}; conf_file.is_open())
        {
            conf_file << "width =" << width << std::endl;
            conf_file << "height =" << height << std::endl;
            conf_file << "food_static =" << food_static << std::endl;
            conf_file << "state_delay_ms =" << state_delay_ms << std::endl;
            conf_file.close();
        }
    }

    int ConfigKeeper::get_width()
    {
        return width;
    }

    int ConfigKeeper::get_height()
    {
        return height;
    }

    int ConfigKeeper::get_food_static()
    {
        return food_static;
    }

    int ConfigKeeper::get_state_delay_ms()
    {
        return state_delay_ms;
    }
} // engine