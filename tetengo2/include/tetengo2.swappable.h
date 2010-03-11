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
    protected:
        // constructors and destructor

        /*!
            \brief Creates a swappable.
        */
        swappable()
        {}

        /*!
            \brief Destroys the swappable.
        */
        ~swappable()
        throw ()
        {}


        // functions


    };


}


#endif
