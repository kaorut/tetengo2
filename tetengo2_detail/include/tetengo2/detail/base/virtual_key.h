/*! \file
    \brief The definition of tetengo2::detail::base::virtual_key.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_VIRTUALKEY_H)
#define TETENGO2_DETAIL_BASE_VIRTUALKEY_H

#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of virtual keys.
    */
    class virtual_key : private boost::noncopyable
    {
    public:
        // types

        //! The code type.
        using code_type = unsigned char;

        //! The string type.
        using string_type = type_list::string_type;


        // constructors and destructor

        virtual ~virtual_key();


        // functions

        //! Returns the key code and string for BackSpace.
        //! \return The key code and string.
        std::pair<code_type, string_type> backspace() const;

        //! Returns the key code and string for Tab.
        //! \return The key code and string.
        std::pair<code_type, string_type> tab() const;

        //! Returns the key code and string for Enter.
        //! \return The key code and string.
        std::pair<code_type, string_type> enter() const;

        //! Returns the key code and string for Shift.
        //! \return The key code and string.
        std::pair<code_type, string_type> shift() const;

        //! Returns the key code and string for Control.
        //! \return The key code and string.
        std::pair<code_type, string_type> control() const;

        //! Returns the key code and string for Meta.
        //! \return The key code and string.
        std::pair<code_type, string_type> meta() const;

        //! Returns the key code and string for Escape.
        //! \return The key code and string.
        std::pair<code_type, string_type> escape() const;

        //! Returns the key code and string for Space.
        //! \return The key code and string.
        std::pair<code_type, string_type> space() const;

        //! Returns the key code and string for PageUp.
        //! \return The key code and string.
        std::pair<code_type, string_type> page_up() const;

        //! Returns the key code and string for PageDown.
        //! \return The key code and string.
        std::pair<code_type, string_type> page_down() const;

        //! Returns the key code and string for End.
        //! \return The key code and string.
        std::pair<code_type, string_type> end() const;

        //! Returns the key code and string for Home.
        //! \return The key code and string.
        std::pair<code_type, string_type> home() const;

        //! Returns the key code and string for Left.
        //! \return The key code and string.
        std::pair<code_type, string_type> left() const;

        //! Returns the key code and string for Up.
        //! \return The key code and string.
        std::pair<code_type, string_type> up() const;

        //! Returns the key code and string for Right.
        //! \return The key code and string.
        std::pair<code_type, string_type> right() const;

        //! Returns the key code and string for Down.
        //! \return The key code and string.
        std::pair<code_type, string_type> down() const;

        //! Returns the key code and string for Insert.
        //! \return The key code and string.
        std::pair<code_type, string_type> insert() const;

        //! Returns the key code and string for Delete.
        //! \return The key code and string.
        std::pair<code_type, string_type> del() const;

        //! Returns the key code and string for '0'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_0() const;

        //! Returns the key code and string for '1'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_1() const;

        //! Returns the key code and string for 'A'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_2() const;

        //! Returns the key code and string for '3'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_3() const;

        //! Returns the key code and string for '4'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_4() const;

        //! Returns the key code and string for '5'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_5() const;

        //! Returns the key code and string for '6'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_6() const;

        //! Returns the key code and string for '7'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_7() const;

        //! Returns the key code and string for '8'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_8() const;

        //! Returns the key code and string for '9'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_9() const;

        //! Returns the key code and string for 'A'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_a() const;

        //! Returns the key code and string for 'B'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_b() const;

        //! Returns the key code and string for 'C'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_c() const;

        //! Returns the key code and string for 'D'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_d() const;

        //! Returns the key code and string for 'E'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_e() const;

        //! Returns the key code and string for 'F'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_f() const;

        //! Returns the key code and string for 'G'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_g() const;

        //! Returns the key code and string for 'H'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_h() const;

        //! Returns the key code and string for 'I'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_i() const;

        //! Returns the key code and string for 'J'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_j() const;

        //! Returns the key code and string for 'K'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_k() const;

        //! Returns the key code and string for 'L'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_l() const;

        //! Returns the key code and string for 'M'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_m() const;

        //! Returns the key code and string for 'N'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_n() const;

        //! Returns the key code and string for 'O'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_o() const;

        //! Returns the key code and string for 'P'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_p() const;

        //! Returns the key code and string for 'Q'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_q() const;

        //! Returns the key code and string for 'R'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_r() const;

        //! Returns the key code and string for 'S'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_s() const;

        //! Returns the key code and string for 'T'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_t() const;

        //! Returns the key code and string for 'U'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_u() const;

        //! Returns the key code and string for 'V'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_v() const;

        //! Returns the key code and string for 'W'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_w() const;

        //! Returns the key code and string for 'X'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_x() const;

        //! Returns the key code and string for 'Y'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_y() const;

        //! Returns the key code and string for 'Z'.
        //! \return The key code and string.
        std::pair<code_type, string_type> char_z() const;

        //! Returns the key code and string for F1.
        //! \return The key code and string.
        std::pair<code_type, string_type> f1() const;

        //! Returns the key code and string for F2.
        //! \return The key code and string.
        std::pair<code_type, string_type> f2() const;

        //! Returns the key code and string for F3.
        //! \return The key code and string.
        std::pair<code_type, string_type> f3() const;

        //! Returns the key code and string for F4.
        //! \return The key code and string.
        std::pair<code_type, string_type> f4() const;

        //! Returns the key code and string for F5.
        //! \return The key code and string.
        std::pair<code_type, string_type> f5() const;

        //! Returns the key code and string for F6.
        //! \return The key code and string.
        std::pair<code_type, string_type> f6() const;

        //! Returns the key code and string for F7.
        //! \return The key code and string.
        std::pair<code_type, string_type> f7() const;

        //! Returns the key code and string for F8.
        //! \return The key code and string.
        std::pair<code_type, string_type> f8() const;

        //! Returns the key code and string for F9.
        //! \return The key code and string.
        std::pair<code_type, string_type> f9() const;

        //! Returns the key code and string for F10.
        //! \return The key code and string.
        std::pair<code_type, string_type> f10() const;

        //! Returns the key code and string for F11.
        //! \return The key code and string.
        std::pair<code_type, string_type> f11() const;

        //! Returns the key code and string for F12.
        //! \return The key code and string.
        std::pair<code_type, string_type> f12() const;

        /*!
            \brief Returns the string representation of the combined keys.

            \param key_strings The string representations of the each combined keys.

            \return The whole string representation of the combined keys.
        */
        string_type to_combined_string(const std::vector<string_type>& key_strings) const;


    protected:
        // constructors

        virtual_key();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual std::pair<code_type, string_type> backspace_impl() const = 0;

        virtual std::pair<code_type, string_type> tab_impl() const = 0;

        virtual std::pair<code_type, string_type> enter_impl() const = 0;

        virtual std::pair<code_type, string_type> shift_impl() const = 0;

        virtual std::pair<code_type, string_type> control_impl() const = 0;

        virtual std::pair<code_type, string_type> meta_impl() const = 0;

        virtual std::pair<code_type, string_type> escape_impl() const = 0;

        virtual std::pair<code_type, string_type> space_impl() const = 0;

        virtual std::pair<code_type, string_type> page_up_impl() const = 0;

        virtual std::pair<code_type, string_type> page_down_impl() const = 0;

        virtual std::pair<code_type, string_type> end_impl() const = 0;

        virtual std::pair<code_type, string_type> home_impl() const = 0;

        virtual std::pair<code_type, string_type> left_impl() const = 0;

        virtual std::pair<code_type, string_type> up_impl() const = 0;

        virtual std::pair<code_type, string_type> right_impl() const = 0;

        virtual std::pair<code_type, string_type> down_impl() const = 0;

        virtual std::pair<code_type, string_type> insert_impl() const = 0;

        virtual std::pair<code_type, string_type> del_impl() const = 0;

        virtual std::pair<code_type, string_type> char_0_impl() const = 0;

        virtual std::pair<code_type, string_type> char_1_impl() const = 0;

        virtual std::pair<code_type, string_type> char_2_impl() const = 0;

        virtual std::pair<code_type, string_type> char_3_impl() const = 0;

        virtual std::pair<code_type, string_type> char_4_impl() const = 0;

        virtual std::pair<code_type, string_type> char_5_impl() const = 0;

        virtual std::pair<code_type, string_type> char_6_impl() const = 0;

        virtual std::pair<code_type, string_type> char_7_impl() const = 0;

        virtual std::pair<code_type, string_type> char_8_impl() const = 0;

        virtual std::pair<code_type, string_type> char_9_impl() const = 0;

        virtual std::pair<code_type, string_type> char_a_impl() const = 0;

        virtual std::pair<code_type, string_type> char_b_impl() const = 0;

        virtual std::pair<code_type, string_type> char_c_impl() const = 0;

        virtual std::pair<code_type, string_type> char_d_impl() const = 0;

        virtual std::pair<code_type, string_type> char_e_impl() const = 0;

        virtual std::pair<code_type, string_type> char_f_impl() const = 0;

        virtual std::pair<code_type, string_type> char_g_impl() const = 0;

        virtual std::pair<code_type, string_type> char_h_impl() const = 0;

        virtual std::pair<code_type, string_type> char_i_impl() const = 0;

        virtual std::pair<code_type, string_type> char_j_impl() const = 0;

        virtual std::pair<code_type, string_type> char_k_impl() const = 0;

        virtual std::pair<code_type, string_type> char_l_impl() const = 0;

        virtual std::pair<code_type, string_type> char_m_impl() const = 0;

        virtual std::pair<code_type, string_type> char_n_impl() const = 0;

        virtual std::pair<code_type, string_type> char_o_impl() const = 0;

        virtual std::pair<code_type, string_type> char_p_impl() const = 0;

        virtual std::pair<code_type, string_type> char_q_impl() const = 0;

        virtual std::pair<code_type, string_type> char_r_impl() const = 0;

        virtual std::pair<code_type, string_type> char_s_impl() const = 0;

        virtual std::pair<code_type, string_type> char_t_impl() const = 0;

        virtual std::pair<code_type, string_type> char_u_impl() const = 0;

        virtual std::pair<code_type, string_type> char_v_impl() const = 0;

        virtual std::pair<code_type, string_type> char_w_impl() const = 0;

        virtual std::pair<code_type, string_type> char_x_impl() const = 0;

        virtual std::pair<code_type, string_type> char_y_impl() const = 0;

        virtual std::pair<code_type, string_type> char_z_impl() const = 0;

        virtual std::pair<code_type, string_type> f1_impl() const = 0;

        virtual std::pair<code_type, string_type> f2_impl() const = 0;

        virtual std::pair<code_type, string_type> f3_impl() const = 0;

        virtual std::pair<code_type, string_type> f4_impl() const = 0;

        virtual std::pair<code_type, string_type> f5_impl() const = 0;

        virtual std::pair<code_type, string_type> f6_impl() const = 0;

        virtual std::pair<code_type, string_type> f7_impl() const = 0;

        virtual std::pair<code_type, string_type> f8_impl() const = 0;

        virtual std::pair<code_type, string_type> f9_impl() const = 0;

        virtual std::pair<code_type, string_type> f10_impl() const = 0;

        virtual std::pair<code_type, string_type> f11_impl() const = 0;

        virtual std::pair<code_type, string_type> f12_impl() const = 0;

        virtual string_type to_combined_string_impl(const std::vector<string_type>& key_strings) const = 0;
    };
}


#endif
