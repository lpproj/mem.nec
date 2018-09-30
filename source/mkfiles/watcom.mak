#
# WATCOM.MAK - MEM copiler options for OpenWatcom 1.3
#

CC  = wcl
CFLAGS        = -zq -fr -c -j -wx -ms -oahls -s
CFLAGS_DEBUG  = -zq -c -j -wx -ms -oahls -s -d2
LFLAGS        = -zq -fm -"option statics"
LFLAGS_DEBUG  = -zq -fm -"option statics" -"debug all"
MEMSUPT       =
OBJOUT        = -fo=
EXEOUT        = -fe=
# This is similar to GNU Make's .PHONY except it's used as a dependency and
# not a target
SYMBOLIC      = .SYMBOLIC