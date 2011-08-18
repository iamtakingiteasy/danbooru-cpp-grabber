all:

core:
	cd core; cmake .; make

modules:
	cd modules; cmake .; make

clean:
	cd core; make clean; true
	cd modules; make clean; true
	cd core; rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile config.h
	cd modules; rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile config.h

.PHONY: all core modules clean