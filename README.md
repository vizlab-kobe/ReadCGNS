# ReadCGNS
CGNS data reader for KVS.

## Requirements
The following libraries are required to build ReadCGNS.

* [KVS](https://github.com/naohisas/KVS)
* [CGNS](http://cgns.github.io)

## Build
First, the static library (libReadCGNS) should be compiled as follows:

    $ cd Lib
    $ ./kvsmake.py

Then, a test code can be compiled and executed as follows:

    $ cd App/Test
    $ kvsmake -G
    $ kvsmake
    $ ./Test data.cgns
