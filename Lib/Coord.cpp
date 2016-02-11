/*****************************************************************************/
/**
 *  @file   Coord.cpp
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
#include "Coord.h"
#include "CGNSData.h"
#include "Base.h"
#include "Zone.h"


namespace local
{

namespace cgns
{

Coord::Coord( const Coord::Parent& parent ):
    m_parent( parent ),
    m_index( 0 ),
    m_data_type( DataTypeNull ),
    m_name( "" )
{
}

void Coord::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Data type: " << this->dataTypeName() << std::endl;
    os << indent << "Name: " << this->name() << std::endl;
}

bool Coord::read( const int cindex, const cgsize_t range_min, const cgsize_t range_max )
{
    const int handler = m_parent.parent().parent().handler();
    const int bindex = m_parent.parent().index();
    const int zindex = m_parent.index();
    m_index = cindex;

    char name[128];
    CGNS_CALL( cg_coord_info( handler, bindex, zindex, m_index, &m_data_type, name ) );
    m_name = std::string( name );

    const size_t n = range_max - range_min + 1;
    switch ( m_data_type )
    {
    case RealSingle:
    {
        kvs::ValueArray<kvs::Real32> coords( n );
        CGNS_CALL( cg_coord_read( handler, bindex, zindex,
                                  m_name.c_str(), m_data_type, &range_min, &range_max, coords.data() ) );
        m_coords = kvs::AnyValueArray( coords );
        break;
    }
    case RealDouble:
    {
        kvs::ValueArray<kvs::Real64> coords( n );
        CGNS_CALL( cg_coord_read( handler, bindex, zindex,
                                  m_name.c_str(), m_data_type, &range_min, &range_max, coords.data() ) );
        m_coords = kvs::AnyValueArray( coords );
        break;
    }
    default: break;
    }

    return true;
}

} // end of namespace cgns

} // end of namespace local
