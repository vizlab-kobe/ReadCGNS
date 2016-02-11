/*****************************************************************************/
/**
 *  @file   Zone.h
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
#include "Grid.h"
#include "Coord.h"
#include "Section.h"
#include "Solution.h"
#include <iostream>
#include <string>
#include <vector>
#include <kvs/Indent>


namespace local
{

namespace cgns
{

class Base;

class Zone
{
public:
    typedef cgns::Base Parent;

private:
    const Parent& m_parent;
    int m_index;
    double m_id;
    ZoneType_t m_type;
    std::string m_name;
    cgsize_t m_sizes[9];
    int m_index_dim;
    std::vector<cgns::Grid> m_grids;
    std::vector<cgns::Coord> m_coords;
    std::vector<cgns::Section> m_sections;
    std::vector<cgns::Solution> m_solutions;

public:
    Zone( const Parent& parent );

    const Parent& parent() const { return m_parent; }
    int index() const { return m_index; }
    double id() const { return m_id; }
    std::string name() const { return m_name; }
    ZoneType_t type() const { return m_type; }
    std::string typeName() const { return std::string( ZoneTypeName[m_type] ); }
    int indexDim() const { return m_index_dim; }
    const std::vector<cgns::Grid>& grids() const { return m_grids; }
    const std::vector<cgns::Coord>& coords() const { return m_coords; }
    const std::vector<cgns::Section>& sections() const { return m_sections; }
    const std::vector<cgns::Solution>& solutions() const { return m_solutions; }
    const cgsize_t* sizes() const { return m_sizes; }
    const cgns::Grid& grid( const size_t index ) const { return m_grids[index]; }
    const cgns::Coord& coord( const size_t index ) const { return m_coords[index]; }
    const cgns::Section& section( const size_t index ) const { return m_sections[index]; }
    const cgns::Solution& solution( const size_t index ) const { return m_solutions[index]; }
    cgsize_t size( const size_t index ) const { return m_sizes[index]; }
    size_t numberOfGrids() const { return m_grids.size(); }
    size_t numberOfCoords() const { return m_coords.size(); }
    size_t numberOfSections() const { return m_sections.size(); }
    size_t numberOfSolutions() const { return m_solutions.size(); }
    size_t numberOfSizes() const;

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const int zindex );
};

} // end of namespace cgns

} // end of namespace local
