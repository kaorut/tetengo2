/*! \file
    \brief The definition of tetengo2::detail::windows::mouse_capture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MOUSECAPTURE_H)
#define TETENGO2_DETAIL_WINDOWS_MOUSECAPTURE_H

#include <memory>

#include <tetengo2/detail/base/mouse_capture.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a mouse capture.
    */
    class mouse_capture : public base::mouse_capture
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a mouse capture.

            \param widget A widget.
        */
        explicit mouse_capture(const gui::widget::widget& widget);

        /*!
            \brief Destroys the detail implementation of a mouse capture.
        */
        ~mouse_capture();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
