/*! \file
    \brief The definition of tetengo2::detail::windows::virtual_key.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_VIRTUALKEY_H)
#define TETENGO2_DETAIL_WINDOWS_VIRTUALKEY_H

#include <utility>

#include <boost/core/noncopyable.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/text.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of virtual keys.
    */
    class virtual_key : private boost::noncopyable
    {
    public:
        // types

        //! The code type.
        using code_type = unsigned char;


        // static functions

        //! Returns the key code and string for BackSpace.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> backspace()
        {
            return { VK_BACK, String{ TETENGO2_TEXT("BackSpace") } };
        }

        //! Returns the key code and string for Tab.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> tab()
        {
            return { VK_TAB, String{ TETENGO2_TEXT("Tab") } };
        }

        //! Returns the key code and string for Enter.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> enter()
        {
            return { VK_RETURN, String{ TETENGO2_TEXT("Enter") } };
        }

        //! Returns the key code and string for Shift.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> shift()
        {
            return { VK_SHIFT, String{ TETENGO2_TEXT("Shift") } };
        }

        //! Returns the key code and string for Control.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> control()
        {
            return { VK_CONTROL, String{ TETENGO2_TEXT("Ctrl") } };
        }

        //! Returns the key code and string for Meta.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> meta()
        {
            return { VK_MENU, String{ TETENGO2_TEXT("Alt") } };
        }

        //! Returns the key code and string for Escape.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> escape()
        {
            return { VK_ESCAPE, String{ TETENGO2_TEXT("Esc") } };
        }

        //! Returns the key code and string for Space.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> space()
        {
            return { VK_SPACE, String{ TETENGO2_TEXT("Space") } };
        }

        //! Returns the key code and string for PageUp.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> page_up()
        {
            return { VK_PRIOR, String{ TETENGO2_TEXT("PageUp") } };
        }

        //! Returns the key code and string for PageDown.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> page_down()
        {
            return { VK_NEXT, String{ TETENGO2_TEXT("PageDown") } };
        }

        //! Returns the key code and string for End.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> end()
        {
            return { VK_END, String{ TETENGO2_TEXT("End") } };
        }

        //! Returns the key code and string for Home.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> home()
        {
            return { VK_HOME, String{ TETENGO2_TEXT("Home") } };
        }

        //! Returns the key code and string for Left.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> left()
        {
            return { VK_LEFT, String{ TETENGO2_TEXT("Left") } };
        }

        //! Returns the key code and string for Up.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> up()
        {
            return { VK_UP, String{ TETENGO2_TEXT("Up") } };
        }

        //! Returns the key code and string for Right.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> right()
        {
            return { VK_RIGHT, String{ TETENGO2_TEXT("Right") } };
        }

        //! Returns the key code and string for Down.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> down()
        {
            return { VK_DOWN, String{ TETENGO2_TEXT("Down") } };
        }

        //! Returns the key code and string for Insert.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> insert()
        {
            return { VK_INSERT, String{ TETENGO2_TEXT("Ins") } };
        }

        //! Returns the key code and string for Delete.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> del()
        {
            return { VK_DELETE, String{ TETENGO2_TEXT("Del") } };
        }

        //! Returns the key code and string for '0'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_0()
        {
            return { '0', String{ TETENGO2_TEXT("0") } };
        }

        //! Returns the key code and string for '1'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_1()
        {
            return { '1', String{ TETENGO2_TEXT("1") } };
        }

        //! Returns the key code and string for 'A'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_2()
        {
            return { '2', String{ TETENGO2_TEXT("2") } };
        }

        //! Returns the key code and string for '3'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_3()
        {
            return { '3', String{ TETENGO2_TEXT("3") } };
        }

        //! Returns the key code and string for '4'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_4()
        {
            return { '4', String{ TETENGO2_TEXT("4") } };
        }

        //! Returns the key code and string for '5'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_5()
        {
            return { '5', String{ TETENGO2_TEXT("5") } };
        }

        //! Returns the key code and string for '6'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_6()
        {
            return { '6', String{ TETENGO2_TEXT("6") } };
        }

        //! Returns the key code and string for '7'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_7()
        {
            return { '7', String{ TETENGO2_TEXT("7") } };
        }

        //! Returns the key code and string for '8'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_8()
        {
            return { '8', String{ TETENGO2_TEXT("8") } };
        }

        //! Returns the key code and string for '9'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_9()
        {
            return { '9', String{ TETENGO2_TEXT("9") } };
        }

        //! Returns the key code and string for 'A'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_a()
        {
            return { 'A', String{ TETENGO2_TEXT("A") } };
        }

        //! Returns the key code and string for 'B'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_b()
        {
            return { 'B', String{ TETENGO2_TEXT("B") } };
        }

        //! Returns the key code and string for 'C'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_c()
        {
            return { 'C', String{ TETENGO2_TEXT("C") } };
        }

        //! Returns the key code and string for 'D'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_d()
        {
            return { 'D', String{ TETENGO2_TEXT("D") } };
        }

        //! Returns the key code and string for 'E'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_e()
        {
            return { 'E', String{ TETENGO2_TEXT("E") } };
        }

        //! Returns the key code and string for 'F'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_f()
        {
            return { 'F', String{ TETENGO2_TEXT("F") } };
        }

        //! Returns the key code and string for 'G'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_g()
        {
            return { 'G', String{ TETENGO2_TEXT("G") } };
        }

        //! Returns the key code and string for 'H'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_h()
        {
            return { 'H', String{ TETENGO2_TEXT("H") } };
        }

        //! Returns the key code and string for 'I'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_i()
        {
            return { 'I', String{ TETENGO2_TEXT("I") } };
        }

        //! Returns the key code and string for 'J'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_j()
        {
            return { 'J', String{ TETENGO2_TEXT("J") } };
        }

        //! Returns the key code and string for 'K'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_k()
        {
            return { 'K', String{ TETENGO2_TEXT("K") } };
        }

        //! Returns the key code and string for 'L'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_l()
        {
            return { 'L', String{ TETENGO2_TEXT("L") } };
        }

        //! Returns the key code and string for 'M'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_m()
        {
            return { 'M', String{ TETENGO2_TEXT("M") } };
        }

        //! Returns the key code and string for 'N'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_n()
        {
            return { 'N', String{ TETENGO2_TEXT("N") } };
        }

        //! Returns the key code and string for 'O'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_o()
        {
            return { 'O', String{ TETENGO2_TEXT("O") } };
        }

        //! Returns the key code and string for 'P'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_p()
        {
            return { 'P', String{ TETENGO2_TEXT("P") } };
        }

        //! Returns the key code and string for 'Q'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_q()
        {
            return { 'Q', String{ TETENGO2_TEXT("Q") } };
        }

        //! Returns the key code and string for 'R'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_r()
        {
            return { 'R', String{ TETENGO2_TEXT("R") } };
        }

        //! Returns the key code and string for 'S'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_s()
        {
            return { 'S', String{ TETENGO2_TEXT("S") } };
        }

        //! Returns the key code and string for 'T'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_t()
        {
            return { 'T', String{ TETENGO2_TEXT("T") } };
        }

        //! Returns the key code and string for 'U'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_u()
        {
            return { 'U', String{ TETENGO2_TEXT("U") } };
        }

        //! Returns the key code and string for 'V'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_v()
        {
            return { 'V', String{ TETENGO2_TEXT("V") } };
        }

        //! Returns the key code and string for 'W'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_w()
        {
            return { 'W', String{ TETENGO2_TEXT("W") } };
        }

        //! Returns the key code and string for 'X'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_x()
        {
            return { 'X', String{ TETENGO2_TEXT("X") } };
        }

        //! Returns the key code and string for 'Y'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_y()
        {
            return { 'Y', String{ TETENGO2_TEXT("Y") } };
        }

        //! Returns the key code and string for 'Z'.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> char_z()
        {
            return { 'Z', String{ TETENGO2_TEXT("Z") } };
        }

        //! Returns the key code and string for F1.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f1()
        {
            return { VK_F1, String{ TETENGO2_TEXT("F1") } };
        }

        //! Returns the key code and string for F2.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f2()
        {
            return { VK_F2, String{ TETENGO2_TEXT("F2") } };
        }

        //! Returns the key code and string for F3.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f3()
        {
            return { VK_F3, String{ TETENGO2_TEXT("F3") } };
        }

        //! Returns the key code and string for F4.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f4()
        {
            return { VK_F4, String{ TETENGO2_TEXT("F4") } };
        }

        //! Returns the key code and string for F5.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f5()
        {
            return { VK_F5, String{ TETENGO2_TEXT("F5") } };
        }

        //! Returns the key code and string for F6.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f6()
        {
            return { VK_F6, String{ TETENGO2_TEXT("F6") } };
        }

        //! Returns the key code and string for F7.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f7()
        {
            return { VK_F7, String{ TETENGO2_TEXT("F7") } };
        }

        //! Returns the key code and string for F8.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f8()
        {
            return { VK_F8, String{ TETENGO2_TEXT("F8") } };
        }

        //! Returns the key code and string for F9.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f9()
        {
            return { VK_F9, String{ TETENGO2_TEXT("F9") } };
        }

        //! Returns the key code and string for F10.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f10()
        {
            return { VK_F10, String{ TETENGO2_TEXT("F10") } };
        }

        //! Returns the key code and string for F11.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f11()
        {
            return { VK_F11, String{ TETENGO2_TEXT("F11") } };
        }

        //! Returns the key code and string for F12.
        //! \tparam String A string type.
        //! \return The key code and string.
        template <typename String>
        static std::pair<code_type, String> f12()
        {
            return { VK_F12, String{ TETENGO2_TEXT("F12") } };
        }

        /*!
            \brief Returns the string representation of combined keys.

            \tparam String        A string type.
            \tparam InputIterator An input iterator type.

            \param first The first position of the combined keys.
            \param last  The last position of the combined keys.

            \return The string representation of combined keys.
        */
        template <typename String, typename InputIterator>
        static String to_combined_string(const InputIterator first, const InputIterator last)
        {
            String string;
            for (InputIterator i = first; i != last; ++i)
            {
                if (i != first)
                    string += String{ TETENGO2_TEXT("+") };
                string += (*i)->to_string();
            }
            return string;
        }


    private:
        // forbidden operations

        virtual_key()
        = delete;

    
    };


}}}


#endif
