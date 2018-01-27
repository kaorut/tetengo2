/*! \file
    \brief The definition of tetengo2::gui::fixture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_FIXTURE_H)
#define TETENGO2_GUI_FIXTURE_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_fixture.h>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for a GUI fixture.
    */
    class fixture : private boost::noncopyable
    {
    public:
        // types

        //! The fixture details type.
        using fixture_details_type = detail::base::gui_fixture;


        // constructors and destructor

        /*!
            \brief Creates a GUI fixture.

            \param p_fixture_details A unique pointer to a detail implementation of a fixture.
        */
        explicit fixture(std::unique_ptr<fixture_details_type> p_fixture_details);

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


}}

#endif
