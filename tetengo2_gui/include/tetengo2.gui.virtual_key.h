/*! \file
    \brief The definition of tetengo2::gui::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_VIRTUALKEY_H)
#define TETENGO2_GUI_VIRTUALKEY_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for virtual keys.

        \tparam Details A detail implementation type.
    */
    template <typename Details>
    class virtual_key
    {
    public:
        // types

        //! The detail implementation type.
        typedef Details details_type;

        //! The code type.
        typedef typename details_type::code_type code_type;


        // static functions

        //! Returns the key code for 'A'.
        //! \return The key code.
        static code_type char_a() { return details_type::char_a(); }


    };


}}


#endif
