#include "kdecs_config.hpp"

kdecs_config parseConfig(std::string wallpaper_path)
{
    /* Loead the config file for the program */
    std::string config_path(getenv("HOME"));
    config_path.append("/.config/kdecs/conf.ini");

    std::fstream kdecs_config_file;
    kdecs_config_file.open(config_path, std::ios::in);

    kdecs_config k_conf;
    std::string line;

    if (!kdecs_config_file)
    {
        syslog(LOG_ERR, "KDECS Config file missing");
    }
    else
    {
        while (!kdecs_config_file.eof())
        {
            std::getline(kdecs_config_file, line);

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

            if (key == "backend")
                k_conf.backend = value;
            else if (key == "accent")
                k_conf.accent = value;
            else if (key == "lightMode")
                k_conf.light_mode = value;
        }
        k_conf.wallpaper_path = wallpaper_path;
        kdecs_config_file.close();
    }

    return k_conf;
}

std::string makeCommand(std::string wallpaper_path)
{
    kdecs_config kcf = parseConfig(wallpaper_path);

    std::string command = "sh $HOME/.config/polybar/scripts/scheme.sh ";

    command += "-b " + kcf.backend + " ";
    command += "-i " + kcf.wallpaper_path + " ";
    command += "-n " + kcf.accent + " ";

    if (kcf.light_mode == "true")
        command += "-l";

    return command;
}