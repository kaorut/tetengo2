/*! \file
    \brief The definition of tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TABFRAME_H)
#define TETENGO2_GUI_WIDGET_TABFRAME_H

#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui { namespace widget {
    class control;
}}}


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a tab frame.
    */
    class tab_frame : public custom_control
    {
    public:
        // types

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        //! The tab label type.
        class tab_label_type : public inner_item
        {
        public:
            // constructors and destructor

            /*!
                \brief Creates a tab label.

                \param parent A parent.
                \param index  A tab index.
                */
            tab_label_type(tab_frame& parent, size_type index);

            /*!
                \brief Destroys the tab body.
            */
            virtual ~tab_label_type();


            // functions

            /*!
                \brief Returns the index.

                \return The index.
            */
            size_type index() const;

            /*!
                \brief Sets a tab index.

                \param index A tab index.
            */
            void set_index(size_type index);

            /*!
                \brief Returns the title.

                \return The title.
            */
            const string_type& title() const;

            /*!
                \brief Sets a title.

                \param title A title.
            */
            void set_title(string_type title);


        private:
            // types

            class impl;


            // variables

            const std::unique_ptr<impl> m_p_impl;


            // virtual functions

            virtual void resized_impl() override;

            virtual void paint_impl(canvas_type& canvas) const override;

            virtual void mouse_released_impl(const position_type& cursor_position) override;
        };

        //! The tab body type.
        class tab_body_type : public inner_item
        {
        public:
            // constructors and destructor

            /*!
                \brief Creates a tab body.

                \param parent   A parent.
                \param control_ A control.
            */
            tab_body_type(tab_frame& parent, control& control_);

            /*!
                \brief Destroys the tab body.
            */
            virtual ~tab_body_type();


            // functions

            /*!
                \brief Returns the control.

                \tparam Control A concrete control type.

                \return The control.
            */
            template <typename Control>
            const Control& get() const
            {
                assert(dynamic_cast<const Control*>(&get_impl()));
                return dynamic_cast<const Control&>(get_impl());
            }

            /*!
                \brief Returns the control.

                \tparam Control A concrete control type.

                \return The control.
            */
            template <typename Control>
            Control& get()
            {
                assert(dynamic_cast<Control*>(&get_impl()));
                return dynamic_cast<Control&>(get_impl());
            }


        private:
            // types

            class impl;


            // variables

            const std::unique_ptr<impl> m_p_impl;


            // virtual functions

            virtual void resized_impl() override;


            // functions

            const control& get_impl() const;

            control& get_impl();
        };

        //! The tab type.
        class tab_type : private boost::noncopyable
        {
        public:
            // constructors and destructor

            /*!
                \brief Creates a tab.

                \param parent  A parent.
                \param index   A tab index.
                \param control_ A control.
            */
            tab_type(tab_frame& parent, size_type index, control& control_);


            // functions

            /*!
                \brief Returns the label.

                \return The label.
            */
            const tab_label_type& label() const;

            /*!
                \brief Returns the label.

                \return The label.
            */
            tab_label_type& label();

            /*!
                \brief Returns the body.

                \return The body.
            */
            const tab_body_type& body() const;

            /*!
                \brief Returns the body.

                \return The body.
            */
            tab_body_type& body();

            /*!
                \brief Returns the index.

                \return The index.
            */
            size_type index() const;

            /*!
                \brief Sets a tab index.

                \param index A tab index.
            */
            void set_index(size_type index);

            /*!
                \brief Returns the selected status.

                \return The selected status.
            */
            bool selected() const;

            /*!
                \brief Selects this tab.
            */
            void select();

            /*!
                \brief Unselects this tab.
            */
            void unselect();


        private:
            // types

            class impl;


            // variables

            const std::unique_ptr<impl> m_p_impl;
        };


        // constructors and destructor

        /*!
            \brief Creates a tab frame.

            \param parent A parent widget.
        */
        explicit tab_frame(widget& parent);

        /*!
            \brief Destroys the tab frame.
        */
        virtual ~tab_frame();


        // functions

        /*!
            \brief Returns the tab count.

            \return The tab count.
        */
        size_type tab_count() const;

        /*!
            \brief Returns the tab at the specified index.

            \param index An index.

            \return The tab at the speficied position.

            \throw std::out_of_range When the index is out of the range.
        */
        const tab_type& tab_at(size_type index) const;

        /*!
            \brief Returns the tab at the specified index.

            \param index An index.

            \return The tab at the speficied position.

            \throw std::out_of_range When the index is out of the range.
        */
        tab_type& tab_at(size_type index);

        /*!
            \brief Returns the selected tab index.

            \return The selected tab index.

            \throw std::logic_error When no tab is selected.
        */
        size_type selected_tab_index() const;

        /*!
            \brief Selects a tab.

            \param index A tab index.

            \throw std::out_of_range When the index is out of the range.
        */
        void select_tab(size_type index);

        /*!
            \brief Moves a tab.

            \param from An origin index.
            \param to   A destination index.

            \throw std::out_of_range When from and/or to are out of the range.
        */
        void move_tab(size_type from, size_type to);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
