/*****************************************************************************/
/**
 *  @file   Solution.cpp
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
#include "Solution.h"
#include "CGNSData.h"
#include "Base.h"
#include "Zone.h"


namespace ReadCGNS
{

namespace cgns
{

Solution::Solution( const Solution::Parent& parent ):
    m_parent( parent ),
    m_index( 0 ),
    m_name( "" ),
    m_grid_location( GridLocationNull )
{
}

void Solution::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Name: " << this->name() << std::endl;
    os << indent << "Grid location: " << this->gridLocationName() << std::endl;

    os << indent << "Num. of fields: " << this->numberOfFields() << std::endl;
    const size_t nfields = this->numberOfFields();
    for ( size_t i = 0; i < nfields; i++ )
    {
        m_fields[i].print( os, indent.nextIndent() );
    }
}

bool Solution::read( const int sindex )
{
    const int handler = m_parent.parent().parent().handler();
    const int bindex = m_parent.parent().index();
    const int zindex = m_parent.index();
    m_index = sindex;

    char name[128];
    CGNS_CALL( cg_sol_info( handler, bindex, zindex, m_index, name, &m_grid_location ) );
    m_name = std::string( name );

    cgsize_t range_min[3] = { 1, 1, 1 };
    cgsize_t range_max[3] = { 1, 1, 1 };
    if ( m_parent.type() == Structured )
    {
        if ( m_grid_location == Vertex )
        {
            if ( m_parent.parent().cellDim() == 1 )
            {
                range_max[0] = m_parent.size(0);
            }
            else if ( m_parent.parent().cellDim() == 2 )
            {
                range_max[0] = m_parent.size(0);
                range_max[1] = m_parent.size(1);
            }
            else
            {
                range_max[0] = m_parent.size(0);
                range_max[1] = m_parent.size(1);
                range_max[2] = m_parent.size(2);
            }
        }
        else
        {
            if ( m_parent.parent().cellDim() == 1 )
            {
                range_max[0] = m_parent.size(1);
            }
            else if ( m_parent.parent().cellDim() == 2 )
            {
                range_max[0] = m_parent.size(2);
                range_max[1] = m_parent.size(3);
            }
            else
            {
                range_max[0] = m_parent.size(3);
                range_max[1] = m_parent.size(4);
                range_max[2] = m_parent.size(5);
            }
        }
    }
    else if ( m_parent.type() == Unstructured )
    {
        if ( m_grid_location == Vertex )
        {
            range_max[0] = m_parent.size(0);
        }
        else
        {
            range_max[0] = m_parent.size(1);
        }
    }

    int nfields = 0;
    CGNS_CALL( cg_nfields( handler, bindex, zindex, m_index, &nfields ) );
    for ( int i = 0; i < nfields; i++ )
    {
        const int findex = i + 1;
        cgns::Field field( *this );
        field.read( findex, range_min, range_max );
        m_fields.push_back( field );
    }

    return true;
}

} // end of namespace cgns

} // end of namespace ReadCGNS
