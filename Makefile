all: native-core native-modules

clean: native-clean



cross-win: cross-win-core cross-win-modules

cross-clean: cross-win-clean




native-core:
	cd build-native; make core

native-modules:
	cd build-native; make modules

native-clean:
	cd build-native; make clean




cross-win-core:
	cd build-cross-win; make core

cross-win-modules:
	cd build-cross-win; make modules

cross-win-clean:
	cd build-cross-win; make clean