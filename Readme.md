Readme
======

Simple project with some basic containers implemented in C. The
project is simple and contains just a header `c-container.h` and the
library `libcontainer.so`.

This requires a compiler with support for `struct` extension in C
**-fms-extensions**.

To run the test just do:

```
make check
```

The tests/example codes are in the `tests` directory.

To build the library and the documentation only do:

```
make
```

Which will create the library `libcontainer.so` and a directory
`Doxygen` with html documentation extracted with `doxygen`. The
documentation creation only happen when `doxygen` is installed else,
you can directly read the comments in the header `c-container.h`.
