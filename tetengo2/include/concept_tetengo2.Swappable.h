/*! \file
    \brief The definition of concept_tetengo2::Swappable.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_SWAPPABLEE_H)
#define CONCEPTTETENGO2_SWAPPABLEE_H

#include <boost/concept_check.hpp>
#include <boost/swap.hpp>


namespace concept_tetengo2
{
    /*!
        \brief The concept check class template for a swappable.

        \tparam Type A type.
    */
    template <typename Type>
    class Swappable
    {
#if !defined(DOCUMENTATION)
    public:
        // types


        // usage checks

        BOOST_CONCEPT_USAGE(Swappable)
        {
            m_object.swap(m_object);

            boost::swap(m_object, m_object);
        }


    private:
        // variables

        Type m_object;


#endif
    };


}

#endif
