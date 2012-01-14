/*! \file
    \brief The definition of tetengo2::gui::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_VIRTUALKEY_H)
#define TETENGO2_GUI_VIRTUALKEY_H

#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for virtual keys.

        \tparam Details A detail implementation type.
    */
    template <typename Details>
    class virtual_key :
        private boost::noncopyable,
        private boost::equality_comparable<virtual_key<Details>>
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

        //! Returns the virtual key for '0'.
        //! \return The virtual key.
        static const virtual_key& char_0()
        {
            static const virtual_key singleton(details_type::char_0());
            return singleton;
        }

        //! Returns the virtual key for '1'.
        //! \return The virtual key.
        static const virtual_key& char_1()
        {
            static const virtual_key singleton(details_type::char_1());
            return singleton;
        }

        //! Returns the virtual key for '2'.
        //! \return The virtual key.
        static const virtual_key& char_2()
        {
            static const virtual_key singleton(details_type::char_2());
            return singleton;
        }

        //! Returns the virtual key for '3'.
        //! \return The virtual key.
        static const virtual_key& char_3()
        {
            static const virtual_key singleton(details_type::char_3());
            return singleton;
        }

        //! Returns the virtual key for '4'.
        //! \return The virtual key.
        static const virtual_key& char_4()
        {
            static const virtual_key singleton(details_type::char_4());
            return singleton;
        }

        //! Returns the virtual key for '5'.
        //! \return The virtual key.
        static const virtual_key& char_5()
        {
            static const virtual_key singleton(details_type::char_5());
            return singleton;
        }

        //! Returns the virtual key for '6'.
        //! \return The virtual key.
        static const virtual_key& char_6()
        {
            static const virtual_key singleton(details_type::char_6());
            return singleton;
        }

        //! Returns the virtual key for '7'.
        //! \return The virtual key.
        static const virtual_key& char_7()
        {
            static const virtual_key singleton(details_type::char_7());
            return singleton;
        }

        //! Returns the virtual key for '8'.
        //! \return The virtual key.
        static const virtual_key& char_8()
        {
            static const virtual_key singleton(details_type::char_8());
            return singleton;
        }

        //! Returns the virtual key for '9'.
        //! \return The virtual key.
        static const virtual_key& char_9()
        {
            static const virtual_key singleton(details_type::char_9());
            return singleton;
        }

        //! Returns the virtual key for 'A'.
        //! \return The virtual key.
        static const virtual_key& char_a()
        {
            static const virtual_key singleton(details_type::char_a());
            return singleton;
        }

        //! Returns the virtual key for 'B'.
        //! \return The virtual key.
        static const virtual_key& char_b()
        {
            static const virtual_key singleton(details_type::char_b());
            return singleton;
        }

        //! Returns the virtual key for 'C'.
        //! \return The virtual key.
        static const virtual_key& char_c()
        {
            static const virtual_key singleton(details_type::char_c());
            return singleton;
        }

        //! Returns the virtual key for 'D'.
        //! \return The virtual key.
        static const virtual_key& char_d()
        {
            static const virtual_key singleton(details_type::char_d());
            return singleton;
        }

        //! Returns the virtual key for 'E'.
        //! \return The virtual key.
        static const virtual_key& char_e()
        {
            static const virtual_key singleton(details_type::char_e());
            return singleton;
        }

        //! Returns the virtual key for 'F'.
        //! \return The virtual key.
        static const virtual_key& char_f()
        {
            static const virtual_key singleton(details_type::char_f());
            return singleton;
        }

        //! Returns the virtual key for 'G'.
        //! \return The virtual key.
        static const virtual_key& char_g()
        {
            static const virtual_key singleton(details_type::char_g());
            return singleton;
        }

        //! Returns the virtual key for 'H'.
        //! \return The virtual key.
        static const virtual_key& char_h()
        {
            static const virtual_key singleton(details_type::char_h());
            return singleton;
        }

        //! Returns the virtual key for 'I'.
        //! \return The virtual key.
        static const virtual_key& char_i()
        {
            static const virtual_key singleton(details_type::char_i());
            return singleton;
        }

        //! Returns the virtual key for 'J'.
        //! \return The virtual key.
        static const virtual_key& char_j()
        {
            static const virtual_key singleton(details_type::char_j());
            return singleton;
        }

        //! Returns the virtual key for 'K'.
        //! \return The virtual key.
        static const virtual_key& char_k()
        {
            static const virtual_key singleton(details_type::char_k());
            return singleton;
        }

        //! Returns the virtual key for 'L'.
        //! \return The virtual key.
        static const virtual_key& char_l()
        {
            static const virtual_key singleton(details_type::char_l());
            return singleton;
        }

        //! Returns the virtual key for 'M'.
        //! \return The virtual key.
        static const virtual_key& char_m()
        {
            static const virtual_key singleton(details_type::char_m());
            return singleton;
        }

        //! Returns the virtual key for 'N'.
        //! \return The virtual key.
        static const virtual_key& char_n()
        {
            static const virtual_key singleton(details_type::char_n());
            return singleton;
        }

        //! Returns the virtual key for 'O'.
        //! \return The virtual key.
        static const virtual_key& char_o()
        {
            static const virtual_key singleton(details_type::char_o());
            return singleton;
        }

        //! Returns the virtual key for 'P'.
        //! \return The virtual key.
        static const virtual_key& char_p()
        {
            static const virtual_key singleton(details_type::char_p());
            return singleton;
        }

        //! Returns the virtual key for 'Q'.
        //! \return The virtual key.
        static const virtual_key& char_q()
        {
            static const virtual_key singleton(details_type::char_q());
            return singleton;
        }

        //! Returns the virtual key for 'R'.
        //! \return The virtual key.
        static const virtual_key& char_r()
        {
            static const virtual_key singleton(details_type::char_r());
            return singleton;
        }

        //! Returns the virtual key for 'S'.
        //! \return The virtual key.
        static const virtual_key& char_s()
        {
            static const virtual_key singleton(details_type::char_s());
            return singleton;
        }

        //! Returns the virtual key for 'T'.
        //! \return The virtual key.
        static const virtual_key& char_t()
        {
            static const virtual_key singleton(details_type::char_t());
            return singleton;
        }

        //! Returns the virtual key for 'U'.
        //! \return The virtual key.
        static const virtual_key& char_u()
        {
            static const virtual_key singleton(details_type::char_u());
            return singleton;
        }

        //! Returns the virtual key for 'V'.
        //! \return The virtual key.
        static const virtual_key& char_v()
        {
            static const virtual_key singleton(details_type::char_v());
            return singleton;
        }

        //! Returns the virtual key for 'W'.
        //! \return The virtual key.
        static const virtual_key& char_w()
        {
            static const virtual_key singleton(details_type::char_w());
            return singleton;
        }

        //! Returns the virtual key for 'X'.
        //! \return The virtual key.
        static const virtual_key& char_x()
        {
            static const virtual_key singleton(details_type::char_x());
            return singleton;
        }

        //! Returns the virtual key for 'Y'.
        //! \return The virtual key.
        static const virtual_key& char_y()
        {
            static const virtual_key singleton(details_type::char_y());
            return singleton;
        }

        //! Returns the virtual key for 'Z'.
        //! \return The virtual key.
        static const virtual_key& char_z()
        {
            static const virtual_key singleton(details_type::char_z());
            return singleton;
        }

        //! Returns the virtual key for F1.
        //! \return The virtual key.
        static const virtual_key& f1()
        {
            static const virtual_key singleton(details_type::f1());
            return singleton;
        }

        //! Returns the virtual key for F2.
        //! \return The virtual key.
        static const virtual_key& f2()
        {
            static const virtual_key singleton(details_type::f2());
            return singleton;
        }

        //! Returns the virtual key for F3.
        //! \return The virtual key.
        static const virtual_key& f3()
        {
            static const virtual_key singleton(details_type::f3());
            return singleton;
        }

        //! Returns the virtual key for F4.
        //! \return The virtual key.
        static const virtual_key& f4()
        {
            static const virtual_key singleton(details_type::f4());
            return singleton;
        }

        //! Returns the virtual key for F5.
        //! \return The virtual key.
        static const virtual_key& f5()
        {
            static const virtual_key singleton(details_type::f5());
            return singleton;
        }

        //! Returns the virtual key for F6.
        //! \return The virtual key.
        static const virtual_key& f6()
        {
            static const virtual_key singleton(details_type::f6());
            return singleton;
        }

        //! Returns the virtual key for F7.
        //! \return The virtual key.
        static const virtual_key& f7()
        {
            static const virtual_key singleton(details_type::f7());
            return singleton;
        }

        //! Returns the virtual key for F8.
        //! \return The virtual key.
        static const virtual_key& f8()
        {
            static const virtual_key singleton(details_type::f8());
            return singleton;
        }

        //! Returns the virtual key for F9.
        //! \return The virtual key.
        static const virtual_key& f9()
        {
            static const virtual_key singleton(details_type::f9());
            return singleton;
        }

        //! Returns the virtual key for F10.
        //! \return The virtual key.
        static const virtual_key& f10()
        {
            static const virtual_key singleton(details_type::f10());
            return singleton;
        }

        //! Returns the virtual key for F11.
        //! \return The virtual key.
        static const virtual_key& f11()
        {
            static const virtual_key singleton(details_type::f11());
            return singleton;
        }

        //! Returns the virtual key for F12.
        //! \return The virtual key.
        static const virtual_key& f12()
        {
            static const virtual_key singleton(details_type::f12());
            return singleton;
        }


        // functions

        /*!
            \brief Checks whether one virtual key is equal to another.

            \param one     One virtual key.
            \param another Another virtual key.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(
            const virtual_key& one,
            const virtual_key& another
        )
        {
            return one.m_code == another.m_code;
        }

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

        explicit virtual_key(code_and_string_type&& code_and_string)
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
