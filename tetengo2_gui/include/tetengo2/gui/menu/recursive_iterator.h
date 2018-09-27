/*! \file
    \brief The definition of tetengo2::gui::menu::recursive_iterator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_RECURSIVEITERATOR_H)
#define TETENGO2_GUI_MENU_RECURSIVEITERATOR_H

#include <memory>

#include <boost/iterator/iterator_facade.hpp>

namespace boost::iterators {
    struct forward_traversal_tag;
}


namespace tetengo2::gui::menu {
    /*!
        \brief The class template for a recursive iterator.

        \tparam MenuBase A menu base type.
    */
    template <typename MenuBase>
    class recursive_iterator
    : public boost::iterator_facade<recursive_iterator<MenuBase>, MenuBase, boost::forward_traversal_tag>
    {
    public:
        // types

        //! The menu base type.
        using menu_base_type = MenuBase;


        // constructors and destructor

        /*!
            \brief Creates a recursive iterator.
        */
        recursive_iterator();

        /*!
            \brief Creates a recursive iterator.

            \param p_menu A pointer to a menu.
        */
        explicit recursive_iterator(menu_base_type* const p_menu);

        /*!
            \brief Copies a recursive iterator.

            \param another Another recursive iterator.
        */
        recursive_iterator(const recursive_iterator& another);

        /*!
            \brief Moves a recursive iterator.

            \param another Another recursive iterator.
        */
        recursive_iterator(recursive_iterator&& another);

        /*!
            \brief Destroys the recursive iterator.
        */
        ~recursive_iterator();


        // functions

        /*!
            \brief Assigns an recursive iterator.

            \param another Another recursive_iterator.

            \return This object.
        */
        recursive_iterator& operator=(const recursive_iterator& another);

        /*!
            \brief Assigns an recursive iterator.

            \param another Another recursive_iterator.

            \return This object.
        */
        recursive_iterator& operator=(recursive_iterator&& another);

        /*!
            \brief Dereferences the iterator.

            \return The value.
        */
        menu_base_type& dereference() const;

        /*!
            \brief Returns whether this iterator is equal to another.

            \param another Another recursive iterator.

            \retval true  When this iterator is equal to another.
            \retval false Otherwise.
        */
        bool equal(const recursive_iterator& another) const;

        /*!
            \brief Increments the iterator.
        */
        void increment();


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;
    };
}


#endif
