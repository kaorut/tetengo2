/*! \file
    \brief The definition of bobura::load_save::load_from_file.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_LOADFROMFILE_H)
#define BOBURA_LOADSAVE_LOADFROMFILE_H

#include <cassert>
#include <ios>
//#include <iterator>
//#include <memory>
#include <stdexcept>
//#include <utility>

#include <boost/filesystem/fstream.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.stdalt.h>
#include <tetengo2.text.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a file loading.

        \tparam Model           A model type.
        \tparam AbstractWindow  An abstract window type.
        \tparam MessageBox      A message box type.
        \tparam FileOpenDialog  A file open dialog type.
        \tparam ConfirmFileSave A file save confirmation type.
        \tparam ReaderSelector  A reader selector type.
        \tparam ReaderSet       A reader set type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename Model,
        typename AbstractWindow,
        typename MessageBox,
        typename FileOpenDialog,
        typename ConfirmFileSave,
        typename ReaderSelector,
        typename ReaderSet,
        typename MessageCatalog
    >
    class load_from_file
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The message box type.
        typedef MessageBox message_box_type;

        //! The file open dialog type.
        typedef FileOpenDialog file_open_dialog_type;

        //! The path type.
        typedef typename file_open_dialog_type::path_type path_type;

        //! The file save confirmation type.
        typedef ConfirmFileSave confirm_file_save_type;

        //! The reader selector type.
        typedef ReaderSelector reader_selector_type;

        //! The reader set type.
        typedef ReaderSet reader_set_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a file loading.

            \param ask_file_path     Set true to show a file selection dialog.
            \param confirm_file_save A file save confirmation.
            \param message_catalog   A message catalog.
        */
        load_from_file(
            const bool                    ask_file_path,
            const confirm_file_save_type& confirm_file_save,
            const message_catalog_type&   message_catalog
        )
        :
        m_ask_file_path(ask_file_path),
        m_confirm_file_save(confirm_file_save),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Return whether the model is reloadable.

            \param model      A model.
            \param given_path A given path.

            \retval true  When the model is reloadable.
            \retval false Otherwise.
        */
        bool reloadable(const model_type& model, const boost::optional<path_type>& given_path)
        const
        {
            return m_ask_file_path || model.has_path() || given_path;
        }

        /*!
            \brief Executes the load_save.

            \param model      A model.
            \param given_path A given path.
            \param parent     A parent window.
        */
        void operator()(model_type& model, const boost::optional<path_type>& given_path, abstract_window_type& parent)
        const
        {
            if (!m_ask_file_path && !model.has_path() && !given_path)
                return;

            if (!m_confirm_file_save(parent))
                return;

            path_type path;
            if (m_ask_file_path)
            {
                file_open_dialog_type dialog(
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Open")), make_file_filters(), parent
                );
                const auto ok = dialog.do_modal();
                if (!ok)
                    return;

                path = dialog.result();
            }
            else if (given_path)
            {
                path = *given_path;
            }
            else
            {
                assert(model.has_path());
                path = model.path();
            }

            boost::filesystem::ifstream input_stream(path, std::ios_base::binary);
            if (!input_stream)
            {
                create_cant_open_file_message_box(path, parent)->do_modal();
                return;
            }

            reader_selector_type reader_selector(
                reader_set_type::create_readers(parent, path.template string<string_type>(), m_message_catalog)
            );
            auto error = reader_error_type::none;
            auto p_timetable =
                reader_selector.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );
            if (!p_timetable)
            {
                switch (error)
                {
                case reader_error_type::canceled:
                    break; // Do nothing.
                case reader_error_type::corrupted:
                    create_file_broken_message_box(path, parent)->do_modal();
                    break;
                case reader_error_type::unsupported:
                    create_unsupported_format_file_message_box(path, parent)->do_modal();
                    break;
                default:
                    assert(false);
                    BOOST_THROW_EXCEPTION(std::logic_error("Unknown reader error."));
                }
                return;
            }

            model.reset_timetable(std::move(p_timetable), path);
        }


    private:
        // types

        typedef typename abstract_window_type::string_type string_type;

        typedef typename reader_selector_type::error_type reader_error_type;


        // variables

        const bool m_ask_file_path;

        const confirm_file_save_type& m_confirm_file_save;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<message_box_type> create_cant_open_file_message_box(
            const path_type&      path,
            abstract_window_type& parent
        )
        const
        {
            return
                tetengo2::stdalt::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:Can't open the file.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        std::unique_ptr<message_box_type> create_file_broken_message_box(
            const path_type&      path,
            abstract_window_type& parent
        )
        const
        {
            return
                tetengo2::stdalt::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:The timetable file is corrupted.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        std::unique_ptr<message_box_type> create_unsupported_format_file_message_box(
            const path_type&      path,
            abstract_window_type& parent
        )
        const
        {
            return
                tetengo2::stdalt::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:Unsupported format file.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        typename file_open_dialog_type::file_filters_type
        make_file_filters()
        const
        {
            typename file_open_dialog_type::file_filters_type filters;

            filters.emplace_back(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:All Timetable Files")),
                string_type(TETENGO2_TEXT("btt;*.btt_bz2;*.oud;*.dia"))
            );
            filters.emplace_back(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files")),
                string_type(TETENGO2_TEXT("btt"))
            );
            filters.emplace_back(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files (Compressed)")),
                string_type(TETENGO2_TEXT("btt_bz2"))
            );
            filters.emplace_back(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:OuDia Files")),
                string_type(TETENGO2_TEXT("oud"))
            );
            filters.emplace_back(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:WinDIA Files")),
                string_type(TETENGO2_TEXT("dia"))
            );
            filters.emplace_back(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:All Files")), string_type(TETENGO2_TEXT("*"))
            );

            return filters;
        }


    };


}}


#endif
