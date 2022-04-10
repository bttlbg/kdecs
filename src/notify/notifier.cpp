#include "notifier.hpp"

void notifier(std::string config_path, int *fd, int *wd)
{

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
                if (event->mask & IN_ISDIR)
                {
                    syslog(LOG_NOTICE, "Directory created");
                    printf("The directory %s was created.\n", event->name);
                }
                else
                {
                    /*
                     * Plasma creates a temporary lock file when we change the wall,
                     * let's catch it and do some magic
                    */
                    if (!strcmp(event->name, "plasma-org.kde.plasma.desktop-appletsrc.lock"))
                    {
                        sleep(1); // Wait for the system to write the new wallpaper
                        syslog(LOG_NOTICE, "Wallpaper changed");
                        readWallpaper();
                    }
                    else
                    {
                        syslog(LOG_NOTICE, "File created");
                    }
                }
            }
        }
        i += EVENT_SIZE + event->len;
    }
}
