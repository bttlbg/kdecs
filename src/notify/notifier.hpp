/*
 * Just the function that manages the part of
 * listening when the wallpaper changes
 * @file notifier.hpp
 * @author Giovanni Cuervo
 * @version 0.1
 */

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

#include "../config/plasma_config.hpp"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

/*
 * This function will set up the inotify listener that will
 * trigger the rest of actions when the wallpaper is changed.
 * @param config_path The path to the config folder of the system
 * @param *fd The holder of tie inotify instance, we'll use to close it later
 * @param *wd Holds the watcher instance
 */
std::string notifier(std::string config_path, int *fd, int *wd);

#endif