/*! \file
    \brief The definition of tetengo2::detail::stub::message_handler.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_MESSAGEHANDLER_H)
#define TETENGO2_DETAIL_STUB_MESSAGEHANDLER_H

#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>


namespace tetengo2::detail::stub {
    /*!
        \brief The class for a detail implementation of a message handler.
    */
    class message_handler : private boost::noncopyable
    {
    public:
        // types

        //! The message handler type.
        using message_handler_type = std::function<void()>;

        //! The message handler map type.
        using message_handler_map_type = std::unordered_map<int, std::vector<message_handler_type>>;


        // static functions

        /*!
            \brief Make a message handler map for an abstract window.

            \tparam AbstractWindow An abstract window type.

            \param abstract_window An abstract window.
            \param initial_map     An initial message handler map.

            \return A message handler map.
        */
        template <typename AbstractWindow>
        static message_handler_map_type make_abstract_window_message_handler_map(
            [[maybe_unused]] AbstractWindow& abstract_window,
            message_handler_map_type&&       initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a button.

            \tparam Button A button type.

            \param button      A button.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Button>
        static message_handler_map_type
            make_button_message_handler_map([[maybe_unused]] Button& button, message_handler_map_type&& initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a control.

            \tparam Control A control type.

            \param control     A control.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Control>
        static message_handler_map_type
            make_control_message_handler_map([[maybe_unused]] Control& control, message_handler_map_type&& initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a custom control.

            \tparam CustomControl A custom control type.

            \param custom_control A custom control.
            \param initial_map    An initial message handler map.

            \return A message handler map.
        */
        template <typename CustomControl>
        static message_handler_map_type make_custom_control_message_handler_map(
            [[maybe_unused]] CustomControl& custom_control,
            message_handler_map_type&&      initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a dialog.

            \tparam Dialog A dialog type.

            \param dialog      A dialog.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Dialog>
        static message_handler_map_type
            make_dialog_message_handler_map([[maybe_unused]] Dialog& dialog, message_handler_map_type&& initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a dropdown box.

            \tparam DropdownBox A dropdown box type.

            \param dropdown_box A dropdown box.
            \param initial_map  An initial message handler map.

            \return A message handler map.
        */
        template <typename DropdownBox>
        static message_handler_map_type make_dropdown_box_message_handler_map(
            [[maybe_unused]] DropdownBox& dropdown_box,
            message_handler_map_type&&    initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for an image.

            \tparam Image An image type.

            \param image       An image.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Image>
        static message_handler_map_type
            make_image_message_handler_map([[maybe_unused]] Image& image, message_handler_map_type&& initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a label.

            \tparam Label A label type.

            \param label       A label.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Label>
        static message_handler_map_type
            make_label_message_handler_map([[maybe_unused]] Label& label, message_handler_map_type&& initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a list box.

            \tparam ListBox A list box type.

            \param list_box    A list box.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename ListBox>
        static message_handler_map_type make_list_box_message_handler_map(
            [[maybe_unused]] ListBox&  list_box,
            message_handler_map_type&& initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a picture box.

            \tparam PictureBox A picture box type.

            \param picture_box A picture box.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename PictureBox>
        static message_handler_map_type make_picture_box_message_handler_map(
            [[maybe_unused]] PictureBox& picture_box,
            message_handler_map_type&&   initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a text box.

            \tparam TextBox A text box type.

            \param text_box    A text box.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename TextBox>
        static message_handler_map_type make_text_box_message_handler_map(
            [[maybe_unused]] TextBox&  text_box,
            message_handler_map_type&& initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a widget.

            \tparam Widget A widget type.

            \param widget      A widget.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Widget>
        static message_handler_map_type
            make_widget_message_handler_map([[maybe_unused]] Widget& widget, message_handler_map_type&& initial_map)
        {
            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a window.

            \tparam Window A window type.

            \param window      A window.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Window>
        static message_handler_map_type
            make_window_message_handler_map([[maybe_unused]] Window& window, message_handler_map_type&& initial_map)
        {
            return std::move(initial_map);
        }


    private:
        // forbidden operations

        message_handler() = delete;
    };
}


#endif
