/*! \file
    \brief The definition of tetengo2::detail::base::gui_fixture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_GUIFIXTURE_H)
#define TETENGO2_DETAIL_BASE_GUIFIXTURE_H

#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace detail { namespace base {
    /*!
        \brief The class for a detail implementation of a GUI fixture.
    */
    class gui_fixture : private boost::noncopyable
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


}}}


#endif
