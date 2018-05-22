len1=0
while read -r line; do
	len1=$(( $len1+1 ))
done < $1

len2=0
while read -r line; do
	len2=$(( $len2+1 ))
done < $2

[[ len1 -lt len2 ]] && end=$len1 || end=$len2

if [ -e $3 ]; then
	rm $3
	touch $3
fi

for i in $(seq 1 $end); do
	echo $(sed -n ${i}p $1) $(sed -n ${i}p $2) >> $3
done

