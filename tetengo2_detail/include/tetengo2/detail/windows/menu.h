/*! \file
    \brief The definition of tetengo2::detail::windows::menu.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MENU_H)
#define TETENGO2_DETAIL_WINDOWS_MENU_H

#include <memory>

#include <tetengo2/detail/base/menu.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui { namespace menu {
    class abstract_popup;
    class menu_base;
}}}


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a menu.
    */
    class menu : public base::menu
    {
    public:
        // types

        //! The menu details type.
        using menu_details_type = base::menu::menu_details_type;

        //! The windows menu details type.
        struct windows_menu_details_type : public menu_details_type
        {
            //! The ID.
            type_list::size_type id;

            //! The handle.
            std::intptr_t handle;

            //! The parent handle.
            std::intptr_t parent_handle;

            /*!
                \brief Creates a windows menu details

                \param id            A ID.
                \param handle        A handle.
                \param parent_handle A parent handle.
            */
            windows_menu_details_type(type_list::size_type id, std::intptr_t handle, std::intptr_t parent_handle);

            /*!
                \brief Destroys the windows menu details.
            */
            virtual ~windows_menu_details_type() noexcept;
        };

        //! The menu details pointer type.
        using menu_details_ptr_type = base::menu::menu_details_ptr_type;

        //! The shortcut key table details type.
        using shortcut_key_table_details_type = base::menu::shortcut_key_table_details_type;

        //! The windows shortcut key table details type.
        class windows_shortcut_key_table_details_type : public shortcut_key_table_details_type
        {
        public:
            /*!
                \brief Creates a windows shortcut key table details.
            */
            windows_shortcut_key_table_details_type();

            /*!
                \brief Creates a windows shortcut key table details.

                \param accelerator_table_handle An accelerator table handle.
            */
            explicit windows_shortcut_key_table_details_type(std::intptr_t accelerator_table_handle);

            /*!
                \brief Destroys the windows shortcut key table details.
            */
            virtual ~windows_shortcut_key_table_details_type() noexcept;

            /*!
                \brief Returns the accerator table handle.

                \return The accerator table handle.
            */
            std::intptr_t get() const;

        private:
            std::intptr_t m_accelerator_table_handle;
        };

        //! The shortcut key table details pointer type.
        using shortcut_key_table_details_ptr_type = base::menu::shortcut_key_table_details_ptr_type;

        //! The style tag type.
        using style_tag = base::menu::style_tag;

        //! The state type.
        using state_type = menu::state_type;

        //! The iterator type.
        using iterator = menu::iterator;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const menu& instance();


        // constructors and destructor

        /*!
            \brief Destroy the detail implementation.
        */
        virtual ~menu();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        menu();


        // virtual functions

        virtual menu_details_ptr_type create_menu_bar_impl() const override;

        virtual menu_details_ptr_type create_popup_menu_impl() const override;

        virtual menu_details_ptr_type create_menu_impl() const override;

        virtual void set_enabled_impl(gui::menu::menu_base& menu, bool enabled) const override;

        virtual void set_state_impl(gui::menu::menu_base& menu, state_type state) const override;

        virtual shortcut_key_table_details_ptr_type create_shortcut_key_table_impl() const override;

        virtual shortcut_key_table_details_ptr_type
        create_shortcut_key_table_impl(const gui::menu::menu_base& root_menu) const override;

        virtual void insert_menu_impl(
            gui::menu::abstract_popup& popup_menu,
            const iterator&            offset,
            gui::menu::menu_base&      menu) const override;

        virtual void erase_menus_impl(
            gui::menu::abstract_popup& popup_menu,
            const iterator&            first,
            const iterator&            last) const override;

        virtual const style_tag& menu_bar_style_impl() const override;

        virtual const style_tag& popup_menu_style_impl() const override;

        virtual const style_tag& menu_command_style_impl() const override;

        virtual const style_tag& menu_separator_style_impl() const override;
    };
}


#endif
