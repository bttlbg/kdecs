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

	std::string wallpaper_path = "", oldWallpaper = "";

	kdecs_config k_config;

	while (1)
	{
		syslog(LOG_NOTICE, "kdecs daemon is waiting");
		wallpaper_path = notifier(config_path, &fd, &wd);
		oldWallpaper = getOldWallpaper();
		if (!wallpaper_path.empty() && wallpaper_path != oldWallpaper)
		{
			std::string command = makeCommand(wallpaper_path);
			system(command.c_str());
			saveWallpaper(wallpaper_path);

			/*
			 * REMOVE THE LINES BEFORE THIS COMMENT AN WRITE
			 * A CALL TO YOUR OWN FUNCTION TO WRITTE YOUR COLORS
			 */
			// writeColorScheme(k_config);
		}
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