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
#include <boost/noncopyable.hpp>

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
    class alerter : private boost::noncopyable
    {
    public:
        // types

        //! The window handle type.
        typedef WindowHandle window_handle_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // static functions

        /*!
            \brief Returns the alerter.

            \return The alerter.
        */
        static const alerter& instance()
        {
            static const alerter singleton(encoder_type::instance());

            return singleton;
        }


        // constructors and destructor

        /*!
            \brief Destroys the alerter object.
        */
        ~alerter()
        throw ()
        {}


        // functions

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

        // constructors

        alerter(const encoder_type& encoder)
        :
        m_encoder(encoder)
        {}


        // variables

        const encoder_type& m_encoder;


    };
}}}

#endif
