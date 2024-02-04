baddr=0x80400000
step=0x20000
c=0
for file in `ls  ./src/*.c`
do
	apps[$c]=$file
	((c++))
done
c=0
apps_len=${#apps[@]}
sddr=0
while (($c < $apps_len)) 
do
	baddr=$(( ${baddr}+${step} ))
	sddr=`printf "%x" ${baddr}`
	mddr=`printf "%x" $((${baddr}-${step}))`
	sed -i "s/0x${mddr}/0x${sddr}/"  ./src/linker.ld
	make build_bin BIN=${apps[$c]}
	let "c++"
done
