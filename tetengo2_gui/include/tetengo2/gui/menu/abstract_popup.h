/*! \file
    \brief The definition of tetengo2::gui::menu::abstract_popup.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_ABSTRACTPOPUP_H)
#define TETENGO2_GUI_MENU_ABSTRACTPOPUP_H

#include <memory>

#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The base class for an abstract popup menu.
   */
    class abstract_popup : public menu_base
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The detail implementation pointer type.
        using details_ptr_type = detail::base::menu::menu_details_ptr_type;

        //! The base type.
        using base_type = menu_base;

        //! The const iterator type.
        using const_iterator = typename base_type::const_iterator;

        //! The iterator type.
        using iterator = typename base_type::iterator;

        //! The const recursive iterator type.
        using const_recursive_iterator_type = typename base_type::const_recursive_iterator_type;

        //! The recursive iterator type.
        using recursive_iterator_type = typename base_type::recursive_iterator_type;


        // constructors and destructor

        /*!
            \brief Destroys the abstract_popup.
        */
        virtual ~abstract_popup();


    protected:
        // constructors

        /*!
            \brief Creates an abstract popup menu.

            \param text      A text.
            \param p_details A unique pointer to a detail implementation.
        */
        abstract_popup(string_type text, details_ptr_type p_details);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual const_iterator begin_impl() const override;

        virtual iterator begin_impl() override;

        virtual const_iterator end_impl() const override;

        virtual iterator end_impl() override;

        virtual const_recursive_iterator_type recursive_begin_impl() const override;

        virtual recursive_iterator_type recursive_begin_impl() override;

        virtual const_recursive_iterator_type recursive_end_impl() const override;

        virtual recursive_iterator_type recursive_end_impl() override;

        virtual void insert_impl(const iterator offset, std::unique_ptr<base_type> p_menu) override;

        virtual void erase_impl(const iterator first, const iterator last) override;
    };
}


#endif
