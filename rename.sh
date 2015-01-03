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

gen_v16()
{
    svn copy x86_v4u32.h x86_v8u16.h
    svn copy x86_v4u32_inl.h x86_v8u16_inl.h
    svn copy x86_v4s32.h x86_v8s16.h
    svn copy x86_v4s32_inl.h x86_v8s16_inl.h
}

#remove_std_int
