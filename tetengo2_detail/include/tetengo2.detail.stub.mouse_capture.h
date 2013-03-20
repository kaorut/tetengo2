/*! \file
    \brief The definition of tetengo2::detail::stub::mouse_capture.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_MOUSECAPTURE_H)
#define TETENGO2_DETAIL_STUB_MOUSECAPTURE_H

#include <boost/noncopyable.hpp>

#include "tetengo2.utility.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a mouse capture.
    */
    class mouse_capture : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a mouse capture.

            \tparam Widget A widget type.

            \param widget A widget.
        */
        template <typename Widget>
        explicit mouse_capture(const Widget& widget)
        {
            suppress_unused_variable_warning(widget);
        }


    };


}}}


#endif
