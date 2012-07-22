#! /bin/sh

rename()
{
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
}

remove_std_int()
{
    for i in ./*.h ./*.cc
    do
	cat $i | sed s/std::uint/uint/g | sed s/std::int/int/g >/tmp/$i
	echo mv /tmp/$i $i
    done
}

remove_std_int
