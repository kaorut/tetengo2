/*! \file
    \brief The definition of tetengo2::gui::fixture.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_FIXTURE_H)
#define TETENGO2_GUI_FIXTURE_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a GUI fixture.

        \tparam FixtureDetails A detail implementation type of a fixture.
    */
    template <typename FixtureDetails>
    class fixture : private boost::noncopyable
    {
    public:
        // types

        //! The detail implementation type of a fixture.
        typedef FixtureDetails fixture_details_type;


        // constructors and destructor

        /*!
            \brief Creates a GUI fixture.
        */
        fixture()
        :
        m_fixture_details()
        {}


    private:
        // variables

        const fixture_details_type m_fixture_details;


    };


}}

#endif
