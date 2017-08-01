/*! \file
    \brief The definition of tetengo2::gui::dimension.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <tetengo2/gui/dimension.h>


namespace tetengo2 { namespace gui
{
    dimension::dimension(value_type width, value_type height)
    :
    m_width(std::move(width)),
    m_height(std::move(height))
    {}

    bool operator==(const dimension& one, const dimension& another)
    {
        return one.m_width == another.m_width && one.m_height == another.m_height;
    }

    const dimension::value_type& dimension::width()
    const
    {
        return m_width;
    }

    const dimension::value_type& dimension::height()
    const
    {
        return m_height;
    }


}}
