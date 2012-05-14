/*! \file
    \brief The definition of tetengo2::detail::stub::scroll.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_SCROLL_H)
#define TETENGO2_DETAIL_STUB_SCROLL_H

#include <memory>
#include <tuple>
#include <utility>

#include <boost/noncopyable.hpp>

#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a scroll.
    */
    class scroll : private boost::noncopyable
    {
    public:
        // types

        //! The scroll bar details type.
        typedef std::tuple<std::size_t, std::pair<std::size_t, std::size_t>, std::size_t> scroll_bar_details_type;

        //! The scroll bar details pointer type.
        typedef std::unique_ptr<scroll_bar_details_type> scroll_bar_details_ptr_type;


        // static functions

        /*!
            \brief Creates a scroll bar.

            \tparam Widget A widget type.

            \param widget A widget.

            \return A unique pointer to a scroll bar. 

            \throw std::system_error When a system cursor cannot be created.
        */
        template <typename Widget>
        scroll_bar_details_ptr_type create_scroll_bar(Widget& widget)
        {
            return tetengo2::make_unique<scroll_bar_details_type>(0, std::make_pair(0, 100), 10);
        }


    private:
        // static functions


        // forbidden operations

        scroll();


    };


}}}


#endif
