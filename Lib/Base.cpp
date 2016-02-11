/*****************************************************************************/
/**
 *  @file   Base.cpp
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
#include "Base.h"
#include "CGNSData.h"


namespace local
{

namespace cgns
{

Base::Base( const Base::Parent& parent ):
    m_parent( parent ),
    m_index( 0 ),
    m_id( 0.0 ),
    m_name( "" ),
    m_cell_dim( 0 ),
    m_pyhs_dim( 0 ),
    m_simulation_type( SimulationTypeNull )
{
}

void Base::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Base ID: " << this->id() << std::endl;
    os << indent << "Name: " << this->name() << std::endl;
    os << indent << "Cell dim: " << this->cellDim() << std::endl;
    os << indent << "Pyhs dim: " << this->pyhsDim() << std::endl;
    os << indent << "Simulation type: " << this->simulationTypeName() << std::endl;

    os << indent << "Num. of zones: " << this->numberOfZones() << std::endl;
    const size_t nzones = this->numberOfZones();
    for ( int i = 0; i < nzones; i++ )
    {
        m_zones[i].print( os, indent.nextIndent() );
    }
}

bool Base::read( const int bindex )
{
    const int handler = m_parent.handler();
    m_index = bindex;

    CGNS_CALL( cg_base_id( handler, m_index, &m_id ) );

    char name[128];
    CGNS_CALL( cg_base_read( handler, m_index, name, &m_cell_dim, &m_pyhs_dim ) );
    m_name = std::string( name );

    CGNS_CALL( cg_simulation_type_read( handler, m_index, &m_simulation_type ) );

    int nzones = 0;
    CGNS_CALL( cg_nzones( handler, m_index, &nzones ) );
    for ( int i = 0; i < nzones; i++ )
    {
        const int zindex = i + 1;
        cgns::Zone zone( *this );
        zone.read( zindex );
        m_zones.push_back( zone );
    }

    return true;
}

} // end of namespace cgns

} // end of namespace local
