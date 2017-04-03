/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SHORTCUTKEY_H)
#define TETENGO2_GUI_MENU_SHORTCUTKEY_H

#include <vector>

#include <boost/operators.hpp>

#include <tetengo2/gui/virtual_key.h>


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a shortcut key.

        \tparam String            A string type.
        \tparam VirtualKeyDetails A virtual key detail implementation type.
   */
    template <typename String, typename VirtualKeyDetails>
    class shortcut_key : private boost::equality_comparable<shortcut_key<String, VirtualKeyDetails>>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The virtual key details type.
        using virtual_key_details_type = VirtualKeyDetails;

        //! The virtual key type.
        using virtual_key_type = gui::virtual_key<string_type, virtual_key_details_type>;


        // constructors and destructor

        /*!
            \brief Creates a shortcut key.

            \param key     A key.
            \param shift   True when a shift key is required.
            \param control True when a control key is required.
            \param meta    True when a meta key is required.
        */
        shortcut_key(const virtual_key_type& key, const bool shift, const bool control, const bool meta)
        :
        m_p_key(&key),
        m_shift(shift),
        m_control(control),
        m_meta(meta)
        {}

        
        // functions

        /*!
            \brief Checks whether one shortcut key is equal to another.

            \param one     One shortcut key.
            \param another Another shortcut key.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const shortcut_key& one, const shortcut_key& another)
        {
            return
                one.m_p_key == another.m_p_key &&
                one.m_shift == another.m_shift &&
                one.m_control == another.m_control &&
                one.m_meta == another.m_meta;
        }

        /*!
            \brief Returns the key.

            \return The key.
        */
        const virtual_key_type& key()
        const
        {
            return *m_p_key;
        }

        /*!
            \brief Returns the shift key state.

            \retval true  When a shift key is required.
            \retval false Otherwise.
        */
        bool shift()
        const
        {
            return m_shift;
        }

        /*!
            \brief Returns the control key state.

            \retval true  When a control key is required.
            \retval false Otherwise.
        */
        bool control()
        const
        {
            return m_control;
        }

        /*!
            \brief Returns the meta key state.

            \retval true  When a meta key is required.
            \retval false Otherwise.
        */
        bool meta()
        const
        {
            return m_meta;
        }

        /*!
            \brief Returns the string representation.

            \return The string representation.
        */
        string_type to_string()
        const
        {
            std::vector<const virtual_key_type*> keys{};
            
            if (m_shift)
                keys.push_back(&virtual_key_type::shift());
            if (m_control)
                keys.push_back(&virtual_key_type::control());
            if (m_meta)
                keys.push_back(&virtual_key_type::meta());
            keys.push_back(m_p_key);

            return virtual_key_details_type::template to_combined_string<string_type>(keys.begin(), keys.end());
        }


    private:
        // variables

        const virtual_key_type* m_p_key;

        bool m_shift;

        bool m_control;

        bool m_meta;


    };


}}}


#endif
