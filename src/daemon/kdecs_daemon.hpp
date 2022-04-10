/*
 * The daemon that's gonna be running in the background
 * @file kdecs_daemon.hpp
 * @author Giovanni Cuervo
 * @version 0.1
 */

#ifndef DAEMON_H
#define DAEMON_H

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

void kdecs_daemon();

#endif