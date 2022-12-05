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

CFLAGS += -I. -g -fms-extensions -Wno-microsoft-anon-tag

all: libcontainer.so

%.o: src/%.c
	$(CC) $(CFLAGS) -c -Wall -Werror -fpic $^ -o $@

libcontainer.so: $(objects_obj)
	$(CC) $(CFLAGS) -shared $^ -o $@

%.x: tests/%.c libcontainer.so
	$(CC) $(CFLAGS) $^ -o $@ -L. -Wl,-rpath,. -lcontainer

# Doxygen rules conditionally.
ifneq (, $(shell which doxygen))
all: Doxygen

Doxygen: doxyfile.txt
	doxygen $^
endif

# PHONY rules
.PHONY: check clean

clean:
	rm -rf *.o *.so *.x Doxygen *.gcda *.gcno coverage.info

check: $(tests_exe)
	for number in $^ ; do \
		echo "Testing: $${number}" ; \
		./$${number} ; \
		echo "Returned: $$?" ; \
	done
