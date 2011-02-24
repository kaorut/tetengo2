/*! \file
    \brief The definition of tetengo2::gui::win32::gui_initializer_finalizer.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIINITIALIZERFINALIZER_H)
#define TETENGO2_GUI_GUIINITIALIZERFINALIZER_H

#include <boost/noncopyable.hpp>

namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a GUI fixture.

        \tparam FixtureDetailsTuple A detail implementation tuple type of a
                                    fixture.
    */
    template <typename FixtureDetailsTuple>
    class gui_initializer_finalizer : private boost::noncopyable
    {
    public:
        // types

        //! The detail implementation tuple type of a fixture.
        typedef FixtureDetailsTuple fixture_details_tuple_type;


        // constructors and destructor

        /*!
            \brief Creates a GUI fixture.
        */
        gui_initializer_finalizer()
        :
        m_fixture_details_tuple()
        {}


    private:
        // variables

        const fixture_details_tuple_type m_fixture_details_tuple;


    };


}}}

#endif
