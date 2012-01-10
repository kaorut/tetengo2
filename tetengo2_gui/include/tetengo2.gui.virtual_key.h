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

        //! Returns the virtual key for BackSpace.
        //! \return The virtual key.
        static const virtual_key& backspace()
        {
            static const virtual_key singleton(details_type::backspace());
            return singleton;
        }

        //! Returns the virtual key for Tab.
        //! \return The virtual key.
        static const virtual_key& tab()
        {
            static const virtual_key singleton(details_type::tab());
            return singleton;
        }

        //! Returns the virtual key for Enter.
        //! \return The virtual key.
        static const virtual_key& enter()
        {
            static const virtual_key singleton(details_type::enter());
            return singleton;
        }

        //! Returns the virtual key for Shift.
        //! \return The virtual key.
        static const virtual_key& shift()
        {
            static const virtual_key singleton(details_type::shift());
            return singleton;
        }

        //! Returns the virtual key for Control.
        //! \return The virtual key.
        static const virtual_key& control()
        {
            static const virtual_key singleton(details_type::control());
            return singleton;
        }

        //! Returns the virtual key for Meta.
        //! \return The virtual key.
        static const virtual_key& meta()
        {
            static const virtual_key singleton(details_type::meta());
            return singleton;
        }

        //! Returns the virtual key for Escape.
        //! \return The virtual key.
        static const virtual_key& escape()
        {
            static const virtual_key singleton(details_type::escape());
            return singleton;
        }

        //! Returns the virtual key for Space.
        //! \return The virtual key.
        static const virtual_key& space()
        {
            static const virtual_key singleton(details_type::space());
            return singleton;
        }

        //! Returns the virtual key for PageUp.
        //! \return The virtual key.
        static const virtual_key& page_up()
        {
            static const virtual_key singleton(details_type::page_up());
            return singleton;
        }

        //! Returns the virtual key for PageDown.
        //! \return The virtual key.
        static const virtual_key& page_down()
        {
            static const virtual_key singleton(details_type::page_down());
            return singleton;
        }

        //! Returns the virtual key for End.
        //! \return The virtual key.
        static const virtual_key& end()
        {
            static const virtual_key singleton(details_type::end());
            return singleton;
        }

        //! Returns the virtual key for Home.
        //! \return The virtual key.
        static const virtual_key& home()
        {
            static const virtual_key singleton(details_type::home());
            return singleton;
        }

        //! Returns the virtual key for Left.
        //! \return The virtual key.
        static const virtual_key& left()
        {
            static const virtual_key singleton(details_type::left());
            return singleton;
        }

        //! Returns the virtual key for Up.
        //! \return The virtual key.
        static const virtual_key& up()
        {
            static const virtual_key singleton(details_type::up());
            return singleton;
        }

        //! Returns the virtual key for Right.
        //! \return The virtual key.
        static const virtual_key& right()
        {
            static const virtual_key singleton(details_type::right());
            return singleton;
        }

        //! Returns the virtual key for Down.
        //! \return The virtual key.
        static const virtual_key& down()
        {
            static const virtual_key singleton(details_type::down());
            return singleton;
        }

        //! Returns the virtual key for Insert.
        //! \return The virtual key.
        static const virtual_key& insert()
        {
            static const virtual_key singleton(details_type::insert());
            return singleton;
        }

        //! Returns the virtual key for Delete.
        //! \return The virtual key.
        static const virtual_key& del()
        {
            static const virtual_key singleton(details_type::del());
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
