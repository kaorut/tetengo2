/*! \file
    \brief The definition of tetengo2::gui::recursive_menu_iterator.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_RECURSIVEMENUITERATOR_H)
#define TETENGO2_GUI_RECURSIVEMENUITERATOR_H

#include <cassert>
#include <cstddef>
#include <iterator>
#include <stack>
#include <utility>

#include <boost/next_prior.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a recursive menu iterator.

        \tparam Menu A menu type.
    */
    template <typename Menu>
    class recursive_menu_iterator :
        public boost::iterator_facade<
            recursive_menu_iterator<Menu>, Menu, boost::forward_traversal_tag
        >
    {
    public:
        // types

        //! The menu type.
        typedef Menu menu_type;


        // constructors and destructor

        /*!
            \brief Creates a recursive menu iterator.
        */
        recursive_menu_iterator()
        :
        m_p_menu(NULL),
        m_parents()
        {
            m_parents.push(
                parent_and_index_type(static_cast<menu_type*>(NULL), 0)
            );
        }

        /*!
            \brief Creates a recursive menu iterator.

            \param p_menu A pointer to a menu.
        */
        explicit recursive_menu_iterator(menu_type* const p_menu)
        :
        m_p_menu(p_menu),
        m_parents()
        {
            m_parents.push(
                parent_and_index_type(static_cast<menu_type*>(NULL), 0)
            );
        }


        // functions

        /*!
            \brief Dereferences the iterator.

            \return The value.
        */
        menu_type& dereference()
        const
        {
            return *m_p_menu;
        }

        /*!
            \brief Returns whether this iterator is equal to another.

            \param another Another recursive menu iterator.

            \retval true  When this iterator is equal to another.
            \retval false Otherwise.
        */
        bool equal(const recursive_menu_iterator& another)
        const
        {
            return m_p_menu == another.m_p_menu;
        }

        /*!
            \brief Increments the iterator.
        */
        void increment()
        {
            assert(m_p_menu != NULL);

            if (
                m_parents.top().second <
                std::distance(m_p_menu->begin(), m_p_menu->end())
            )
            {
                const menu_difference_type index = m_parents.top().second;
                m_parents.push(parent_and_index_type(m_p_menu, 0));
                m_p_menu = &*boost::next(m_p_menu->begin(), index);
                return;
            }

            if (m_parents.top().first == NULL)
            {
                m_p_menu = NULL;
                return;
            }

            m_p_menu = m_parents.top().first;
            m_parents.pop();
            ++m_parents.top().second;
            increment();
        }


    private:
        // types

        typedef
            typename menu_type::const_iterator::difference_type
            menu_difference_type;

        typedef
            std::pair<menu_type*, menu_difference_type> parent_and_index_type;


        // variables

        menu_type* m_p_menu;

        std::stack<parent_and_index_type> m_parents;


    };


}}

#endif
