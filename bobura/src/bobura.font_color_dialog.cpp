/*! \file
    \brief The definition of bobura::font_color_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <sstream>
//#include <stdexcept>
//#include <utility>
//#include <vector>

//#include <boost/format.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>
//#include <boost/optional.hpp>
#include <boost/rational.hpp>
//#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"
#include "bobura.type_list.h"

#include "bobura.font_color_dialog.h"


namespace bobura
{
    namespace
    {
        template <
            typename Dialog,
            typename MessageCatalog,
            typename IntSize,
            typename Font,
            typename PointSize,
            typename Color
        >
        class font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::impl :
            private boost::noncopyable
        {
        public:
            // types

            typedef Dialog base_type;

            typedef typename base_type::base_type abstract_window_type;

            typedef typename base_type::string_type string_type;

            typedef typename base_type::background_type background_type;

            typedef MessageCatalog message_catalog_type;

            typedef IntSize int_size_type;

            typedef Font font_type;

            typedef PointSize point_size_type;

            typedef Color color_type;

            typedef
                typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_color_type
                font_color_type;


            // constructors and destructor

            impl(
                base_type&                  base,
                abstract_window_type&       parent,
                const message_catalog_type& message_catalog
            )
            :
            m_base(base),
            m_message_catalog(message_catalog),
            m_font_color_list(9, internal_font_color_type(boost::none, boost::none)),
            m_current_category_index(),
            m_p_category_label(),
            m_p_category_list_box(),
            m_p_font_button(),
            m_p_font_text_box(),
            m_p_color_button(),
            m_p_sample_label(),
            m_p_sample_picture_box(),
            m_p_ok_button(),
            m_p_cancel_button()
            {
                initialize_dialog(parent);
            }


            // functions

            const color_type& background()
            const
            {
                return to_color(m_font_color_list[0]);
            }

            void set_background(const color_type& color)
            {
                m_font_color_list[0] = internal_font_color_type(boost::none, boost::make_optional(color));
            }

            font_color_type company_line_name()
            const
            {
                return to_font_color(m_font_color_list[1]);
            }

            void set_company_line_name(const font_type& font, const color_type& color)
            {
                m_font_color_list[1] =
                    internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
            }

            font_color_type note()
            const
            {
                return to_font_color(m_font_color_list[2]);
            }

            void set_note(const font_type& font, const color_type& color)
            {
                m_font_color_list[2] =
                    internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
            }

            font_color_type time_line()
            const
            {
                return to_font_color(m_font_color_list[3]);
            }

            void set_time_line(const font_type& font, const color_type& color)
            {
                m_font_color_list[3] =
                    internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
            }

            font_color_type local_station()
            const
            {
                return to_font_color(m_font_color_list[4]);
            }

            void set_local_station(const font_type& font, const color_type& color)
            {
                m_font_color_list[4] =
                    internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
            }

            font_color_type principal_station()
            const
            {
                return to_font_color(m_font_color_list[5]);
            }

            void set_principal_station(const font_type& font, const color_type& color)
            {
                m_font_color_list[5] =
                    internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
            }

            font_color_type local_terminal_station()
            const
            {
                return to_font_color(m_font_color_list[6]);
            }

            void set_local_terminal_station(const font_type& font, const color_type& color)
            {
                m_font_color_list[6] =
                    internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
            }

            font_color_type principal_terminal_station()
            const
            {
                return to_font_color(m_font_color_list[7]);
            }

            void set_principal_terminal_station(const font_type& font, const color_type& color)
            {
                m_font_color_list[7] =
                    internal_font_color_type(boost::make_optional(font), boost::make_optional(color));
            }

            const font_type& train_name()
            const
            {
                return to_font(m_font_color_list[8]);
            }

            void set_train_name(const font_type& font)
            {
                m_font_color_list[8] = internal_font_color_type(boost::make_optional(font), boost::none);
            }

            void do_modal_impl()
            {
                m_p_category_list_box->select_item(0);
                m_current_category_index = boost::make_optional<int_size_type>(0);
                update();
            }



        private:
            // types

            typedef typename boost::mpl::at<ui_type_list, type::ui::label>::type label_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::list_box>::type list_box_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::text_box>::type text_box_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::button>::type button_type;

            typedef typename boost::mpl::at<ui_type_list, type::ui::picture_box>::type picture_box_type;

            typedef
                typename boost::mpl::at<ui_type_list, type::ui::transparent_background>::type
                transparent_background_type;

            typedef
                typename message::font_color_dialog::type_list<
                    int_size_type,
                    base_type,
                    list_box_type,
                    typename boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                    typename boost::mpl::at<common_dialog_type_list, type::common_dialog::font>::type,
                    typename boost::mpl::at<common_dialog_type_list, type::common_dialog::color>::type,
                    message_catalog_type
                >::type
                font_color_dialog_message_type_list_type;

            typedef typename base_type::dimension_type dimension_type;

            typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

            typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

            typedef typename base_type::position_type position_type;

            typedef typename tetengo2::gui::position<position_type>::left_type left_type;

            typedef typename tetengo2::gui::position<position_type>::top_type top_type;

            typedef std::pair<boost::optional<font_type>, boost::optional<color_type>> internal_font_color_type;


            // static functions

            static const font_type& to_font(const internal_font_color_type& internal_font_color)
            {
                if (!internal_font_color.first)
                    BOOST_THROW_EXCEPTION(std::logic_error("The font has not been set."));

                return *internal_font_color.first;
            }

            static const color_type& to_color(const internal_font_color_type& internal_font_color)
            {
                if (!internal_font_color.second)
                    BOOST_THROW_EXCEPTION(std::logic_error("The color has not been set."));

                return *internal_font_color.second;
            }

            static font_color_type to_font_color(const internal_font_color_type& internal_font_color)
            {
                if (!internal_font_color.first || !internal_font_color.second)
                    BOOST_THROW_EXCEPTION(std::logic_error("The font and/or the color have not been set."));

                return font_color_type(*internal_font_color.first, *internal_font_color.second);
            }


            // variables

            base_type& m_base;

            const message_catalog_type& m_message_catalog;

            std::vector<internal_font_color_type> m_font_color_list;

            boost::optional<int_size_type> m_current_category_index;

            std::unique_ptr<label_type> m_p_category_label;

            std::unique_ptr<list_box_type> m_p_category_list_box;

            std::unique_ptr<button_type> m_p_font_button;

            std::unique_ptr<text_box_type> m_p_font_text_box;

            std::unique_ptr<button_type> m_p_color_button;

            std::unique_ptr<label_type> m_p_sample_label;

            std::unique_ptr<picture_box_type> m_p_sample_picture_box;

            std::unique_ptr<button_type> m_p_ok_button;

            std::unique_ptr<button_type> m_p_cancel_button;


            // functions

            void initialize_dialog(const abstract_window_type& parent)
            {
                m_base.set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Fonts And Colors")));

                m_p_category_label = create_category_label();
                m_p_category_list_box = create_category_list_box();
                m_p_font_button = create_font_button();
                m_p_font_text_box = create_font_text_box();
                m_p_color_button = create_color_button();
                m_p_sample_label = create_sample_label();
                m_p_sample_picture_box = create_sample_picture_box();
                m_p_ok_button = create_ok_button();
                m_p_cancel_button = create_cancel_button();

                locate_controls();

                insert_category_list_box_items();
            }

            std::unique_ptr<label_type> create_category_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:C&ategories:")));
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<list_box_type> create_category_list_box()
            {
                std::unique_ptr<list_box_type> p_list_box =
                    tetengo2::make_unique<list_box_type>(m_base, list_box_type::scroll_bar_style_type::vertical);

                p_list_box->list_box_observer_set().selection_changed().connect(
                    typename boost::mpl::at<
                        font_color_dialog_message_type_list_type,
                        message::font_color_dialog::type::category_list_box_selection_changed
                    >::type(m_current_category_index, *p_list_box, TETENGO2_CPP11_BIND(&impl::update, this))
                );

                return std::move(p_list_box);
            }

            std::unique_ptr<button_type> create_font_button()
            {
                std::unique_ptr<button_type> p_button =
                    tetengo2::make_unique<button_type>(m_base, button_type::style_type::normal);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Font...")));
                p_button->mouse_observer_set().clicked().connect(
                    typename boost::mpl::at<
                        font_color_dialog_message_type_list_type,
                        message::font_color_dialog::type::font_button_mouse_clicked
                    >::type(
                        m_base,
                        m_font_color_list,
                        m_current_category_index,
                        TETENGO2_CPP11_BIND(&impl::update, this),
                        m_message_catalog
                    )
                );

                return std::move(p_button);
            }

            std::unique_ptr<text_box_type> create_font_text_box()
            {
                std::unique_ptr<text_box_type> p_text_box =
                    tetengo2::make_unique<text_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

                p_text_box->set_read_only(true);

                return std::move(p_text_box);
            }

            std::unique_ptr<button_type> create_color_button()
            {
                std::unique_ptr<button_type> p_button =
                    tetengo2::make_unique<button_type>(m_base, button_type::style_type::normal);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Color...")));
                p_button->mouse_observer_set().clicked().connect(
                    typename boost::mpl::at<
                        font_color_dialog_message_type_list_type,
                        message::font_color_dialog::type::color_button_mouse_clicked
                    >::type(
                        m_base,
                        m_font_color_list,
                        m_current_category_index,
                        TETENGO2_CPP11_BIND(&impl::update, this),
                        m_message_catalog
                    )
                );

                return std::move(p_button);
            }

            std::unique_ptr<label_type> create_sample_label()
            {
                std::unique_ptr<label_type> p_label = tetengo2::make_unique<label_type>(m_base);

                p_label->set_text(m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:&Sample:")));
                std::unique_ptr<background_type> p_background(tetengo2::make_unique<transparent_background_type>());
                p_label->set_background(std::move(p_background));

                return std::move(p_label);
            }

            std::unique_ptr<picture_box_type> create_sample_picture_box()
            {
                std::unique_ptr<picture_box_type> p_picture_box =
                    tetengo2::make_unique<picture_box_type>(m_base, list_box_type::scroll_bar_style_type::none);

                p_picture_box->set_dimension(dimension_type(width_type(24), height_type(8)));
                p_picture_box->fast_paint_observer_set().paint().connect(
                    typename boost::mpl::at<
                        font_color_dialog_message_type_list_type,
                        message::font_color_dialog::type::sample_picture_box_paint
                    >::type(
                        m_font_color_list, m_current_category_index, p_picture_box->client_dimension(), m_message_catalog
                    )
                );

                return std::move(p_picture_box);
            }

            std::unique_ptr<button_type> create_ok_button()
            {
                std::unique_ptr<button_type> p_button =
                    tetengo2::make_unique<button_type>(m_base, button_type::style_type::default_);

                p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:OK")));
                p_button->mouse_observer_set().clicked().connect(
                    typename boost::mpl::at<
                        font_color_dialog_message_type_list_type,
                        message::font_color_dialog::type::ok_button_mouse_clicked
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
                        font_color_dialog_message_type_list_type,
                        message::font_color_dialog::type::cancel_button_mouse_clicked
                    >::type(m_base)
                );

                return std::move(p_button);
            }

            void locate_controls()
            {
                m_base.set_client_dimension(dimension_type(width_type(46), height_type(22)));

                const left_type category_label_left(2);

                m_p_category_label->fit_to_content();
                m_p_category_label->set_position(position_type(category_label_left, top_type(1)));

                m_p_category_list_box->set_dimension(dimension_type(width_type(16), height_type(16)));
                m_p_category_list_box->set_position(
                    position_type(
                        category_label_left,
                        tetengo2::gui::position<position_type>::top(m_p_category_label->position()) +
                            top_type::from(
                                tetengo2::gui::dimension<dimension_type>::height(m_p_category_label->dimension())
                            )
                    )
                );

                const left_type font_button_left(20);
            
                m_p_font_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_font_button->set_position(position_type(font_button_left, top_type(2)));

                m_p_font_text_box->set_dimension(dimension_type(width_type(16), height_type(2)));
                m_p_font_text_box->set_position(position_type(font_button_left + left_type(8), top_type(2)));

                m_p_color_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_color_button->set_position(position_type(font_button_left, top_type(5)));

                m_p_sample_label->fit_to_content();
                m_p_sample_label->set_position(position_type(font_button_left, top_type(8)));

                m_p_sample_picture_box->set_position(
                    position_type(
                        font_button_left,
                        tetengo2::gui::position<position_type>::top(m_p_sample_label->position()) +
                            top_type::from(
                                tetengo2::gui::dimension<dimension_type>::height(m_p_sample_label->dimension())
                            )
                    )
                );

                m_p_ok_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_ok_button->set_position(position_type(left_type(27), top_type(19)));

                m_p_cancel_button->set_dimension(dimension_type(width_type(8), height_type(2)));
                m_p_cancel_button->set_position(position_type(left_type(36), top_type(19)));
            }

            void insert_category_list_box_items()
            {
                m_p_category_list_box->insert_item(
                    m_p_category_list_box->item_count(),
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Background"))
                );
                m_p_category_list_box->insert_item(
                    m_p_category_list_box->item_count(),
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Company and Line Names"))
                );
                m_p_category_list_box->insert_item(
                    m_p_category_list_box->item_count(),
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Note"))
                );
                m_p_category_list_box->insert_item(
                    m_p_category_list_box->item_count(),
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Time Lines"))
                );
                m_p_category_list_box->insert_item(
                    m_p_category_list_box->item_count(),
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Local Stations"))
                );
                m_p_category_list_box->insert_item(
                    m_p_category_list_box->item_count(),
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Principal Stations"))
                );
                m_p_category_list_box->insert_item(
                    m_p_category_list_box->item_count(),
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Local Terminal Stations"))
                );
                m_p_category_list_box->insert_item(
                    m_p_category_list_box->item_count(),
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Principal Terminal Stations"))
                );
                m_p_category_list_box->insert_item(
                    m_p_category_list_box->item_count(),
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FontAndColor:Train Names"))
                );
            }

            void update()
            {
                const string_type font_name_and_size_ = font_name_and_size();
                m_p_font_text_box->set_text(font_name_and_size_);
                m_p_font_text_box->set_enabled(!font_name_and_size_.empty());
                m_p_font_button->set_enabled(!font_name_and_size_.empty());

                m_p_color_button->set_enabled(color_enabled());

                m_p_sample_picture_box->repaint();
            }

            string_type font_name_and_size()
            const
            {
                if (!m_current_category_index)
                    return string_type();

                const boost::optional<font_type>& font = m_font_color_list[*m_current_category_index].first;
                if (!font)
                    return string_type();

                std::basic_ostringstream<typename string_type::value_type> stream;
                stream <<
                    boost::basic_format<typename string_type::value_type>(string_type(TETENGO2_TEXT("%s, %dpt"))) %
                    font->family() %
                    boost::rational_cast<int>(point_size_type::from_pixels(font->size()).value());

                return stream.str();
            }

            bool color_enabled()
            {
                return m_current_category_index && m_font_color_list[*m_current_category_index].second;
            }


        };


    }


    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_color_dialog(
        abstract_window_type&       parent,
        const message_catalog_type& message_catalog
    )
    :
    base_type(parent),
    m_p_impl(tetengo2::make_unique<impl>(*this, parent, message_catalog))
    {}

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::~font_color_dialog()
    TETENGO2_CPP11_NOEXCEPT
    {}

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    const typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::color_type&
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::background()
    const
    {
        return m_p_impl->background();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::set_background(const color_type& color)
    {
        m_p_impl->set_background(color);
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_color_type
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::company_line_name()
    const
    {
        return m_p_impl->company_line_name();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::set_company_line_name(
        const font_type&  font,
        const color_type& color
    )
    {
        m_p_impl->set_company_line_name(font, color);
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_color_type
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::note()
    const
    {
        return m_p_impl->note();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::set_note(
        const font_type&  font,
        const color_type& color
    )
    {
        m_p_impl->set_note(font, color);
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_color_type
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::time_line()
    const
    {
        return m_p_impl->time_line();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::set_time_line(
        const font_type&  font,
        const color_type& color
    )
    {
        m_p_impl->set_time_line(font, color);
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_color_type
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::local_station()
    const
    {
        return m_p_impl->local_station();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::set_local_station(
        const font_type&  font,
        const color_type& color
    )
    {
        m_p_impl->set_local_station(font, color);
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_color_type
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::principal_station()
    const
    {
        return m_p_impl->principal_station();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::set_principal_station(
        const font_type&  font,
        const color_type& color
    )
    {
        m_p_impl->set_principal_station(font, color);
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_color_type
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::local_terminal_station()
    const
    {
        return m_p_impl->local_terminal_station();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::set_local_terminal_station(
        const font_type&  font,
        const color_type& color
    )
    {
        m_p_impl->set_local_terminal_station(font, color);
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_color_type
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::principal_terminal_station()
    const
    {
        return m_p_impl->principal_terminal_station();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::set_principal_terminal_station(
        const font_type&  font,
        const color_type& color
    )
    {
        m_p_impl->set_principal_terminal_station(font, color);
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    const typename font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::font_type&
    font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::train_name()
    const
    {
        return m_p_impl->train_name();
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::set_train_name(const font_type& font)
    {
        m_p_impl->set_train_name(font);
    }

    template <
        typename Dialog,
        typename MessageCatalog,
        typename IntSize,
        typename Font,
        typename PointSize,
        typename Color
    >
    void font_color_dialog<Dialog, MessageCatalog, IntSize, Font, PointSize, Color>::do_modal_impl()
    {
        m_p_impl->do_modal_impl();
    }


    template class font_color_dialog<
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
        typename boost::mpl::at<common_type_list, type::size>::type,
        typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
        typename boost::mpl::at<ui_type_list, type::ui::point_unit_size>::type,
        typename boost::mpl::at<ui_type_list, type::ui::color>::type
    >;


}
