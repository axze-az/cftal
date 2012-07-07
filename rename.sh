#! /bin/sh

for i in ./x86vec*.h ./x86vec*.cc
do
    cat $i | sed s/_float/_f32/g | sed s/_double/_f64/g >/tmp/$i
    echo mv /tmp/$i $i
done

for i in check/*_float*.cc check/*_double*.cc
do
    nn=`echo $i | sed s/_float/_f32/g | sed s/_double/_f64/g`
    echo rm $nn
    echo svn rename $i $nn
done
