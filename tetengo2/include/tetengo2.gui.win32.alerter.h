/*! \file
    \brief The definition of tetengo2::gui::win32::alerter.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ALERTER_H)
#define TETENGO2_GUI_WIN32_ALERTER_H

#include <exception>
#include <sstream>

#include <boost/format.hpp>
#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for an alerter for Win32 platforms.

        \param WindowHandle A window handle type. It must conform to
                            tetengo2::gui::concepts::HandleConcept.
    */
    template <typename WindowHandle>
    class alerter : private boost::noncopyable
    {
    public:
        // types

        //! The window handle type.
        typedef WindowHandle window_handle_type;


        // static functions

        /*!
            \brief Returns the alerter.

            \return The alerter.
        */
        static const alerter& instance()
        {
            static alerter singleton;

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
                std::ostringstream message;
                message << boost::format("%1$s:\n%2$s")
                    % typeid(exception).name() % exception.what();

                ::MessageBoxA(
                    window_handle,
                    message.str().c_str(),
                    "ERROR",
                    MB_OK | MB_ICONSTOP | MB_APPLMODAL
                );
            }
            catch (...)
            {}

        }


    private:

        // constructors

        alerter()
        {}


    };
}}}

#endif
