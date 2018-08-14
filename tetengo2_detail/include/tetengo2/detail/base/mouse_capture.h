/*! \file
    \brief The definition of tetengo2::detail::base::mouse_capture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_MOUSECAPTURE_H)
#define TETENGO2_DETAIL_BASE_MOUSECAPTURE_H

#include <memory>

#include <boost/core/noncopyable.hpp>


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a mouse capture.
    */
    class mouse_capture : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a mouse capture.
        */
        mouse_capture();

        /*!
            \brief Destroys the detail implementation of a mouse capture.
        */
        virtual ~mouse_capture();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
