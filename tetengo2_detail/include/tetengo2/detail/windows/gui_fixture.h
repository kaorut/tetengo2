/*! \file
    \brief The definition of tetengo2::detail::windows::gui_fixture.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GUIFIXTURE_H)
#define TETENGO2_DETAIL_WINDOWS_GUIFIXTURE_H

#include <memory>
#include <system_error>

#include <tetengo2/detail/base/gui_fixture.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a GUI fixture.
    */
    class gui_fixture : public base::gui_fixture
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a GUI fixture.

            \throw std::system_error When an initialization fails.
        */
        gui_fixture();

        /*!
            \brief Destroys the detail implementation of a GUI fixture.
        */
        virtual ~gui_fixture();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}}


#endif
