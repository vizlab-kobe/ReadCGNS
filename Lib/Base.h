/*****************************************************************************/
/**
 *  @file   Base.h
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
#include <string>
#include <vector>
#include <iostream>
#include <kvs/Indent>
#include "Zone.h"


namespace ReadCGNS
{

class CGNSData;

namespace cgns
{

class Base
{
public:
    typedef ReadCGNS::CGNSData Parent;

private:
    const Parent& m_parent;
    int m_index;
    double m_id;
    std::string m_name;
    int m_cell_dim;
    int m_pyhs_dim;
    SimulationType_t m_simulation_type;
    std::vector<cgns::Zone> m_zones;

public:
    Base( const Parent& parent );

    const Parent& parent() const { return m_parent; }
    int index() const { return m_index; }
    double id() const { return m_id; }
    std::string name() const { return m_name; }
    int cellDim() const { return m_cell_dim; }
    int pyhsDim() const { return m_pyhs_dim; }
    SimulationType_t simulationType() const { return m_simulation_type; }
    std::string simulationTypeName() const { return std::string(SimulationTypeName[m_simulation_type]); }
    size_t numberOfZones() const { return m_zones.size(); }
    const std::vector<cgns::Zone>& zones() const { return m_zones; }
    const cgns::Zone& zone( const size_t index ) const { return m_zones[index]; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const int bindex );
};

} // end of namespace cgns

} // end of namespace ReadCGNS
