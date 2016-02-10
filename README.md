# ReadCGNS
CGNS data reader for KVS.

## Requirements
The following libraries are required to build ReadCGNS.

* [KVS](https://github.com/naohisas/KVS)
* [CGNS](http://cgns.github.io)

## Build
ReadCGNS can be easily complied with Python script (kvsmake.py) as follows:

    $ cd Lib
    $ ./kvsmake.py

If Python has not been installed on your development environment, the library can be compiled with kvsmake command as follows:

    $ cd Lib
    $ kvsmake -g ReadCGNS
    $ kvsmake lib

## Test
After compiling ReadCGNS as static library, a test code can be compiled and executed as follows:

    $ cd App/Test
    $ kvsmake -G
    $ kvsmake
    $ ./Test data.cgns
