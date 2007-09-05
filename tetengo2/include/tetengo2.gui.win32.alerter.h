/*! \file
    \brief The definition of tetengo2::gui::win32::alerter.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ALERTER_H)
#define TETENGO2_GUI_WIN32_ALERTER_H

#include <exception>
#include <sstream>
#include <string>

#include <boost/format.hpp>

#define OEMRESOURCE
#include <windows.h>
#include <commctrl.h>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for an alerter for Win32 platforms.

        \param WindowHandle A window handle type. It must conform to
                            tetengo2::gui::concepts::HandleConcept.
        \param Encoder      An encoder type. It must conform to
                            tetengo2::concepts::EncoderConcept.
    */
    template <typename WindowHandle, typename Encoder>
    class alerter
    {
    public:
        // types

        //! The window handle type.
        typedef WindowHandle window_handle_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates an alerter object.

            \param encoder An encoder.
        */
        alerter(const encoder_type& encoder)
        :
        m_encoder(encoder)
        {}

        /*!
            \brief Copies an alerter object.

            \param another Another alerter.
        */
        alerter(const alerter& another)
        :
        m_encoder(alerter.m_encoder)
        {}

        /*!
            \brief Destroys the alerter object.
        */
        ~alerter()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps this for another.

            \param another Another alerter.
        */
        void swap(alerter& another)
        throw ()
        {
            m_encoder.swap(another.m_encoder);
        }

        /*!
            \brief Assigns an alerter.

            \param another Another alerter.
        */
        alerter& operator=(const alerter& another)
        {
            alerter(another).swap(*this);
            return *this;
        }

        /*!
            \brief Alerts a fatal error.

            \param window_handle A window handle.
            \param exception     An exception.
        */
        void alert(
            const window_handle_type window_handle,
            const std::exception&    exception =
                std::runtime_error("Unknown Error!")
        )
        const
        throw ()
        {
            try
            {
                ::TaskDialog(
                    window_handle,
                    ::GetModuleHandle(NULL),
                    L"Alert",
                    m_encoder.encode<std::wstring>(
                        typeid(exception).name()
                    ).c_str(),
                    m_encoder.encode<std::wstring>(exception.what()).c_str(),
                    TDCBF_OK_BUTTON,
                    TD_ERROR_ICON,
                    NULL
                );
            }
            catch (...)
            {}

        }


    private:
        // variables

       encoder_type m_encoder;


    };
}}}

#endif
