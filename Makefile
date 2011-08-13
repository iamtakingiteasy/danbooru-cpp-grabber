all: native

native:
	cd build-native; cmake .; make;

cross-win32:
	cd build-cross-win32; cmake .; make;

make-all: native cross-win32

clean:
	cd build-native; \
		make clean; true
	cd build-native; \
		rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
	rm -rf CMakeFiles CMakeCache.txt

clean-cross-win32:
	cd build-cross-win32; \
		make clean; true
	cd build-cross-win32; \
		rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
	rm -rf CMakeFiles CMakeCache.txt

clean-all: clean clean-cross-win32

commit:
	git add docs src
	git commit -a
	git push

