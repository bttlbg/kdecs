#include "cache.hpp"

std::string getCache(std::string key)
{
    std::string cache_path(getenv("HOME"));
    cache_path.append("/.cache/kdecs/info.ini");
    std::fstream cache_file;
    cache_file.open(cache_path, std::ios::in);

    std::string line;

    if (!cache_file)
        return "";
    else
    {
        while (!cache_file.eof())
        {
            std::getline(cache_file, line);

            if (line.length() == 0)
                continue;

            if (line.at(0) == ';')
                continue;

            int eq_pos = line.find("=");

            std::string key_cache = "";
            for (int i = 0; i < eq_pos; i++)
                key_cache += line.at(i);

            std::string value = "";
            for (int i = eq_pos + 1; i < (int)line.length(); i++)
                value += line.at(i);

            if (key_cache == key)
                return value;
        }
    }
    return "";
}

void saveCache(std::string wall_Path, std::string color_mode)
{
    std::string wall_name = "";

    for (int i = (int)wall_Path.length() - 1; i >= 0; i--)
    {
        if (wall_Path.at(i) == '/')
            break;
        else
            wall_name = wall_Path.at(i) + wall_name;
    }

    std::string cache_path(getenv("HOME"));
    cache_path.append("/.cache/kdecs/info.ini");
    std::ofstream cache_file;
    cache_file.open(cache_path);
    cache_file << "oldWall=" << wall_name << std::endl;
    cache_file << "lastColorMode=" << color_mode << std::endl;
    cache_file.close();
}
