/*! \file
    \brief The definition of tetengo2::detail::windows::error_category.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cstddef>
#include <string>
#include <system_error>
#include <vector> // IWYU pragma: keep

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <wincodec.h>

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h> // IWYU pragma: keep
#include <tetengo2/text/encoding/utf8.h> // IWYU pragma: keep


namespace tetengo2::detail::windows {
    namespace detail {
        using encoder_type = text::encoder<text::encoding::utf8, text::encoding::locale<std::wstring>>;

        inline const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }
    }


    error_category::~error_category() = default;

    const char* error_category::name() const noexcept
    {
        return "win32";
    }

    std::string error_category::message(const int error_value) const
    {
        const std::size_t    message_capacity = 64 * 1024;
        std::vector<wchar_t> message(message_capacity, 0);
        auto                 message_length = ::FormatMessageW(
            FORMAT_MESSAGE_FROM_SYSTEM,
            nullptr,
            error_value,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &message[0],
            message_capacity,
            nullptr);
        if (message_length == 0)
            return "Unknown Error";

        while (message_length > 0 && (message[message_length - 1] == L'\r' || message[message_length - 1] == L'\n'))
        {
            --message_length;
        }

        return detail::encoder().decode(std::wstring{ message.begin(), message.begin() + message_length });
    }


    const std::error_category& win32_category()
    {
        static const error_category singleton;
        return singleton;
    }


    wic_error_category::~wic_error_category() = default;

    const char* wic_error_category::name() const noexcept
    {
        return "Windows Imaging Component";
    }

    std::string wic_error_category::message(const int error_value) const
    {
        switch (error_value)
        {
        case WINCODEC_ERR_ABORTED:
            return "WIC Error: Aborted.";
        case WINCODEC_ERR_ACCESSDENIED:
            return "WIC Error: Access denied.";
        case WINCODEC_ERR_ALREADYLOCKED:
            return "WIC Error: Already locked.";
        case WINCODEC_ERR_BADHEADER:
            return "WIC Error: Bad header.";
        case WINCODEC_ERR_BADIMAGE:
            return "WIC Error: Bad image.";
        case WINCODEC_ERR_BADMETADATAHEADER:
            return "WIC Error: Bad metadata header.";
        case WINCODEC_ERR_BADSTREAMDATA:
            return "WIC Error: Bad stream data.";
        case WINCODEC_ERR_CODECNOTHUMBNAIL:
            return "WIC Error: Codec not thumbnail.";
        case WINCODEC_ERR_CODECPRESENT:
            return "WIC Error: Codec present.";
        case WINCODEC_ERR_CODECTOOMANYSCANLINES:
            return "WIC Error: Codec too many scan lines.";
        case WINCODEC_ERR_COMPONENTINITIALIZEFAILURE:
            return "WIC Error: Component initialize failure.";
        case WINCODEC_ERR_COMPONENTNOTFOUND:
            return "WIC Error: Component not found.";
        case WINCODEC_ERR_DUPLICATEMETADATAPRESENT:
            return "WIC Error: Duplicate metadata present.";
        case WINCODEC_ERR_FRAMEMISSING:
            return "WIC Error: Frame missing.";
        case WINCODEC_ERR_GENERIC_ERROR:
            return "WIC Error: Generic error.";
        case WINCODEC_ERR_IMAGESIZEOUTOFRANGE:
            return "WIC Error: Image size out of range.";
        case WINCODEC_ERR_INSUFFICIENTBUFFER:
            return "WIC Error: Insufficient buffer.";
        case WINCODEC_ERR_INTERNALERROR:
            return "WIC Error: Internal error.";
        case WINCODEC_ERR_INVALIDPARAMETER:
            return "WIC Error: Invalid parameter.";
        case WINCODEC_ERR_INVALIDQUERYCHARACTER:
            return "WIC Error: Invalid query character.";
        case WINCODEC_ERR_INVALIDQUERYREQUEST:
            return "WIC Error: Invalid query request.";
        case WINCODEC_ERR_INVALIDREGISTRATION:
            return "WIC Error: Invalid registration.";
        case WINCODEC_ERR_NOTIMPLEMENTED:
            return "WIC Error: Not implemented.";
        case WINCODEC_ERR_NOTINITIALIZED:
            return "WIC Error: Not initialized.";
        case WINCODEC_ERR_OUTOFMEMORY:
            return "WIC Error: Out of memory.";
        case WINCODEC_ERR_PALETTEUNAVAILABLE:
            return "WIC Error: Palette unavailable.";
        case WINCODEC_ERR_PROPERTYNOTFOUND:
            return "WIC Error: Property not found.";
        case WINCODEC_ERR_PROPERTYNOTSUPPORTED:
            return "WIC Error: Property not supplied.";
        case WINCODEC_ERR_PROPERTYSIZE:
            return "WIC Error: Property size.";
        case WINCODEC_ERR_PROPERTYUNEXPECTEDTYPE:
            return "WIC Error: Property unexpected type.";
        case WINCODEC_ERR_REQUESTONLYVALIDATMETADATAROOT:
            return "WIC Error: Request only validat metadata root.";
        case WINCODEC_ERR_SOURCERECTDOESNOTMATCHDIMENSIONS:
            return "WIC Error: Source rect does not match demensions.";
        case WINCODEC_ERR_STREAMWRITE:
            return "WIC Error: Stream write.";
        case WINCODEC_ERR_STREAMREAD:
            return "WIC Error: Stream read.";
        case WINCODEC_ERR_STREAMNOTAVAILABLE:
            return "WIC Error: Stream not available.";
        case WINCODEC_ERR_TOOMUCHMETADATA:
            return "WIC Error: Too much metadata.";
        case WINCODEC_ERR_UNKNOWNIMAGEFORMAT:
            return "WIC Error: Unknown image format.";
        case WINCODEC_ERR_UNEXPECTEDMETADATATYPE:
            return "WIC Error: Unexpected metadata type.";
        case WINCODEC_ERR_UNEXPECTEDSIZE:
            return "WIC Error: Unexpected size.";
        case WINCODEC_ERR_UNSUPPORTEDOPERATION:
            return "WIC Error: Unsupported operation.";
        case WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT:
            return "WIC Error: Unsupported pixel format.";
        case WINCODEC_ERR_UNSUPPORTEDVERSION:
            return "WIC Error: Unsupported version.";
        case WINCODEC_ERR_VALUEOUTOFRANGE:
            return "WIC Error: Value out of range.";
        case WINCODEC_ERR_VALUEOVERFLOW:
            return "WIC Error: Value overflow.";
        case WINCODEC_ERR_WRONGSTATE:
            return "WIC Error: Wrong state.";
        default:
            return win32_category().message(error_value);
        };
    }


    const std::error_category& wic_category()
    {
        static const wic_error_category singleton;
        return singleton;
    }
}
