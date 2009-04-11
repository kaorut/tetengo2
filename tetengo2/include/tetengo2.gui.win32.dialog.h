/*! \file
    \brief The definition of tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DIALOG_H)
#define TETENGO2_GUI_WIN32_DIALOG_H

#include <cassert>
//#include <memory>
#include <stdexcept>

//#include <boost/concept_check.hpp>
#include <boost/scope_exit.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.Window.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a modal dialog.
 
        \tparam Window          A window type. It must conform to
                                concept_tetengo2::gui::Window<Window>.
        \tparam MessageLoop     A generator type for a message loop. It must
                                conform to
                                boost::Generator<MessageLoop, int>.
        \tparam QuitMessageLoop A unary functor type for quitting the message
                                loop. It must conform to
                                boost::UnaryFunction<QuitMessageLoop, void, int>
   */
    template <typename Window, typename MessageLoop, typename QuitMessageLoop>
    class dialog : public Window
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));
        BOOST_CONCEPT_ASSERT((boost::Generator<MessageLoop, int>));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
        ));


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

        //! The font type.
        typedef typename window_type::font_type font_type;

        //! The child type.
        typedef typename window_type::child_type child_type;

        //! The paint observer type.
        typedef typename window_type::paint_observer_type paint_observer_type;

        //! The mouse observer type.
        typedef typename window_type::mouse_observer_type mouse_observer_type;

        //! The main menu type.
        typedef typename window_type::main_menu_type main_menu_type;

        //! The window observer type.
        typedef
            typename window_type::window_observer_type window_observer_type;

        //! The style type.
        typedef typename window_type::style_type style_type;

        //! The message loop type.
        typedef MessageLoop message_loop_type;

        //! The quit message loop type.
        typedef QuitMessageLoop quit_message_loop_type;


        // constructors and destructor

        /*!
            \brief Creates a dialog.

            \param parent A parent window.
            \param style  A style.

            \throw std::runtime_error When a dialog cannot be created.
        */
        dialog(
            const window_type& parent,
            const style_type   style = style_dialog
        )
        :
        window_type(parent, style)
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

            \throw std::runtime_error When the dialog is already destroyed.
        */
        virtual void do_modal()
        {
            check_destroyed();

            assert(this->has_parent());
            window_type& parent = dynamic_cast<window_type&>(this->parent());
            parent.set_enabled(false);
            BOOST_SCOPE_EXIT((&parent))
            {
                parent.set_enabled(true);
                parent.activate();
            } BOOST_SCOPE_EXIT_END

            this->add_window_observer(
                std::auto_ptr<window_observer_type> (
                    new dialog_window_observer_type()
                )
            );
            this->set_visible(true);

            message_loop_type()();
        }


    protected:
        // functions

        /*!
            \brief Dispatches the window messages.

            \param uMsg                       A message.
            \param wParam                     A word-sized parameter.
            \param lParam                     A long-sized parameter.
            \param p_default_window_procedure A pointer to a default window
                                              procedure.

            \return The result code.
        */
        virtual ::LRESULT window_procedure(
            const ::UINT    uMsg,
            const ::WPARAM  wParam,
            const ::LPARAM  lParam,
            const ::WNDPROC p_default_window_procedure
        )
        {
            return this->window_type::window_procedure(
                uMsg, wParam, lParam, p_default_window_procedure
            );
        }


    private:
        // types

        struct dialog_window_observer_type : public window_observer_type
        {
            virtual void destroyed()
            {
                quit_message_loop_type()(0);
            }
        };


    };


}}}

#endif
