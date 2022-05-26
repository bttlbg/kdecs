#include "notifier.hpp"

std::string notifier(std::string config_path, int *fd, int *wd)
{
    std::string wallpaper_path = "";

    int length, i = 0;
    char buffer[BUF_LEN];

    *fd = inotify_init();

    if (*fd < 0)
    {
        perror("inotify_init");
    }

    *wd = inotify_add_watch(*fd, config_path.c_str(), IN_CREATE);
    length = read(*fd, buffer, BUF_LEN);

    if (length < 0)
    {
        syslog(LOG_ERR, "Error");
    }

    while (i < length)
    {
        struct inotify_event *event = (struct inotify_event *)&buffer[i];
        if (event->len)
        {
            if (event->mask & IN_CREATE)
            {
                /*
                 * Plasma creates this file when the desktop suffers any change and later,
                 * is copied into the actual config file. For this reason it is now our trigger.
                */
                if (!strcmp(event->name, "plasma-org.kde.plasma.desktop-appletsrc.lock"))
                {
                    sleep(1); // Wait for the system to write the new wallpaper
                    wallpaper_path = getWallpaper();
                }
            }
        }
        i += EVENT_SIZE + event->len;
    }
    return wallpaper_path;
}
