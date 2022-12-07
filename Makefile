# Copyright (C) 2022  Jimmy Aguilar Mena

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

objects_src := $(wildcard src/*.c)
objects_obj := $(patsubst %.c,%.o,$(notdir $(objects_src)))

tests_src := $(wildcard tests/*.c)
tests_exe := $(patsubst %.c,%.x,$(notdir $(tests_src)))

CFLAGS += -I. -g -fms-extensions -Wno-microsoft-anon-tag -Wall -Werror

all: libcontainer.so

# Objects
%.o: src/%.c
	$(CC) $(CFLAGS) -c -fpic $^ -o $@

# Shared libraries (using fancy variables)
libcontainer.so: $(objects_obj)
%.so:
	$(CC) $(CFLAGS) -shared $^ -o $@

# Executables
%.x: tests/%.c libcontainer.so
	$(CC) $(CFLAGS) $^ -o $@ -L. -Wl,-rpath,. -lcontainer

# Coveralls
coverage.info: CFLAGS += --coverage

coverage.info: clean check
	lcov --capture --directory . --output-file coverage.info

coverage: coverage.info
	genhtml coverage.info --output-directory $@


# Doxygen rules conditionally.
ifneq (, $(shell which doxygen))
all: Doxygen

Doxygen: doxyfile.txt
	doxygen $^
endif

# PHONY rules
.PHONY: check clean

clean:
	rm -rf *.{,s}o $(tests_exe) Doxygen *.gc{da,no} coverage*

FAIL=\033[0;31m FAIL\033[0m
OK=\033[0;32m OK\033[0m

check: $(tests_exe)
	@(for number in $^ ; do \
		echo -n "Testing: $${number}" ; \
		./$${number} ; \
		[[ $$? == 0 ]] && echo -e "$(OK)" || echo -e "$(FAIL)" ; \
	done)
