/*****************************************************************************/
/**
 *  @file   Section.h
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
#include <kvs/ValueArray>


namespace local
{

namespace cgns
{

class Zone;

class Section
{
public:
    typedef cgns::Zone Parent;

private:
    const Parent& m_parent;
    int m_index;
    std::string m_name;
    ElementType_t m_element_type;
    cgsize_t m_start_index;
    cgsize_t m_end_index;
    int m_last_boundary_index;
    int m_parent_flag;
    kvs::ValueArray<cgsize_t> m_elements;

public:
    Section( const Parent& parent );

    const Parent& parent() const { return m_parent; }
    int index() const { return m_index; }
    std::string name() const { return m_name; }
    ElementType_t elementType() const { return m_element_type; }
    std::string elementTypeName() const { return std::string(ElementTypeName[m_element_type]); }
    cgsize_t startIndex() const { return m_start_index; }
    cgsize_t endIndex() const { return m_end_index; }
    int lastBoundaryIndex() const { return m_last_boundary_index; }
    int parentFlag() const { return m_parent_flag; }
    const kvs::ValueArray<cgsize_t>& elements() const { return m_elements; }
    int npe( const ElementType_t type ) const { int n = 0; CGNS_CALL( cg_npe( type, &n ) ); return n; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const int sindex );
};

} // end of namespace cgns

} // end of namespace local
