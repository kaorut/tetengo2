/*! \file
    \brief The definition of tetengo2::gui::virtual_key.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_VIRTUALKEY_H)
#define TETENGO2_GUI_VIRTUALKEY_H

#include <cassert>
#include <unordered_map>
#include <utility>

#include <boost/operators.hpp>


namespace tetengo2 { namespace gui {
    /*!
        \brief The class template for virtual keys.

        \tparam String  A string type.
        \tparam Details A detail implementation type.
    */
    template <typename String, typename Details>
    class virtual_key : private boost::equality_comparable<virtual_key<String, Details>>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The details type.
        using details_type = Details;

        //! The code type.
        using code_type = typename details_type::code_type;


        // static functions

        /*!
            \brief Finds the virtual key by a code.

            \param code A code.

            \return The pointer to the virtual key. Or nullptr when no corresponding virtual key to the code.
        */
        static const virtual_key* find_by_code(const code_type code)
        {
            const auto found = key_map().find(code);
            return found != key_map().end() ? &found->second : nullptr;
        }

        //! Returns the virtual key for BackSpace.
        //! \return The virtual key.
        static const virtual_key& backspace()
        {
            const auto p_key = find_by_code(details_type::template backspace<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Tab.
        //! \return The virtual key.
        static const virtual_key& tab()
        {
            const auto p_key = find_by_code(details_type::template tab<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Enter.
        //! \return The virtual key.
        static const virtual_key& enter()
        {
            const auto p_key = find_by_code(details_type::template enter<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Shift.
        //! \return The virtual key.
        static const virtual_key& shift()
        {
            const auto p_key = find_by_code(details_type::template shift<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Control.
        //! \return The virtual key.
        static const virtual_key& control()
        {
            const auto p_key = find_by_code(details_type::template control<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Meta.
        //! \return The virtual key.
        static const virtual_key& meta()
        {
            const auto p_key = find_by_code(details_type::template meta<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Escape.
        //! \return The virtual key.
        static const virtual_key& escape()
        {
            const auto p_key = find_by_code(details_type::template escape<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Space.
        //! \return The virtual key.
        static const virtual_key& space()
        {
            const auto p_key = find_by_code(details_type::template space<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for PageUp.
        //! \return The virtual key.
        static const virtual_key& page_up()
        {
            const auto p_key = find_by_code(details_type::template page_up<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for PageDown.
        //! \return The virtual key.
        static const virtual_key& page_down()
        {
            const auto p_key = find_by_code(details_type::template page_down<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for End.
        //! \return The virtual key.
        static const virtual_key& end()
        {
            const auto p_key = find_by_code(details_type::template end<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Home.
        //! \return The virtual key.
        static const virtual_key& home()
        {
            const auto p_key = find_by_code(details_type::template home<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Left.
        //! \return The virtual key.
        static const virtual_key& left()
        {
            const auto p_key = find_by_code(details_type::template left<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Up.
        //! \return The virtual key.
        static const virtual_key& up()
        {
            const auto p_key = find_by_code(details_type::template up<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Right.
        //! \return The virtual key.
        static const virtual_key& right()
        {
            const auto p_key = find_by_code(details_type::template right<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Down.
        //! \return The virtual key.
        static const virtual_key& down()
        {
            const auto p_key = find_by_code(details_type::template down<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Insert.
        //! \return The virtual key.
        static const virtual_key& insert()
        {
            const auto p_key = find_by_code(details_type::template insert<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for Delete.
        //! \return The virtual key.
        static const virtual_key& del()
        {
            const auto p_key = find_by_code(details_type::template del<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '0'.
        //! \return The virtual key.
        static const virtual_key& char_0()
        {
            const auto p_key = find_by_code(details_type::template char_0<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '1'.
        //! \return The virtual key.
        static const virtual_key& char_1()
        {
            const auto p_key = find_by_code(details_type::template char_1<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '2'.
        //! \return The virtual key.
        static const virtual_key& char_2()
        {
            const auto p_key = find_by_code(details_type::template char_2<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '3'.
        //! \return The virtual key.
        static const virtual_key& char_3()
        {
            const auto p_key = find_by_code(details_type::template char_3<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '4'.
        //! \return The virtual key.
        static const virtual_key& char_4()
        {
            const auto p_key = find_by_code(details_type::template char_4<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '5'.
        //! \return The virtual key.
        static const virtual_key& char_5()
        {
            const auto p_key = find_by_code(details_type::template char_5<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '6'.
        //! \return The virtual key.
        static const virtual_key& char_6()
        {
            const auto p_key = find_by_code(details_type::template char_6<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '7'.
        //! \return The virtual key.
        static const virtual_key& char_7()
        {
            const auto p_key = find_by_code(details_type::template char_7<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '8'.
        //! \return The virtual key.
        static const virtual_key& char_8()
        {
            const auto p_key = find_by_code(details_type::template char_8<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for '9'.
        //! \return The virtual key.
        static const virtual_key& char_9()
        {
            const auto p_key = find_by_code(details_type::template char_9<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'A'.
        //! \return The virtual key.
        static const virtual_key& char_a()
        {
            const auto p_key = find_by_code(details_type::template char_a<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'B'.
        //! \return The virtual key.
        static const virtual_key& char_b()
        {
            const auto p_key = find_by_code(details_type::template char_b<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'C'.
        //! \return The virtual key.
        static const virtual_key& char_c()
        {
            const auto p_key = find_by_code(details_type::template char_c<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'D'.
        //! \return The virtual key.
        static const virtual_key& char_d()
        {
            const auto p_key = find_by_code(details_type::template char_d<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'E'.
        //! \return The virtual key.
        static const virtual_key& char_e()
        {
            const auto p_key = find_by_code(details_type::template char_e<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'F'.
        //! \return The virtual key.
        static const virtual_key& char_f()
        {
            const auto p_key = find_by_code(details_type::template char_f<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'G'.
        //! \return The virtual key.
        static const virtual_key& char_g()
        {
            const auto p_key = find_by_code(details_type::template char_g<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'H'.
        //! \return The virtual key.
        static const virtual_key& char_h()
        {
            const auto p_key = find_by_code(details_type::template char_h<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'I'.
        //! \return The virtual key.
        static const virtual_key& char_i()
        {
            const auto p_key = find_by_code(details_type::template char_i<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'J'.
        //! \return The virtual key.
        static const virtual_key& char_j()
        {
            const auto p_key = find_by_code(details_type::template char_j<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'K'.
        //! \return The virtual key.
        static const virtual_key& char_k()
        {
            const auto p_key = find_by_code(details_type::template char_k<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'L'.
        //! \return The virtual key.
        static const virtual_key& char_l()
        {
            const auto p_key = find_by_code(details_type::template char_l<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'M'.
        //! \return The virtual key.
        static const virtual_key& char_m()
        {
            const auto p_key = find_by_code(details_type::template char_m<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'N'.
        //! \return The virtual key.
        static const virtual_key& char_n()
        {
            const auto p_key = find_by_code(details_type::template char_n<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'O'.
        //! \return The virtual key.
        static const virtual_key& char_o()
        {
            const auto p_key = find_by_code(details_type::template char_o<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'P'.
        //! \return The virtual key.
        static const virtual_key& char_p()
        {
            const auto p_key = find_by_code(details_type::template char_p<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'Q'.
        //! \return The virtual key.
        static const virtual_key& char_q()
        {
            const auto p_key = find_by_code(details_type::template char_q<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'R'.
        //! \return The virtual key.
        static const virtual_key& char_r()
        {
            const auto p_key = find_by_code(details_type::template char_r<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'S'.
        //! \return The virtual key.
        static const virtual_key& char_s()
        {
            const auto p_key = find_by_code(details_type::template char_s<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'T'.
        //! \return The virtual key.
        static const virtual_key& char_t()
        {
            const auto p_key = find_by_code(details_type::template char_t<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'U'.
        //! \return The virtual key.
        static const virtual_key& char_u()
        {
            const auto p_key = find_by_code(details_type::template char_u<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'V'.
        //! \return The virtual key.
        static const virtual_key& char_v()
        {
            const auto p_key = find_by_code(details_type::template char_v<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'W'.
        //! \return The virtual key.
        static const virtual_key& char_w()
        {
            const auto p_key = find_by_code(details_type::template char_w<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'X'.
        //! \return The virtual key.
        static const virtual_key& char_x()
        {
            const auto p_key = find_by_code(details_type::template char_x<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'Y'.
        //! \return The virtual key.
        static const virtual_key& char_y()
        {
            const auto p_key = find_by_code(details_type::template char_y<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for 'Z'.
        //! \return The virtual key.
        static const virtual_key& char_z()
        {
            const auto p_key = find_by_code(details_type::template char_z<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F1.
        //! \return The virtual key.
        static const virtual_key& f1()
        {
            const auto p_key = find_by_code(details_type::template f1<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F2.
        //! \return The virtual key.
        static const virtual_key& f2()
        {
            const auto p_key = find_by_code(details_type::template f2<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F3.
        //! \return The virtual key.
        static const virtual_key& f3()
        {
            const auto p_key = find_by_code(details_type::template f3<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F4.
        //! \return The virtual key.
        static const virtual_key& f4()
        {
            const auto p_key = find_by_code(details_type::template f4<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F5.
        //! \return The virtual key.
        static const virtual_key& f5()
        {
            const auto p_key = find_by_code(details_type::template f5<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F6.
        //! \return The virtual key.
        static const virtual_key& f6()
        {
            const auto p_key = find_by_code(details_type::template f6<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F7.
        //! \return The virtual key.
        static const virtual_key& f7()
        {
            const auto p_key = find_by_code(details_type::template f7<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F8.
        //! \return The virtual key.
        static const virtual_key& f8()
        {
            const auto p_key = find_by_code(details_type::template f8<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F9.
        //! \return The virtual key.
        static const virtual_key& f9()
        {
            const auto p_key = find_by_code(details_type::template f9<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F10.
        //! \return The virtual key.
        static const virtual_key& f10()
        {
            const auto p_key = find_by_code(details_type::template f10<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F11.
        //! \return The virtual key.
        static const virtual_key& f11()
        {
            const auto p_key = find_by_code(details_type::template f11<string_type>().first);
            assert(p_key);
            return *p_key;
        }

        //! Returns the virtual key for F12.
        //! \return The virtual key.
        static const virtual_key& f12()
        {
            const auto p_key = find_by_code(details_type::template f12<string_type>().first);
            assert(p_key);
            return *p_key;
        }


        // functions

        /*!
            \brief Checks whether one virtual key is equal to another.

            \param one     One virtual key.
            \param another Another virtual key.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const virtual_key& one, const virtual_key& another)
        {
            return one.m_code == another.m_code;
        }

        /*!
            \brief Returns the code.

            \return The code.
        */
        code_type code() const
        {
            return m_code;
        }

        /*!
            \brief Returns the string representation.

            \return The string representation.
        */
        const string_type& to_string() const
        {
            return m_string;
        }


    private:
        // types

        using code_and_string_type = std::pair<code_type, string_type>;

        using key_map_type = std::unordered_map<code_type, virtual_key>;


        // static functions

        static const key_map_type& key_map()
        {
            static const auto key_map = build_key_map();
            return key_map;
        }

        static key_map_type build_key_map()
        {
            key_map_type key_map{};

            insert_key(key_map, details_type::template backspace<string_type>());
            insert_key(key_map, details_type::template tab<string_type>());
            insert_key(key_map, details_type::template enter<string_type>());
            insert_key(key_map, details_type::template shift<string_type>());
            insert_key(key_map, details_type::template control<string_type>());
            insert_key(key_map, details_type::template meta<string_type>());
            insert_key(key_map, details_type::template escape<string_type>());
            insert_key(key_map, details_type::template space<string_type>());
            insert_key(key_map, details_type::template page_up<string_type>());
            insert_key(key_map, details_type::template page_down<string_type>());
            insert_key(key_map, details_type::template end<string_type>());
            insert_key(key_map, details_type::template home<string_type>());
            insert_key(key_map, details_type::template left<string_type>());
            insert_key(key_map, details_type::template up<string_type>());
            insert_key(key_map, details_type::template right<string_type>());
            insert_key(key_map, details_type::template down<string_type>());
            insert_key(key_map, details_type::template insert<string_type>());
            insert_key(key_map, details_type::template del<string_type>());
            insert_key(key_map, details_type::template char_0<string_type>());
            insert_key(key_map, details_type::template char_1<string_type>());
            insert_key(key_map, details_type::template char_2<string_type>());
            insert_key(key_map, details_type::template char_3<string_type>());
            insert_key(key_map, details_type::template char_4<string_type>());
            insert_key(key_map, details_type::template char_5<string_type>());
            insert_key(key_map, details_type::template char_6<string_type>());
            insert_key(key_map, details_type::template char_7<string_type>());
            insert_key(key_map, details_type::template char_8<string_type>());
            insert_key(key_map, details_type::template char_9<string_type>());
            insert_key(key_map, details_type::template char_a<string_type>());
            insert_key(key_map, details_type::template char_b<string_type>());
            insert_key(key_map, details_type::template char_c<string_type>());
            insert_key(key_map, details_type::template char_d<string_type>());
            insert_key(key_map, details_type::template char_e<string_type>());
            insert_key(key_map, details_type::template char_f<string_type>());
            insert_key(key_map, details_type::template char_g<string_type>());
            insert_key(key_map, details_type::template char_h<string_type>());
            insert_key(key_map, details_type::template char_i<string_type>());
            insert_key(key_map, details_type::template char_j<string_type>());
            insert_key(key_map, details_type::template char_k<string_type>());
            insert_key(key_map, details_type::template char_l<string_type>());
            insert_key(key_map, details_type::template char_m<string_type>());
            insert_key(key_map, details_type::template char_n<string_type>());
            insert_key(key_map, details_type::template char_o<string_type>());
            insert_key(key_map, details_type::template char_p<string_type>());
            insert_key(key_map, details_type::template char_q<string_type>());
            insert_key(key_map, details_type::template char_r<string_type>());
            insert_key(key_map, details_type::template char_s<string_type>());
            insert_key(key_map, details_type::template char_t<string_type>());
            insert_key(key_map, details_type::template char_u<string_type>());
            insert_key(key_map, details_type::template char_v<string_type>());
            insert_key(key_map, details_type::template char_w<string_type>());
            insert_key(key_map, details_type::template char_x<string_type>());
            insert_key(key_map, details_type::template char_y<string_type>());
            insert_key(key_map, details_type::template char_z<string_type>());
            insert_key(key_map, details_type::template f1<string_type>());
            insert_key(key_map, details_type::template f2<string_type>());
            insert_key(key_map, details_type::template f3<string_type>());
            insert_key(key_map, details_type::template f4<string_type>());
            insert_key(key_map, details_type::template f5<string_type>());
            insert_key(key_map, details_type::template f6<string_type>());
            insert_key(key_map, details_type::template f7<string_type>());
            insert_key(key_map, details_type::template f8<string_type>());
            insert_key(key_map, details_type::template f9<string_type>());
            insert_key(key_map, details_type::template f10<string_type>());
            insert_key(key_map, details_type::template f11<string_type>());
            insert_key(key_map, details_type::template f12<string_type>());

            return key_map;
        }

        static void insert_key(key_map_type& key_map, code_and_string_type code_and_string)
        {
            const auto code = code_and_string.first;
            key_map.insert(std::make_pair(code, virtual_key{ std::move(code_and_string) }));
        }


        // constructors

        explicit virtual_key(code_and_string_type code_and_string)
        : m_code(code_and_string.first), m_string(std::move(code_and_string.second))
        {}


        // variables

        code_type m_code;

        string_type m_string;
    };


}}


#endif
