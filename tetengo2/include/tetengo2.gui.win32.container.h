/*! \file
    \brief The definition of tetengo2::gui::win32::container.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_CONTAINER_H)
#define TETENGO2_GUI_WIN32_CONTAINER_H

#include <vector>

//#include <boost/concept_check.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.Widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a container widget for Win32
               platforms.

        \tparam Widget A widget type. It must conform to
                       concept_tetengo2::gui::Widget<Widget>.
    */
    template <typename Widget>
    class container : public Widget
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Widget<Widget>));


    public:
        // types

        //! The widget type.
        typedef Widget widget_type;

        //! The handle type.
        typedef typename widget_type::handle_type handle_type;

        //! The canvas type.
        typedef typename widget_type::canvas_type canvas_type;

        //! The alerting unary functor type.
        typedef typename widget_type::alert_type alert_type;

        //! The difference type.
        typedef typename widget_type::difference_type difference_type;

        //! The size type.
        typedef typename widget_type::size_type size_type;

        //! The position type.
        typedef typename widget_type::position_type position_type;

        //! The dimension type.
        typedef typename widget_type::dimension_type dimension_type;

        //! The string type.
        typedef typename widget_type::string_type string_type;

        //! The unary functor type for encoding from the native.
        typedef
            typename widget_type::encode_from_native_type
            encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef
            typename widget_type::encode_to_native_type
            encode_to_native_type;

        //! The paint observer type.
        typedef
            typename widget_type::paint_observer_type paint_observer_type;

        //! The widgets type.
        typedef std::vector<widget_type*> widgets_type;

        //! The constant widgets type.
        typedef std::vector<const widget_type*> const_widgets_type;


        // constructors and destructor

        /*!
            \brief Destroys the container.
        */
        virtual ~container()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the children.

            \return The children.
        */
        const widgets_type children()
        {
            return widgets_type();
        }

        /*!
            \brief Returns the constant children.

            \return The children.
        */
        const const_widgets_type children()
        const
        {
            return const_widgets_type();
        }


    protected:
        // constructors

        /*!
            \brief Creates a container.
        */
        container()
        {}

        /*!
            \brief Creates a container.

            \param parent A parent.
        */
        container(const widget_type& parent)
        :
        widget_type(parent)
        {}


        // functions

        /*!
            \brief Dispatches the window messages.

            \param uMsg   A message.
            \param wParam A word-sized parameter.
            \param lParam A long-sized parameter.

            \return The result code.
        */
        virtual ::LRESULT window_procedure(
            const ::UINT   uMsg,
            const ::WPARAM wParam,
            const ::LPARAM lParam
        )
        {
            return this->widget_type::window_procedure(uMsg, wParam, lParam);
        }


    };


}}}

#endif
