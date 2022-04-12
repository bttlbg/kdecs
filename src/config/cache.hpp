#ifndef CACHE_HPP
#define CACHE_HPP

#include <iostream>
#include <fstream>

std::string getOldWallpaper();

void saveCache(std::string wall_Path, std::string color_mode);

std::string getLastColorMode();

void saveWallpaper(std::string wall_Path, std::string color_mode);
#endif