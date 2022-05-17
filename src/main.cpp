/*
 * @file main.cpp
 * @author Giovanni Cuervo
 * @version 0.1
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "config/cache.hpp"
#include "colors/colors.hpp"
#include "daemon/kdecs_daemon.hpp"
#include "config/kdecs_config.hpp"
#include "notify/notifier.hpp"

int main()
{
	/* Create the daemon */
	kdecs_daemon();

	int fd, wd;

	/* get user home */
	std::string config_path(getenv("HOME"));
	config_path.append("/.config");

	std::string wallpaper_path = "", oldWallpaper = "", new_wall_name_only = "";

	std::string last_color_mode;

	while (1)
	{
		syslog(LOG_NOTICE, "kdecs daemon is waiting");
		wallpaper_path = notifier(config_path, &fd, &wd);
		oldWallpaper = getOldWallpaper();

		for (int i = wallpaper_path.length() - 1; i >= 0; i--)
		{
			if (wallpaper_path.at(i) == '/')
				break;
			else
				new_wall_name_only = wallpaper_path.at(i) + new_wall_name_only;
		}

		// if (!wallpaper_path.empty() && wallpaper_path != oldWallpaper)
		if (!wallpaper_path.empty() && new_wall_name_only != oldWallpaper)
		{
			syslog(LOG_NOTICE, "Wallpaper changed");
			std::string command = makeCommand(wallpaper_path, last_color_mode);
			system(command.c_str());
			if (last_color_mode != getLastColorMode())
				system("qdbus org.kde.KWin /KWin reconfigure");

			saveCache(wallpaper_path, last_color_mode);
			syslog(LOG_NOTICE, new_wall_name_only.c_str());
			syslog(LOG_NOTICE, oldWallpaper.c_str());
			syslog(LOG_NOTICE, command.c_str());
		}
		else
		{
			syslog(LOG_NOTICE, "Invalid wallpaper or the images are the same");
			syslog(LOG_NOTICE, "No changes made.");
		}
		new_wall_name_only = "";
	}

	(void)inotify_rm_watch(fd, wd);
	(void)close(fd);

	syslog(LOG_NOTICE, "- where were you when kdecs die");
	syslog(LOG_NOTICE, "> i was at home eating dorito when phone ring");
	syslog(LOG_NOTICE, "> \"kdecs is ded\"");
	syslog(LOG_NOTICE, "> no");
	closelog();

	return EXIT_SUCCESS;
}