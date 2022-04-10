#include <iostream>

#include "daemon/kdecs_daemon.hpp"
#include "notify/notifier.hpp"

#include <signal.h>
#include <sys/stat.h>
#include <syslog.h>

#include <string.h>

#include <time.h>

#include <stdlib.h>

int main()
{
	/* Create the daemon */
	kdecs_daemon();

    /* get user home */
	std::string config_path(getenv("HOME"));
	config_path.append("/.config");

	int fd, wd;

	while (1)
	{
		syslog(LOG_NOTICE, "kdecs daemon is waiting");
		notifier(config_path, &fd, &wd);
		sleep(1);
	}

	(void)inotify_rm_watch(fd, wd);
	(void)close(fd);

	syslog(LOG_NOTICE, "- where were you when kdecs die");
	syslog(LOG_NOTICE, "> i was at home eating dorito when phone ring");
	syslog(LOG_NOTICE, "> kdecs is ded");
	syslog(LOG_NOTICE, "> no");
	closelog();

	return EXIT_SUCCESS;
}