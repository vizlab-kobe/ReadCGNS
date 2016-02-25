#include <string>
#include <iostream>
#include <Lib/CGNSData.h>


int main( int argc, char** argv )
{
    std::string filename( argv[1] );
    ReadCGNS::CGNSData data( filename.c_str() );
    data.print( std::cout );

    return 0;
}
