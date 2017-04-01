/*! \file
    \brief The definition of tetengo2::iterator::polymorphic_forward_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_ITERATOR_POLYMORPHICFORWARDITERATOR_H)
#define TETENGO2_ITERATOR_POLYMORPHICFORWARDITERATOR_H

#include <iterator>

#include <boost/operators.hpp>

namespace tetengo2 { namespace iterator
{
    /*!
        \brief The class template for a polymorphic forward iterator.

        \tparam T A type.
    */
    template <typename T>
    class polymorphic_forward_iterator :
        public std::iterator<std::forward_iterator_tag, T>,
        private boost::equality_comparable<polymorphic_forward_iterator<T>>
    {
    public:
        // types

        //! The value type.
        using value_type = T;

        //! The difference type.
        using difference_type = typename std::iterator<std::forward_iterator_tag, T>::difference_type;

        //! The pointer type.
        using pointer = typename std::iterator<std::forward_iterator_tag, T>::pointer;

        //! The reference type.
        using reference = typename std::iterator<std::forward_iterator_tag, T>::reference;

        //! The iterator category type.
        using iterator_category = std::forward_iterator_tag;


        // functions

        /*!
            \brief Dereferences the iterator.

            \return The reference to the value.
        */
        reference operator*()
        const
        {
            return const_cast<polymorphic_forward_iterator*>(this)->dereference();
        }

        /*!
            \brief Dereferences the iterator.

            \return The reference to the value.
        */
        pointer operator->()
        const
        {
            return &const_cast<polymorphic_forward_iterator*>(this)->dereference();
        }

        /*!
            \brief Increments the iterator.
            
            \return THis iterator.
        */
        polymorphic_forward_iterator& operator++()
        {
            increment();
            return *this;
        }

        /*!
            \brief Increments the iterator.

            The post increment operator of the polymorphic forward iterator does not return the previous state value.
        */
        void operator++(int)
        {
            increment();
        }

        /*!
            \brief Checks whether one polymorphic forward iterator is equal to another.

            \param one     One iterator.
            \param another Another iterator.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const polymorphic_forward_iterator& one, const polymorphic_forward_iterator& another)
        {
            return one.equal(another);
        }


    protected:
        // constructors

        /*!
            \brief Creates a polymorphic forward iterator.
        */
        polymorphic_forward_iterator()
        {}


    private:
        // variables


        // virtual functions

        virtual reference dereference()
        = 0;

        virtual bool equal(const polymorphic_forward_iterator& another)
        const = 0;

        virtual void increment()
        = 0;


    };


}}


#endif
