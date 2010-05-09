/*! \file
    \brief The definition of tetengo2::gui::window_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WINDOWOBSERVER_H)
#define TETENGO2_GUI_WINDOWOBSERVER_H //!< !! Include Guard !!

#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class for a window observer.
    */
    class window_observer :
        public boost::signals::trackable, private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a window observer.
        */
        window_observer()
        {}

        /*!
            \brief Destroys the window observer.
        */
        virtual ~window_observer()
        throw ()
        {}


        // functions

        /*!
            \brief Called when the window is destroyed.
        */
        virtual void destroyed()
        {}


    };


}}

#endif
