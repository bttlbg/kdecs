#ifndef NOTIF_H
#define NOTIF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#include <syslog.h>

#include "../config/read_config.hpp"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

void notifier(std::string config_path, int *fd, int *wd);

#endif