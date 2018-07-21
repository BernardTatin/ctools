cmake_minimum_required(VERSION 3.10)
project(ctools C)

set(CMAKE_C_STANDARD 11)

include_directories(hexdump/include)
include_directories(lib/include)
include_directories(lib/include/_compat)
include_directories(x-top/freebsd)
include_directories(x-top/include)
include_directories(x-top/solaris)

add_executable(ctools
        hexdump/include/file-reader.h
        hexdump/include/hexops.h
        hexdump/include/private-file-header.h
        hexdump/src/file-reader.c
        hexdump/src/hexdump.c
        hexdump/src/hexops.c
        lib/include/_compat/_stdbool.h
        lib/include/_compat/_stdint.h
        lib/include/basedef.h
        lib/include/clist.h
        lib/include/compat.h
        lib/include/rbuffer.h
        lib/src/clist.c
        lib/src/rbuffer.c
        meltdown-spectre/meltdown-spectre.c
        read-files-perfs/main.c
        x-top/freebsd/compat.h
        x-top/include/solar-infos.h
        x-top/include/Xconf.h
        x-top/include/Xhelper.h
        x-top/solaris/compat.h
        x-top/src/solar-infos.c
        x-top/src/x-top.c
        x-top/src/Xconf.c
        x-top/src/Xhelper.c)
