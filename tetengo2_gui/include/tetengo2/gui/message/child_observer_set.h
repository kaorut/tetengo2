/*! \file
    \brief The definition of tetengo2::gui::message::child_observer_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_CHILDOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_CHILDOBSERVERSET_H

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a child observer set.

        \tparam Widget A widget type.
    */
    template <typename Widget>
    class child_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        using widget_type = Widget;

        /*!
            \brief The observer type of child creation.

            \param child A child.
        */
#if BOOST_VERSION_NUMBER(12, 0, 0) <= BOOST_COMP_MSVC && BOOST_COMP_MSVC < BOOST_VERSION_NUMBER(13, 0, 0)
        // Somehow Visual C++ 2013 won't compile the type alias.
        typedef void created_type(widget_type& child);
#else
        using created_type = void (widget_type& child);
#endif

        //! The signal type of child creation.
        using created_signal_type = boost::signals2::signal<created_type>;


        // functions

        /*!
            \brief Returns the observer called when a child is created.

            \return The observer called when a child is created.
        */
        const created_signal_type& created()
        const
        {
            return m_created;
        }

        /*!
            \brief Returns the observer called when a child is created.

            \return The observer called when a child is created.
        */
        created_signal_type& created()
        {
            return m_created;
        }


    private:
        // variables

        created_signal_type m_created;


    };


}}}


#endif
