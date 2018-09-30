# Perl is needed if you want to rebuild the mem_<lang>.exe binaries
PERL      = perl

UPX       = upx --8086 --best

COMPILER = watcom
#COMPILER  = turbocpp

EXTRA_CFLAGS = -DNEC98
EXTRA_AFLAGS = -DNEC98

!include "mkfiles\$(COMPILER).mak"
