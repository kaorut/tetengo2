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
    protected:
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


        // constructors

        /*!
            \brief Creates a polymorphic forward iterator.
        */
        polymorphic_forward_iterator()
        {}

        // X b(a)


        // functions

        // b = a

        // ++a

        // a++

        // a == b

        // a != b

        // *a

        // a->m

        // *a = t

        // *a++ = t

        // b=a; *a++; *b;


    private:
        // variables


        // functions

        // c.dereference()

        // c.equal(y)

        // a.increment()


    };


}}


#endif
