cmake_minimum_required(VERSION 3.6)
project(tshlab_handout)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    test.dSYM/Contents/Resources/DWARF/test
    test.dSYM/Contents/Info.plist
    config.h
    csapp.c
    csapp.h
    fork.c
    Makefile
    mycat.c
    myenv.c
    myintp.c
    myints.c
    myspin1.c
    myspin2.c
    mysplit.c
    mysplitp.c
    mytstpp.c
    mytstps.c
    README
    runtrace.c
    sdriver.c
    test
    test.c
    test.txt
    trace00.txt
    trace01.txt
    trace02.txt
    trace03.txt
    trace04.txt
    trace05.txt
    trace06.txt
    trace07.txt
    trace08.txt
    trace09.txt
    trace10.txt
    trace11.txt
    trace12.txt
    trace13.txt
    trace14.txt
    trace15.txt
    trace16.txt
    trace17.txt
    trace18.txt
    trace19.txt
    trace20.txt
    trace21.txt
    trace22.txt
    trace23.txt
    trace24.txt
    tsh.c
    tshref)

add_executable(tshlab_handout ${SOURCE_FILES})