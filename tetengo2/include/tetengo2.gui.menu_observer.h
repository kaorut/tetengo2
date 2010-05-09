/*! \file
    \brief The definition of tetengo2::gui::menu_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUOBSERVER_H)
#define TETENGO2_GUI_MENUOBSERVER_H //!< !! Include Guard !!

#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class for a menu observer.
    */
    class menu_observer :
        public boost::signals::trackable, private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a menu observer.
        */
        menu_observer()
        {}

        /*!
            \brief Destroys the menu observer.
        */
        virtual ~menu_observer()
        throw ()
        {}


        // functions

        /*!
            \brief Called when the menu is selected.
        */
        virtual void selected()
        {}


    };


}}

#endif
