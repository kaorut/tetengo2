/*! \file
    \brief The definition of utilities.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_UTILITY_H)
#define TETENGO2_UTILITY_H


namespace tetengo2
{
	/*!
        \brief Suppresses an unused variable warning.

        \tparam T A type.

        \param v A value.
    */
    template <typename T>
    void suppress_unused_variable_warning(const T v)
    {}


}


#endif
