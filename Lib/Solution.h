/*****************************************************************************/
/**
 *  @file   Solution.h
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
#include "Field.h"
#include <iostream>
#include <string>
#include <vector>
#include <kvs/Indent>
#include <kvs/ValueArray>


namespace local
{

namespace cgns
{

class Zone;

class Solution
{
public:
    typedef cgns::Zone Parent;

private:
    const Parent& m_parent;
    int m_index;
    std::string m_name;
    GridLocation_t m_grid_location;
    std::vector<cgns::Field> m_fields;

public:
    Solution( const Parent& parent );

    const Parent& parent() const { return m_parent; }
    int index() const { return m_index; }
    std::string name() const { return m_name; }
    GridLocation_t gridLocation() const { return m_grid_location; }
    std::string gridLocationName() const { return std::string(GridLocationName[m_grid_location]); }
    const std::vector<cgns::Field>& fields() const { return m_fields; }
    const cgns::Field& field( const size_t index ) const { return m_fields[index]; }
    size_t numberOfFields() const { return m_fields.size(); }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const int sindex );
};

} // end of namespace cgns

} // end of namespace local
