/*! \file
    \brief The definition of tetengo2::gui::widget::window.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WINDOW_H)
#define TETENGO2_GUI_WIDGET_WINDOW_H

#include <cassert>

#include <boost/predef.h>

#include <tetengo2/gui/widget/abstract_window.h>


namespace tetengo2 { namespace gui { namespace widget {
    /*!
        \brief The class template for a window.

        \tparam Traits        A traits type.
        \tparam DetailsTraits A detail implementation type traits.
        \tparam MenuDetails   A detail implementation type of a menu.
    */
    template <typename Traits, typename DetailsTraits, typename MenuDetails>
    class window : public abstract_window<Traits, DetailsTraits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The widget details type.
        using widget_details_type = typename details_traits_type::widget_details_type;

        //! The details type.
        using details_type = typename widget_details_type::widget_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = typename widget_details_type::widget_details_ptr_type;

        //! The message handler details type.
        using message_handler_details_type = typename details_traits_type::message_handler_details_type;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The base type.
        using base_type = abstract_window<traits_type, details_traits_type, menu_details_type>;

        //! The scroll bar style type.
        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;


        // constructors and destructor

        /*!
            \brief Creates a top level window.

            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.
        */
        explicit window(
            const scroll_bar_style_type scroll_bar_style = base_type::scroll_bar_style_type::none,
            const bool                  file_droppable = false)
        : base_type{ scroll_bar_style, file_droppable, message_handler_map_type{} }, m_p_details{
              widget_details_type::template create_window<typename base_type::base_type>(
                  nullptr,
                  scroll_bar_style,
                  file_droppable)
          }
        {
            initialize_window();
        }

        /*!
            \brief Creates a owned window.

            \param parent           A parent window.
            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.
        */
        window(base_type& parent, const scroll_bar_style_type scroll_bar_style, const bool file_droppable)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          base_type{ scroll_bar_style,
                     file_droppable,
                     message_handler_details_type::make_window_message_handler_map(*this, message_handler_map_type{}) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
          m_p_details{ widget_details_type::template create_window<typename base_type::base_type>(
              &parent,
              scroll_bar_style,
              file_droppable) }
        {
            initialize_window();

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the window.
        */
        virtual ~window() noexcept
        {
            try
            {
                if (this->has_parent())
                    this->parent().child_observer_set().destroying()(*this);
            }
            catch (...)
            {
            }
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        const details_ptr_type m_p_details;


        // virtual functions

        virtual const details_type& details_impl() const override
        {
            assert(m_p_details);
            return *m_p_details;
        }

        virtual details_type& details_impl() override
        {
            assert(m_p_details);
            return *m_p_details;
        }


        // functions

        void initialize_window()
        {
            base_type::initialize(this);
        }
    };


}}}


#endif
