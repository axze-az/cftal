#! /bin/sh

ssh srv "cd projects/cpplib && svn update && cd cftal/build && nice -19 make -j16"

