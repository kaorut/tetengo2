/*! \file
    \brief The definition of bobura::view::diagram::selection.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_SELECTION_H)
#define BOBURA_VIEW_DIAGRAM_SELECTION_H

#include <cstddef>

#include <boost/noncopyable.hpp>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view selection.

        \tparam Train A train type.
    */
    template <typename Train>
    class selection : private boost::noncopyable
    {
    public:
        // types

        //! The train type.
        typedef Train train_type;


        // constructors and destructor

        /*!
            \brief Creates a selection.
        */
        selection()
        :
        m_p_selected_train(NULL)
        {}

        /*!
            \brief Moves a selection.

            \param another Another selection.
        */
        selection(selection&& another)
        :
        m_p_selected_train(another.m_p_selected_train)
        {}


        // functions

        /*!
            \brief Checks whether the train is selected.

            \param train A train.

            \retval true  When the train is selected.
            \retval false Otherwise.
        */
        bool selected(const train_type& train)
        const
        {
            if (!m_p_selected_train)
                return false;

            return &train == m_p_selected_train;
        }

        /*!
            \brief Selects a train.

            \param train A train.
        */
        void select(const train_type& train)
        {
            unselect_all();

            m_p_selected_train = &train;
        }

        /*!
            \brief Unselects all the items.
        */
        void unselect_all()
        {
            m_p_selected_train = NULL;
        }


    private:
        // variables

        const train_type* m_p_selected_train;


    };


}}}


#endif
