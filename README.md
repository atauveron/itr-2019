# itr-2019

Tutorials/project for the ITR course (2019)

## Description

Source code is in the `src` directory.

This project makes extensive use of the Posix interface.

## Compilation

To compile, run `make` from the project root. Object files will be stored in the `build` directory, executable binaries in the `bin` directory.

This project is intended to be cross-compiled to an ARM board. Please set the compiler path (variable `CMP`) in accordance with your environment and settings. Support for C++11 is required.

## Documentation

Documentation for this project is generated automatically using [Doxygen](http://www.doxygen.nl/). At the root of the project, run `doxygen`.
