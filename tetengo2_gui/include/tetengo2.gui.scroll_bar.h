/*! \file
    \brief The definition of tetengo2::gui::scroll_bar.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_SCROLLBAR_H)
#define TETENGO2_GUI_SCROLLBAR_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a scroll bar.

        \tparam Size A size type.
    */
    template <typename Size>
    class scroll_bar : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;


        // constructors and destructor

        /*!
            \brief Creates a scroll bar.
        */
        scroll_bar()
        {}


    };


}}

#endif
