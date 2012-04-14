/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SHORTCUTKEY_H)
#define TETENGO2_GUI_MENU_SHORTCUTKEY_H

#include <vector>

#include <boost/operators.hpp>

#include "tetengo2.cpp11.h"


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a shortcut key.

        \tparam VirtualKey A virtual key type.
   */
    template <typename VirtualKey>
    class shortcut_key : private boost::equality_comparable<shortcut_key<VirtualKey>>
    {
    public:
        // types

        //! The virtual key type.
        typedef VirtualKey virtual_key_type;

        //! The string type.
        typedef typename virtual_key_type::string_type string_type;


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
        m_key(cpp11::cref(key)),
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
                one.m_key.get() == another.m_key.get() &&
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
            return m_key.get();
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
            std::vector<typename cpp11::reference_wrapper<const virtual_key_type>::type> keys;
            
            if (m_shift)
                keys.push_back(cpp11::cref(virtual_key_type::shift()));
            if (m_control)
                keys.push_back(cpp11::cref(virtual_key_type::control()));
            if (m_meta)
                keys.push_back(cpp11::cref(virtual_key_type::meta()));
            keys.push_back(m_key);

            return virtual_key_details_type::template to_combined_string<string_type>(keys.begin(), keys.end());
        }


    private:
        // types

        typedef typename virtual_key_type::details_type virtual_key_details_type;


        // variables

        typename cpp11::reference_wrapper<const virtual_key_type>::type m_key;

        bool m_shift;

        bool m_control;

        bool m_meta;


    };


}}}


#endif
