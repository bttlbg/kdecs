#include "cache.hpp"

std::string getOldWallpaper()
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

            std::string key = "";
            for (int i = 0; i < eq_pos; i++)
                key += line.at(i);

            std::string value = "";
            for (int i = eq_pos + 1; i < (int)line.length(); i++)
                value += line.at(i);

            if (key == "oldWall")
                return value;
        }
    }
    return "";
}

void saveWallpaper(std::string wall_Path)
{
    
    if (wall_Path.at(0) == '/')
    {
        std::string aux_str = "";
        for (int i = 1; i < (int)wall_Path.length(); i++)
        {
            aux_str += wall_Path.at(i);
        }
        wall_Path = aux_str;
    }

    std::string cache_path(getenv("HOME"));
    cache_path.append("/.cache/kdecs/info.ini");
    std::ofstream cache_file;
    cache_file.open(cache_path);
    cache_file << "oldWall=" << wall_Path << std::endl;
    cache_file.close();

    /*std::fstream cache_file;
    cache_file.open(cache_path, std::ios::out | std::ios::in);

    std::string line;

    if (cache_file)
    {
        while (!cache_file.eof())
        {
            std::getline(cache_file, line);

            if (line.length() == 0)
                continue;

            if (line.at(0) == ';')
                continue;

            cache_file << "oldWall=" + wall_Path << std::endl;
            if (line.find("oldWall") != std::string::npos)
            {
                cache_file << "oldWall=" + wall_Path << std::endl;
                break;
            }
        }
        cache_file.close();
    }*/
}