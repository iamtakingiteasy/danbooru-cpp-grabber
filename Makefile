all: native

native:
	cd build-native; cmake .; make;

clean:
	cd build-native; \
		make clean; true
	cd build-native; \
		rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
	rm -rf modules CMakeFiles CMakeCache.txt

commit:
	git add docs src
	git commit -a
	git push

