/*! \file
    \brief The definition of bobura::bobura.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_BOBURA_H)
#define BOBURA_BOBURA_H

#include <memory>

#include <boost/noncopyable.hpp>


namespace bobura
{
   /*!
        \brief The class template for a bobura application.

        \tparam Settings                  A settings type.
        \tparam Model                     A model type.
        \tparam MessageCatalog            A message catalog type.
        \tparam CommandSet                A command set type.
        \tparam MainWindow                A main window type.
        \tparam MainWindowMessageTypeList A main window message type list.
        \tparam MenuBar                   A menu bar type.
        \tparam MenuCommand               A menu command type.
        \tparam PopupMenu                 A popup menu type.
        \tparam MenuSeparator             A menu separator type.
        \tparam MessageLoop               A message loop type.
        \tparam MessageLoopBreak          A message loop break type.
        \tparam GuiFixture                A GUI fixture type.
    */
    template <
        typename Settings,
        typename Model,
        typename MessageCatalog,
        typename CommandSet,
        typename MainWindow,
        typename MainWindowMessageTypeList,
        typename MenuBar,
        typename MenuCommand,
        typename PopupMenu,
        typename MenuSeparator,
        typename MessageLoop,
        typename MessageLoopBreak,
        typename GuiFixture
    >
    class bobura : private boost::noncopyable
    {
    public:
        // types

        //! The settings type.
        typedef Settings settings_type;

        //! The model type.
        typedef Model model_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The command set type.
        typedef CommandSet command_set_type;

        //! The main window type.
        typedef MainWindow main_window_type;

        //! The message type list type.
        typedef MainWindowMessageTypeList main_window_message_type_list_type;

        //! The menu bar type.
        typedef MenuBar menu_bar_type;

        //! The menu command type.
        typedef MenuCommand menu_command_type;

        //! The popup menu type.
        typedef PopupMenu popup_menu_type;

        //! The menu separator type.
        typedef MenuSeparator menu_separator_type;

        //! The message loop type.
        typedef MessageLoop message_loop_type;

        //! The message loop break type.
        typedef MessageLoopBreak message_loop_break_type;

        //! The GUI fixture type.
        typedef GuiFixture gui_fixture_type;


        // constructors and destructor

        /*!
            \brief Creates a bobura application.

            \param settings Settings of the bobura.
        */
        explicit bobura(const settings_type& settings)
        :
        m_gui_fixture(),
        m_settings(settings),
        m_model()
        {}


        // functions

        /*!
            \brief Runs the main process of the application.

            \return The exit status code.
        */
        int run()
        const
        {
            const message_catalog_type message_catalog;

            main_window_type main_window(message_catalog, m_settings);
            const command_set_type command_set(main_window);
            main_window.set_menu_bar(
                build_main_window_menu(
                    command_set, main_window, m_settings, message_catalog
                )
            );
            main_window.set_visible(true);

            return message_loop_type(main_window)();
        }


    private:
        // types

        typedef typename command_set_type::command_type command_type;

        typedef typename menu_command_type::base_type menu_base_type;

        typedef typename menu_base_type::shortcut_key_type shortcut_key_type;

        typedef typename shortcut_key_type::virtual_key_type virtual_key_type;


        // static functions

        static std::unique_ptr<menu_bar_type> build_main_window_menu(
            const command_set_type&     command_set,
            main_window_type&           main_window,
            const settings_type&        settings,
            const message_catalog_type& message_catalog
        )
        {
            std::unique_ptr<menu_bar_type> p_menu_bar(
                tetengo2::make_unique<menu_bar_type>()
            );

            {
                std::unique_ptr<menu_base_type> p_popup_menu(
                    tetengo2::make_unique<popup_menu_type>(
                        message_catalog.get(TETENGO2_TEXT("Menu:&File"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:File:&New")),
                    command_set.nop(),
                    shortcut_key_type(
                        virtual_key_type::char_n(), false, true, false
                    )
                );
                //append_menu_command(
                //    *p_popup_menu,
                //    message_catalog.get(
                //        TETENGO2_TEXT("Menu:File:&Open...")
                //    ),
                //    typename boost::mpl::at<
                //        command_type_list_type, command::type::load_from_file
                //    >::type(*this, message_catalog),
                //    shortcut_key_type(
                //        virtual_key_type::char_o(), false, true, false
                //    )
                //);
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:File:&Save")),
                    command_set.nop(),
                    shortcut_key_type(
                        virtual_key_type::char_s(), false, true, false
                    )
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(
                        TETENGO2_TEXT("Menu:File:Save &As...")
                    ),
                    command_set.nop()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Menu:File:E&xit")),
                    command_set.exit()
                );

                p_menu_bar->insert(
                    p_menu_bar->end(), std::move(p_popup_menu)
                );
            }
            {
                std::unique_ptr<menu_base_type>
                p_popup_menu(
                    tetengo2::make_unique<popup_menu_type>(
                        message_catalog.get(TETENGO2_TEXT("Menu:&Help"))
                    )
                );

                //append_menu_command(
                //    *p_popup_menu,
                //    message_catalog.get(
                //        TETENGO2_TEXT("Menu:Help:&About")
                //    ),
                //    typename boost::mpl::at<
                //        command_type_list_type, command::type::about
                //    >::type(main_window, message_catalog, settings)
                //);

                p_menu_bar->insert(
                    p_menu_bar->end(), std::move(p_popup_menu)
                );
            }

            return std::move(p_menu_bar);
        }

        static void append_menu_command(
            menu_base_type&                        popup_menu,
            typename menu_base_type::string_type&& text,
            const command_type&                    command
        )
        {
            std::unique_ptr<menu_base_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(
                    std::forward<typename menu_base_type::string_type>(text)
                )
            );

            p_menu_command->menu_observer_set().selected().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::menu
                >::type(command)
            );

            popup_menu.insert(popup_menu.end(), std::move(p_menu_command));
        }

        static void append_menu_command(
            menu_base_type&                        popup_menu,
            typename menu_base_type::string_type&& text,
            const command_type&                    command,
            shortcut_key_type&&                    shortcut_key
        )
        {
            std::unique_ptr<menu_base_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(
                    std::forward<typename menu_base_type::string_type>(text),
                    std::forward<shortcut_key_type>(shortcut_key)
                )
            );

            p_menu_command->menu_observer_set().selected().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::menu
                >::type(command)
            );

            popup_menu.insert(popup_menu.end(), std::move(p_menu_command));
        }

        static void append_menu_separator(menu_base_type& popup_menu)
        {
            std::unique_ptr<menu_base_type> p_menu_separator(
                tetengo2::make_unique<menu_separator_type>()
            );
            popup_menu.insert(popup_menu.end(), std::move(p_menu_separator));
        }


        // variables

        const gui_fixture_type m_gui_fixture;

        const settings_type& m_settings;

        model_type m_model;


    };


}

#endif
