/*! \file
    \brief The definition of tetengo2::observable_forward_iterator.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_OBSERVABLEINPUTITERATOR_H)
#define TETENGO2_OBSERVABLEINPUTITERATOR_H

#include <functional>
#include <iterator>
#include <memory>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/signals2.hpp>


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

        //! The increment observer signature type.
        typedef void increment_observer_signature_type(observable_forward_iterator current);

        //! The increment observer type.
        using increment_observer_type = std::function<increment_observer_signature_type>;

        //! The increment signal type.
        using increment_signal_type = boost::signals2::signal<increment_observer_signature_type>;


        // constructors and destructor

        /*!
            \brief Creates an observable forward iterator.

            \param forward_iterator A forward iterator.
        */
        explicit observable_forward_iterator(iterator forward_iterator)
        :
        m_forward_iterator(forward_iterator),
        m_p_increment_signal(std::make_shared<increment_signal_type>())
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
            (*m_p_increment_signal)(*this);
        }

        /*!
            \brief Returns the base iterator.

            \return The base iterator.
        */
        const iterator& base()
        const
        {
            return m_forward_iterator;
        }

        /*!
            \brief Returns the base iterator.

            \return The base iterator.
        */
        iterator& base()
        {
            return m_forward_iterator;
        }

        /*!
            \brief Returns the incremental signal.

            \return The incremental signal.
        */
        const increment_signal_type& increment_signal()
        const
        {
            return *m_p_increment_signal;
        }

        /*!
            \brief Returns the incremental signal.

            \return The incremental signal.
        */
        increment_signal_type& increment_signal()
        {
            return *m_p_increment_signal;
        }


    private:
        // variables

        iterator m_forward_iterator;

        std::shared_ptr<increment_signal_type> m_p_increment_signal;


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
