/*! \file
    \brief The definition of tetengo2::gui::drawing::background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_BACKGROUND_H)
#define TETENGO2_GUI_DRAWING_BACKGROUND_H

#include <boost/noncopyable.hpp>

#include "tetengo2.cpp0x_keyword.h"


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a background.

        \tparam Handle A handle type.
    */
    template <typename Handle>
    class background : private boost::noncopyable
    {
    public:
        // types

        //! The handle type.
        typedef Handle handle_type;


        // constructors and destructor

        /*!
            \brief Destroys the background.
        */
        virtual ~background()
        TETENGO2_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the handle;

            \return The handle.
        */
        handle_type handle()
        const
        {
            return handle_impl();
        }


    protected:
        // constructors

        /*!
            \brief Creates a background.
        */
        background()
        {}


    private:
        // virtual functions

        virtual handle_type handle_impl()
        const = 0;


    };


}}}


#endif
