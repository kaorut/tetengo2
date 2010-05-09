/*! \file
    \brief The definition of tetengo2::gui::mouse_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MOUSEOBSERVER_H)
#define TETENGO2_GUI_MOUSEOBSERVER_H //!< !! Include Guard !!

#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class for a mouse observer.
    */
    class mouse_observer :
        public boost::signals::trackable, private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a mouse observer.
        */
        mouse_observer()
        {}

        /*!
            \brief Destroys the mouse observer.
        */
        virtual ~mouse_observer()
        throw ()
        {}


        // functions

        /*!
            \brief Called when the widget is clicked.
        */
        virtual void clicked()
        {}


    };


}}

#endif
