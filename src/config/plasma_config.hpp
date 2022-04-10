/*
 * Functions related to anything related to read or write into
 * KDE Plasma config files
 * @file plasma_config.hpp
 * @author Giovanni Cuervo
 * @version 0.1
 */

#ifndef PLASMA_CONFIG_H
#define PLASMA_CONFIG_H

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include <syslog.h>

#include <stdlib.h>

/*
 * This function will read the file that holds
 * the path to the wallpaper set by the system
 */
std::string getWallpaper();

#endif