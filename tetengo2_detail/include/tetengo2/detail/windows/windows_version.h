/*! \file
    \brief The definition of Windows version utilities for tetengo2::detail::windows.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_WINDOWSVERSION_H)
#define TETENGO2_DETAIL_WINDOWS_WINDOWSVERSION_H


namespace tetengo2::detail::windows {
    /*!
        \brief Returns whether the system is running on Windows Vista or
               later.

        \retval true  When the system is runnin on Windows Vista or later.
        \retval false Otherwise.
    */
    bool on_windows_vista_or_later();
}


#endif
