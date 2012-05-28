/*! \file
    \brief The definition of tetengo2::gui::message::mouse_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_MOUSEOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_MOUSEOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/rational.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a mouse observer set.

        \tparam Difference A difference type.
    */
    template <typename Difference>
    class mouse_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The difference type.
        typedef Difference difference_type;

        /*!
            \brief The observer type of clicked.
        */
        typedef void clicked_type();

        //! The signal type of clicked.
        typedef boost::signals2::signal<clicked_type> clicked_signal_type;

        //! The mouse wheel delta type.
        typedef boost::rational<difference_type> delta_type;

        //! The mouse wheel direction type.
        enum direction_type
        {
            direction_vertical,   //!< Vertical.
            direction_horizontal, //!< Horizontal.
        };

        /*!
            \brief The observer type of wheeled.

            \param delta     A delta.
            \param direction A direction.
            \param shift     True when shift key is pressed.
            \param control   True when control key is pressed.
            \param meta      True when meta key is pressed.
        */
        typedef
            void wheeled_type(const delta_type& delta, direction_type direction, bool shift, bool control, bool meta);

        //! The signal type of wheeled.
        typedef boost::signals2::signal<wheeled_type> wheeled_signal_type;


        // functions

        /*!
            \brief Returns the observer called when a mouse button is clicked.

            \return The observer called when a mouse button is clicked.
        */
        const clicked_signal_type& clicked()
        const
        {
            return m_clicked;
        }

        /*!
            \brief Returns the observer called when a mouse button is clicked.

            \return The observer called when a mouse button is clicked.
        */
        clicked_signal_type& clicked()
        {
            return m_clicked;
        }

        /*!
            \brief Returns the observer called when a mouse wheel is wheeled.

            \return The observer called when a mouse wheel is wheeled.
        */
        const wheeled_signal_type& wheeled()
        const
        {
            return m_wheeled;
        }

        /*!
            \brief Returns the observer called when a mouse wheel is wheeled.

            \return The observer called when a mouse wheel is wheeled.
        */
        wheeled_signal_type& wheeled()
        {
            return m_wheeled;
        }


    private:
        // variables

        clicked_signal_type m_clicked;

        wheeled_signal_type m_wheeled;


    };


}}}


#endif
