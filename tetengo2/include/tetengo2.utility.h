/*! \file
    \brief The definition of utilities.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_UTILITY_H)
#define TETENGO2_UTILITY_H

#include <boost/concept_check.hpp>


namespace tetengo2
{
	/*!
        \brief Suppresses an unused variable warning.

        \tparam T1 A type #1.

        \param v1 A value #1.
    */
    template <typename T1>
    void suppress_unused_variable_warning(const T1& v1)
    {
        boost::ignore_unused_variable_warning(v1);
    }

#if !defined(DOCUMENTATION)
    template <typename T1, typename T2>
    void suppress_unused_variable_warning(const T1& v1, const T2& v2)
    {
        boost::ignore_unused_variable_warning(v1);
        boost::ignore_unused_variable_warning(v2);
    }

    template <typename T1, typename T2, typename T3>
    void suppress_unused_variable_warning(const T1& v1, const T2& v2, const T3& v3)
    {
        boost::ignore_unused_variable_warning(v1);
        boost::ignore_unused_variable_warning(v2);
        boost::ignore_unused_variable_warning(v3);
    }

    template <typename T1, typename T2, typename T3, typename T4>
    void suppress_unused_variable_warning(const T1& v1, const T2& v2, const T3& v3, const T4& v4)
    {
        boost::ignore_unused_variable_warning(v1);
        boost::ignore_unused_variable_warning(v2);
        boost::ignore_unused_variable_warning(v3);
        boost::ignore_unused_variable_warning(v4);
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    void suppress_unused_variable_warning(const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5)
    {
        boost::ignore_unused_variable_warning(v1);
        boost::ignore_unused_variable_warning(v2);
        boost::ignore_unused_variable_warning(v3);
        boost::ignore_unused_variable_warning(v4);
        boost::ignore_unused_variable_warning(v5);
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    void suppress_unused_variable_warning(
        const T1& v1,
        const T2& v2,
        const T3& v3,
        const T4& v4,
        const T5& v5,
        const T6& v6
    )
    {
        boost::ignore_unused_variable_warning(v1);
        boost::ignore_unused_variable_warning(v2);
        boost::ignore_unused_variable_warning(v3);
        boost::ignore_unused_variable_warning(v4);
        boost::ignore_unused_variable_warning(v5);
        boost::ignore_unused_variable_warning(v6);
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    void suppress_unused_variable_warning(
        const T1& v1,
        const T2& v2,
        const T3& v3,
        const T4& v4,
        const T5& v5,
        const T6& v6,
        const T7& v7
    )
    {
        boost::ignore_unused_variable_warning(v1);
        boost::ignore_unused_variable_warning(v2);
        boost::ignore_unused_variable_warning(v3);
        boost::ignore_unused_variable_warning(v4);
        boost::ignore_unused_variable_warning(v5);
        boost::ignore_unused_variable_warning(v6);
        boost::ignore_unused_variable_warning(v7);
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    void suppress_unused_variable_warning(
        const T1& v1,
        const T2& v2,
        const T3& v3,
        const T4& v4,
        const T5& v5,
        const T6& v6,
        const T7& v7,
        const T8& v8
    )
    {
        boost::ignore_unused_variable_warning(v1);
        boost::ignore_unused_variable_warning(v2);
        boost::ignore_unused_variable_warning(v3);
        boost::ignore_unused_variable_warning(v4);
        boost::ignore_unused_variable_warning(v5);
        boost::ignore_unused_variable_warning(v6);
        boost::ignore_unused_variable_warning(v7);
        boost::ignore_unused_variable_warning(v8);
    }

    template <
        typename T1,
        typename T2,
        typename T3,
        typename T4,
        typename T5,
        typename T6,
        typename T7,
        typename T8,
        typename T9
    >
    void suppress_unused_variable_warning(
        const T1& v1,
        const T2& v2,
        const T3& v3,
        const T4& v4,
        const T5& v5,
        const T6& v6,
        const T7& v7,
        const T8& v8,
        const T9& v9
    )
    {
        boost::ignore_unused_variable_warning(v1);
        boost::ignore_unused_variable_warning(v2);
        boost::ignore_unused_variable_warning(v3);
        boost::ignore_unused_variable_warning(v4);
        boost::ignore_unused_variable_warning(v5);
        boost::ignore_unused_variable_warning(v6);
        boost::ignore_unused_variable_warning(v7);
        boost::ignore_unused_variable_warning(v8);
        boost::ignore_unused_variable_warning(v9);
    }

    template <
        typename T1,
        typename T2,
        typename T3,
        typename T4,
        typename T5,
        typename T6,
        typename T7,
        typename T8,
        typename T9,
        typename T10
    >
    void suppress_unused_variable_warning(
        const T1&  v1,
        const T2&  v2,
        const T3&  v3,
        const T4&  v4,
        const T5&  v5,
        const T6&  v6,
        const T7&  v7,
        const T8&  v8,
        const T9&  v9,
        const T10& v10
    )
    {
        boost::ignore_unused_variable_warning(v1);
        boost::ignore_unused_variable_warning(v2);
        boost::ignore_unused_variable_warning(v3);
        boost::ignore_unused_variable_warning(v4);
        boost::ignore_unused_variable_warning(v5);
        boost::ignore_unused_variable_warning(v6);
        boost::ignore_unused_variable_warning(v7);
        boost::ignore_unused_variable_warning(v8);
        boost::ignore_unused_variable_warning(v9);
        boost::ignore_unused_variable_warning(v10);
    }
#endif


}


#endif
