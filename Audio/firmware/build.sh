#!/bin/bash

if [ -f "toolpath" ]; then
	toolPath=$(cat toolpath)
	PATH="$toolPath:$PATH"
fi

build()
{
	mayskip=1
	for s in $sources; do
		if [[ ! -f "$out.elf" ]] || [[ "$s" -nt "$out.elf" ]]; then
			mayskip=0
		fi
	done

	if [[ $mayskip == 1 ]]; then
		return
	fi

	objdir=$(dirname $out)
	objs=""
	count=0
	for s in $sources; do
		ext=$(echo $s | sed -E 's/^.*\.([a-zA-Z]+)$/\1/')
		case $ext in
			c )
			lang="c -std=c99"
				;;
			cpp )
			lang="c++"
				;;
			s )
			lang=assembler
				;;
			S )
			lang=assembler-with-cpp
				;;
		esac
		f=$(basename $s | sed -E 's/(^.*)\.[a-zA-Z]+$/\1/')
		o="$objdir/$count-$f.o"
		count=$(($count + 1))

		echo "Building $s"
		arm-none-eabi-gcc $codegen -DPART=lpc1343 -I . -o $o -x $lang -c $s

			if [ $? -ne 0 ]; then
				exit -1
			fi
		objs="$objs $o"
	done

	echo Linking...
	arm-none-eabi-gcc $codegen -T $linkerFile -o $out.elf $objs

	if [ $? == 0 ]; then
		
		echo "addr  length  F  name" > $out.elf.memmap.txt
		echo "---- -------- - -------------------------------" >> $out.elf.memmap.txt
		arm-none-eabi-nm -Sn $out.elf | grep -E "^1000" | arm-none-eabi-c++filt >> $out.elf.memmap.txt
		
		arm-none-eabi-objcopy -j .text -j .data -O binary $out.elf $out.unsigned.bin
		/usr/local/bin/node cortex-checksum.js < $out.unsigned.bin > $out.bin
		arm-none-eabi-objdump -d $out.elf > $out.disasm.txt

		arm-none-eabi-size $out.elf
	fi
}


linkerFile="LPC1343.x"

codegen="-Wall -Wextra -Wno-switch -nostdlib -nodefaultlibs -fno-exceptions -g -Os -mthumb -march=armv7-m -mcpu=cortex-m3 -Wno-attributes"

mkdir -p out

out="out/receiver"
sources="\
GalagoAPI.cpp \
LPC13xx.cpp \
receiver.cpp \
"

build

out="out/transmitter"
sources="\
GalagoAPI.cpp \
LPC13xx.cpp \
transmitter.cpp \
"

build

out="out/usb-charge"
sources="\
GalagoAPI.cpp \
LPC13xx.cpp \
usb-charge.cpp \
"

build

out="out/timer"
sources="\
GalagoAPI.cpp \
LPC13xx.cpp \
timer.cpp \
"

build

out="out/beacon"
sources="\
GalagoAPI.cpp \
LPC13xx.cpp \
beacon.cpp \
"

build

out="out/playabeats-selftest"
sources="\
GalagoAPI.cpp \
LPC13xx.cpp \
playabeats-selftest.cpp \
"

build
