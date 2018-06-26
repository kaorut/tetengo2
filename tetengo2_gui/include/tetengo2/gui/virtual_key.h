/*! \file
    \brief The definition of tetengo2::gui::virtual_key.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_VIRTUALKEY_H)
#define TETENGO2_GUI_VIRTUALKEY_H

#include <memory>
#include <utility>
#include <vector>

#include <boost/operators.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::gui {
    /*!
        \brief The class for a virtual key.
    */
    class virtual_key : private boost::equality_comparable<virtual_key>
    {
    public:
        // types

        //! The code type.
        using code_type = int;

        //! The string type.
        using string_type = tetengo2::type_list::string_type;


        // constructors and destructor

        /*!
            \brief Copies a virtual key.

            \param another Another virtual key.
        */
        virtual_key(const virtual_key& another);

        /*!
            \brief Moves a virtual key.

            \param another Another virtual key.
        */
        virtual_key(virtual_key&& another);

        /*!
            \brief Destroys the virtual key.
        */
        ~virtual_key();


        // static functions

        /*!
            \brief Finds the virtual key by a code.

            \param code A code.

            \return The pointer to the virtual key. Or nullptr when no corresponding virtual key to the code.
        */
        static const virtual_key* find_by_code(const code_type code);

        //! Returns the virtual key for BackSpace.
        //! \return The virtual key.
        static const virtual_key& backspace();

        //! Returns the virtual key for Tab.
        //! \return The virtual key.
        static const virtual_key& tab();

        //! Returns the virtual key for Enter.
        //! \return The virtual key.
        static const virtual_key& enter();

        //! Returns the virtual key for Shift.
        //! \return The virtual key.
        static const virtual_key& shift();

        //! Returns the virtual key for Control.
        //! \return The virtual key.
        static const virtual_key& control();

        //! Returns the virtual key for Meta.
        //! \return The virtual key.
        static const virtual_key& meta();

        //! Returns the virtual key for Escape.
        //! \return The virtual key.
        static const virtual_key& escape();

        //! Returns the virtual key for Space.
        //! \return The virtual key.
        static const virtual_key& space();

        //! Returns the virtual key for PageUp.
        //! \return The virtual key.
        static const virtual_key& page_up();

        //! Returns the virtual key for PageDown.
        //! \return The virtual key.
        static const virtual_key& page_down();

        //! Returns the virtual key for End.
        //! \return The virtual key.
        static const virtual_key& end();

        //! Returns the virtual key for Home.
        //! \return The virtual key.
        static const virtual_key& home();

        //! Returns the virtual key for Left.
        //! \return The virtual key.
        static const virtual_key& left();

        //! Returns the virtual key for Up.
        //! \return The virtual key.
        static const virtual_key& up();

        //! Returns the virtual key for Right.
        //! \return The virtual key.
        static const virtual_key& right();

        //! Returns the virtual key for Down.
        //! \return The virtual key.
        static const virtual_key& down();

        //! Returns the virtual key for Insert.
        //! \return The virtual key.
        static const virtual_key& insert();

        //! Returns the virtual key for Delete.
        //! \return The virtual key.
        static const virtual_key& del();

        //! Returns the virtual key for '0'.
        //! \return The virtual key.
        static const virtual_key& char_0();

        //! Returns the virtual key for '1'.
        //! \return The virtual key.
        static const virtual_key& char_1();

        //! Returns the virtual key for '2'.
        //! \return The virtual key.
        static const virtual_key& char_2();

        //! Returns the virtual key for '3'.
        //! \return The virtual key.
        static const virtual_key& char_3();

        //! Returns the virtual key for '4'.
        //! \return The virtual key.
        static const virtual_key& char_4();

        //! Returns the virtual key for '5'.
        //! \return The virtual key.
        static const virtual_key& char_5();

        //! Returns the virtual key for '6'.
        //! \return The virtual key.
        static const virtual_key& char_6();

        //! Returns the virtual key for '7'.
        //! \return The virtual key.
        static const virtual_key& char_7();

        //! Returns the virtual key for '8'.
        //! \return The virtual key.
        static const virtual_key& char_8();

        //! Returns the virtual key for '9'.
        //! \return The virtual key.
        static const virtual_key& char_9();

        //! Returns the virtual key for 'A'.
        //! \return The virtual key.
        static const virtual_key& char_a();

        //! Returns the virtual key for 'B'.
        //! \return The virtual key.
        static const virtual_key& char_b();

        //! Returns the virtual key for 'C'.
        //! \return The virtual key.
        static const virtual_key& char_c();

        //! Returns the virtual key for 'D'.
        //! \return The virtual key.
        static const virtual_key& char_d();

        //! Returns the virtual key for 'E'.
        //! \return The virtual key.
        static const virtual_key& char_e();

        //! Returns the virtual key for 'F'.
        //! \return The virtual key.
        static const virtual_key& char_f();

        //! Returns the virtual key for 'G'.
        //! \return The virtual key.
        static const virtual_key& char_g();

        //! Returns the virtual key for 'H'.
        //! \return The virtual key.
        static const virtual_key& char_h();

        //! Returns the virtual key for 'I'.
        //! \return The virtual key.
        static const virtual_key& char_i();

        //! Returns the virtual key for 'J'.
        //! \return The virtual key.
        static const virtual_key& char_j();

        //! Returns the virtual key for 'K'.
        //! \return The virtual key.
        static const virtual_key& char_k();

        //! Returns the virtual key for 'L'.
        //! \return The virtual key.
        static const virtual_key& char_l();

        //! Returns the virtual key for 'M'.
        //! \return The virtual key.
        static const virtual_key& char_m();

        //! Returns the virtual key for 'N'.
        //! \return The virtual key.
        static const virtual_key& char_n();

        //! Returns the virtual key for 'O'.
        //! \return The virtual key.
        static const virtual_key& char_o();

        //! Returns the virtual key for 'P'.
        //! \return The virtual key.
        static const virtual_key& char_p();

        //! Returns the virtual key for 'Q'.
        //! \return The virtual key.
        static const virtual_key& char_q();

        //! Returns the virtual key for 'R'.
        //! \return The virtual key.
        static const virtual_key& char_r();

        //! Returns the virtual key for 'S'.
        //! \return The virtual key.
        static const virtual_key& char_s();

        //! Returns the virtual key for 'T'.
        //! \return The virtual key.
        static const virtual_key& char_t();

        //! Returns the virtual key for 'U'.
        //! \return The virtual key.
        static const virtual_key& char_u();

        //! Returns the virtual key for 'V'.
        //! \return The virtual key.
        static const virtual_key& char_v();

        //! Returns the virtual key for 'W'.
        //! \return The virtual key.
        static const virtual_key& char_w();

        //! Returns the virtual key for 'X'.
        //! \return The virtual key.
        static const virtual_key& char_x();

        //! Returns the virtual key for 'Y'.
        //! \return The virtual key.
        static const virtual_key& char_y();

        //! Returns the virtual key for 'Z'.
        //! \return The virtual key.
        static const virtual_key& char_z();

        //! Returns the virtual key for F1.
        //! \return The virtual key.
        static const virtual_key& f1();

        //! Returns the virtual key for F2.
        //! \return The virtual key.
        static const virtual_key& f2();

        //! Returns the virtual key for F3.
        //! \return The virtual key.
        static const virtual_key& f3();

        //! Returns the virtual key for F4.
        //! \return The virtual key.
        static const virtual_key& f4();

        //! Returns the virtual key for F5.
        //! \return The virtual key.
        static const virtual_key& f5();

        //! Returns the virtual key for F6.
        //! \return The virtual key.
        static const virtual_key& f6();

        //! Returns the virtual key for F7.
        //! \return The virtual key.
        static const virtual_key& f7();

        //! Returns the virtual key for F8.
        //! \return The virtual key.
        static const virtual_key& f8();

        //! Returns the virtual key for F9.
        //! \return The virtual key.
        static const virtual_key& f9();

        //! Returns the virtual key for F10.
        //! \return The virtual key.
        static const virtual_key& f10();

        //! Returns the virtual key for F11.
        //! \return The virtual key.
        static const virtual_key& f11();

        //! Returns the virtual key for F12.
        //! \return The virtual key.
        static const virtual_key& f12();

        /*!
            \brief Returns the string representation of the combined keys.

            \param keys The bombined keys.

            \return The whole string representation of the combined keys.
        */
        static string_type to_combined_string(const std::vector<virtual_key>& keys);


        // functions

        /*!
            \brief Checks whether one virtual key is equal to another.

            \param one     One virtual key.
            \param another Another virtual key.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const virtual_key& one, const virtual_key& another);

        /*!
            \brief Returns the code.

            \return The code.
        */
        code_type code() const;

        /*!
            \brief Returns the string representation.

            \return The string representation.
        */
        const string_type& to_string() const;


    private:
        // types

        class impl;

        using code_and_string_type = std::pair<code_type, string_type>;


        // variables

        std::unique_ptr<impl> m_p_impl;


        // constructors

        explicit virtual_key(code_and_string_type code_and_string);
    };
}


#endif
