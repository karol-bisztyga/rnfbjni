#!/bin/bash

export IDS=$(adb devices -l | tail -n +2 | cut -d ' ' -f 1 | tail -n +1)
export ABIS=""

for ID in $IDS
do
	export ABIS="${ABIS} $(adb -s $ID shell getprop ro.product.cpu.abi)"
done


echo $ABIS

