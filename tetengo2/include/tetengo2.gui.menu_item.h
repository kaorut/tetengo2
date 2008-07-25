/*! \file
    \brief The definition of tetengo2::gui::menu_item.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUITEM_H)
#define TETENGO2_GUI_MENUITEM_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.String.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class template for a menu item.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
   */
    template <typename String>
    class menu_item
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));


    public:
        // types

        //! The string type
        typedef String string_type;


        // constructors and destructor

        /*!
            \brief Destroys the menu item.
        */
        virtual ~menu_item()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the text.

            \return The text.
        */
        virtual const string_type& text()
        const
        {
            return m_text;
        }

        /*!
            \brief Sets the text.

            \param text A text.
        */
        virtual void set_text(const string_type& text)
        {
            m_text = text;
        }


    //protected:
        // constructors

        /*!
            \brief Creates a menu item.

            \param text A text.
        */
        menu_item(const string_type& text)
        :
        m_text(text)
        {}


    private:
        // variables

        string_type m_text;


    };


}}

#endif
