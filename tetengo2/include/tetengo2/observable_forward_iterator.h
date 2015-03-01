/*! \file
    \brief The definition of tetengo2::observable_forward_iterator.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_OBSERVABLEINPUTITERATOR_H)
#define TETENGO2_OBSERVABLEINPUTITERATOR_H

#include <functional>
#include <iterator>
#include <utility>

#include <boost/iterator/iterator_facade.hpp>


namespace tetengo2
{
    /*!
        \brief The class template for an observable forward iterator.

        \tparam ForwardIterator A forward iterator type.
    */
    template <typename ForwardIterator>
    class observable_forward_iterator :
        public boost::iterator_facade<
            observable_forward_iterator<ForwardIterator>,
            typename ForwardIterator::value_type,
            std::forward_iterator_tag
        >
    {
    public:
        // types

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The observer type.
        using observer_type = std::function<void ()>;


        // constructors and destructor

        /*!
            \brief Creates an observable forward iterator.

            \param forward_iterator A forward iterator.
        */
        explicit observable_forward_iterator(iterator forward_iterator)
        :
        m_input_iterator(forward_iterator),
        m_observer([]() {})
        {}


        // functions

        /*!
            \brief Dereferences the iterator.

            \return The dereferenced value.
        */
        typename observable_forward_iterator::reference dereference()
        const
        {
            return *m_input_iterator;
        }

        /*!
            \brief Checks whether the iterator is equal to another iterator.

            \param another Another iterator.

            \retval true  When the iterator is equal to another iterator.
            \retval false Otherwise.
        */
        bool equal(const observable_forward_iterator& another)
        const
        {
            return m_input_iterator == another.m_input_iterator;
        }

        /*!
            \brief Increments the iterator.
        */
        void increment()
        {
            ++m_input_iterator;
            m_observer();
        }

        /*!
            \brief Sets an observer.

            \param observer An observer.
        */
        void set_observer(observer_type observer)
        {
            m_observer = std::move(observer);
        }


    private:
        // variables

        iterator m_input_iterator;

        observer_type m_observer;


    };


    /*!
        \brief Creates an observable forward iterator.

        \tparam ForwardIterator A forward iterator type.

        \param forward_iterator A forward iterator.

        \return An observable forward iterator.
    */
    template <typename ForwardIterator>
    observable_forward_iterator<ForwardIterator> make_observable_forward_iterator(ForwardIterator forward_iterator)
    {
        return observable_forward_iterator<ForwardIterator>{ forward_iterator };
    }


}


#endif
