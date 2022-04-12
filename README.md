# **kdecs**
A daemon to change the color scheme of KDE

This branch is intended for the public user. It's only a daemon that runs a shell script when the wallpaper changes.
This branch will probably not receive more updates. As for now the program only creates a color scheme for KDE Plasma.

#### **Dependencies**

##### **Arch**

    yay -Syu pywal-git colorz bc

##### **Other distros**

    You're on your own

#### **Instructions**
Just run

    sh install.sh

Then execute the makefile and run

    ./main

And it's all, it'll generate the colors when you change your wallpaper.

Optional: You can run

    cp main $HOME/.config/autostart/

to make the start when you boot your system. The program isn't heavy so it should not be a performance impact.

*Note: The file name and the path to the wallpaper should not have white spaces, otherwise the program will behave weird*

#### **Config**
It's located on `$HOME/.config/kdecs/`, the config file only is very descriptive on its own, just read it.
