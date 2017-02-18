#! /bin/sh
#set -e
set -x
files=`find . \( -name '*.h' -o -name '*.cc' \)`
offset=0

for i in $files
do
    ll=`cat $i| wc -l`
    ll=$(($ll-$offset))
cat >/tmp/$$ <<EOF
//
// Copyright Axel Zeuner 2010-2017. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
EOF
    tail -n $ll $i >>/tmp/$$
    mv /tmp/$$ $i
done
#rm /tmp/$$
