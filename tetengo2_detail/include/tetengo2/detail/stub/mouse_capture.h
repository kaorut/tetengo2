/*! \file
    \brief The definition of tetengo2::detail::stub::mouse_capture.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_MOUSECAPTURE_H)
#define TETENGO2_DETAIL_STUB_MOUSECAPTURE_H

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>


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
            boost::ignore_unused(widget);
        }


    };


}}}


#endif
