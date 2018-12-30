/*! \file
    \brief The definition of tetengo2::detail::stub::virtual_key.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_VIRTUALKEY_H)
#define TETENGO2_DETAIL_STUB_VIRTUALKEY_H

#include <memory>
#include <utility>
#include <vector>

#include <tetengo2/detail/base/virtual_key.h>


namespace tetengo2::detail::stub {
    /*!
        \brief The class for a detail implementation of virtual keys.
    */
    class virtual_key : public base::virtual_key
    {
    public:
        // types

        //! The code type.
        using code_type = base::virtual_key::code_type;

        //! The string type.
        using string_type = base::virtual_key::string_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const virtual_key& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~virtual_key();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        virtual_key();


        // virtual functions

        virtual std::pair<code_type, string_type> backspace_impl() const override;

        virtual std::pair<code_type, string_type> tab_impl() const override;

        virtual std::pair<code_type, string_type> enter_impl() const override;

        virtual std::pair<code_type, string_type> shift_impl() const override;

        virtual std::pair<code_type, string_type> control_impl() const override;

        virtual std::pair<code_type, string_type> meta_impl() const override;

        virtual std::pair<code_type, string_type> escape_impl() const override;

        virtual std::pair<code_type, string_type> space_impl() const override;

        virtual std::pair<code_type, string_type> page_up_impl() const override;

        virtual std::pair<code_type, string_type> page_down_impl() const override;

        virtual std::pair<code_type, string_type> end_impl() const override;

        virtual std::pair<code_type, string_type> home_impl() const override;

        virtual std::pair<code_type, string_type> left_impl() const override;

        virtual std::pair<code_type, string_type> up_impl() const override;

        virtual std::pair<code_type, string_type> right_impl() const override;

        virtual std::pair<code_type, string_type> down_impl() const override;

        virtual std::pair<code_type, string_type> insert_impl() const override;

        virtual std::pair<code_type, string_type> del_impl() const override;

        virtual std::pair<code_type, string_type> char_0_impl() const override;

        virtual std::pair<code_type, string_type> char_1_impl() const override;

        virtual std::pair<code_type, string_type> char_2_impl() const override;

        virtual std::pair<code_type, string_type> char_3_impl() const override;

        virtual std::pair<code_type, string_type> char_4_impl() const override;

        virtual std::pair<code_type, string_type> char_5_impl() const override;

        virtual std::pair<code_type, string_type> char_6_impl() const override;

        virtual std::pair<code_type, string_type> char_7_impl() const override;

        virtual std::pair<code_type, string_type> char_8_impl() const override;

        virtual std::pair<code_type, string_type> char_9_impl() const override;

        virtual std::pair<code_type, string_type> char_a_impl() const override;

        virtual std::pair<code_type, string_type> char_b_impl() const override;

        virtual std::pair<code_type, string_type> char_c_impl() const override;

        virtual std::pair<code_type, string_type> char_d_impl() const override;

        virtual std::pair<code_type, string_type> char_e_impl() const override;

        virtual std::pair<code_type, string_type> char_f_impl() const override;

        virtual std::pair<code_type, string_type> char_g_impl() const override;

        virtual std::pair<code_type, string_type> char_h_impl() const override;

        virtual std::pair<code_type, string_type> char_i_impl() const override;

        virtual std::pair<code_type, string_type> char_j_impl() const override;

        virtual std::pair<code_type, string_type> char_k_impl() const override;

        virtual std::pair<code_type, string_type> char_l_impl() const override;

        virtual std::pair<code_type, string_type> char_m_impl() const override;

        virtual std::pair<code_type, string_type> char_n_impl() const override;

        virtual std::pair<code_type, string_type> char_o_impl() const override;

        virtual std::pair<code_type, string_type> char_p_impl() const override;

        virtual std::pair<code_type, string_type> char_q_impl() const override;

        virtual std::pair<code_type, string_type> char_r_impl() const override;

        virtual std::pair<code_type, string_type> char_s_impl() const override;

        virtual std::pair<code_type, string_type> char_t_impl() const override;

        virtual std::pair<code_type, string_type> char_u_impl() const override;

        virtual std::pair<code_type, string_type> char_v_impl() const override;

        virtual std::pair<code_type, string_type> char_w_impl() const override;

        virtual std::pair<code_type, string_type> char_x_impl() const override;

        virtual std::pair<code_type, string_type> char_y_impl() const override;

        virtual std::pair<code_type, string_type> char_z_impl() const override;

        virtual std::pair<code_type, string_type> f1_impl() const override;

        virtual std::pair<code_type, string_type> f2_impl() const override;

        virtual std::pair<code_type, string_type> f3_impl() const override;

        virtual std::pair<code_type, string_type> f4_impl() const override;

        virtual std::pair<code_type, string_type> f5_impl() const override;

        virtual std::pair<code_type, string_type> f6_impl() const override;

        virtual std::pair<code_type, string_type> f7_impl() const override;

        virtual std::pair<code_type, string_type> f8_impl() const override;

        virtual std::pair<code_type, string_type> f9_impl() const override;

        virtual std::pair<code_type, string_type> f10_impl() const override;

        virtual std::pair<code_type, string_type> f11_impl() const override;

        virtual std::pair<code_type, string_type> f12_impl() const override;

        virtual string_type to_combined_string_impl(const std::vector<string_type>& key_strings) const override;
    };
}


#endif
