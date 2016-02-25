/*****************************************************************************/
/**
 *  @file   Section.cpp
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
#include "Section.h"
#include "CGNSData.h"
#include "Base.h"
#include "Zone.h"


namespace ReadCGNS
{

namespace cgns
{

Section::Section( const Section::Parent& parent ):
    m_parent( parent ),
    m_index( 0 ),
    m_name( "" ),
    m_element_type( ElementTypeNull ),
    m_start_index( 0 ),
    m_end_index( 0 ),
    m_last_boundary_index( 0 ),
    m_parent_flag( 0 )
{
}

void Section::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Name: " << this->name() << std::endl;
    os << indent << "Element type name: " << this->elementTypeName() << std::endl;
    os << indent << "Start index: " << this->startIndex() << std::endl;
    os << indent << "End index: " << this->endIndex() << std::endl;
    os << indent << "Last boundary index: " << this->lastBoundaryIndex() << std::endl;
    os << indent << "Parent flag: " << this->parentFlag() << std::endl;
    os << indent << "Element data size: " << this->elements().size() << std::endl;
}

bool Section::read( const int sindex )
{
    const int handler = m_parent.parent().parent().handler();
    const int bindex = m_parent.parent().index();
    const int zindex = m_parent.index();
    m_index = sindex;

    char name[128];
    CGNS_CALL( cg_section_read( handler, bindex, zindex, m_index,
                                name, &m_element_type,
                                &m_start_index, &m_end_index, &m_last_boundary_index,
                                &m_parent_flag ) );
    m_name = std::string( name );

    cgsize_t element_data_size = 0;
    CGNS_CALL( cg_ElementDataSize( handler, bindex, zindex, m_index, &element_data_size ) );

    m_elements.allocate( element_data_size );
    CGNS_CALL( cg_elements_read( handler, bindex, zindex, m_index, m_elements.data(), NULL ) );

    return true;
}

} // end of namespace cgns

} // end of namespace ReadCGNS
