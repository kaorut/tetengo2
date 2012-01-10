/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SHORTCUTKEY_H)
#define TETENGO2_GUI_MENU_SHORTCUTKEY_H

#include <boost/noncopyable.hpp>

#include "tetengo2.cpp11.h"


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a shortcut key.

        \tparam VirtualKey A virtual key type.
   */
    template <typename VirtualKey>
    class shortcut_key : private boost::noncopyable
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
        shortcut_key(
            const virtual_key_type& key,
            const bool              shift,
            const bool              control,
            const bool              meta
        )
        :
        m_key(key),
        m_shift(shift),
        m_control(control),
        m_meta(meta)
        {}

        
        // functions

        /*!
            \brief Returns the key.

            \return The key.
        */
        const virtual_key_type& key()
        const
        {
            return m_key;
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
            std::vector<
                typename cpp11::reference_wrapper<
                    const virtual_key_type
                >::type
            > keys;
            
            if (m_shift)
                keys.push_back(cpp11::cref(virtual_key_type::shift()));
            if (m_control)
                keys.push_back(cpp11::cref(virtual_key_type::control()));
            if (m_meta)
                keys.push_back(cpp11::cref(virtual_key_type::meta()));
            keys.push_back(cpp11::cref(m_key));

            return virtual_key_details_type::to_combined_string(
                keys.begin(), keys.end()
            );
        }


    private:
        // types

        typedef
            typename virtual_key_type::details_type virtual_key_details_type;


        // variables

        const virtual_key_type& m_key;

        const bool m_shift;

        const bool m_control;

        const bool m_meta;


    };


}}}


#endif
