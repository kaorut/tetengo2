/*! \file
    \brief The definition of bobura::oudia_diagram_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <stdexcept>
//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>
//#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"
#include "bobura.type_list.h"

#include "bobura.oudia_diagram_dialog.h"


namespace bobura
{
    namespace
    {
        template <typename Dialog, typename MessageCatalog, typename IntSize>
        class oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::impl : private boost::noncopyable
        {
        public:
            // types

            typedef Dialog base_type;

            typedef typename base_type::string_type string_type;

            typedef typename base_type::background_type background_type;

            typedef MessageCatalog message_catalog_type;

            typedef IntSize int_size_type;


            // constructors and destructor

            impl(base_type& base, const message_catalog_type& message_catalog)
            :
            m_base(base),
            m_message_catalog(message_catalog),
            m_file_name(),
            m_names(),
            m_selected_index(),
            m_p_file_name_label(),
            m_p_prompt_label(),
            m_p_diagram_list_box(),
            m_p_ok_button(),
            m_p_cancel_button()
            {
                initialize_dialog();
            }


            // functions

            const string_type& file_name()
            const
            {
                return m_file_name;
            }

            void set_file_name(string_type file_name)
            {
                m_file_name = std::move(file_name);
                if (!m_p_file_name_label->destroyed())
                    m_p_file_name_label->set_text(m_file_name);
            }

            const std::vector<string_type>& names()
            const
            {
                return m_names;
            }

            void set_names(std::vector<string_type> names)
            {
                m_names = std::move(names);
                if (!m_p_diagram_list_box->destroyed())
                {
                    m_p_diagram_list_box->clear();
                    for (const string_type& name: m_names)
                    {
                        m_p_diagram_list_box->insert_item(m_p_diagram_list_box->item_count(), name);
                    }
                }

                m_selected_index = m_p_diagram_list_box->selected_item_index();
            }

            const boost::optional<int_size_type>& selected_index()
            const
            {
                return m_selected_index;
            }

            void set_selected_index(const int_size_type index)
            {
                if (index >= m_p_diagram_list_box->item_count())
                    BOOST_THROW_EXCEPTION(std::out_of_range("index is greater than the diagram count."));

                m_selected_index = boost::make_optional(index);
                if (!m_p_diagram_list_box->destroyed())
                    m_p_diagram_list_box->select_item(*m_selected_index);
            }

            void set_result_impl()
            {
                m_selected_index = m_p_diagram_list_box->selected_item_index();
            }


        private:
            // types

            typedef typename boost::mpl::at<ui_type_list, type::ui::label>::type label_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::list_box>::type list_box_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::button>::type button_type;

            typedef
                typename boost::mpl::at<ui_type_list, type::ui::transparent_background>::type
                transparent_background_type;

            typedef
                typename message::oudia_diagram_dialog::type_list<base_type>::type
                oudia_diagram_dialog_message_type_list_type;

            typedef typename base_type::dimension_type dimension_type;

            typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

            typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

            typedef typename base_type::position_type position_type;

            typedef typename tetengo2::gui::position<position_type>::left_type left_type;

            typedef typename tetengo2::gui::position<position_type>::top_type top_type;


            // variables

            base_type& m_base;

            const message_catalog_type& m_message_catalog;

            string_type m_file_name;

            std::vector<string_type> m_names;

            boost::optional<int_size_type> m_selected_index;

            std::unique_ptr<label_type> m_p_file_name_label;

            std::unique_ptr<label_type> m_p_prompt_label;

            std::unique_ptr<list_box_type> m_p_diagram_list_box;

            std::unique_ptr<button_type> m_p_ok_button;

            std::unique_ptr<button_type> m_p_cancel_button;


            // functions

            void initialize_dialog()
            {
                m_base.set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:OuDiaDiagram:Diagram Selection")));

                m_p_file_name_label = create_file_name_label();
                m_p_prompt_label = create_prompt_label();
                m_p_diagram_list_box = create_diagram_list_box();
                m_p_ok_button = create_ok_button();
                m_p_cancel_button = create_cancel_button();

                locate_controls();
            }

            std::unique_ptr<label_type> create_file_name_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(m_file_name);
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<label_type> create_prompt_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(
                    m_message_catalog.get(
                        TETENGO2_TEXT("Dialog:OuDiaDiagram:&Select a diagram to load:")
                    )
                );
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<list_box_type> create_diagram_list_box()
            {
                std::unique_ptr<list_box_type> p_list_box =
                    tetengo2::make_unique<list_box_type>(m_base, list_box_type::scroll_bar_style_type::vertical);

                p_list_box->mouse_observer_set().doubleclicked().connect(
                    typename boost::mpl::at<
                        oudia_diagram_dialog_message_type_list_type,
                        message::oudia_diagram_dialog::type::ok_button_mouse_clicked
                    >::type(m_base)
                );

                return std::move(p_list_box);
            }

            std::unique_ptr<button_type> create_ok_button()
            {
                std::unique_ptr<button_type> p_button =
                    tetengo2::make_unique<button_type>(m_base, button_type::style_type::default_);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
                p_button->mouse_observer_set().clicked().connect(
                    typename boost::mpl::at<
                        oudia_diagram_dialog_message_type_list_type,
                        message::oudia_diagram_dialog::type::ok_button_mouse_clicked
                    >::type(m_base)
                );

                return std::move(p_button);
            }

            std::unique_ptr<button_type> create_cancel_button()
            {
                std::unique_ptr<button_type> p_button =
                    tetengo2::make_unique<button_type>(m_base, button_type::style_type::cancel);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
                p_button->mouse_observer_set().clicked().connect(
                    typename boost::mpl::at<
                        oudia_diagram_dialog_message_type_list_type,
                        message::oudia_diagram_dialog::type::cancel_button_mouse_clicked
                    >::type(m_base)
                );

                return std::move(p_button);
            }

            void locate_controls()
            {
                m_base.set_client_dimension(dimension_type(width_type(32), height_type(19)));

                const left_type label_left(2);
                const width_type control_width(28);

                m_p_file_name_label->set_dimension(dimension_type(control_width, height_type(2)));
                m_p_file_name_label->set_position(position_type(label_left, top_type(1)));

                m_p_prompt_label->fit_to_content(control_width);
                m_p_prompt_label->set_position(position_type(label_left, top_type(3)));

                m_p_diagram_list_box->set_dimension(dimension_type(control_width, height_type(10)));
                m_p_diagram_list_box->set_position(
                    position_type(
                        label_left,
                        tetengo2::gui::position<position_type>::top(m_p_prompt_label->position()) +
                            top_type::from(
                                tetengo2::gui::dimension<dimension_type>::height(m_p_prompt_label->dimension())
                            )
                    )
                );

                m_p_ok_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_ok_button->set_position(position_type(left_type(13), top_type(16)));

                m_p_cancel_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_cancel_button->set_position(position_type(left_type(22), top_type(16)));
            }


        };


    }


    template <typename Dialog, typename MessageCatalog, typename IntSize>
    oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::oudia_diagram_dialog(
        abstract_window_type&       parent,
        const message_catalog_type& message_catalog
    )
    :
    base_type(parent),
    m_p_impl(tetengo2::make_unique<impl>(*this, message_catalog))
    {}

    template <typename Dialog, typename MessageCatalog, typename IntSize>
    oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::~oudia_diagram_dialog()
    TETENGO2_CPP11_NOEXCEPT
    {}

    template <typename Dialog, typename MessageCatalog, typename IntSize>
    const typename oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::string_type&
    oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::file_name()
    const
    {
        return m_p_impl->file_name();
    }

    template <typename Dialog, typename MessageCatalog, typename IntSize>
    void oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::set_file_name(string_type file_name)
    {
        m_p_impl->set_file_name(std::move(file_name));
    }

    template <typename Dialog, typename MessageCatalog, typename IntSize>
    const std::vector<typename oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::string_type>&
    oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::names()
    const
    {
        return m_p_impl->names();
    }

    template <typename Dialog, typename MessageCatalog, typename IntSize>
    void oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::set_names(std::vector<string_type> names)
    {
        m_p_impl->set_names(std::move(names));
    }

    template <typename Dialog, typename MessageCatalog, typename IntSize>
    const boost::optional<typename oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::int_size_type>&
    oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::selected_index()
    const
    {
        return m_p_impl->selected_index();
    }

    template <typename Dialog, typename MessageCatalog, typename IntSize>
    void oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::set_selected_index(const int_size_type index)
    {
        m_p_impl->set_selected_index(index);
    }

    template <typename Dialog, typename MessageCatalog, typename IntSize>
    void oudia_diagram_dialog<Dialog, MessageCatalog, IntSize>::set_result_impl()
    {
        m_p_impl->set_result_impl();
    }


    template class oudia_diagram_dialog<
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
        typename boost::mpl::at<common_type_list, type::size>::type
    >;


}
