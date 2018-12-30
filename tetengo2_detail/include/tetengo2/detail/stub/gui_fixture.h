/*! \file
    \brief The definition of tetengo2::detail::stub::gui_fixture.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_GUIFIXTURE_H)
#define TETENGO2_DETAIL_STUB_GUIFIXTURE_H

#include <tetengo2/detail/base/gui_fixture.h>


namespace tetengo2::detail::stub {
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
            \brief Destroy the detail implementation of a GUI fixture.
        */
        virtual ~gui_fixture();
    };
}


#endif
