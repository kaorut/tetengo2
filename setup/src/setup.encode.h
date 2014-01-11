/*! \file
    \brief String encoding conversion

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(SETUP_ENCODE_H)
#define SETUP_ENCODE_H

#include <string>


namespace setup
{
    /*!
        \brief Converts a string encoding.

        \param string A string.

        \return An encoded string.
    */
    std::wstring encode(const std::string& string);


}


#endif
