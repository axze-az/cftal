#! /bin/sh
#set -x
i=1
fac="1"

echo "const cftal::d_real<double> inv_fac[] = {"
val=`echo "scale=64;  val=1.0/($fac); print(val)" | bc`
echo -n "\t${val}_dd"
while [ $i -lt 32 ] 
do
    echo ","
    fac="$fac*$i"
    val=`echo "scale=64;  val=1.0/($fac); print(val)" | bc`
    #echo "const cftal::d_real<double> inv_fac_$i="
    echo -n "\t${val}_dd"
    i=`expr $i + 1`
done
echo
echo "};"
