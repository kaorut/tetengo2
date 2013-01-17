/*! \file
    \brief The definition of bobura::oudia_diagram_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_OUDIADIAGRAMDIALOG_H)
#define BOBURA_OUDIADIAGRAMDIALOG_H

//#include <memory>
//#include <utility>
#include <stdexcept>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the OuDia diagram dialog.

        \tparam Dialog                            A dialog type.
        \tparam MessageCatalog                    A message catalog type.
        \tparam Label                             A label type.
        \tparam ListBox                           A list box type.
        \tparam Button                            A button type.
        \tparam TransparentBackground             A transparent background type.
        \tparam OuDiaDiagramDialogMessageTypeList A message type list type.
    */
    template <
        typename Dialog,
        typename MessageCatalog,
        typename Label,
        typename ListBox,
        typename Button,
        typename TransparentBackground,
        typename OuDiaDiagramDialogMessageTypeList
    >
    class oudia_diagram_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        typedef Dialog base_type;

        //! The abstract window type.
        typedef typename base_type::base_type abstract_window_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The background type.
        typedef typename base_type::background_type background_type;

        //! The result type.
        typedef typename base_type::result_type result_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The label type.
        typedef Label label_type;

        //! The list box type.
        typedef ListBox list_box_type;

        //! The integer size type.
        typedef typename list_box_type::int_size_type int_size_type;

        //! The button type.
        typedef Button button_type;

        //! The transparent background type.
        typedef TransparentBackground transparent_background_type;

        //! The message type list type.
        typedef OuDiaDiagramDialogMessageTypeList oudia_diagram_dialog_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a OuDia diagram dialog.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        oudia_diagram_dialog(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        base_type(parent),
        m_message_catalog(message_catalog),
        m_names(),
        m_selected_index(),
        m_p_prompt_label(),
        m_p_diagram_list_box(),
        m_p_ok_button(),
        m_p_cancel_button()
        {
            initialize_dialog(parent);
        }

        /*!
            \brief Destroys the OuDia diagram dialog.
        */
        virtual ~oudia_diagram_dialog()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the names.

            \return The names.
        */
        const std::vector<string_type>& names()
        const
        {
            return m_names;
        }

        /*!
            \brief Sets names.

            \param names Names.
        */
        void set_names(std::vector<string_type> names)
        {
            m_names = std::move(names);
            if (!m_p_diagram_list_box->destroyed())
            {
                m_p_diagram_list_box->clear();
                BOOST_FOREACH (const string_type& name, m_names)
                {
                    m_p_diagram_list_box->insert_item(m_p_diagram_list_box->item_count(), name);
                }
            }

            m_selected_index = m_p_diagram_list_box->selected_item_index();
        }

        /*!
            \brief Returns the selected index.

            \return The selected index.
        */
        const boost::optional<int_size_type>& selected_index()
        const
        {
            return m_selected_index;
        }

        /*!
            \brief Sets a selected index.

            \param index An index.

            \throw std::out_of_range When index is greater than the diagram count.
        */
        void set_selected_index(const int_size_type index)
        {
            if (index >= m_p_diagram_list_box->item_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is greater than the diagram count."));

            m_selected_index = boost::make_optional(index);
            if (!m_p_diagram_list_box->destroyed())
                m_p_diagram_list_box->select_item(*m_selected_index);
        }


    private:
        // types

        typedef typename oudia_diagram_dialog::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename oudia_diagram_dialog::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;


        // variables

        const message_catalog_type& m_message_catalog;

        std::vector<string_type> m_names;

        boost::optional<int_size_type> m_selected_index;

        std::unique_ptr<label_type> m_p_prompt_label;

        std::unique_ptr<list_box_type> m_p_diagram_list_box;

        std::unique_ptr<button_type> m_p_ok_button;

        std::unique_ptr<button_type> m_p_cancel_button;


        // virtual functions

        virtual void set_result_impl()
        {
            m_selected_index = m_p_diagram_list_box->selected_item_index();
        }


        // functions

        void initialize_dialog(const abstract_window_type& parent)
        {
            set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:OuDiaDiagram:Diagram Selection")));

            this->set_client_dimension(dimension_type(width_type(24), height_type(18)));

            m_p_prompt_label = create_prompt_label();
            m_p_diagram_list_box = create_diagram_list_box();
            m_p_ok_button = create_ok_button();
            m_p_cancel_button = create_cancel_button();

            locate_controls();
        }

        std::unique_ptr<label_type> create_prompt_label()
        {
            std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(*this);

            p_label->set_text(
                m_message_catalog.get(
                    TETENGO2_TEXT("Dialog:OuDiaDiagram:The timetable file has multiple diagrams. Choose one to load.")
                )
            );
            std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<list_box_type> create_diagram_list_box()
        {
            std::unique_ptr<list_box_type> p_list_box =
                tetengo2::make_unique<list_box_type>(*this, list_box_type::scroll_bar_style_type::vertical);

            return std::move(p_list_box);
        }

        std::unique_ptr<button_type> create_ok_button()
        {
            std::unique_ptr<button_type> p_button =
                tetengo2::make_unique<button_type>(*this, button_type::style_type::default_);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    oudia_diagram_dialog_message_type_list_type,
                    message::oudia_diagram_dialog::type::ok_button_mouse_clicked
                >::type(*this)
            );

            return std::move(p_button);
        }

        std::unique_ptr<button_type> create_cancel_button()
        {
            std::unique_ptr<button_type> p_button =
                tetengo2::make_unique<button_type>(*this, button_type::style_type::cancel);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    oudia_diagram_dialog_message_type_list_type,
                    message::oudia_diagram_dialog::type::cancel_button_mouse_clicked
                >::type(*this)
            );

            return std::move(p_button);
        }

        void locate_controls()
        {
            const left_type label_left(2);

            m_p_prompt_label->set_dimension(dimension_type(width_type(20), height_type(3)));
            m_p_prompt_label->set_position(position_type(label_left, top_type(1)));

            m_p_diagram_list_box->set_dimension(dimension_type(width_type(20), height_type(10)));
            m_p_diagram_list_box->set_position(
                position_type(
                    label_left,
                    tetengo2::gui::position<position_type>::top(m_p_prompt_label->position()) +
                        top_type::from(tetengo2::gui::dimension<dimension_type>::height(m_p_prompt_label->dimension()))
                )
            );

            m_p_ok_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_ok_button->set_position(position_type(left_type(5), top_type(15)));

            m_p_cancel_button->set_dimension(dimension_type(width_type(8), height_type(2)));
            m_p_cancel_button->set_position(position_type(left_type(14), top_type(15)));
        }


    };


}

#endif
