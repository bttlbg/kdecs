/*
 * The functions to create, read or parse the config file for
 * the program.
 * @file kdecs_config.hpp
 * @author Giovanni Cuervo
 * @version 0.1
 */

#ifndef KDECS_CONFIG
#define KDECS_CONFIG

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

// Test includes, removable
#include <syslog.h>

typedef struct
{
    std::string backend;
    std::string accent;
    std::string light_mode;
    std::string wallpaper_path;
} kdecs_config;

kdecs_config parseConfig(std::string wallpaper_path);
std::string makeCommand(std::string wallpaper_path, std::string &last_color_mode);

#endif