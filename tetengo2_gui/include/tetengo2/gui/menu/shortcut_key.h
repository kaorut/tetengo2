/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SHORTCUTKEY_H)
#define TETENGO2_GUI_MENU_SHORTCUTKEY_H

#include <memory>

#include <boost/operators.hpp>

#include <tetengo2/gui/virtual_key.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class for a shortcut key.
   */
    class shortcut_key : private boost::equality_comparable<shortcut_key>
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The virtual key type.
        using virtual_key_type = gui::virtual_key;


        // constructors and destructor

        /*!
            \brief Creates a shortcut key.

            \param key     A key.
            \param shift   True when a shift key is required.
            \param control True when a control key is required.
            \param meta    True when a meta key is required.
        */
        shortcut_key(const virtual_key_type& key, bool shift, bool control, bool meta);

        /*!
            \brief Copies a shortcut key.

            \param another Another shortcut key.
        */
        shortcut_key(const shortcut_key& another);

        /*!
            \brief Moves a shortcut key.

            \param another Another shortcut key.
        */
        shortcut_key(shortcut_key&& another);

        /*!
            \brief Destroys the shortcut key.
        */
        ~shortcut_key();


        // functions

        /*!
            \brief Checks whether one shortcut key is equal to another.

            \param one     One shortcut key.
            \param another Another shortcut key.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const shortcut_key& one, const shortcut_key& another);

        /*!
            \brief Returns the key.

            \return The key.
        */
        const virtual_key_type& key() const;

        /*!
            \brief Returns the shift key state.

            \retval true  When a shift key is required.
            \retval false Otherwise.
        */
        bool shift() const;

        /*!
            \brief Returns the control key state.

            \retval true  When a control key is required.
            \retval false Otherwise.
        */
        bool control() const;

        /*!
            \brief Returns the meta key state.

            \retval true  When a meta key is required.
            \retval false Otherwise.
        */
        bool meta() const;

        /*!
            \brief Returns the string representation.

            \return The string representation.
        */
        string_type to_string() const;


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;
    };
}


#endif
