/*! \file
    \brief The definition of utilities for tetengo2.

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
    */
    inline void suppress_unused_variable_warning()
    {}

    /*!
        \brief Suppresses an unused variable warning.

        \tparam T A type.
        \tparam R Rest types.

        \param v A value.
        \param r A rest values.
    */
    template <typename T, typename... R>
    void suppress_unused_variable_warning(const T& v, const R&... r)
    {
        boost::ignore_unused_variable_warning(v);
        suppress_unused_variable_warning(r...);
    }


}


#endif
