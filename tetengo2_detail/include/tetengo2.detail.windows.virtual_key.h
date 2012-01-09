/*! \file
    \brief The definition of tetengo2::detail::windows::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_VIRTUALKEY_H)
#define TETENGO2_DETAIL_WINDOWS_VIRTUALKEY_H

#include <utility>

#include <boost/noncopyable.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.text.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class template for a detail implementation of virtual keys.

        \tparam String A string type.
    */
    template <typename String>
    class virtual_key : private boost::noncopyable
    {
    public:
        // types

        //! The code type.
        typedef unsigned char code_type;

        //! The string type.
        typedef String string_type;

        //! The code and string type.
        typedef std::pair<code_type, string_type> code_and_string_type;


        // static functions

        //! Returns the key code and string for BackSpace.
        //! \return The key code and string.
        static code_and_string_type backspace()
        {
            return code_and_string_type(
                VK_BACK, string_type(TETENGO2_TEXT("BackSpace"))
            );
        }

        //! Returns the key code and string for Tab.
        //! \return The key code and string.
        static code_and_string_type tab()
        {
            return code_and_string_type(
                VK_TAB, string_type(TETENGO2_TEXT("Tab"))
            );
        }

        //! Returns the key code and string for Enter.
        //! \return The key code and string.
        static code_and_string_type enter()
        {
            return code_and_string_type(
                VK_RETURN, string_type(TETENGO2_TEXT("Enter"))
            );
        }

        //! Returns the key code and string for Shift.
        //! \return The key code and string.
        static code_and_string_type shift()
        {
            return code_and_string_type(
                VK_SHIFT, string_type(TETENGO2_TEXT("Shift"))
            );
        }

        //! Returns the key code and string for Control.
        //! \return The key code and string.
        static code_and_string_type control()
        {
            return code_and_string_type(
                VK_CONTROL, string_type(TETENGO2_TEXT("Ctrl"))
            );
        }

        //! Returns the key code and string for Meta.
        //! \return The key code and string.
        static code_and_string_type meta()
        {
            return code_and_string_type(
                VK_MENU, string_type(TETENGO2_TEXT("Alt"))
            );
        }

        //! Returns the key code and string for Escape.
        //! \return The key code and string.
        static code_and_string_type escape()
        {
            return code_and_string_type(
                VK_ESCAPE, string_type(TETENGO2_TEXT("Esc"))
            );
        }

        //! Returns the key code and string for Space.
        //! \return The key code and string.
        static code_and_string_type space()
        {
            return code_and_string_type(
                VK_SPACE, string_type(TETENGO2_TEXT("Space"))
            );
        }

        //! Returns the key code and string for PageUp.
        //! \return The key code and string.
        static code_and_string_type page_up()
        {
            return code_and_string_type(
                VK_PRIOR, string_type(TETENGO2_TEXT("PageUp"))
            );
        }

        //! Returns the key code and string for PageDown.
        //! \return The key code and string.
        static code_and_string_type page_down()
        {
            return code_and_string_type(
                VK_NEXT, string_type(TETENGO2_TEXT("PageDown"))
            );
        }

        //! Returns the key code and string for End.
        //! \return The key code and string.
        static code_and_string_type end()
        {
            return code_and_string_type(
                VK_END, string_type(TETENGO2_TEXT("End"))
            );
        }

        //! Returns the key code and string for Home.
        //! \return The key code and string.
        static code_and_string_type home()
        {
            return code_and_string_type(
                VK_HOME, string_type(TETENGO2_TEXT("Home"))
            );
        }

        //! Returns the key code and string for Left.
        //! \return The key code and string.
        static code_and_string_type left()
        {
            return code_and_string_type(
                VK_LEFT, string_type(TETENGO2_TEXT("Left"))
            );
        }

        //! Returns the key code and string for Right.
        //! \return The key code and string.
        static code_and_string_type right()
        {
            return code_and_string_type(
                VK_RIGHT, string_type(TETENGO2_TEXT("Right"))
            );
        }

        //! Returns the key code and string for Up.
        //! \return The key code and string.
        static code_and_string_type up()
        {
            return code_and_string_type(
                VK_UP, string_type(TETENGO2_TEXT("Up"))
            );
        }

        //! Returns the key code and string for Down.
        //! \return The key code and string.
        static code_and_string_type down()
        {
            return code_and_string_type(
                VK_DOWN, string_type(TETENGO2_TEXT("Down"))
            );
        }

        //! Returns the key code and string for Insert.
        //! \return The key code and string.
        static code_and_string_type up()
        {
            return code_and_string_type(
                VK_INSERT, string_type(TETENGO2_TEXT("Ins"))
            );
        }

        //! Returns the key code and string for Delete.
        //! \return The key code and string.
        static code_and_string_type del()
        {
            return code_and_string_type(
                VK_DELETE, string_type(TETENGO2_TEXT("Del"))
            );
        }

        //! Returns the key code and string for '0'.
        //! \return The key code and string.
        static code_and_string_type char_0()
        {
            return code_and_string_type('0', string_type(TETENGO2_TEXT("0")));
        }

        //! Returns the key code and string for '1'.
        //! \return The key code and string.
        static code_and_string_type char_1()
        {
            return code_and_string_type('1', string_type(TETENGO2_TEXT("1")));
        }

        //! Returns the key code and string for 'A'.
        //! \return The key code and string.
        static code_and_string_type char_2()
        {
            return code_and_string_type('2', string_type(TETENGO2_TEXT("2")));
        }

        //! Returns the key code and string for '3'.
        //! \return The key code and string.
        static code_and_string_type char_3()
        {
            return code_and_string_type('3', string_type(TETENGO2_TEXT("3")));
        }

        //! Returns the key code and string for '4'.
        //! \return The key code and string.
        static code_and_string_type char_4()
        {
            return code_and_string_type('4', string_type(TETENGO2_TEXT("4")));
        }

        //! Returns the key code and string for '5'.
        //! \return The key code and string.
        static code_and_string_type char_5()
        {
            return code_and_string_type('5', string_type(TETENGO2_TEXT("5")));
        }

        //! Returns the key code and string for '6'.
        //! \return The key code and string.
        static code_and_string_type char_6()
        {
            return code_and_string_type('6', string_type(TETENGO2_TEXT("6")));
        }

        //! Returns the key code and string for '7'.
        //! \return The key code and string.
        static code_and_string_type char_7()
        {
            return code_and_string_type('7', string_type(TETENGO2_TEXT("7")));
        }

        //! Returns the key code and string for '8'.
        //! \return The key code and string.
        static code_and_string_type char_8()
        {
            return code_and_string_type('8', string_type(TETENGO2_TEXT("8")));
        }

        //! Returns the key code and string for '9'.
        //! \return The key code and string.
        static code_and_string_type char_9()
        {
            return code_and_string_type('9', string_type(TETENGO2_TEXT("9")));
        }

        //! Returns the key code and string for 'A'.
        //! \return The key code and string.
        static code_and_string_type char_a()
        {
            return code_and_string_type('A', string_type(TETENGO2_TEXT("A")));
        }


    private:
        // forbidden operations

        virtual_key();

    
    };


}}}


#endif
