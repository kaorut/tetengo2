/*! \file
    \brief The definition of tetengo2::detail::stub::virtual_key.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/virtual_key.h>
#include <tetengo2/text.h>


namespace tetengo2::detail::stub {
    class virtual_key::impl : private boost::noncopyable
    {
    public:
        // types

        using code_type = virtual_key::code_type;

        using string_type = virtual_key::string_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const virtual_key& instance()
        {
            static const virtual_key singleton{};
            return singleton;
        }


        // functions

        std::pair<code_type, string_type> backspace_impl() const
        {
            return { static_cast<code_type>(0x08), string_type{ TETENGO2_TEXT("BackSpace") } };
        }

        std::pair<code_type, string_type> tab_impl() const
        {
            return { static_cast<code_type>(0x09), string_type{ TETENGO2_TEXT("Tab") } };
        }

        std::pair<code_type, string_type> enter_impl() const
        {
            return { static_cast<code_type>(0x0D), string_type{ TETENGO2_TEXT("Enter") } };
        }

        std::pair<code_type, string_type> shift_impl() const
        {
            return { static_cast<code_type>(0x10), string_type{ TETENGO2_TEXT("Shift") } };
        }

        std::pair<code_type, string_type> control_impl() const
        {
            return { static_cast<code_type>(0x11), string_type{ TETENGO2_TEXT("Ctrl") } };
        }

        std::pair<code_type, string_type> meta_impl() const
        {
            return { static_cast<code_type>(0x12), string_type{ TETENGO2_TEXT("Alt") } };
        }

        std::pair<code_type, string_type> escape_impl() const
        {
            return { static_cast<code_type>(0x1B), string_type{ TETENGO2_TEXT("Esc") } };
        }

        std::pair<code_type, string_type> space_impl() const
        {
            return { static_cast<code_type>(0x20), string_type{ TETENGO2_TEXT("Space") } };
        }

        std::pair<code_type, string_type> page_up_impl() const
        {
            return { static_cast<code_type>(0x21), string_type{ TETENGO2_TEXT("PageUp") } };
        }

        std::pair<code_type, string_type> page_down_impl() const
        {
            return { static_cast<code_type>(0x22), string_type{ TETENGO2_TEXT("PageDown") } };
        }

        std::pair<code_type, string_type> end_impl() const
        {
            return { static_cast<code_type>(0x23), string_type{ TETENGO2_TEXT("End") } };
        }

        std::pair<code_type, string_type> home_impl() const
        {
            return { static_cast<code_type>(0x24), string_type{ TETENGO2_TEXT("Home") } };
        }

        std::pair<code_type, string_type> left_impl() const
        {
            return { static_cast<code_type>(0x25), string_type{ TETENGO2_TEXT("Left") } };
        }

        std::pair<code_type, string_type> up_impl() const
        {
            return { static_cast<code_type>(0x26), string_type{ TETENGO2_TEXT("Up") } };
        }

        std::pair<code_type, string_type> right_impl() const
        {
            return { static_cast<code_type>(0x27), string_type{ TETENGO2_TEXT("Right") } };
        }

        std::pair<code_type, string_type> down_impl() const
        {
            return { static_cast<code_type>(0x28), string_type{ TETENGO2_TEXT("Down") } };
        }

        std::pair<code_type, string_type> insert_impl() const
        {
            return { static_cast<code_type>(0x2D), string_type{ TETENGO2_TEXT("Ins") } };
        }

        std::pair<code_type, string_type> del_impl() const
        {
            return { static_cast<code_type>(0x2E), string_type{ TETENGO2_TEXT("Del") } };
        }

        std::pair<code_type, string_type> char_0_impl() const
        {
            return { static_cast<code_type>('0'), string_type{ TETENGO2_TEXT("0") } };
        }

        std::pair<code_type, string_type> char_1_impl() const
        {
            return { static_cast<code_type>('1'), string_type{ TETENGO2_TEXT("1") } };
        }

        std::pair<code_type, string_type> char_2_impl() const
        {
            return { static_cast<code_type>('2'), string_type{ TETENGO2_TEXT("2") } };
        }

        std::pair<code_type, string_type> char_3_impl() const
        {
            return { static_cast<code_type>('3'), string_type{ TETENGO2_TEXT("3") } };
        }

        std::pair<code_type, string_type> char_4_impl() const
        {
            return { static_cast<code_type>('4'), string_type{ TETENGO2_TEXT("4") } };
        }

        std::pair<code_type, string_type> char_5_impl() const
        {
            return { static_cast<code_type>('5'), string_type{ TETENGO2_TEXT("5") } };
        }

        std::pair<code_type, string_type> char_6_impl() const
        {
            return { static_cast<code_type>('6'), string_type{ TETENGO2_TEXT("6") } };
        }

        std::pair<code_type, string_type> char_7_impl() const
        {
            return { static_cast<code_type>('7'), string_type{ TETENGO2_TEXT("7") } };
        }

        std::pair<code_type, string_type> char_8_impl() const
        {
            return { static_cast<code_type>('8'), string_type{ TETENGO2_TEXT("8") } };
        }

        std::pair<code_type, string_type> char_9_impl() const
        {
            return { static_cast<code_type>('9'), string_type{ TETENGO2_TEXT("9") } };
        }

        std::pair<code_type, string_type> char_a_impl() const
        {
            return { static_cast<code_type>('A'), string_type{ TETENGO2_TEXT("A") } };
        }

        std::pair<code_type, string_type> char_b_impl() const
        {
            return { static_cast<code_type>('B'), string_type{ TETENGO2_TEXT("B") } };
        }

        std::pair<code_type, string_type> char_c_impl() const
        {
            return { static_cast<code_type>('C'), string_type{ TETENGO2_TEXT("C") } };
        }

        std::pair<code_type, string_type> char_d_impl() const
        {
            return { static_cast<code_type>('D'), string_type{ TETENGO2_TEXT("D") } };
        }

        std::pair<code_type, string_type> char_e_impl() const
        {
            return { static_cast<code_type>('E'), string_type{ TETENGO2_TEXT("E") } };
        }

        std::pair<code_type, string_type> char_f_impl() const
        {
            return { static_cast<code_type>('F'), string_type{ TETENGO2_TEXT("F") } };
        }

        std::pair<code_type, string_type> char_g_impl() const
        {
            return { static_cast<code_type>('G'), string_type{ TETENGO2_TEXT("G") } };
        }

        std::pair<code_type, string_type> char_h_impl() const
        {
            return { static_cast<code_type>('H'), string_type{ TETENGO2_TEXT("H") } };
        }

        std::pair<code_type, string_type> char_i_impl() const
        {
            return { static_cast<code_type>('I'), string_type{ TETENGO2_TEXT("I") } };
        }

        std::pair<code_type, string_type> char_j_impl() const
        {
            return { static_cast<code_type>('J'), string_type{ TETENGO2_TEXT("J") } };
        }

        std::pair<code_type, string_type> char_k_impl() const
        {
            return { static_cast<code_type>('K'), string_type{ TETENGO2_TEXT("K") } };
        }

        std::pair<code_type, string_type> char_l_impl() const
        {
            return { static_cast<code_type>('L'), string_type{ TETENGO2_TEXT("L") } };
        }

        std::pair<code_type, string_type> char_m_impl() const
        {
            return { static_cast<code_type>('M'), string_type{ TETENGO2_TEXT("M") } };
        }

        std::pair<code_type, string_type> char_n_impl() const
        {
            return { static_cast<code_type>('N'), string_type{ TETENGO2_TEXT("N") } };
        }

        std::pair<code_type, string_type> char_o_impl() const
        {
            return { static_cast<code_type>('O'), string_type{ TETENGO2_TEXT("O") } };
        }

        std::pair<code_type, string_type> char_p_impl() const
        {
            return { static_cast<code_type>('P'), string_type{ TETENGO2_TEXT("P") } };
        }

        std::pair<code_type, string_type> char_q_impl() const
        {
            return { static_cast<code_type>('Q'), string_type{ TETENGO2_TEXT("Q") } };
        }

        std::pair<code_type, string_type> char_r_impl() const
        {
            return { static_cast<code_type>('R'), string_type{ TETENGO2_TEXT("R") } };
        }

        std::pair<code_type, string_type> char_s_impl() const
        {
            return { static_cast<code_type>('S'), string_type{ TETENGO2_TEXT("S") } };
        }

        std::pair<code_type, string_type> char_t_impl() const
        {
            return { static_cast<code_type>('T'), string_type{ TETENGO2_TEXT("T") } };
        }

        std::pair<code_type, string_type> char_u_impl() const
        {
            return { static_cast<code_type>('U'), string_type{ TETENGO2_TEXT("U") } };
        }

        std::pair<code_type, string_type> char_v_impl() const
        {
            return { static_cast<code_type>('V'), string_type{ TETENGO2_TEXT("V") } };
        }

        std::pair<code_type, string_type> char_w_impl() const
        {
            return { static_cast<code_type>('W'), string_type{ TETENGO2_TEXT("W") } };
        }

        std::pair<code_type, string_type> char_x_impl() const
        {
            return { static_cast<code_type>('X'), string_type{ TETENGO2_TEXT("X") } };
        }

        std::pair<code_type, string_type> char_y_impl() const
        {
            return { static_cast<code_type>('Y'), string_type{ TETENGO2_TEXT("Y") } };
        }

        std::pair<code_type, string_type> char_z_impl() const
        {
            return { static_cast<code_type>('Z'), string_type{ TETENGO2_TEXT("Z") } };
        }

        std::pair<code_type, string_type> f1_impl() const
        {
            return { static_cast<code_type>(0x70), string_type{ TETENGO2_TEXT("F1") } };
        }

        std::pair<code_type, string_type> f2_impl() const
        {
            return { static_cast<code_type>(0x71), string_type{ TETENGO2_TEXT("F2") } };
        }

        std::pair<code_type, string_type> f3_impl() const
        {
            return { static_cast<code_type>(0x72), string_type{ TETENGO2_TEXT("F3") } };
        }

        std::pair<code_type, string_type> f4_impl() const
        {
            return { static_cast<code_type>(0x73), string_type{ TETENGO2_TEXT("F4") } };
        }

        std::pair<code_type, string_type> f5_impl() const
        {
            return { static_cast<code_type>(0x74), string_type{ TETENGO2_TEXT("F5") } };
        }

        std::pair<code_type, string_type> f6_impl() const
        {
            return { static_cast<code_type>(0x75), string_type{ TETENGO2_TEXT("F6") } };
        }

        std::pair<code_type, string_type> f7_impl() const
        {
            return { static_cast<code_type>(0x76), string_type{ TETENGO2_TEXT("F7") } };
        }

        std::pair<code_type, string_type> f8_impl() const
        {
            return { static_cast<code_type>(0x77), string_type{ TETENGO2_TEXT("F8") } };
        }

        std::pair<code_type, string_type> f9_impl() const
        {
            return { static_cast<code_type>(0x78), string_type{ TETENGO2_TEXT("F9") } };
        }

        std::pair<code_type, string_type> f10_impl() const
        {
            return { static_cast<code_type>(0x79), string_type{ TETENGO2_TEXT("F10") } };
        }

        std::pair<code_type, string_type> f11_impl() const
        {
            return { static_cast<code_type>(0x7A), string_type{ TETENGO2_TEXT("F11") } };
        }

        std::pair<code_type, string_type> f12_impl() const
        {
            return { static_cast<code_type>(0x7B), string_type{ TETENGO2_TEXT("F12") } };
        }

        string_type to_combined_string_impl(const std::vector<string_type>& key_strings) const
        {
            string_type string;
            for (const auto& ks : key_strings)
            {
                if (!string.empty())
                    string += string_type{ TETENGO2_TEXT("+") };
                string += ks;
            }
            return string;
        }
    };


    const virtual_key& virtual_key::instance()
    {
        return impl::instance();
    }

    virtual_key::~virtual_key() = default;

    virtual_key::virtual_key() : m_p_impl{ std::make_unique<impl>() } {}

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::backspace_impl() const
    {
        return m_p_impl->backspace_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::tab_impl() const
    {
        return m_p_impl->tab_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::enter_impl() const
    {
        return m_p_impl->enter_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::shift_impl() const
    {
        return m_p_impl->shift_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::control_impl() const
    {
        return m_p_impl->control_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::meta_impl() const
    {
        return m_p_impl->meta_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::escape_impl() const
    {
        return m_p_impl->escape_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::space_impl() const
    {
        return m_p_impl->space_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::page_up_impl() const
    {
        return m_p_impl->page_up_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::page_down_impl() const
    {
        return m_p_impl->page_down_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::end_impl() const
    {
        return m_p_impl->end_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::home_impl() const
    {
        return m_p_impl->home_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::left_impl() const
    {
        return m_p_impl->left_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::up_impl() const
    {
        return m_p_impl->up_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::right_impl() const
    {
        return m_p_impl->right_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::down_impl() const
    {
        return m_p_impl->down_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::insert_impl() const
    {
        return m_p_impl->insert_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::del_impl() const
    {
        return m_p_impl->del_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_0_impl() const
    {
        return m_p_impl->char_0_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_1_impl() const
    {
        return m_p_impl->char_1_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_2_impl() const
    {
        return m_p_impl->char_2_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_3_impl() const
    {
        return m_p_impl->char_3_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_4_impl() const
    {
        return m_p_impl->char_4_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_5_impl() const
    {
        return m_p_impl->char_5_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_6_impl() const
    {
        return m_p_impl->char_6_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_7_impl() const
    {
        return m_p_impl->char_7_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_8_impl() const
    {
        return m_p_impl->char_8_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_9_impl() const
    {
        return m_p_impl->char_9_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_a_impl() const
    {
        return m_p_impl->char_a_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_b_impl() const
    {
        return m_p_impl->char_b_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_c_impl() const
    {
        return m_p_impl->char_c_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_d_impl() const
    {
        return m_p_impl->char_d_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_e_impl() const
    {
        return m_p_impl->char_e_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_f_impl() const
    {
        return m_p_impl->char_f_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_g_impl() const
    {
        return m_p_impl->char_g_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_h_impl() const
    {
        return m_p_impl->char_h_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_i_impl() const
    {
        return m_p_impl->char_i_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_j_impl() const
    {
        return m_p_impl->char_j_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_k_impl() const
    {
        return m_p_impl->char_k_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_l_impl() const
    {
        return m_p_impl->char_l_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_m_impl() const
    {
        return m_p_impl->char_m_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_n_impl() const
    {
        return m_p_impl->char_n_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_o_impl() const
    {
        return m_p_impl->char_o_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_p_impl() const
    {
        return m_p_impl->char_p_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_q_impl() const
    {
        return m_p_impl->char_q_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_r_impl() const
    {
        return m_p_impl->char_r_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_s_impl() const
    {
        return m_p_impl->char_s_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_t_impl() const
    {
        return m_p_impl->char_t_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_u_impl() const
    {
        return m_p_impl->char_u_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_v_impl() const
    {
        return m_p_impl->char_v_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_w_impl() const
    {
        return m_p_impl->char_w_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_x_impl() const
    {
        return m_p_impl->char_x_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_y_impl() const
    {
        return m_p_impl->char_y_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_z_impl() const
    {
        return m_p_impl->char_z_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f1_impl() const
    {
        return m_p_impl->f1_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f2_impl() const
    {
        return m_p_impl->f2_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f3_impl() const
    {
        return m_p_impl->f3_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f4_impl() const
    {
        return m_p_impl->f4_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f5_impl() const
    {
        return m_p_impl->f5_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f6_impl() const
    {
        return m_p_impl->f6_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f7_impl() const
    {
        return m_p_impl->f7_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f8_impl() const
    {
        return m_p_impl->f8_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f9_impl() const
    {
        return m_p_impl->f9_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f10_impl() const
    {
        return m_p_impl->f10_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f11_impl() const
    {
        return m_p_impl->f11_impl();
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f12_impl() const
    {
        return m_p_impl->f12_impl();
    }

    virtual_key::string_type virtual_key::to_combined_string_impl(const std::vector<string_type>& key_strings) const
    {
        return m_p_impl->to_combined_string_impl(key_strings);
    }
}
