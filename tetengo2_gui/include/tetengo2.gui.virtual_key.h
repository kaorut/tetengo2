/*! \file
    \brief The definition of tetengo2::gui::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_VIRTUALKEY_H)
#define TETENGO2_GUI_VIRTUALKEY_H

#include <unordered_map>
#include <utility>

#include <boost/operators.hpp>
#include <boost/optional.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for virtual keys.

        \tparam Details A detail implementation type.
    */
    template <typename Details>
    class virtual_key :
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

        /*!
            \brief Finds the virtual key by a code.

            \param code.

            \return The virtual key.
        */
        static boost::optional<const virtual_key&> find_by_code(
            const code_type code
        )
        {
            const typename key_map_type::const_iterator found =
                key_map().find(code);
            if (found == key_map().end())
                return boost::none;

            return boost::make_optional<const virtual_key&>(found->second);
        }

        //! Returns the virtual key for BackSpace.
        //! \return The virtual key.
        static const virtual_key& backspace()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::backspace().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Tab.
        //! \return The virtual key.
        static const virtual_key& tab()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::tab().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Enter.
        //! \return The virtual key.
        static const virtual_key& enter()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::enter().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Shift.
        //! \return The virtual key.
        static const virtual_key& shift()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::shift().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Control.
        //! \return The virtual key.
        static const virtual_key& control()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::control().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Meta.
        //! \return The virtual key.
        static const virtual_key& meta()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::meta().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Escape.
        //! \return The virtual key.
        static const virtual_key& escape()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::escape().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Space.
        //! \return The virtual key.
        static const virtual_key& space()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::space().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for PageUp.
        //! \return The virtual key.
        static const virtual_key& page_up()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::page_up().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for PageDown.
        //! \return The virtual key.
        static const virtual_key& page_down()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::page_down().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for End.
        //! \return The virtual key.
        static const virtual_key& end()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::end().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Home.
        //! \return The virtual key.
        static const virtual_key& home()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::home().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Left.
        //! \return The virtual key.
        static const virtual_key& left()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::left().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Up.
        //! \return The virtual key.
        static const virtual_key& up()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::up().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Right.
        //! \return The virtual key.
        static const virtual_key& right()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::right().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Down.
        //! \return The virtual key.
        static const virtual_key& down()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::down().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Insert.
        //! \return The virtual key.
        static const virtual_key& insert()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::insert().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for Delete.
        //! \return The virtual key.
        static const virtual_key& del()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::del().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '0'.
        //! \return The virtual key.
        static const virtual_key& char_0()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_0().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '1'.
        //! \return The virtual key.
        static const virtual_key& char_1()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_1().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '2'.
        //! \return The virtual key.
        static const virtual_key& char_2()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_2().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '3'.
        //! \return The virtual key.
        static const virtual_key& char_3()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_3().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '4'.
        //! \return The virtual key.
        static const virtual_key& char_4()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_4().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '5'.
        //! \return The virtual key.
        static const virtual_key& char_5()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_5().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '6'.
        //! \return The virtual key.
        static const virtual_key& char_6()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_6().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '7'.
        //! \return The virtual key.
        static const virtual_key& char_7()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_7().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '8'.
        //! \return The virtual key.
        static const virtual_key& char_8()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_8().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for '9'.
        //! \return The virtual key.
        static const virtual_key& char_9()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_9().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'A'.
        //! \return The virtual key.
        static const virtual_key& char_a()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_a().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'B'.
        //! \return The virtual key.
        static const virtual_key& char_b()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_b().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'C'.
        //! \return The virtual key.
        static const virtual_key& char_c()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_c().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'D'.
        //! \return The virtual key.
        static const virtual_key& char_d()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_d().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'E'.
        //! \return The virtual key.
        static const virtual_key& char_e()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_e().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'F'.
        //! \return The virtual key.
        static const virtual_key& char_f()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_f().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'G'.
        //! \return The virtual key.
        static const virtual_key& char_g()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_g().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'H'.
        //! \return The virtual key.
        static const virtual_key& char_h()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_h().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'I'.
        //! \return The virtual key.
        static const virtual_key& char_i()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_i().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'J'.
        //! \return The virtual key.
        static const virtual_key& char_j()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_j().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'K'.
        //! \return The virtual key.
        static const virtual_key& char_k()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_k().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'L'.
        //! \return The virtual key.
        static const virtual_key& char_l()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_l().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'M'.
        //! \return The virtual key.
        static const virtual_key& char_m()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_m().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'N'.
        //! \return The virtual key.
        static const virtual_key& char_n()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_n().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'O'.
        //! \return The virtual key.
        static const virtual_key& char_o()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_o().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'P'.
        //! \return The virtual key.
        static const virtual_key& char_p()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_p().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'Q'.
        //! \return The virtual key.
        static const virtual_key& char_q()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_q().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'R'.
        //! \return The virtual key.
        static const virtual_key& char_r()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_r().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'S'.
        //! \return The virtual key.
        static const virtual_key& char_s()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_s().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'T'.
        //! \return The virtual key.
        static const virtual_key& char_t()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_t().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'U'.
        //! \return The virtual key.
        static const virtual_key& char_u()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_u().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'V'.
        //! \return The virtual key.
        static const virtual_key& char_v()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_v().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'W'.
        //! \return The virtual key.
        static const virtual_key& char_w()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_w().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'X'.
        //! \return The virtual key.
        static const virtual_key& char_x()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_x().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'Y'.
        //! \return The virtual key.
        static const virtual_key& char_y()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_y().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for 'Z'.
        //! \return The virtual key.
        static const virtual_key& char_z()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::char_z().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F1.
        //! \return The virtual key.
        static const virtual_key& f1()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f1().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F2.
        //! \return The virtual key.
        static const virtual_key& f2()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f2().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F3.
        //! \return The virtual key.
        static const virtual_key& f3()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f3().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F4.
        //! \return The virtual key.
        static const virtual_key& f4()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f4().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F5.
        //! \return The virtual key.
        static const virtual_key& f5()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f5().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F6.
        //! \return The virtual key.
        static const virtual_key& f6()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f6().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F7.
        //! \return The virtual key.
        static const virtual_key& f7()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f7().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F8.
        //! \return The virtual key.
        static const virtual_key& f8()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f8().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F9.
        //! \return The virtual key.
        static const virtual_key& f9()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f9().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F10.
        //! \return The virtual key.
        static const virtual_key& f10()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f10().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F11.
        //! \return The virtual key.
        static const virtual_key& f11()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f11().first);
            assert(key);
            return *key;
        }

        //! Returns the virtual key for F12.
        //! \return The virtual key.
        static const virtual_key& f12()
        {
            const boost::optional<const virtual_key&> key =
                find_by_code(details_type::f12().first);
            assert(key);
            return *key;
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

        typedef std::unordered_map<code_type, virtual_key> key_map_type;

        
        // static functions

        static const key_map_type& key_map()
        {
            static const key_map_type key_map = build_key_map();
            return key_map;
        }

        static key_map_type build_key_map()
        {
            key_map_type key_map;

            insert_key(key_map, details_type::backspace());
            insert_key(key_map, details_type::tab());
            insert_key(key_map, details_type::enter());
            insert_key(key_map, details_type::shift());
            insert_key(key_map, details_type::control());
            insert_key(key_map, details_type::meta());
            insert_key(key_map, details_type::escape());
            insert_key(key_map, details_type::space());
            insert_key(key_map, details_type::page_up());
            insert_key(key_map, details_type::page_down());
            insert_key(key_map, details_type::end());
            insert_key(key_map, details_type::home());
            insert_key(key_map, details_type::left());
            insert_key(key_map, details_type::up());
            insert_key(key_map, details_type::right());
            insert_key(key_map, details_type::down());
            insert_key(key_map, details_type::insert());
            insert_key(key_map, details_type::del());
            insert_key(key_map, details_type::char_0());
            insert_key(key_map, details_type::char_1());
            insert_key(key_map, details_type::char_2());
            insert_key(key_map, details_type::char_3());
            insert_key(key_map, details_type::char_4());
            insert_key(key_map, details_type::char_5());
            insert_key(key_map, details_type::char_6());
            insert_key(key_map, details_type::char_7());
            insert_key(key_map, details_type::char_8());
            insert_key(key_map, details_type::char_9());
            insert_key(key_map, details_type::char_a());
            insert_key(key_map, details_type::char_b());
            insert_key(key_map, details_type::char_c());
            insert_key(key_map, details_type::char_d());
            insert_key(key_map, details_type::char_e());
            insert_key(key_map, details_type::char_f());
            insert_key(key_map, details_type::char_g());
            insert_key(key_map, details_type::char_h());
            insert_key(key_map, details_type::char_i());
            insert_key(key_map, details_type::char_j());
            insert_key(key_map, details_type::char_k());
            insert_key(key_map, details_type::char_l());
            insert_key(key_map, details_type::char_m());
            insert_key(key_map, details_type::char_n());
            insert_key(key_map, details_type::char_o());
            insert_key(key_map, details_type::char_p());
            insert_key(key_map, details_type::char_q());
            insert_key(key_map, details_type::char_r());
            insert_key(key_map, details_type::char_s());
            insert_key(key_map, details_type::char_t());
            insert_key(key_map, details_type::char_u());
            insert_key(key_map, details_type::char_v());
            insert_key(key_map, details_type::char_w());
            insert_key(key_map, details_type::char_x());
            insert_key(key_map, details_type::char_y());
            insert_key(key_map, details_type::char_z());
            insert_key(key_map, details_type::f1());
            insert_key(key_map, details_type::f2());
            insert_key(key_map, details_type::f3());
            insert_key(key_map, details_type::f4());
            insert_key(key_map, details_type::f5());
            insert_key(key_map, details_type::f6());
            insert_key(key_map, details_type::f7());
            insert_key(key_map, details_type::f8());
            insert_key(key_map, details_type::f9());
            insert_key(key_map, details_type::f10());
            insert_key(key_map, details_type::f11());
            insert_key(key_map, details_type::f12());

            return key_map;
        }

        static void insert_key(
            key_map_type&          key_map,
            code_and_string_type&& code_and_string
        )
        {
            const code_type code = code_and_string.first;
            key_map.insert(
                std::make_pair(
                    code,
                    virtual_key(
                        std::forward<code_and_string_type>(code_and_string)
                    )
                )
            );
        }


        // constructors

        explicit virtual_key(code_and_string_type&& code_and_string)
        :
        m_code(code_and_string.first),
        m_string(std::move(code_and_string.second))
        {}
        

        // variables

        code_type m_code;

        string_type m_string;


    };


}}


#endif
