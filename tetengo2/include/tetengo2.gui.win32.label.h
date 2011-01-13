/*! \file
    \brief The definition of tetengo2::gui::win32::label.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_LABEL_H)
#define TETENGO2_GUI_WIN32_LABEL_H

//#include <cstddef>
//#include <stdexcept>
//#include <utility>

//#include <boost/scope_exit.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.win32.control.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a label for Win32 platforms.
 
        \tparam Traits A traits type.
   */
    template <typename Traits>
    class label : public control<typename Traits::base_type>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef control<typename traits_type::base_type> base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;


        // constructors and destructor

        /*!
            \brief Creates a label.

            \param parent A parent widget.

            \throw std::runtime_error When a label cannot be created.
        */
        explicit label(widget_type& parent)
        :
        base_type(
            make_message_handler_map(message_handler_map_type()),
            create_window(parent)
        )
        {
            initialize(this);
        }

        /*!
            \brief Destroys the label.
        */
        virtual ~label()
        TETENGO2_NOEXCEPT
        {}


        // functions

        /*!
            \brief Fit the dimension to the dimension of the text.
        */
        void fit_to_content()
        {
            set_client_dimension(calculate_text_dimension());
        }


    private:
        // static functions

        static handle_type create_window(const widget_type& parent)
        {
            const handle_type handle = ::CreateWindowExW(
                0,
                L"Static",
                L"tetengo2::gui::win32::label",
                WS_CHILD | WS_TABSTOP | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                parent.handle(),
                NULL,
                ::GetModuleHandle(NULL),
                NULL
            );
            if (handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a label!")
                );
            }

            return handle;
        }


        // functions

        std::pair<size_type, size_type> calculate_text_dimension()
        const
        {
            const handle_type handle = this->handle();
            const ::HDC hdc = ::GetDC(handle);
            BOOST_SCOPE_EXIT((handle)(hdc))
            {
                ::ReleaseDC(handle, hdc);
            } BOOST_SCOPE_EXIT_END;

            ::SIZE size = {};
            if (
                ::GetTextExtentPoint32W(
                    hdc,
                    text().c_str(),
                    static_cast<int>(text().length()),
                    &size
                ) == 0
            )
            {
                throw std::runtime_error("Can't get text extent.");
            }

            return std::pair<size_type, size_type>(
                to_unit<size_type>(size.cx), to_unit<size_type>(size.cy)
            );
        }

        message_handler_map_type make_message_handler_map(
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            return map;
        }


    };


}}}

#endif
