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
#include <string.h>
#include <syslog.h>

#include "../config/kdecs_config.hpp"

typedef struct
{
	std::string background;
	std::string background_2;
	std::string foreground;
	std::string accent;

	std::string background_rgb[3];
	std::string foreground_rgb[3];
	std::string accent_rgb[3];
} wal_colors;

std::string convertHEX(const char *num);

void writeColorScheme(kdecs_config kconf);

#endif