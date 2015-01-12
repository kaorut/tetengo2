/*! \file
    \brief The definition of tetengo2::gui::widget::progress dialog.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H)
#define TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H

#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a progress dialog.

        \tparam Traits             A traits type.
        \tparam DetailsTraits      A detail implementation type traits.
        \tparam MenuDetails        A detail implementation type of a menu.
        \tparam MessageLoopDetails A detail implementation type of a message loop.
    */
    template <typename Traits, typename DetailsTraits, typename MenuDetails, typename MessageLoopDetails>
    class progress_dialog : public dialog<Traits, DetailsTraits, MenuDetails, MessageLoopDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The message loop details type.
        using message_loop_details_type = MessageLoopDetails;

        //! The base type.
        using base_type = dialog<traits_type, details_traits_type, menu_details_type, message_loop_details_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;


        // constructors and destructor

        /*!
            \brief Creates a progress dialog.

            \param parent A parent window.
        */
        explicit progress_dialog(abstract_window_type& parent)
        :
        base_type(parent, false)
        {
            initialize_progress_dialog();
        }

        /*!
            \brief Destroys the progress dialog.
        */
        virtual ~progress_dialog()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        // virtual functions

        virtual void do_modal_impl()
        override
        {
        
        }

        virtual void do_modal_finished_impl()
        override
        {
        
        }


        // functions

        void initialize_progress_dialog()
        {
            base_type::initialize_dialog();
        }


    };


}}}


#endif
