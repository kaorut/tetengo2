/*! \file
    \brief The definition of tetengo2::gui::fixture.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/fixture.h>


namespace tetengo2::gui {
    class fixture::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        impl() : m_p_fixture_details{ detail::gui_detail_impl_set().create_gui_fixture() } {}


    private:
        // variables

        std::unique_ptr<detail::base::gui_fixture> m_p_fixture_details;
    };


    fixture::fixture() : m_p_impl{ std::make_unique<impl>() } {}

    fixture::~fixture() = default;
}
