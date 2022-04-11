/*
 * Functions to write the new colors in their
 * respective config files.
 * @file plasma_config.hpp
 * @author Giovanni Cuervo
 * @version 0.1
*/

#ifndef COLORS_HPP
#define COLORS_HPP

#include <iostream>
#include <fstream>
#include <syslog.h>

#include "../config/kdecs_config.hpp"

typedef struct
{
	std::string background;
	std::string background_2;
	std::string accent;
} wal_colors;

void writeColorScheme(kdecs_config kconf);

#endif