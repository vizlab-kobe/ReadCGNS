/*****************************************************************************/
/**
 *  @file   Coord.h
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
#pragma once

#include "CGNSLib.h"
#include <iostream>
#include <string>
#include <kvs/Indent>
#include <kvs/AnyValueArray>


namespace ReadCGNS
{

namespace cgns
{

class Zone;

class Coord
{
public:
    typedef cgns::Zone Parent;

private:
    const Parent& m_parent;
    int m_index;
    DataType_t m_data_type;
    std::string m_name;
    kvs::AnyValueArray m_coords;

public:
    Coord( const Parent& parent );

    const Parent& parent() const { return m_parent; }
    int index() const { return m_index; }
    DataType_t dataType() const { return m_data_type; }
    std::string dataTypeName() const { return std::string( DataTypeName[m_data_type] ); }
    std::string name() const { return m_name; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const int cindex, const cgsize_t range_min, const cgsize_t range_max );
};

} // end of namespace cgns

} // end of namespace ReadCGNS
