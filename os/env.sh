#!/bin/bash
set -e
min_tool_ver()
{
if [ $# != 1 ]; then
	echo "Usage: $0 toolname" >&2
	exit 1
fi

case "$1" in
riscv64-linux-gnu-binutils)
	echo 2.39
	;;
riscv64-linux-gnu-gcc)
	echo 12.2.0
	;;
llvm)
	if [ "$SRCARCH" = s390 ]; then
		echo 15.0.0
	else
		echo 11.0.0
	fi
	;;
rustc)
	echo nightly-2023-10-09
	;;
bindgen)
	echo 0.65.1
	;;
cbindgen)
	echo 0.26.0
	;;
make)
	echo 4.4.1
	;;
bash)
	echo 5.2.21
	;;
*)
	echo "$1: unknown tool" >&2
	exit 1
	;;
esac
}
ver_check()
{
case $1 in 
rust)
	if ! type -p $2 &>/dev/null
	then 
		echo "ERROR: Cannot find $2 ($1)"; return 1; 
	fi
	v=$($2 --version 2>&1 | grep -E -o '[0-9]+\.[0-9\.]+[a-z]*' | head -n1)
	if [[ $3 != $v ]]
	then
		rustup override set $(min_tool_ver rustc)
	fi
	if !  rustup component list |  grep \
		"rust-src (installed)"  &>/dev/null 
	then
		rustup component add rust-src
	fi
	if !  rustup target list | grep \
		"riscv64gc-unknown-none-elf (installed)" &>/dev/null
	then
		rustup target add riscv64gc-unknown-none-elf
	fi
     printf "OK:    %-9s %-6s = $3\n" "$1" "$v"; return 0;
	;;

bindgen)
	if ! type -p $2 &>/dev/null
	then 
		cargo install --locked --version \
			$(min_tool_ver bindgen) bindgen-cli
	fi
	v=$($2 --version 2>&1 | grep -E -o '[0-9]+\.[0-9\.]+[a-z]*' | head -n1)
	if [[ $v != $3 ]]
	then
		cargo install --locked --version \
			$(min_tool_ver bindgen) bindgen-cli
	fi
     printf "OK:    %-9s %-6s = $3\n" "$1" "$v"; return 0;
	;;
cbindgen)
	if ! type -p $2 &>/dev/null
	then 
		cargo install --locked --version \
			$(min_tool_ver cbindgen) cbindgen
	fi
	v=$($2 --version 2>&1 | grep -E -o '[0-9]+\.[0-9\.]+[a-z]*' | head -n1)
	if [[ $v != $3 ]]
	then
		cargo install --locked --version \
			$(min_tool_ver cbindgen) bindgen
	fi
     printf "OK:    %-9s %-6s = $3\n" "$1" "$v"; return 0;
	;;

*)
   if ! type -p $2 &>/dev/null
   then 
     echo "ERROR: Cannot find $2 ($1)"; return 1; 
   fi
   v=$($2 --version 2>&1 | grep -E -o '[0-9]+\.[0-9\.]+[a-z]*' | head -n1)
   if printf '%s\n' $3 $v | sort --version-sort --check &>/dev/null
   then 
     printf "OK:    %-9s %-6s >= $3\n" "$1" "$v"; return 0;
   else 
     printf "ERROR: %-9s is TOO OLD ($3 or later required)\n" "$1"; 
     return 1; 
   fi
	;;
esac

}

ver_check rust   rustc $(min_tool_ver rustc )
ver_check bindgen   bindgen $(min_tool_ver bindgen )
ver_check cbindgen   cbindgen $(min_tool_ver cbindgen )
ver_check riscv64-linux-gnu-binutils riscv64-linux-gnu-as \
	$(min_tool_ver riscv64-linux-gnu-binutils)
ver_check riscv64-linux-gnu-gcc riscv64-linux-gnu-gcc \
	$(min_tool_ver riscv64-linux-gnu-gcc)
ver_check bash bash $(min_tool_ver bash)
ver_check make make $(min_tool_ver make)