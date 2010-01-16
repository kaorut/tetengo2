/*! \file
    \brief The definition of tetengo2::gui::recursive_menu_iterator.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_RECURSIVEMENUITERATOR_H)
#define TETENGO2_GUI_RECURSIVEMENUITERATOR_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class for a menu observer.
    */
    class recursive_menu_iterator
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a menu observer.
        */
        recursive_menu_iterator()
        {}

        /*!
            \brief Destroys the menu observer.
        */
        virtual ~recursive_menu_iterator()
        throw ()
        {}


        // functions


    };


}}

#endif
