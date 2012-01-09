/*! \file
    \brief The definition of tetengo2::gui::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_VIRTUALKEY_H)
#define TETENGO2_GUI_VIRTUALKEY_H

#include <utility>

#include <boost/noncopyable.hpp>


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

        //! The string type.
        typedef typename details_type::string_type string_type;


        // static functions

        //! Returns the virtual key for 'A'.
        //! \return The virtual key.
        static const virtual_key& char_a()
        {
            static const virtual_key singleton(details_type::char_a());
            return singleton;
        }


        // functions

        /*!
            \brief Returns the code.

            \return The code.
        */
        code_type code()
        const
        {
            return m_code;
        }

        /*!
            \brief Returns the string representation.

            \return The string representation.
        */
        const string_type& to_string()
        const
        {
            return m_string;
        }


    private:
        // types

        typedef
            typename details_type::code_and_string_type code_and_string_type;

        // constructors

        virtual_key(code_and_string_type&& code_and_string)
        :
        m_code(code_and_string.first),
        m_string(std::move(code_and_string.second))
        {}
        

        // variables

        const code_type m_code;

        const string_type m_string;


    };


}}


#endif
