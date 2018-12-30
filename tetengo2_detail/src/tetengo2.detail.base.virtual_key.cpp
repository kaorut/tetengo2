/*! \file
    \brief The definition of tetengo2::detail::base::virtual_key.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/virtual_key.h>


namespace tetengo2::detail::base {
    class virtual_key::impl : private boost::noncopyable
    {
    public:
        // types

        using code_type = virtual_key::code_type;

        using string_type = virtual_key::string_type;


        // functions

        std::pair<code_type, string_type> backspace(const virtual_key& base) const
        {
            return base.backspace_impl();
        }

        std::pair<code_type, string_type> tab(const virtual_key& base) const
        {
            return base.tab_impl();
        }

        std::pair<code_type, string_type> enter(const virtual_key& base) const
        {
            return base.enter_impl();
        }

        std::pair<code_type, string_type> shift(const virtual_key& base) const
        {
            return base.shift_impl();
        }

        std::pair<code_type, string_type> control(const virtual_key& base) const
        {
            return base.control_impl();
        }

        std::pair<code_type, string_type> meta(const virtual_key& base) const
        {
            return base.meta_impl();
        }

        std::pair<code_type, string_type> escape(const virtual_key& base) const
        {
            return base.escape_impl();
        }

        std::pair<code_type, string_type> space(const virtual_key& base) const
        {
            return base.space_impl();
        }

        std::pair<code_type, string_type> page_up(const virtual_key& base) const
        {
            return base.page_up_impl();
        }

        std::pair<code_type, string_type> page_down(const virtual_key& base) const
        {
            return base.page_down_impl();
        }

        std::pair<code_type, string_type> end(const virtual_key& base) const
        {
            return base.end_impl();
        }

        std::pair<code_type, string_type> home(const virtual_key& base) const
        {
            return base.home_impl();
        }

        std::pair<code_type, string_type> left(const virtual_key& base) const
        {
            return base.left_impl();
        }

        std::pair<code_type, string_type> up(const virtual_key& base) const
        {
            return base.up_impl();
        }

        std::pair<code_type, string_type> right(const virtual_key& base) const
        {
            return base.right_impl();
        }

        std::pair<code_type, string_type> down(const virtual_key& base) const
        {
            return base.down_impl();
        }

        std::pair<code_type, string_type> insert(const virtual_key& base) const
        {
            return base.insert_impl();
        }

        std::pair<code_type, string_type> del(const virtual_key& base) const
        {
            return base.del_impl();
        }

        std::pair<code_type, string_type> char_0(const virtual_key& base) const
        {
            return base.char_0_impl();
        }

        std::pair<code_type, string_type> char_1(const virtual_key& base) const
        {
            return base.char_1_impl();
        }

        std::pair<code_type, string_type> char_2(const virtual_key& base) const
        {
            return base.char_2_impl();
        }

        std::pair<code_type, string_type> char_3(const virtual_key& base) const
        {
            return base.char_3_impl();
        }

        std::pair<code_type, string_type> char_4(const virtual_key& base) const
        {
            return base.char_4_impl();
        }

        std::pair<code_type, string_type> char_5(const virtual_key& base) const
        {
            return base.char_5_impl();
        }

        std::pair<code_type, string_type> char_6(const virtual_key& base) const
        {
            return base.char_6_impl();
        }

        std::pair<code_type, string_type> char_7(const virtual_key& base) const
        {
            return base.char_7_impl();
        }

        std::pair<code_type, string_type> char_8(const virtual_key& base) const
        {
            return base.char_8_impl();
        }

        std::pair<code_type, string_type> char_9(const virtual_key& base) const
        {
            return base.char_9_impl();
        }

        std::pair<code_type, string_type> char_a(const virtual_key& base) const
        {
            return base.char_a_impl();
        }

        std::pair<code_type, string_type> char_b(const virtual_key& base) const
        {
            return base.char_b_impl();
        }

        std::pair<code_type, string_type> char_c(const virtual_key& base) const
        {
            return base.char_c_impl();
        }

        std::pair<code_type, string_type> char_d(const virtual_key& base) const
        {
            return base.char_d_impl();
        }

        std::pair<code_type, string_type> char_e(const virtual_key& base) const
        {
            return base.char_e_impl();
        }

        std::pair<code_type, string_type> char_f(const virtual_key& base) const
        {
            return base.char_f_impl();
        }

        std::pair<code_type, string_type> char_g(const virtual_key& base) const
        {
            return base.char_g_impl();
        }

        std::pair<code_type, string_type> char_h(const virtual_key& base) const
        {
            return base.char_h_impl();
        }

        std::pair<code_type, string_type> char_i(const virtual_key& base) const
        {
            return base.char_i_impl();
        }

        std::pair<code_type, string_type> char_j(const virtual_key& base) const
        {
            return base.char_j_impl();
        }

        std::pair<code_type, string_type> char_k(const virtual_key& base) const
        {
            return base.char_k_impl();
        }

        std::pair<code_type, string_type> char_l(const virtual_key& base) const
        {
            return base.char_l_impl();
        }

        std::pair<code_type, string_type> char_m(const virtual_key& base) const
        {
            return base.char_m_impl();
        }

        std::pair<code_type, string_type> char_n(const virtual_key& base) const
        {
            return base.char_n_impl();
        }

        std::pair<code_type, string_type> char_o(const virtual_key& base) const
        {
            return base.char_o_impl();
        }

        std::pair<code_type, string_type> char_p(const virtual_key& base) const
        {
            return base.char_p_impl();
        }

        std::pair<code_type, string_type> char_q(const virtual_key& base) const
        {
            return base.char_q_impl();
        }

        std::pair<code_type, string_type> char_r(const virtual_key& base) const
        {
            return base.char_r_impl();
        }

        std::pair<code_type, string_type> char_s(const virtual_key& base) const
        {
            return base.char_s_impl();
        }

        std::pair<code_type, string_type> char_t(const virtual_key& base) const
        {
            return base.char_t_impl();
        }

        std::pair<code_type, string_type> char_u(const virtual_key& base) const
        {
            return base.char_u_impl();
        }

        std::pair<code_type, string_type> char_v(const virtual_key& base) const
        {
            return base.char_v_impl();
        }

        std::pair<code_type, string_type> char_w(const virtual_key& base) const
        {
            return base.char_w_impl();
        }

        std::pair<code_type, string_type> char_x(const virtual_key& base) const
        {
            return base.char_x_impl();
        }

        std::pair<code_type, string_type> char_y(const virtual_key& base) const
        {
            return base.char_y_impl();
        }

        std::pair<code_type, string_type> char_z(const virtual_key& base) const
        {
            return base.char_z_impl();
        }

        std::pair<code_type, string_type> f1(const virtual_key& base) const
        {
            return base.f1_impl();
        }

        std::pair<code_type, string_type> f2(const virtual_key& base) const
        {
            return base.f2_impl();
        }

        std::pair<code_type, string_type> f3(const virtual_key& base) const
        {
            return base.f3_impl();
        }

        std::pair<code_type, string_type> f4(const virtual_key& base) const
        {
            return base.f4_impl();
        }

        std::pair<code_type, string_type> f5(const virtual_key& base) const
        {
            return base.f5_impl();
        }

        std::pair<code_type, string_type> f6(const virtual_key& base) const
        {
            return base.f6_impl();
        }

        std::pair<code_type, string_type> f7(const virtual_key& base) const
        {
            return base.f7_impl();
        }

        std::pair<code_type, string_type> f8(const virtual_key& base) const
        {
            return base.f8_impl();
        }

        std::pair<code_type, string_type> f9(const virtual_key& base) const
        {
            return base.f9_impl();
        }

        std::pair<code_type, string_type> f10(const virtual_key& base) const
        {
            return base.f10_impl();
        }

        std::pair<code_type, string_type> f11(const virtual_key& base) const
        {
            return base.f11_impl();
        }

        std::pair<code_type, string_type> f12(const virtual_key& base) const
        {
            return base.f12_impl();
        }

        string_type to_combined_string(const std::vector<string_type>& key_strings, const virtual_key& base) const
        {
            return base.to_combined_string_impl(key_strings);
        }


    private:
    };


    virtual_key::~virtual_key() = default;

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::backspace() const
    {
        return m_p_impl->backspace(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::tab() const
    {
        return m_p_impl->tab(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::enter() const
    {
        return m_p_impl->enter(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::shift() const
    {
        return m_p_impl->shift(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::control() const
    {
        return m_p_impl->control(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::meta() const
    {
        return m_p_impl->meta(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::escape() const
    {
        return m_p_impl->escape(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::space() const
    {
        return m_p_impl->space(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::page_up() const
    {
        return m_p_impl->page_up(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::page_down() const
    {
        return m_p_impl->page_down(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::end() const
    {
        return m_p_impl->end(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::home() const
    {
        return m_p_impl->home(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::left() const
    {
        return m_p_impl->left(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::up() const
    {
        return m_p_impl->up(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::right() const
    {
        return m_p_impl->right(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::down() const
    {
        return m_p_impl->down(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::insert() const
    {
        return m_p_impl->insert(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::del() const
    {
        return m_p_impl->del(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_0() const
    {
        return m_p_impl->char_0(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_1() const
    {
        return m_p_impl->char_1(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_2() const
    {
        return m_p_impl->char_2(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_3() const
    {
        return m_p_impl->char_3(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_4() const
    {
        return m_p_impl->char_4(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_5() const
    {
        return m_p_impl->char_5(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_6() const
    {
        return m_p_impl->char_6(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_7() const
    {
        return m_p_impl->char_7(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_8() const
    {
        return m_p_impl->char_8(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_9() const
    {
        return m_p_impl->char_9(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_a() const
    {
        return m_p_impl->char_a(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_b() const
    {
        return m_p_impl->char_b(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_c() const
    {
        return m_p_impl->char_c(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_d() const
    {
        return m_p_impl->char_d(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_e() const
    {
        return m_p_impl->char_e(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_f() const
    {
        return m_p_impl->char_f(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_g() const
    {
        return m_p_impl->char_g(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_h() const
    {
        return m_p_impl->char_h(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_i() const
    {
        return m_p_impl->char_i(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_j() const
    {
        return m_p_impl->char_j(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_k() const
    {
        return m_p_impl->char_k(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_l() const
    {
        return m_p_impl->char_l(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_m() const
    {
        return m_p_impl->char_m(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_n() const
    {
        return m_p_impl->char_n(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_o() const
    {
        return m_p_impl->char_o(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_p() const
    {
        return m_p_impl->char_p(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_q() const
    {
        return m_p_impl->char_q(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_r() const
    {
        return m_p_impl->char_r(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_s() const
    {
        return m_p_impl->char_s(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_t() const
    {
        return m_p_impl->char_t(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_u() const
    {
        return m_p_impl->char_u(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_v() const
    {
        return m_p_impl->char_v(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_w() const
    {
        return m_p_impl->char_w(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_x() const
    {
        return m_p_impl->char_x(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_y() const
    {
        return m_p_impl->char_y(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::char_z() const
    {
        return m_p_impl->char_z(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f1() const
    {
        return m_p_impl->f1(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f2() const
    {
        return m_p_impl->f2(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f3() const
    {
        return m_p_impl->f3(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f4() const
    {
        return m_p_impl->f4(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f5() const
    {
        return m_p_impl->f5(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f6() const
    {
        return m_p_impl->f6(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f7() const
    {
        return m_p_impl->f7(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f8() const
    {
        return m_p_impl->f8(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f9() const
    {
        return m_p_impl->f9(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f10() const
    {
        return m_p_impl->f10(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f11() const
    {
        return m_p_impl->f11(*this);
    }

    std::pair<virtual_key::code_type, virtual_key::string_type> virtual_key::f12() const
    {
        return m_p_impl->f12(*this);
    }

    virtual_key::string_type virtual_key::to_combined_string(const std::vector<string_type>& key_strings) const
    {
        return m_p_impl->to_combined_string(key_strings, *this);
    }

    virtual_key::virtual_key() : m_p_impl{ std::make_unique<impl>() } {}
}
