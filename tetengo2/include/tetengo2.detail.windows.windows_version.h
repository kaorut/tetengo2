/*! \file
    \brief The definition of tetengo2::detail::windows::windows_version.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_WINDOWSVERSION_H)
#define TETENGO2_DETAIL_WINDOWS_WINDOWSVERSION_H

#if !defined(DOCUMENTATION)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows
{
    inline bool verify_windows_version(
        const ::DWORD major,
        const ::DWORD minor,
        const ::WORD  service_pack_major,
        const ::WORD  service_pack_minor
    )
    {
        ::OSVERSIONINFOEXW info = {};
        info.dwOSVersionInfoSize = sizeof(::OSVERSIONINFOEXW);
        info.dwMajorVersion = major;
        info.dwMinorVersion = minor;
        info.wServicePackMajor = service_pack_major;
        info.wServicePackMinor = service_pack_minor;

        ::DWORDLONG condition = 0;
        const int op = VER_GREATER_EQUAL;
        VER_SET_CONDITION(condition, VER_MAJORVERSION, op);
        VER_SET_CONDITION(condition, VER_MINORVERSION, op);
        VER_SET_CONDITION(condition, VER_SERVICEPACKMAJOR, op);
        VER_SET_CONDITION(condition, VER_SERVICEPACKMINOR, op);

        return ::VerifyVersionInfoW(
            &info, 
            VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR |
                VER_SERVICEPACKMINOR,
            condition
        ) != 0;
    }

    inline bool on_windows_vista_or_later()
    {
        static const bool result = verify_windows_version(6, 0, 0, 0);
        return result;
    }


}}}
#endif


#endif
