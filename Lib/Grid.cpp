/*****************************************************************************/
/**
 *  @file   Grid.cpp
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
#include "Grid.h"
#include "CGNSLib.h"
#include "CGNSData.h"
#include "Base.h"
#include "Zone.h"


namespace ReadCGNS
{

namespace cgns
{

Grid::Grid( const Grid::Parent& parent ):
    m_parent( parent ),
    m_index( 0 ),
    m_name( "" )
{
}

void Grid::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Name: " << this->name() << std::endl;
}

bool Grid::read( const int gindex )
{
    const int handler = m_parent.parent().parent().handler();
    const int bindex = m_parent.parent().index();
    const int zindex = m_parent.index();
    m_index = gindex;

    char name[128];
    CGNS_CALL( cg_grid_read( handler, bindex, zindex, m_index, name ) );
    m_name = std::string( name );
    return true;
}

} // end of namespace cgns

} // end of namespace ReadCGNS
