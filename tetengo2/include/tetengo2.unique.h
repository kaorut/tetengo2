/*! \file
    \brief The definition of tetengo2::unique.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_UNIQUE_H)
#define TETENGO2_UNIQUE_H

#include "tetengo2.cpp0x.h"


namespace tetengo2
{
    /*!
        \brief Makes a unique pointer.

        \tparam T A type.

        \return A unique pointer
    */
    template <typename T>
    typename tetengo2::cpp0x::unique_ptr<T>::type make_unique()
    {
        return typename tetengo2::cpp0x::unique_ptr<T>::type(new T());
    }

    /*!
        \brief Makes a unique pointer.

        \tparam T  A type.
        \tparam A1 An argument type #1.

        \param arg1 An argument #1.

        \return A unique pointer
    */
    template <typename T, typename A1>
    typename tetengo2::cpp0x::unique_ptr<T>::type make_unique(A1&& arg1)
    {
        return typename tetengo2::cpp0x::unique_ptr<T>::type(
            new T(std::forward<A1>(arg1))
        );
    }

    /*!
        \brief Upcasts a unique pointer.

        This cast operation is not necessary for std::unique_ptr but
        boost::interprocess::unique_ptr requires it.

        \tparam Base A base type.
        \tparam Derived A derived type.

        \param p_derived A unique pointer to a derived type.

        \return A unique pointer to base type.
    */
    template <typename Base, typename Derived>
    typename tetengo2::cpp0x::unique_ptr<Base>::type unique_ptr_upcast(
        typename tetengo2::cpp0x::unique_ptr<Derived>::type&& p_derived
    )
    {
        return typename tetengo2::cpp0x::unique_ptr<Base>::type(
            p_derived.release()
        );
    }


}


#endif
