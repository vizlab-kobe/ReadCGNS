/*****************************************************************************/
/**
 *  @file   Zone.cpp
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
#include "Zone.h"
#include "Base.h"
#include "CGNSData.h"


namespace ReadCGNS
{

namespace cgns
{

Zone::Zone( const Zone::Parent& parent ):
    m_parent( parent ),
    m_index( 0 ),
    m_id( 0.0 ),
    m_type( ZoneTypeNull ),
    m_name( "" ),
    m_index_dim( 0 )
{
}

size_t Zone::numberOfSizes() const
{
    if ( m_type == Structured )
    {
        if ( m_parent.cellDim() == 2 )
        {
            // 2D Structured
            // m_sizes[0]: NVertexI
            // m_sizes[1]: NVertexJ
            // m_sizes[2]: NCellI = NVertexI - 1
            // m_sizes[3]: NCellJ = NVertexJ - 1
            // m_sizes[4]: NBoundVertexI = 0
            // m_sizes[5]: NBoundVertexJ = 0
            return 6;
        }
        else if ( m_parent.cellDim() == 3 )
        {
            // 3D Structured
            // m_sizes[0]: NVertexI
            // m_sizes[1]: NVertexJ
            // m_sizes[2]: NVertexK
            // m_sizes[3]: NCellI = NVertexI - 1
            // m_sizes[4]: NCellJ = NVertexJ - 1
            // m_sizes[5]: NCellK = NVertexK - 1
            // m_sizes[6]: NBoundVertexI = 0
            // m_sizes[7]: NBoundVertexJ = 0
            // m_sizes[8]: NBoundVertexK = 0
            return 9;
        }
    }
    else if ( m_type ==  Unstructured )
    {
        // 2D/3D Unstructured
        // m_sizes[0]: NVertex
        // m_sizes[1]: NCell2D/NCell3D
        // m_sizes[2]: NBoundVertex
        return 3;
    }

    return 0;
}

void Zone::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Zone ID: " << this->id() << std::endl;
    os << indent << "Type: " << this->typeName() << std::endl;
    os << indent << "Name: " << this->name() << std::endl;
    os << indent << "Index dim.: " << this->indexDim() << std::endl;

    const size_t nsizes = this->numberOfSizes();
    for ( size_t i = 0; i < nsizes; i++ )
    {
        os << indent << "Size[" << i << "]: " << this->size(i) << std::endl;
    }

    os << indent << "Num. of grids: " << this->numberOfGrids() << std::endl;
    const size_t ngrids = this->numberOfGrids();
    for ( size_t i = 0; i < ngrids; i++ )
    {
        m_grids[i].print( os, indent.nextIndent() );
    }

    os << indent << "Num. of coords: " << this->numberOfCoords() << std::endl;
    const size_t ncoords = this->numberOfCoords();
    for ( size_t i = 0; i < ncoords; i++ )
    {
        m_coords[i].print( os, indent.nextIndent() );
    }

    os << indent << "Num. of sections: " << this->numberOfSections() << std::endl;
    const size_t nsections = this->numberOfSections();
    for ( size_t i = 0; i < nsections; i++ )
    {
        m_sections[i].print( os, indent.nextIndent() );
    }

    os << indent << "Num. of solutions: " << this->numberOfSolutions() << std::endl;
    const size_t nsolutions = this->numberOfSolutions();
    for ( size_t i = 0; i < nsolutions; i++ )
    {
        m_solutions[i].print( os, indent.nextIndent() );
    }
}

bool Zone::read( const int zindex )
{
    const int handler = m_parent.parent().handler();
    const int bindex = m_parent.index();
    m_index = zindex;

    CGNS_CALL( cg_zone_id( handler, bindex, m_index, &m_id ) );
    CGNS_CALL( cg_zone_type( handler, bindex, m_index, &m_type ) );

    char name[128];
    CGNS_CALL( cg_zone_read( handler, bindex, m_index, name, m_sizes ) );
    m_name = std::string( name );

    CGNS_CALL( cg_index_dim( handler, bindex, m_index, &m_index_dim ) );

    int ngrids = 0;
    CGNS_CALL( cg_ngrids( handler, bindex, m_index, &ngrids ) );
    for ( int i = 0; i < ngrids; i++ )
    {
        const int gindex = i + 1;
        cgns::Grid grid( *this );
        grid.read( gindex );
        m_grids.push_back( grid );
    }

    cgsize_t range_min[3] = { 1, 1, 1 };
    cgsize_t range_max[3] = { 1, 1, 1 };
    if ( m_type == Structured )
    {
        range_max[0] = m_sizes[0]; // dimi
        range_max[1] = m_sizes[1]; // dimj
        range_max[2] = m_sizes[2]; // dimk
    }
    else if ( m_type == Unstructured )
    {
        range_max[0] = m_sizes[0]; // nvertices
        range_max[1] = m_sizes[0]; // nvertices
        range_max[2] = m_sizes[0]; // nvertices
    }

    int ncoords = 0;
    CGNS_CALL( cg_ncoords( handler, bindex, m_index, &ncoords ) );
    for ( int i = 0; i < ncoords; i++ )
    {
        const int cindex = i + 1;
        cgns::Coord coord( *this );
        coord.read( cindex, range_min[i], range_max[i] );
        m_coords.push_back( coord );
    }

    int nsections = 0;
    CGNS_CALL( cg_nsections( handler, bindex, m_index, &nsections ) );
    for ( int i = 0; i < nsections; i++ )
    {
        const int sindex = i + 1;
        cgns::Section section( *this );
        section.read( sindex );
        m_sections.push_back( section );
    }

    int nsolutions = 0;
    CGNS_CALL( cg_nsols( handler, bindex, m_index, &nsolutions ) );
    for ( int i = 0; i < nsolutions; i++ )
    {
        const int sindex = i + 1;
        cgns::Solution solution( *this );
        solution.read( sindex );
        m_solutions.push_back( solution );
    }

    return true;
}

} // end of namespace cgns

} // end of namespace ReadCGNS
