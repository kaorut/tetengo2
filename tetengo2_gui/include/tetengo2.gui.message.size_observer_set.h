/*! \file
    \brief The definition of tetengo2::gui::message::size_observer_set.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_SIZEOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_SIZEOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class for a size observer set.
    */
    class size_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of resized
        */
        typedef void resized_type();

        //! The signal type of resized.
        typedef boost::signals2::signal<resized_type> resized_signal_type;


        // functions

        /*!
            \brief Returns the observer called when a widget is resized.

            \return The observer called when a widget is resized.
        */
        const resized_signal_type& resized()
        const
        {
            return m_resized;
        }

        /*!
            \brief Returns the observer called when a widget is resized.

            \return The observer called when a widget is resized.
        */
        resized_signal_type& resized()
        {
            return m_resized;
        }


    private:
        // variables

        resized_signal_type m_resized;


    };


}}}


#endif
