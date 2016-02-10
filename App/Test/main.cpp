#include <string>
#include <iostream>
#include <Lib/CGNS.h>


int main( int argc, char** argv )
{
    std::string filename( argv[1] );
    local::CGNS cgns( filename.c_str() );
    cgns.print( std::cout );

    return 0;
}
