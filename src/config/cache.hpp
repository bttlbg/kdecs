#ifndef CACHE_HPP
#define CACHE_HPP

#include <iostream>
#include <fstream>

/*
 * A function that returns the value of a key in the cache file
 * @param key they to shearch in the cache file
 * @return the value of the key
 */
std::string getCache(std::string key);

/*
 * Save cache data
 * @param wall_Path string with the path to the new wallpaper
 * @param color_mode string that tell if we used light mode or not
 */
void saveCache(std::string wall_Path, std::string color_mode);

#endif