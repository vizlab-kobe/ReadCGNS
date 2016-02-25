/*****************************************************************************/
/**
 *  @file   Grid.h
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

#include <iostream>
#include <string>
#include <kvs/Indent>


namespace ReadCGNS
{

namespace cgns
{

class Zone;

class Grid
{
public:
    typedef cgns::Zone Parent;

private:
    const Parent& m_parent;
    int m_index;
    std::string m_name;

public:
    Grid( const cgns::Zone& parent );

    const Parent& parent() const { return m_parent; }
    int index() const { return m_index; }
    std::string name() const { return m_name; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const int gindex );
};

} // end of namespace cgns

} // end of namespace ReadCGNS
