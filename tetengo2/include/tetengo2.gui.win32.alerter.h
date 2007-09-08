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

#include <boost/concept_check.hpp>
#include <boost/format.hpp>

#define OEMRESOURCE
#include <windows.h>
#include <commctrl.h>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for an alerter for Win32 platforms.

        \param WindowHandle A window handle type. It must conform to
                            tetengo2::gui::concept::HandleConcept.
        \param Encode       An encoding unary functor type. It must conform to
                            boost::AdaptableUnaryFunctionConcept<Encode, std::wstring, std::string>.
    */
    template <
        typename WindowHandle,
        template <typename Target, typename Source>
        class Encode
    >
    class alerter
    {
    private:
        // concept checks

        struct concept_check_encode
        {
            typedef Encode<std::wstring, std::string> encode_type;
            typedef std::string exception_what_type;
            typedef std::wstring task_dialog_string_type;
            BOOST_CLASS_REQUIRE3(
                encode_type,
                task_dialog_string_type,
                exception_what_type,
                boost,
                AdaptableUnaryFunctionConcept
            );
        };


    public:
        // types

        //! The window handle type.
        typedef WindowHandle window_handle_type;

        //! The encoding unary functor type.
        typedef Encode<std::wstring, std::string> encode_type;


       // constructors and destructor

        /*!
            \brief Creates an alerter object.

            \param encode An encoding unary functor.
        */
        alerter(const encode_type& encode)
        :
        m_encode(encode)
        {}

        /*!
            \brief Copies an alerter object.

            \param another Another alerter.
        */
        alerter(const alerter& another)
        :
        m_encode(alerter.m_encode)
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
            m_encode.swap(another.m_encode);
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
                    m_encode(typeid(exception).name()).c_str(),
                    m_encode(exception.what()).c_str(),
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

       encode_type m_encode;


    };
}}}

#endif
