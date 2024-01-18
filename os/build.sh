#!/bin/bash
c=0
for file in `ls  ../usr/bin/`
do
	apps[$c]=$file
	((c++))
done
filelink="src/link_app.S"
echo -e "\c" > $filelink
echo ".align 3
    .section .data
    .global _num_app
_num_app:
    .quad ${#apps[@]}" >> $filelink

c=0
apps_len=${#apps[@]}
while (($c < $apps_len)) 
do
	echo "    .quad app_${c}_start" >> $filelink
	let "c++"
done

let "apps_len--"
echo "    .quad app_${apps_len}_end" >> $filelink
let "apps_len++"

c=0
apps_len=${#apps[@]}
target_path="../usr/target/"
while (($c < $apps_len)) 
do
	echo "
    .section .data
    .global app_${c}_start
    .global app_${c}_end
app_${c}_start:
    .incbin \"${target_path}${apps[$c]}.bin\"
app_${c}_end:"        >> $filelink
	let "c++"
done
