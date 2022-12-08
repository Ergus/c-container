Readme
======

This is a simple project with some basic containers implemented in
C. The project is simple and contains just one header `c-container.h`
and the library `libcontainer.so`.

The main goal for this was to practice and test inheritance emulation
in C, this requires a compiler with support for `struct` extension in
C **-fms-extensions**.

But also create an entire example project including documentation
deployment with Doxygen, simple testing, and Coverage with github
actions.

The project page is automatically deployed with github action on:
[Project's github page](https://ergus.github.io/c-container/)

To build the library and the documentation just do:

```
make
```

Which will create the library `libcontainer.so` and a directory
`Doxygen` with html documentation extracted with `doxygen`. The
documentation creation only happen when `doxygen` is installed else,
you can directly read the comments in the header `c-container.h`.

To run the tests:

```
make check
```

The tests/example codes are in the `tests` directory and act also as
examples on how to use the data structures.

It is possible to check the coverage of the tests using **lcov**. To
do so you just need:

```
make coverage
```

This recompile all the files and execute all the test to generate the
trace files; then it process the trace with **lcov** and generate a
**coverage** directory with `genhtml` with the html files.

All these steps are automated also in the github action.

