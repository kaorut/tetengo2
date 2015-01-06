/*! \file
    \brief The definition of tetengo2::gui::message::paint_observer_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_PAINTOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_PAINTOBSERVERSET_H

#include <algorithm>

#include <boost/core/noncopyable.hpp>
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
        using canvas_type = Canvas;

        /*!
            \brief The observer type of paint-background.

            \param canvas A canvas.

            \retval true  When the background is painted by this observer
                          and it should not be painted by the system.
            \retval false Otherwise.
        */
        using paint_background_type = bool (typename paint_observer_set::canvas_type& canvas);

#if defined(DOCUMENTATION)
        //! The logical OR combiner type.
        struct logical_or_combiner;
#else
        struct logical_or_combiner
        {
            using result_type = bool;
            
            static bool is_true(bool b)
            {
                return b;
            }

            template <typename InputIterator>
            bool operator()(const InputIterator first, const InputIterator last)
            const
            {
                return std::any_of(first, last, is_true);
            }

        };
#endif

        //! The signal type of paint-background.
        using paint_background_signal_type = boost::signals2::signal<paint_background_type, logical_or_combiner>;

        /*!
            \brief The observer type of paint.

            \param canvas A canvas.
        */
        using paint_type = void (typename paint_observer_set::canvas_type& canvas);

        //! The signal type of paint.
        using paint_signal_type = boost::signals2::signal<paint_type>;


        // functions

        /*!
            \brief Returns the observer called when the background of a canvas needs to be repainted.

            \return The observer called when the background of a canvas needs to be repainted.
        */
        const paint_background_signal_type& paint_background()
        const
        {
            return m_paint_background;
        }

        /*!
            \brief Returns the observer called when the background of a canvas needs to be repainted.

            \return The observer called when the background of a canvas needs to be repainted.
        */
        paint_background_signal_type& paint_background()
        {
            return m_paint_background;
        }

        /*!
            \brief Returns the observer called when a canvas needs to be repainted.

            \return The observer called when a canvas needs to be repainted.
        */
        const paint_signal_type& paint()
        const
        {
            return m_paint;
        }

        /*!
            \brief Returns the observer called when a canvas needs to be repainted.

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
