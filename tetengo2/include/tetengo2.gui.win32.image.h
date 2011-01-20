/*! \file
    \brief The definition of tetengo2::gui::win32::image.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_IMAGE_H)
#define TETENGO2_GUI_WIN32_IMAGE_H

//#include <cstddef>
//#include <stdexcept>
//#include <utility>

//#include <boost/bind.hpp>
//#include <boost/scoped_ptr.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.control.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for an image for Win32 platforms.
 
        \tparam Traits A traits type.
   */
    template <typename Traits>
    class image : public control<typename Traits::base_type>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef control<typename traits_type::base_type> base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The picture type.
        typedef typename traits_type::picture_type picture_type;


        // constructors and destructor

        /*!
            \brief Creates an image.

            \tparam PictureReader A picture reader type.

            \param parent         A parent widget.
            \param picture_reader A picture reader.

            \throw std::runtime_error When an image cannot be created.
        */
        template <typename PictureReader>
        image(widget_type& parent, PictureReader& picture_reader)
        :
        base_type(
            make_message_handler_map(message_handler_map_type()),
            create_window(parent)
        ),
        m_p_picture(picture_reader.read())
        {
            initialize_image(this);
        }

        /*!
            \brief Destroys the image.
        */
        virtual ~image()
        TETENGO2_NOEXCEPT
        {}


        // functions

        /*!
            \brief Fit the dimension to the dimension of the picture.
        */
        void fit_to_content()
        {
            set_client_dimension(m_p_picture->dimension());
        }


    private:
        // static functions

        static handle_type create_window(const widget_type& parent)
        {
            const handle_type handle = ::CreateWindowExW(
                0,
                L"Static",
                L"tetengo2::gui::win32::image",
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
                    std::runtime_error("Can't create an image!")
                );
            }

            return handle;
        }

        static void initialize_image(image* const p_image)
        {
            initialize(p_image);

            p_image->paint_observer_set().paint().connect(
                boost::bind(&image::paint_picture, p_image, _1)
            );
        }


        // variables

        const boost::scoped_ptr<picture_type> m_p_picture;


        // functions

        message_handler_map_type make_message_handler_map(
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            return map;
        }

        void paint_picture(canvas_type& canvas)
        const
        {
            canvas.paint_picture(
                *m_p_picture, position_type(0, 0), client_dimension()
            );
        }


    };


}}}

#endif
