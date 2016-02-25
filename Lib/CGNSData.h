/*****************************************************************************/
/**
 *  @file   CGNSData.h
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

#include "Base.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <kvs/Indent>


namespace ReadCGNS
{

class CGNSData
{
private:
    int m_handler;
    float m_version;
    std::vector<cgns::Base> m_bases;

public:
    CGNSData();
    CGNSData( const std::string& filename );

    int handler() const { return m_handler; }
    float version() const { return m_version; }
    size_t numberOfBases() const { return m_bases.size(); }
    const std::vector<cgns::Base>& bases() const { return m_bases; }
    const cgns::Base& base( const size_t index ) const { return m_bases[index]; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );
};

} // end of namespace ReadCGNS
