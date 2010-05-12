/*! \file
    \brief The definition of tetengo2::swappable.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_SWAPPABLE_H)
#define TETENGO2_SWAPPABLE_H


namespace tetengo2
{
    /*!
        \brief The class template for a swappable.

        \tparam Derived A derived type.
    */
    template <typename Derived>
    class swappable
    {
    private:
        // friends

        /*!
            \brief Swaps objects.

            \param object1 An object #1.
            \param object2 An object #2.
        */
        friend void swap(Derived& object1, Derived& object2)
        throw ()
        {
            object1.swap(object2);
        }


    };


}


#endif
