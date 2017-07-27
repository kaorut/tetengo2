/*! \file
    \brief The definition of tetengo2::detail::base::gui_fixture.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace base
{
    class gui_fixture::impl : private boost::noncopyable
    {};


    gui_fixture::gui_fixture()
    :
    m_p_impl(stdalt::make_unique<impl>())
    {}

    gui_fixture::~gui_fixture()
    = default;


}}}
