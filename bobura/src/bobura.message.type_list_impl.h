/*! \file
    \brief The definition of bobura::message::type_list.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TYPELISTIMPL_H)
#define BOBURA_MESSAGE_TYPELISTIMPL_H

#include <boost/mpl/pair.hpp>

#include <tetengo2.meta.assoc_list.h>

#include "bobura.message.about_dialog.h"
#include "bobura.message.diagram_picture_box.h"
#include "bobura.message.diagram_view.h"
#include "bobura.message.file_property_dialog.h"
#include "bobura.message.font_color_dialog.h"
#include "bobura.message.main_window.h"
#include "bobura.message.oudia_diagram_dialog.h"
#include "bobura.message.property_bar.h"
#include "bobura.message.timetable_model.h"
#include "bobura.message.train_kind_dialog.h"
#include "bobura.message.type_list.h"


namespace bobura { namespace message
{
    namespace timetable_model
    {
        /*!
            \brief The meta function for the type list of the timetable model messages.

            \tparam TimetableModel A timetable model type.
            \tparam DiagramView    A diagram view type.
            \tparam MainWindow     A main window type.
        */
        template <typename TimetableModel, typename DiagramView, typename MainWindow>
        class type_list
        {
        public:
            // types

            //! The type list for the timetable model.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::reset, reset<TimetableModel, DiagramView, MainWindow>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::changed, changed<TimetableModel, DiagramView, MainWindow>>,
                tetengo2::meta::assoc_list_end
                >>
                type;


        };
    }

    namespace diagram_view
    {
        /*!
            \brief The meta function for the type list of the diagram view messages.

            \tparam PropertyBar    A property bar type.
            \tparam Station        A station type.
            \tparam Train          A train type.
            \tparam MessageCatalog A message catalog type.
        */
        template <typename PropertyBar, typename Station, typename Train, typename MessageCatalog>
        class type_list
        {
        public:
            // types

            //! The type list for the timetable model.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::station_selected, station_selected<PropertyBar, Station, MessageCatalog>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::train_selected, train_selected<PropertyBar, Train, MessageCatalog>>,
                tetengo2::meta::assoc_list<boost::mpl::pair<type::all_unselected, all_unselected<PropertyBar>>,
                tetengo2::meta::assoc_list_end
                >>>
                type;


        };
    }

    namespace main_window
    {
        /*!
            \brief The meta function for the type list of the main window messages.

            \tparam PopupMenu         A popup menu type.
            \tparam CommandSet        A command set type.
            \tparam Command           A command type.
            \tparam Model             A model type.
            \tparam View              A view type.
            \tparam AbstractWindow    An abstract window type.
            \tparam DiagramPictureBox A diagram picture box type.
            \tparam PropertyBar       A property bar type.
            \tparam ConfirmFileSave   A file save confirmation type.
            \tparam Settings          A settings type.
        */
        template <
            typename PopupMenu,
            typename CommandSet,
            typename Command,
            typename Model,
            typename View,
            typename AbstractWindow,
            typename DiagramPictureBox,
            typename PropertyBar,
            typename ConfirmFileSave,
            typename Settings
        >
        class type_list
        {
        public:
            // types

            //! The type list for the main window.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::popup_menu_selected, popup_menu_selected<PopupMenu, Command, Model>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::menu_command_selected, menu_command_selected<Command, Model, AbstractWindow>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::file_dropped, file_dropped<CommandSet, Model, AbstractWindow>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::window_resized, window_resized<View, AbstractWindow, DiagramPictureBox, PropertyBar>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::window_closing, window_closing<AbstractWindow, ConfirmFileSave, Settings>>,
                tetengo2::meta::assoc_list_end
                >>>>>
                type;


        };
    }

    namespace diagram_picture_box
    {
        /*!
            \brief The meta function for the type list of the diagram picture box messages.

            \tparam PictureBox A picture box type.
            \tparam View       A view type.
            \tparam ViewZoom   A view zoom.
            \tparam Canvas     A canvas type.
        */
        template <typename PictureBox, typename View, typename ViewZoom, typename Canvas>
        class type_list
        {
        public:
            // types

            //! The type list for the diagram picture box.
            typedef
                tetengo2::meta::assoc_list<boost::mpl::pair<type::mouse_pressed, mouse_pressed<PictureBox, View>>,
                tetengo2::meta::assoc_list<boost::mpl::pair<type::mouse_released, mouse_released<PictureBox, View>>,
                tetengo2::meta::assoc_list<boost::mpl::pair<type::mouse_moved, mouse_moved<PictureBox, View>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::mouse_wheeled, mouse_wheeled<PictureBox, View, ViewZoom>>,
                tetengo2::meta::assoc_list<boost::mpl::pair<type::keyboard_key_down, keyboard_key_down<PictureBox>>,
                tetengo2::meta::assoc_list<boost::mpl::pair<type::paint_paint, paint_paint<Canvas, PictureBox, View>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::scroll_bar_scrolled, scroll_bar_scrolled<PictureBox, View>>,
                tetengo2::meta::assoc_list_end
                >>>>>>>
                type;
        };
    }

    namespace property_bar
    {
        /*!
            \brief The meta function for the type list of the property bar messages.

            \tparam SideBar A side bar bar type.
            \tparam MapBox  A map box type.
        */
        template <typename SideBar, typename MapBox>
        class type_list
        {
        public:
            // types

            //! The type list for the property bar.
            typedef
                tetengo2::meta::assoc_list<boost::mpl::pair<type::resized, resized<SideBar, MapBox>>,
                tetengo2::meta::assoc_list<boost::mpl::pair<type::mouse_pressed, mouse_pressed<MapBox>>,
                tetengo2::meta::assoc_list_end
                >>
                type;
        };
    }

    namespace oudia_diagram_dialog
    {
        /*!
            \brief The meta function for the type list of the OuDia diagram dialog messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        class type_list
        {
        public:
            // types

            //! The type list for the file property dialog.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list_end
                >>
                type;


        };
    }

    namespace file_property_dialog
    {
        /*!
            \brief The meta function for the type list of the file property dialog messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        class type_list
        {
        public:
            // types

            //! The type list for the file property dialog.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list_end
                >>
                type;


        };
    }

    namespace font_color_dialog
    {
        /*!
            \brief The meta function for the type list of the font and color dialog messages.

            \tparam Size           A size type.
            \tparam Dialog         A dialog type.
            \tparam ListBox        A list box type.
            \tparam Canvas         A canvas type.
            \tparam FontDialog     A font dialog type.
            \tparam ColorDialog    A color dialog type.
            \tparam MessageCatalog A message catalog type.
        */
        template <
            typename Size,
            typename Dialog,
            typename ListBox,
            typename Canvas,
            typename FontDialog,
            typename ColorDialog,
            typename MessageCatalog
        >
        class type_list
        {
        public:
            // types

            //! The type list for the font and color dialog.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::category_list_box_selection_changed, category_list_box_selection_changed<Size, ListBox>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::sample_picture_box_paint, sample_picture_box_paint<Size, Canvas, MessageCatalog>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::font_button_mouse_clicked,
                        font_button_mouse_clicked<Size, Dialog, FontDialog, Canvas, MessageCatalog>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::color_button_mouse_clicked,
                        color_button_mouse_clicked<Size, Dialog, ColorDialog, Canvas, MessageCatalog>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list_end
                >>>>>>
                type;


        };
    }

    namespace train_kind_dialog
    {
        /*!
            \brief The meta function for the type list of the train kind dialog messages.

            \tparam InfoSet        An information set type.
            \tparam Size           A size type.
            \tparam Dialog         A dialog type.
            \tparam ListBox        A list box type.
            \tparam Canvas         A canvas type.
            \tparam ColorDialog    A color dialog type.
            \tparam MessageCatalog A message catalog type.
        */
        template <
            typename InfoSet,
            typename Size,
            typename Dialog,
            typename ListBox,
            typename Canvas,
            typename ColorDialog,
            typename MessageCatalog
        >
        class type_list
        {
        public:
            // types

            //! The type list for the font and color dialog.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::train_kind_list_box_selection_changed,
                        train_kind_list_box_selection_changed<Size, ListBox>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::add_button_mouse_clicked, add_button_mouse_clicked<InfoSet, Size, MessageCatalog>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::delete_button_mouse_clicked, delete_button_mouse_clicked<InfoSet, Size>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::up_button_mouse_clicked, up_button_mouse_clicked<InfoSet, Size>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::down_button_mouse_clicked, down_button_mouse_clicked<InfoSet, Size>>,
                tetengo2::meta::assoc_list<boost::mpl::pair<type::name_text_box_changed, name_text_box_changed>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::abbreviation_text_box_changed, abbreviation_text_box_changed>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::color_button_mouse_clicked, color_button_mouse_clicked<Dialog, ColorDialog>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::weight_dropdown_box_selection_changed, weight_dropdown_box_selection_changed
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::line_style_dropdown_box_selection_changed, line_style_dropdown_box_selection_changed
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::sample_picture_box_paint, sample_picture_box_paint<InfoSet, Size, Canvas>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list_end
                >>>>>>>>>>>>>
                type;


        };
    }

    namespace about_dialog
    {
        /*!
            \brief The meta function for the type list of the about dialog messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        class type_list
        {
        public:
            // types

            //! The type list for the about dialog.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list_end
                >
                type;


        };
    }


}}


#endif
