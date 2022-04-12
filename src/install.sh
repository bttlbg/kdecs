#!/bin/env bash

mkdir $HOME/.config/kdecs/
cp $PWD/base/conf.ini $HOME/.config/kdecs/
cp $PWD/base/scheme.sh $HOME/.config/kdecs/

mkdir $HOME/.cache/kdecs/
cp $PWD/base/info.ini $HOME/.cache/kdecs/

cp $PWD/base/kdecs.colors $HOME/.local/share/color-schemes/

make