/*! \file
    \brief The definition of tetengo2::detail::stub::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_VIRTUALKEY_H)
#define TETENGO2_DETAIL_STUB_VIRTUALKEY_H

#include <utility>

#include <boost/noncopyable.hpp>

#include "tetengo2.text.h"


namespace tetengo2 { namespace detail { namespace stub
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
                0x08, string_type(TETENGO2_TEXT("BackSpace"))
            );
        }

        //! Returns the key code and string for Tab.
        //! \return The key code and string.
        static code_and_string_type tab()
        {
            return code_and_string_type(
                0x09, string_type(TETENGO2_TEXT("Tab"))
            );
        }

        //! Returns the key code and string for Enter.
        //! \return The key code and string.
        static code_and_string_type enter()
        {
            return code_and_string_type(
                0x0D, string_type(TETENGO2_TEXT("Enter"))
            );
        }

        //! Returns the key code and string for Shift.
        //! \return The key code and string.
        static code_and_string_type shift()
        {
            return code_and_string_type(
                0x10, string_type(TETENGO2_TEXT("Shift"))
            );
        }

        //! Returns the key code and string for Control.
        //! \return The key code and string.
        static code_and_string_type control()
        {
            return code_and_string_type(
                0x11, string_type(TETENGO2_TEXT("Ctrl"))
            );
        }

        //! Returns the key code and string for Meta.
        //! \return The key code and string.
        static code_and_string_type meta()
        {
            return code_and_string_type(
                0x12, string_type(TETENGO2_TEXT("Alt"))
            );
        }

        //! Returns the key code and string for Escape.
        //! \return The key code and string.
        static code_and_string_type escape()
        {
            return code_and_string_type(
                0x1B, string_type(TETENGO2_TEXT("Esc"))
            );
        }

        //! Returns the key code and string for Space.
        //! \return The key code and string.
        static code_and_string_type space()
        {
            return code_and_string_type(
                0x20, string_type(TETENGO2_TEXT("Space"))
            );
        }

        //! Returns the key code and string for PageUp.
        //! \return The key code and string.
        static code_and_string_type page_up()
        {
            return code_and_string_type(
                0x21, string_type(TETENGO2_TEXT("PageUp"))
            );
        }

        //! Returns the key code and string for PageDown.
        //! \return The key code and string.
        static code_and_string_type page_down()
        {
            return code_and_string_type(
                0x22, string_type(TETENGO2_TEXT("PageDown"))
            );
        }

        //! Returns the key code and string for End.
        //! \return The key code and string.
        static code_and_string_type end()
        {
            return code_and_string_type(
                0x23, string_type(TETENGO2_TEXT("End"))
            );
        }

        //! Returns the key code and string for Home.
        //! \return The key code and string.
        static code_and_string_type home()
        {
            return code_and_string_type(
                0x24, string_type(TETENGO2_TEXT("Home"))
            );
        }

        //! Returns the key code and string for Left.
        //! \return The key code and string.
        static code_and_string_type left()
        {
            return code_and_string_type(
                0x25, string_type(TETENGO2_TEXT("Left"))
            );
        }

        //! Returns the key code and string for Up.
        //! \return The key code and string.
        static code_and_string_type up()
        {
            return code_and_string_type(
                0x26, string_type(TETENGO2_TEXT("Up"))
            );
        }

        //! Returns the key code and string for Right.
        //! \return The key code and string.
        static code_and_string_type right()
        {
            return code_and_string_type(
                0x27, string_type(TETENGO2_TEXT("Right"))
            );
        }

        //! Returns the key code and string for Down.
        //! \return The key code and string.
        static code_and_string_type down()
        {
            return code_and_string_type(
                0x28, string_type(TETENGO2_TEXT("Down"))
            );
        }

        //! Returns the key code and string for Insert.
        //! \return The key code and string.
        static code_and_string_type insert()
        {
            return code_and_string_type(
                0x2D, string_type(TETENGO2_TEXT("Ins"))
            );
        }

        //! Returns the key code and string for Delete.
        //! \return The key code and string.
        static code_and_string_type del()
        {
            return code_and_string_type(
                0x2E, string_type(TETENGO2_TEXT("Del"))
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

        //! Returns the key code and string for 'B'.
        //! \return The key code and string.
        static code_and_string_type char_b()
        {
            return code_and_string_type('B', string_type(TETENGO2_TEXT("B")));
        }

        //! Returns the key code and string for 'C'.
        //! \return The key code and string.
        static code_and_string_type char_c()
        {
            return code_and_string_type('C', string_type(TETENGO2_TEXT("C")));
        }

        //! Returns the key code and string for 'D'.
        //! \return The key code and string.
        static code_and_string_type char_d()
        {
            return code_and_string_type('D', string_type(TETENGO2_TEXT("D")));
        }

        //! Returns the key code and string for 'E'.
        //! \return The key code and string.
        static code_and_string_type char_e()
        {
            return code_and_string_type('E', string_type(TETENGO2_TEXT("E")));
        }

        //! Returns the key code and string for 'F'.
        //! \return The key code and string.
        static code_and_string_type char_f()
        {
            return code_and_string_type('F', string_type(TETENGO2_TEXT("F")));
        }

        //! Returns the key code and string for 'G'.
        //! \return The key code and string.
        static code_and_string_type char_g()
        {
            return code_and_string_type('G', string_type(TETENGO2_TEXT("G")));
        }

        //! Returns the key code and string for 'H'.
        //! \return The key code and string.
        static code_and_string_type char_h()
        {
            return code_and_string_type('H', string_type(TETENGO2_TEXT("H")));
        }

        //! Returns the key code and string for 'I'.
        //! \return The key code and string.
        static code_and_string_type char_i()
        {
            return code_and_string_type('I', string_type(TETENGO2_TEXT("I")));
        }

        //! Returns the key code and string for 'J'.
        //! \return The key code and string.
        static code_and_string_type char_j()
        {
            return code_and_string_type('J', string_type(TETENGO2_TEXT("J")));
        }

        //! Returns the key code and string for 'K'.
        //! \return The key code and string.
        static code_and_string_type char_k()
        {
            return code_and_string_type('K', string_type(TETENGO2_TEXT("K")));
        }

        //! Returns the key code and string for 'L'.
        //! \return The key code and string.
        static code_and_string_type char_l()
        {
            return code_and_string_type('L', string_type(TETENGO2_TEXT("L")));
        }

        //! Returns the key code and string for 'M'.
        //! \return The key code and string.
        static code_and_string_type char_m()
        {
            return code_and_string_type('M', string_type(TETENGO2_TEXT("M")));
        }

        //! Returns the key code and string for 'N'.
        //! \return The key code and string.
        static code_and_string_type char_n()
        {
            return code_and_string_type('N', string_type(TETENGO2_TEXT("N")));
        }

        //! Returns the key code and string for 'O'.
        //! \return The key code and string.
        static code_and_string_type char_o()
        {
            return code_and_string_type('O', string_type(TETENGO2_TEXT("O")));
        }

        //! Returns the key code and string for 'P'.
        //! \return The key code and string.
        static code_and_string_type char_p()
        {
            return code_and_string_type('P', string_type(TETENGO2_TEXT("P")));
        }

        //! Returns the key code and string for 'Q'.
        //! \return The key code and string.
        static code_and_string_type char_q()
        {
            return code_and_string_type('Q', string_type(TETENGO2_TEXT("Q")));
        }

        //! Returns the key code and string for 'R'.
        //! \return The key code and string.
        static code_and_string_type char_r()
        {
            return code_and_string_type('R', string_type(TETENGO2_TEXT("R")));
        }

        //! Returns the key code and string for 'S'.
        //! \return The key code and string.
        static code_and_string_type char_s()
        {
            return code_and_string_type('S', string_type(TETENGO2_TEXT("S")));
        }

        //! Returns the key code and string for 'T'.
        //! \return The key code and string.
        static code_and_string_type char_t()
        {
            return code_and_string_type('T', string_type(TETENGO2_TEXT("T")));
        }

        //! Returns the key code and string for 'U'.
        //! \return The key code and string.
        static code_and_string_type char_u()
        {
            return code_and_string_type('U', string_type(TETENGO2_TEXT("U")));
        }

        //! Returns the key code and string for 'V'.
        //! \return The key code and string.
        static code_and_string_type char_v()
        {
            return code_and_string_type('V', string_type(TETENGO2_TEXT("V")));
        }

        //! Returns the key code and string for 'W'.
        //! \return The key code and string.
        static code_and_string_type char_w()
        {
            return code_and_string_type('W', string_type(TETENGO2_TEXT("W")));
        }

        //! Returns the key code and string for 'X'.
        //! \return The key code and string.
        static code_and_string_type char_x()
        {
            return code_and_string_type('X', string_type(TETENGO2_TEXT("X")));
        }

        //! Returns the key code and string for 'Y'.
        //! \return The key code and string.
        static code_and_string_type char_y()
        {
            return code_and_string_type('Y', string_type(TETENGO2_TEXT("Y")));
        }

        //! Returns the key code and string for 'Z'.
        //! \return The key code and string.
        static code_and_string_type char_z()
        {
            return code_and_string_type('Z', string_type(TETENGO2_TEXT("Z")));
        }

        //! Returns the key code and string for F1.
        //! \return The key code and string.
        static code_and_string_type f1()
        {
            return code_and_string_type(
                0x70, string_type(TETENGO2_TEXT("F1"))
            );
        }

        //! Returns the key code and string for F2.
        //! \return The key code and string.
        static code_and_string_type f2()
        {
            return code_and_string_type(
                0x71, string_type(TETENGO2_TEXT("F2"))
            );
        }

        //! Returns the key code and string for F3.
        //! \return The key code and string.
        static code_and_string_type f3()
        {
            return code_and_string_type(
                0x72, string_type(TETENGO2_TEXT("F3"))
            );
        }

        //! Returns the key code and string for F4.
        //! \return The key code and string.
        static code_and_string_type f4()
        {
            return code_and_string_type(
                0x73, string_type(TETENGO2_TEXT("F4"))
            );
        }

        //! Returns the key code and string for F5.
        //! \return The key code and string.
        static code_and_string_type f5()
        {
            return code_and_string_type(
                0x74, string_type(TETENGO2_TEXT("F5"))
            );
        }

        //! Returns the key code and string for F6.
        //! \return The key code and string.
        static code_and_string_type f6()
        {
            return code_and_string_type(
                0x75, string_type(TETENGO2_TEXT("F6"))
            );
        }

        //! Returns the key code and string for F7.
        //! \return The key code and string.
        static code_and_string_type f7()
        {
            return code_and_string_type(
                0x76, string_type(TETENGO2_TEXT("F7"))
            );
        }

        //! Returns the key code and string for F8.
        //! \return The key code and string.
        static code_and_string_type f8()
        {
            return code_and_string_type(
                0x77, string_type(TETENGO2_TEXT("F8"))
            );
        }

        //! Returns the key code and string for F9.
        //! \return The key code and string.
        static code_and_string_type f9()
        {
            return code_and_string_type(
                0x78, string_type(TETENGO2_TEXT("F9"))
            );
        }

        //! Returns the key code and string for F10.
        //! \return The key code and string.
        static code_and_string_type f10()
        {
            return code_and_string_type(
                0x79, string_type(TETENGO2_TEXT("F10"))
            );
        }

        //! Returns the key code and string for F11.
        //! \return The key code and string.
        static code_and_string_type f11()
        {
            return code_and_string_type(
                0x7A, string_type(TETENGO2_TEXT("F11"))
            );
        }

        //! Returns the key code and string for F12.
        //! \return The key code and string.
        static code_and_string_type f12()
        {
            return code_and_string_type(
                0x7B, string_type(TETENGO2_TEXT("F12"))
            );
        }


    private:
        // forbidden operations

        virtual_key();

    
    };


}}}


#endif
