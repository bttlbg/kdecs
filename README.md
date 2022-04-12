# **kdecs**
A daemon to change the color scheme of KDE

**Note: KDE has planned to release something similar in Plasma 5.25, since this announcement I took the decicion to make this tool compatible only with my dotfiles making it more of a personal tool, I do not recommend using it before doing your own changes to the code.**

**The repo is missing some files so this basically only a daemon to detect when the wallpaper is changed. The code to write the new colors will be posted some day because as of today _it only works on my machines._**

#### **Dependencies**

##### **Arch**
    yay -Syu pywal-git colorz bc

##### **Other distros**
    You're on your own

#### **Instructions**
Just compile it, theres a Makefile in the repo and run it! It'll automatically work when you change your wallpaper!

*Note: The file name and the path to the wallpaper should not have white spaces, otherwise the program will behave weird*

#### **Config**
The config file only is very descriptive on its own.

#### **Roadmap and known bugs**
* Make it compatible with other plugins
* Optimization in general