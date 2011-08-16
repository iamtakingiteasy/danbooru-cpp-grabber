all: native

clean: clean-native


make-all: native cross-win32
clean-all: clean-native clean-cross-win32



native:
	cd build-native; cmake .; make

clean-native:
	cd build-native; make clean; true
	cd build-native; rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile



cross-win32:
	cd build-cross-win32; cmake .; cmake .; make # yep, twice

clean-cross-win32:
	cd build-cross-win32; make clean; true
	cd build-cross-win32; rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile

.PHONY: all clean make-all clean-all native clean-native cross-win32 clean-cross-win32