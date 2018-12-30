/*! \file
    \brief The definition of tetengo2::gui::fixture.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_FIXTURE_H)
#define TETENGO2_GUI_FIXTURE_H

#include <memory>

#include <boost/core/noncopyable.hpp>


namespace tetengo2::gui {
    /*!
        \brief The class for a GUI fixture.
    */
    class fixture : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a GUI fixture.
        */
        fixture();

        /*!
            \brief Destroys the GUI fixture.
        */
        ~fixture();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}

#endif
