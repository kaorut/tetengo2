/*! \file
    \brief The definition of tetengo2::gui::paint_observer_set.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_PAINTOBSERVERSET_H)
#define TETENGO2_GUI_PAINTOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui
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

        //! \return The canvas type.
        typedef Canvas canvas_type;

        /*!
            \brief The observer type of paint.

            \param canvas A canvas.
        */
        typedef void paint_type(canvas_type& canvas);

        //! \return The signal type of paint.
        typedef boost::signals2::signal<paint_type> paint_signal_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer set.
        */
        paint_observer_set()
        :
        m_paint()
        {}

        /*!
            \brief Destroys the paint observer set.
        */
        ~paint_observer_set()
        throw ()
        {}


        // functions

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

        paint_signal_type m_paint;


    };


}}

#endif
