#! /bin/sh

ssh srv "cd projects/cpplib && svn update && cd cftal/gcc8 && nice -19 make -j16"

