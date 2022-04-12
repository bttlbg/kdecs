#!/bin/env bash

mkdir $HOME/.config/kdecs/
cp $PWD/base/conf.ini $HOME/.config/kdecs/

mkdir $HOME/.cache/kdecs/
cp $PWD/base/info.ini $HOME/.cache/kdecs/

make