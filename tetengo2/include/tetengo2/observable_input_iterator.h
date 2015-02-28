/*! \file
    \brief The definition of tetengo2::observable_input_iterator.

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
        \brief The class template for an observable input iterator.

        \tparam InputIterator An input iterator type.
    */
    template <typename InputIterator>
    class observable_input_iterator :
        public boost::iterator_facade<
            observable_input_iterator<InputIterator>, typename InputIterator::value_type, std::input_iterator_tag
        >
    {
    public:
        // types

        //! The iterator type.
        using iterator = InputIterator;

        //! The observer type.
        using observer_type = std::function<void ()>;


        // constructors and destructor

        /*!
            \brief Creates an observable input iterator.

            \param input_iterator An input iterator.
        */
        explicit observable_input_iterator(iterator input_iterator)
        :
        m_input_iterator(input_iterator),
        m_observer([]() {})
        {}


        // functions

        /*!
            \brief Dereferences the iterator.

            \return The dereferenced value.
        */
        typename observable_input_iterator::reference dereference()
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
        bool equal(const observable_input_iterator& another)
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


}


#endif
