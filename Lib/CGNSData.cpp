/*****************************************************************************/
/**
 *  @file   CGNS.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "CGNSData.h"
#include "CGNSLib.h"
#include <kvs/Message>


namespace ReadCGNS
{

CGNSData::CGNSData():
    m_handler( 0 ),
    m_version( 0.0f )
{
}

CGNSData::CGNSData( const std::string& filename ):
    m_handler( 0 ),
    m_version( 0.0f )
{
    if ( !this->read( filename ) )
    {
        kvsMessageError("Can not read %s.", filename.c_str() );
    }
}

void CGNSData::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Version: " << this->version() << std::endl;

    os << indent << "Num. of bases: " << this->numberOfBases() << std::endl;
    const size_t nbases = this->numberOfBases();
    for ( int i = 0; i < nbases; i++ )
    {
        m_bases[i].print( os, indent.nextIndent() );
    }
}

bool CGNSData::read( const std::string& filename )
{
    const int mode = CG_MODE_READ;
    CGNS_CALL( cg_open( filename.c_str(), mode, &m_handler ) );

    CGNS_CALL( cg_version( m_handler, &m_version ) );

    int nbases = 0;
    CGNS_CALL( cg_nbases( m_handler, &nbases ) );
    for ( int i = 0; i < nbases; i++ )
    {
        const int bindex = i + 1;
        cgns::Base base( *this );
        base.read( bindex );
        m_bases.push_back( base );
    }

    CGNS_CALL( cg_close( m_handler ) );

    return true;
}

} // end of namespace ReadCGNS
