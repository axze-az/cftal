#! /bin/sh

ssh srv "cd projects/cpplib && svn update"
ssh srv "cd projects/cpplib/cftal/build && nice -19 make -j16"
