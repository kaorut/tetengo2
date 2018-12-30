/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <vector>

#include <tetengo2/gui/menu/shortcut_key.h>


namespace tetengo2::gui::menu {
    class shortcut_key::impl
    {
    public:
        // types

        using string_type = shortcut_key::string_type;

        using virtual_key_type = shortcut_key::virtual_key_type;


        // constructors and destructor

        impl(const virtual_key_type& key, const bool shift, const bool control, const bool meta)
        : m_p_key{ &key }, m_shift{ shift }, m_control{ control }, m_meta{ meta }
        {}


        // functions

        friend bool operator_equal(const impl& one, const impl& another)
        {
            return one.m_p_key == another.m_p_key && one.m_shift == another.m_shift &&
                   one.m_control == another.m_control && one.m_meta == another.m_meta;
        }

        const virtual_key_type& key() const
        {
            return *m_p_key;
        }

        bool shift() const
        {
            return m_shift;
        }

        bool control() const
        {
            return m_control;
        }

        bool meta() const
        {
            return m_meta;
        }

        string_type to_string() const
        {
            std::vector<virtual_key_type> keys{};

            if (m_shift)
                keys.push_back(virtual_key_type::shift());
            if (m_control)
                keys.push_back(virtual_key_type::control());
            if (m_meta)
                keys.push_back(virtual_key_type::meta());
            keys.push_back(*m_p_key);

            return virtual_key_type::to_combined_string(keys);
        }


    private:
        // variables

        const virtual_key_type* m_p_key;

        bool m_shift;

        bool m_control;

        bool m_meta;
    };


    shortcut_key::shortcut_key(const virtual_key_type& key, const bool shift, const bool control, const bool meta)
    : m_p_impl{ std::make_unique<impl>(key, shift, control, meta) }
    {}

    shortcut_key::shortcut_key(const shortcut_key& another) : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) } {}

    shortcut_key::shortcut_key(shortcut_key&& another) : m_p_impl{ std::move(another.m_p_impl) } {}

    shortcut_key::~shortcut_key() = default;

    bool operator==(const shortcut_key& one, const shortcut_key& another)
    {
        return operator_equal(*one.m_p_impl, *another.m_p_impl);
    }

    const shortcut_key::virtual_key_type& shortcut_key::key() const
    {
        return m_p_impl->key();
    }

    bool shortcut_key::shift() const
    {
        return m_p_impl->shift();
    }

    bool shortcut_key::control() const
    {
        return m_p_impl->control();
    }

    bool shortcut_key::meta() const
    {
        return m_p_impl->meta();
    }

    shortcut_key::string_type shortcut_key::to_string() const
    {
        return m_p_impl->to_string();
    }
}
