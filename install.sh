#!/bin/env bash

mkdir $HOME/.config/kdecs/
cp $PWD/src/base/conf.ini $HOME/.config/kdecs/

mkdir $HOME/.cache/kdecs/
cp $PWD/src/base/info.ini $HOME/.cache/kdecs/

make