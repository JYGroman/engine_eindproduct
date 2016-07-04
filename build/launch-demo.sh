#!/bin/sh
bindir=$(pwd)
cd /home/yorel/Documents/AlfaCollege/Jaar3/MakeMake/framework_yorel/demo/
export LD_LIBRARY_PATH=:$LD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /home/yorel/Documents/AlfaCollege/Jaar3/MakeMake/framework_yorel/build/demo 
	else
		"/home/yorel/Documents/AlfaCollege/Jaar3/MakeMake/framework_yorel/build/demo"  
	fi
else
	"/home/yorel/Documents/AlfaCollege/Jaar3/MakeMake/framework_yorel/build/demo"  
fi
