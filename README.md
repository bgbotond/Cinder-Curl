Cinder-Curl
===========
This is the curl CinderBlock, designed for use with the open-source C++ library Cinder: http://libcinder.org

Integrates curl-7.27.0

#### OS X static libs

There's a duplicate symbol error during linking with the macports static libs.
This is a not so nice, but simple workaround to remove the object file from one
of the libraries.

	lipo -thin i386 libintl.a -output libintl-i386.a
	mkdir libintl-i386
	cd libintl-i386
	ar -x ../libintl-i386.a
	rm localcharset.o
	libtool -static *.o -o ../libintl-i386.a

	lipo -thin x86_64 libintl.a -output libintl-x86_64.a
	mkdir libintl-x86_64
	cd libintl-x86_64
	ar -x ../libintl-x86_64.a
	rm localcharset.o
	libtool  -static *.o -o ../libintl-x86_64.a

	lipo -create libintl-i386.a libintl-x86_64.a -output libintl.a


