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

objects := $(wildcard src/*.c)

tests_src := $(wildcard tests/*.c)
tests_exe := $(patsubst %.c,%.x,$(notdir $(tests_src)))

CFLAGS += -I. -g

all: libcontainer.so

libcontainer.o: $(objects)
	$(CC) $(CFLAGS) -c -Wall -Werror -I. -fpic -g $^ -o $@

%.so: %.o
	$(CC) $(CFLAGS) -shared $< -o $@

%.x: tests/%.c libcontainer.so
	$(CC) $(CFLAGS) $< -o $@ -L. -Wl,-rpath=. -lcontainer

.PHONY: check clean

clean:
	rm -rf *.o *.so *.x

check: $(tests_exe)
	for number in $^ ; do \
		echo "Testing: $${number}" ; \
		./$${number} ; \
	done
