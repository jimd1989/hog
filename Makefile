.POSIX:
PREFIX = /usr/local

.SUFFIXES:
all:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic src/midi/*.c src/synth/*.c src/utils/*.c src/main.c -o "hog"
quick:
	cc src/midi/*.c src/synth/*.c src/utils/*.c src/main.c -o "hog"
	./hog
	rm hog
test:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -DTEST src/midi/*.c src/synth/*.c src/utils/*.c src/tests/*.c src/main.c -o "hog_test"
	./hog_test
	rm hog_test
