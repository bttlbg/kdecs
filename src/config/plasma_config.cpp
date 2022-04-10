#include "plasma_config.hpp"

std::string getWallpaper()
{
	/* get the config file */
	std::string config_file_path(getenv("HOME"));
	config_file_path.append("/.config/plasma-org.kde.plasma.desktop-appletsrc");
	std::fstream kde_config_file;
	kde_config_file.open(config_file_path, std::ios::in);

	std::string current_wallpaper = "";

	if (!kde_config_file)
	{
		syslog(LOG_ERR, "Config file missing");
	}
	else
	{
		while (!kde_config_file.eof())
		{
			std::string line;
			std::getline(kde_config_file, line);

			/*
			 * The strin is temporary, i had a better aproach but I'm too lazy
			 * to do it now.
			 */
			//if (line == "[Containments][99][Wallpaper][org.kde.image][General]")
			if (line.find("[org.kde.image]") != std::string::npos)
			{
				/*
				 *The only line who starts with 'I' is the one with
				 * the wall path, let's search for it
				 */
				while (line.at(0) != 'I')
					std::getline(kde_config_file, line);

				// Start from 7 to remove extra chars from path
				int i = 7;

				/*
				 * When the wallpaper is set from the desktop dialog the
				 * path to the wallpaper is written different, we need to
				 * check that and if so, we need to remove the extra chars
				 * from the path
				 */
				if (line.find("file:///") != std::string::npos)
					i = line.find("file:///") + 7;

				/*
				 * Had to put i = i bacause the compiler kept complaining about
				 * me only writting i or nothing in here, wtf
				 */
				for (i = i; i < (int)line.length(); i++)
					current_wallpaper += line.at(i);

			}
		}
		kde_config_file.close();
	}
	return current_wallpaper;
}