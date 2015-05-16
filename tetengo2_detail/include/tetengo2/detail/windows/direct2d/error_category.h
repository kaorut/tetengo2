/*! \file
    \brief The definition of tetengo2::detail::windows::direct2d::error_category.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_DIRECT2D_ERRORCATEGORY_H)
#define TETENGO2_DETAIL_WINDOWS_DIRECT2D_ERRORCATEGORY_H

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
#include <d2d1.h>

#include <tetengo2/detail/windows/error_category.h>


namespace tetengo2 { namespace detail { namespace windows { namespace direct2d
{
    /*!
        \brief The class for a detail implementation of an error category.
    */
    class error_category : public std::error_category
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of an error category.
        */
        error_category()
        :
        std::error_category()
        {}

        /*!
            \brief Destroys the detail implementation of the error category.
        */
        virtual ~error_category()
        = default;


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        virtual const char* name()
        const override
        {
            return "direct2d";
        }

        /*!
            \brief Returns the message.

            \param error_value An error value.

            \return The message.
        */
        virtual std::string message(const int error_value)
        const override
        {
            if (error_value == D2DERR_INSUFFICIENT_BUFFER)
                return "The supplied buffer is too small to accommodate the data.";

            switch (error_value)
            {
            case D2DERR_BAD_NUMBER:
                return "The number is invalid.";
            case D2DERR_DISPLAY_FORMAT_NOT_SUPPORTED: 
                return "The display format to render is not supported by the hardware device.";
            case D2DERR_DISPLAY_STATE_INVALID:
                return "A valid display state could not be determined.";
            case D2DERR_EXCEEDS_MAX_BITMAP_SIZE:
                return "The requested size is larger than the guaranteed supported texture size.";
            case D2DERR_INCOMPATIBLE_BRUSH_TYPES:
                return "The brush types are incompatible for the call.";
            case D2DERR_INTERNAL_ERROR:
                return "The application should close this instance of Direct2D and restart it as a new process.";
            case D2DERR_INVALID_CALL:
                return "A call to this method is invalid.";
            case D2DERR_LAYER_ALREADY_IN_USE:
                return
                    "The application attempted to reuse a layer resource that has not yet been popped off the stack.";
            case D2DERR_MAX_TEXTURE_SIZE_EXCEEDED:
                return "The requested DX surface size exceeds the maximum texture size.";
            case D2DERR_NO_HARDWARE_DEVICE: 
                return "There is no hardware rendering device available for this operation.";
            case D2DERR_NOT_INITIALIZED:
                return "The object has not yet been initialized.";
            case D2DERR_POP_CALL_DID_NOT_MATCH_PUSH:
                return
                    "The application attempted to pop a layer off the stack when a clip was at the top, or pop a clip "
                    "off the stack when a layer was at the top.";
            case D2DERR_PUSH_POP_UNBALANCED:
                return
                    "The application did not pop all clips and layers off the stack, or it attempted to pop too many "
                    "clips or layers off the stack.";
            case D2DERR_RECREATE_TARGET:
                return
                    "A presentation error has occurred that may be recoverable. The caller needs to re-create the "
                    "render target then attempt to render the frame again.";
            case D2DERR_RENDER_TARGET_HAS_LAYER_OR_CLIPRECT:
                return
                    "The requested operation cannot be performed until all layers and clips have been popped off the "
                    "stack.";
            case D2DERR_SCANNER_FAILED:
                return "The geometry scanner failed to process the data.";
            case D2DERR_SCREEN_ACCESS_DENIED: 
                return "Direct2D could not access the screen.";
            case D2DERR_SHADER_COMPILE_FAILED:
                return "Shader compilation failed.";
            case D2DERR_TARGET_NOT_GDI_COMPATIBLE:
                return "The render target is not compatible with GDI.";
            case D2DERR_TEXT_EFFECT_IS_WRONG_TYPE:
                return "A text client drawing effect object is of the wrong type.";
            case D2DERR_TEXT_RENDERER_NOT_RELEASED:
                return
                    "An application is holding a reference to the IDWriteTextRenderer interface after the "
                    "corresponding DrawText or DrawTextLayout call has returned. ";
            case D2DERR_TOO_MANY_SHADER_ELEMENTS:
                return "Shader construction failed because it was too complex.";
            case D2DERR_UNSUPPORTED_OPERATION:
                return "The requested operation is not supported.";
            case D2DERR_UNSUPPORTED_PIXEL_FORMAT:
                return "The pixel format is not supported.";
            case D2DERR_UNSUPPORTED_VERSION:
                return "The requested Direct2D version is not supported.";
            case D2DERR_WIN32_ERROR: 
                return "An unknown Win32 failure occurred.";
            case D2DERR_WRONG_FACTORY:
                return "Objects used together were not all created from the same factory instance.";
            case D2DERR_WRONG_RESOURCE_DOMAIN:
                return "The resource used was created by a render target in a different resource domain.";
            case D2DERR_WRONG_STATE:
                return "The object was not in the correct state to process the method.";
            case D2DERR_ZERO_VECTOR:
                return "The supplied vector is zero.";
            default:
                return win32_category().message(error_value);
            }
        }


    };


    /*!
        \brief Returns the error category for Direct2D.

        \return The error category.
    */
    inline const std::error_category& direct2d_category()
    {
        static const error_category singleton;
        return singleton;
    }


}}}}


#endif
