/*! \file
    \brief The definition of tetengo2::gui::message::paint_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_PAINTOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_PAINTOBSERVERSET_H

#include <algorithm>
#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp> // IWYU pragma: keep

#if !defined(IWYU)
namespace tetengo2 { namespace gui { namespace drawing {
    class canvas;
}}}
#endif


namespace tetengo2::gui::message {
    /*!
        \brief The class for a paint observer set.
    */
    class paint_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The canvas type.
        using canvas_type = gui::drawing::canvas;

        /*!
            \brief The observer type of paint-background.

            \param canvas A canvas.

            \retval true  When the background is painted by this observer
                          and it should not be painted by the system.
            \retval false Otherwise.
        */
        using paint_background_type = bool(canvas_type& canvas);

#if defined(DOCUMENTATION)
        //! The logical OR combiner type.
        struct logical_or_combiner;
#else
        struct logical_or_combiner
        {
            using result_type = bool;

            static bool is_true(bool b);

            template <typename InputIterator>
            bool operator()(InputIterator first, InputIterator last) const
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
        using paint_type = void(canvas_type& canvas);

        //! The signal type of paint.
        using paint_signal_type = boost::signals2::signal<paint_type>;


        // constructors and destructor

        /*!
            \brief Creates a paint observer set.
        */
        paint_observer_set();

        /*!
            \brief Destroys the paint observer set.
        */
        ~paint_observer_set();


        // functions

        /*!
            \brief Returns the observer called when the background of a canvas needs to be repainted.

            \return The observer called when the background of a canvas needs to be repainted.
        */
        const paint_background_signal_type& paint_background() const;

        /*!
            \brief Returns the observer called when the background of a canvas needs to be repainted.

            \return The observer called when the background of a canvas needs to be repainted.
        */
        paint_background_signal_type& paint_background();

        /*!
            \brief Returns the observer called when a canvas needs to be repainted.

            \return The observer called when a canvas needs to be repainted.
        */
        const paint_signal_type& paint() const;

        /*!
            \brief Returns the observer called when a canvas needs to be repainted.

            \return The observer called when a canvas needs to be repainted.
        */
        paint_signal_type& paint();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
