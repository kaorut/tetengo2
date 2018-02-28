/*! \file
    \brief The definition of Windows version utilities for tetengo2::detail::windows.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_WINDOWSVERSION_H)
#define TETENGO2_DETAIL_WINDOWS_WINDOWSVERSION_H

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows {
    /*!
        \brief Verifies the Windows version.

        \param major              A major version.
        \param minor              A minor version.
        \param service_pack_major A service pack major version.
        \param service_pack_minor A service pack minor version.

        \retval true  When the system is runnin on a later version of Windows than the specified version.
        \retval false Otherwise.
    */
    inline bool verify_windows_version(
        const ::DWORD major,
        const ::DWORD minor,
        const ::WORD  service_pack_major,
        const ::WORD  service_pack_minor)
    {
        ::OSVERSIONINFOEXW info{};
        info.dwOSVersionInfoSize = sizeof(::OSVERSIONINFOEXW);
        info.dwMajorVersion = major;
        info.dwMinorVersion = minor;
        info.wServicePackMajor = service_pack_major;
        info.wServicePackMinor = service_pack_minor;

        ::DWORDLONG condition = 0;
        const int   op = VER_GREATER_EQUAL;
        VER_SET_CONDITION(condition, VER_MAJORVERSION, op);
        VER_SET_CONDITION(condition, VER_MINORVERSION, op);
        VER_SET_CONDITION(condition, VER_SERVICEPACKMAJOR, op);
        VER_SET_CONDITION(condition, VER_SERVICEPACKMINOR, op);

        return ::VerifyVersionInfoW(
                   &info,
                   VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
                   condition) != 0;
    }

    /*!
        \brief Returns whether the system is running on Windows Vista or
               later.

        \retval true  When the system is runnin on Windows Vista or later.
        \retval false Otherwise.
    */
    inline bool on_windows_vista_or_later()
    {
        static const auto result = verify_windows_version(6, 0, 0, 0);
        return result;
    }


}}}


#endif
