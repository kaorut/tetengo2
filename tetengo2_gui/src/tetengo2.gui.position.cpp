/*! \file
    \brief The definition of tetengo2::gui::position.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <tetengo2/gui/position.h>


namespace tetengo2 { namespace gui
{
    position::position(value_type left, value_type top)
    :
    m_left(std::move(left)),
    m_top(std::move(top))
    {}


}}
