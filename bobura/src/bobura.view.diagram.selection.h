/*! \file
    \brief The definition of bobura::view::diagram::selection.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_SELECTION_H)
#define BOBURA_VIEW_DIAGRAM_SELECTION_H

#include <cassert>
#include <cstddef>
#include <limits>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>


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

        //! The stop index type.
        typedef typename train_type::stops_type::size_type stop_index_type;


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

            \param train                A train.
            \param departure_stop_index A departure stop index.
                                        Specity std::numeric_limits<stop_index_type>::max() to test whether any
                                        fragment is selected.
                                        Or specify boost::none to test whether a whole train is selected.

            \retval true  When the train is selected.
            \retval false Otherwise.
        */
        bool selected(const train_type& train, const boost::optional<stop_index_type>& departure_stop_index)
        const
        {
            if (!m_p_selected_train)
                return false;
            if (!departure_stop_index != !m_departure_stop_index)
                return false;
            if (!departure_stop_index)
            {
                assert(!m_departure_stop_index);
                return &train == m_p_selected_train;
            }
            return
                &train == m_p_selected_train &&
                (
                    *departure_stop_index == std::numeric_limits<stop_index_type>::max() ||
                    *departure_stop_index == *m_departure_stop_index
                );
        }

        /*!
            \brief Selects a train.

            \param train                A train.
            \param departure_stop_index A departure stop index. Or specify boost::none when a whole train is selected.
        */
        void select(const train_type& train, const boost::optional<stop_index_type>& departure_stop_index)
        {
            unselect_all();

            m_p_selected_train = &train;
            m_departure_stop_index = departure_stop_index;
        }

        /*!
            \brief Unselects all the items.
        */
        void unselect_all()
        {
            m_p_selected_train = NULL;
            m_departure_stop_index = boost::none;
        }


    private:
        // variables

        const train_type* m_p_selected_train;

        boost::optional<stop_index_type> m_departure_stop_index;


    };


}}}


#endif
