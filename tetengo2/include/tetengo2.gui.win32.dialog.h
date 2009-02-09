/*! \file
    \brief The definition of tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DIALOG_H)
#define TETENGO2_GUI_WIN32_DIALOG_H

#include <cstddef>
#include <stdexcept>

//#include <boost/concept_check.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.Window.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a modal dialog.
 
        \tparam Window A widget type. It must conform to
                       concept_tetengo2::gui::Window<Window>.
   */
    template <typename Window>
    class dialog : public Window
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));


    public:
        // types

        //! The window type.
        typedef Window window_type;

        //! The handle type.
        typedef typename window_type::handle_type handle_type;

        //! The canvas type.
        typedef typename window_type::canvas_type canvas_type;

        //! The alerting unary functor type.
        typedef typename window_type::alert_type alert_type;

        //! The difference type.
        typedef typename window_type::difference_type difference_type;

        //! The size type.
        typedef typename window_type::size_type size_type;

        //! The position type.
        typedef typename window_type::position_type position_type;

        //! The dimension type.
        typedef typename window_type::dimension_type dimension_type;

        //! The string type.
        typedef typename window_type::string_type string_type;

        //! The unary functor type for encoding from the native.
        typedef
            typename window_type::encode_from_native_type
            encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef
            typename window_type::encode_to_native_type
            encode_to_native_type;

        //! The paint observer type.
        typedef
            typename window_type::paint_observer_type paint_observer_type;

        //! The main menu type.
        typedef typename window_type::main_menu_type main_menu_type;

        //! The dialog observer type.
        typedef
            typename window_type::window_observer_type window_observer_type;


        // constructors and destructor

        /*!
            \brief Creates a dialog.

            \param p_parent A pointer to a parent window. Specify NULL when
                            this dialog is on the top level.

            \throw std::runtime_error When a dialog cannot be created.
        */
        dialog(const window_type* const p_parent)
        :
        window_type(style_dialog, p_parent)
        {}

        /*!
            \brief Destroys the dialog.
        */
        virtual ~dialog()
        throw ()
        {}


        // functions

        /*!
            \brief Shows the dialog as modal.
        */
        virtual void do_modal()
        const
        {

        }


    protected:
        // functions

        /*!
            \brief Dispatches the dialog messages.

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
            //switch (uMsg)
            //{
            //case WM_DESTROY:
            //    {
            //        m_window_destroyed_handler();
            //        return 0;
            //    }
            //}
            return this->window_type::window_procedure(uMsg, wParam, lParam);
        }


    };


}}}

#endif
