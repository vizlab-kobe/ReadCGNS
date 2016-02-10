/*****************************************************************************/
/**
 *  @file   Field.cpp
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
#include "Field.h"
#include "CGNS.h"
#include "Base.h"
#include "Zone.h"
#include "Solution.h"


namespace local
{

namespace cgns
{

Field::Field( const cgns::Solution& parent ):
    m_parent( parent ),
    m_index( 0 ),
    m_data_type( DataTypeNull ),
    m_name( "" )
{
}

void Field::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Name: " << this->name() << std::endl;
    os << indent << "Data type name: " << this->dataTypeName() << std::endl;
}

bool Field::read( const int findex, const cgsize_t* range_min, const cgsize_t* range_max )
{
    const int handler = m_parent.parent().parent().parent().handler();
    const int bindex = m_parent.parent().parent().index();
    const int zindex = m_parent.parent().index();
    const int sindex = m_parent.index();
    m_index = findex;

    char name[128];
    CGNS_CALL( cg_field_info( handler, bindex, zindex, sindex, m_index,
                              &m_data_type, name ) );
    m_name = std::string( name );

    size_t size = 0;
    if ( m_parent.parent().type() == Structured )
    {
        size = range_max[0] * range_max[1] * range_max[2];
    }
    else if ( m_parent.parent().type() == Unstructured )
    {
        size = range_max[0];
    }

    if ( m_data_type == Integer )
    {
        kvs::ValueArray<kvs::Int32> values( size );
        CGNS_CALL( cg_field_read( handler, bindex, zindex, sindex, name,
                                  m_data_type, range_min, range_max, values.data() ) );
        m_values = values;
    }
    else if ( m_data_type == LongInteger )
    {
        kvs::ValueArray<kvs::Int64> values( size );
        CGNS_CALL( cg_field_read( handler, bindex, zindex, sindex, name,
                                  m_data_type, range_min, range_max, values.data() ) );
        m_values = values;
    }
    else if ( m_data_type == RealSingle )
    {
        kvs::ValueArray<kvs::Real32> values( size );
        CGNS_CALL( cg_field_read( handler, bindex, zindex, sindex, name,
                                  m_data_type, range_min, range_max, values.data() ) );
        m_values = values;
    }
    else if ( m_data_type == RealDouble )
    {
        kvs::ValueArray<kvs::Real64> values( size );
        CGNS_CALL( cg_field_read( handler, bindex, zindex, sindex, name,
                                  m_data_type, range_min, range_max, values.data() ) );
        m_values = values;
    }

    return true;
}

} // end of namespace cgns

} // end of namespace local
