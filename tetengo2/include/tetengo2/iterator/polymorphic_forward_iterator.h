/*! \file
    \brief The definition of tetengo2::iterator::polymorphic_forward_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_ITERATOR_POLYMORPHICFORWARDITERATOR_H)
#define TETENGO2_ITERATOR_POLYMORPHICFORWARDITERATOR_H

#include <iterator>


namespace tetengo2 { namespace iterator
{
    /*!
        \brief The class template for a polymorphic forward iterator.

        \tparam T A type.
    */
    template <typename T>
    class polymorphic_forward_iterator : public std::iterator<std::forward_iterator_tag, T>
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

        /*
            \brief Dereferences the iterator.

            \return The reference to the value.
        */
        reference operator*()
        const
        {
            return const_cast<polymorphic_forward_iterator*>(this)->dereference();
        }

        // a->m

        /*
            \brief Dereferences the iterator.

            \return The reference to the value.
        */
        pointer operator->()
        const
        {
            return &const_cast<polymorphic_forward_iterator*>(this)->dereference();
        }

        // ++a

        // a++

        // a == b

        // a != b

        // *a = t

        // *a++ = t

        // b=a; *a++; *b;


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
