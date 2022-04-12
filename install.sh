#!/bin/env bash

mkdir $HOME/.config/kdecs/
cp $PWD/src/base/conf.ini $HOME/.config/kdecs/
cp $PWD/src/base/scheme.sh $HOME/.config/kdecs/

mkdir $HOME/.cache/kdecs/
cp $PWD/src/base/info.ini $HOME/.cache/kdecs/

cp $PWD/src/base/kdecs.colors $HOME/.local/share/color-schemes/

make