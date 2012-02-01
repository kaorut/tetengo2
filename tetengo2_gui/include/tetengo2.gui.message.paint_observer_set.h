/*! \file
    \brief The definition of tetengo2::gui::message::paint_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_PAINTOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_PAINTOBSERVERSET_H

#include <algorithm>

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a paint observer set.

        \tparam Canvas A canvas type.
    */
    template <typename Canvas>
    class paint_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The canvas type.
        typedef Canvas canvas_type;

#if !defined(DOCUMENTATION)
        struct logical_or_combiner
        {
            typedef bool result_type;
            
            static bool is_true(bool b)
            {
                return b;
            }

            template <typename InputIterator>
            bool operator()(
                const InputIterator first,
                const InputIterator last
            )
            const
            {
                return std::any_of(first, last, is_true);
            }

        };
#endif

        /*!
            \brief The observer type of paint-background.

            \param canvas A canvas.

            \retval true  When the background is not painted by this observer
                          and it shoud be painted by the system.
            \retval false Otherwise.
        */
        typedef bool paint_background_type(canvas_type& canvas);

        //! The signal type of paint-background.
        typedef
            boost::signals2::signal<
                paint_background_type, logical_or_combiner
            >
            paint_background_signal_type;

        /*!
            \brief The observer type of paint.

            \param canvas A canvas.
        */
        typedef void paint_type(canvas_type& canvas);

        //! The signal type of paint.
        typedef boost::signals2::signal<paint_type> paint_signal_type;


        // functions

        /*!
            \brief Returns the observer called when the background of a canvas
                   needs to be repainted.

            \return The observer called when the background of a canvas needs
                    to be repainted.
        */
        const paint_background_signal_type& paint_background()
        const
        {
            return m_paint_background;
        }

        /*!
            \brief Returns the observer called when the background of a canvas
                   needs to be repainted.

            \return The observer called when the background of a canvas needs
                    to be repainted.
        */
        paint_background_signal_type& paint_background()
        {
            return m_paint_background;
        }

        /*!
            \brief Returns the observer called when a canvas needs to be
                   repainted.

            \return The observer called when a canvas needs to be repainted.
        */
        const paint_signal_type& paint()
        const
        {
            return m_paint;
        }

        /*!
            \brief Returns the observer called when a canvas needs to be
                   repainted.

            \return The observer called when a canvas needs to be repainted.
        */
        paint_signal_type& paint()
        {
            return m_paint;
        }


    private:
        // variables

        paint_background_signal_type m_paint_background;

        paint_signal_type m_paint;


    };


}}}


#endif
