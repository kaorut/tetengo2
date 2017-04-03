/*! \file
    \brief The definition of tetengo2::iterator::observable_forward_iterator.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_ITERATOR_OBSERVABLEFORWARDITERATOR_H)
#define TETENGO2_ITERATOR_OBSERVABLEFORWARDITERATOR_H

#include <functional>
#include <iterator>
#include <utility>

#include <boost/iterator/iterator_facade.hpp>


namespace tetengo2 { namespace iterator
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

        //! The increment observer signature type.
        using increment_observer_signature_type = void (observable_forward_iterator current);

        //! The increment observer type.
        using increment_observer_type = std::function<increment_observer_signature_type>;


        // constructors and destructor

        /*!
            \brief Creates an observable forward iterator.

            \param forward_iterator A forward iterator.
        */
        explicit observable_forward_iterator(iterator forward_iterator)
        :
        m_forward_iterator(forward_iterator),
        m_increment_observer([](const observable_forward_iterator&) {})
        {}


        // functions

        /*!
            \brief Dereferences the iterator.

            \return The dereferenced value.
        */
        typename observable_forward_iterator::reference dereference()
        const
        {
            return *m_forward_iterator;
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
            return m_forward_iterator == another.m_forward_iterator;
        }

        /*!
            \brief Increments the iterator.
        */
        void increment()
        {
            ++m_forward_iterator;
            m_increment_observer(*this);
        }

        /*!
            \brief Returns the distance to another iterator.

            \param another Another iterator.

            \return The distance.
        */
        typename std::iterator_traits<observable_forward_iterator>::difference_type distance_to(
            observable_forward_iterator another
        )
        const
        {
            return
                static_cast<typename std::iterator_traits<observable_forward_iterator>::difference_type>(
                    std::distance(m_forward_iterator, another.m_forward_iterator)
                );
        }

        /*!
            \brief Sets an increment observer.

            \param observer An increment observer.
        */
        void set_increment_observer(increment_observer_type observer)
        {
            m_increment_observer = std::move(observer);
        }


    private:
        // variables

        iterator m_forward_iterator;

        increment_observer_type m_increment_observer;


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


}}


#endif
