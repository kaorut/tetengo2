/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::error_category.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <cassert>
#include <string>
#include <system_error>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max

#include <tetengo2/detail/windows/gdiplus/error_category.h>


namespace tetengo2 { namespace detail { namespace windows { namespace gdiplus
{
    error_category::error_category()
    :
    std::error_category()
    {}

    error_category::~error_category()
    = default;

    const char* error_category::name()
    const noexcept
    {
        return "gdiplus";
    }

    std::string error_category::message(const int error_value)
    const
    {
        switch (error_value)
        {
        case Gdiplus::Ok:
            return "The method call was successful.";
        case Gdiplus::GenericError:
            return
                "There was an error on the method call, which is identified as something other than those defined by "
                "the other elements of this enumeration.";
        case Gdiplus::InvalidParameter:
            return "One of the arguments passed to the method was not valid.";
        case Gdiplus::OutOfMemory:
            return "The operating system is out of memory and could not allocate memory to process the method call.";
        case Gdiplus::ObjectBusy:
            return "One of the arguments specified in the API call is already in use in another thread.";
        case Gdiplus::InsufficientBuffer:
            return
                "A buffer specified as an argument in the API call is not large enough to hold the data to be "
                "received.";
        case Gdiplus::NotImplemented:
            return "The method is not implemented.";
        case Gdiplus::Win32Error:
            return "The method generated a Win32 error.";
        case Gdiplus::WrongState:
            return "The object is in an invalid state to satisfy the API call.";
        case Gdiplus::Aborted:
            return "The method was aborted.";
        case Gdiplus::FileNotFound:
            return "The specified image file or metafile cannot be found.";
        case Gdiplus::ValueOverflow:
            return "The method performed an arithmetic operation that produced a numeric overflow.";
        case Gdiplus::AccessDenied:
            return "A write operation is not allowed on the specified file.";
        case Gdiplus::UnknownImageFormat:
            return "The specified image file format is not known.";
        case Gdiplus::FontFamilyNotFound:
            return
                "The specified font family cannot be found. Either the font family name is incorrect or the font "
                "family is not installed.";
        case Gdiplus::FontStyleNotFound:
            return "The specified style is not available for the specified font family.";
        case Gdiplus::NotTrueTypeFont:
            return "The font retrieved from an HDC or LOGFONT is not a TrueType font and cannot be used with GDI+.";
        case Gdiplus::UnsupportedGdiplusVersion:
            return
                "The version of GDI+ that is installed on the system is incompatible with the version with which the "
                "application was compiled.";
        case Gdiplus::GdiplusNotInitialized:
            return
                "The GDI+API is not in an initialized state. To function, all GDI+ objects require that GDI+ be in an "
                "initialized state. Initialize GDI+ by calling GdiplusStartup.";
        case Gdiplus::PropertyNotFound:
            return "The specified property does not exist in the image.";
        case Gdiplus::PropertyNotSupported:
            return "The specified property is not supported by the format of the image and, therefore, cannot be set.";
#if GDIPVER >= 0x0110
        case Gdiplus::ProfileNotFound:
            return "The color profile required to save an image in CMYK format was not found.";
#endif
        default:
            assert(false);
            return "Unknown Error.";
        }
    }


    const std::error_category& gdiplus_category()
    {
        static const error_category singleton;
        return singleton;
    }


}}}}
