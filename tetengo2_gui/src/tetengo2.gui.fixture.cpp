/*! \file
    \brief The definition of tetengo2::gui::fixture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/fixture.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui {
    class fixture::impl : private boost::noncopyable
    {
    public:
        // types

        using fixture_details_type = fixture::fixture_details_type;


        // constructors and destructor

        explicit impl(std::unique_ptr<fixture_details_type> p_fixture_details)
        : m_p_fixture_details(std::move(p_fixture_details))
        {}


    private:
        // variables

        std::unique_ptr<fixture_details_type> m_p_fixture_details;
    };


    fixture::fixture(std::unique_ptr<fixture_details_type> p_fixture_details)
    : m_p_impl(stdalt::make_unique<impl>(std::move(p_fixture_details)))
    {}

    fixture::~fixture() = default;


}}
