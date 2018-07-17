/*! \file
    \brief The definition of tetengo2::detail::base::gui_impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_GUIIMPLSET_H)
#define TETENGO2_DETAIL_BASE_GUIIMPLSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>


namespace tetengo2::detail {
    namespace base {
        class alert;
        class cursor;
        class gui_fixture;
        class icon;
        class shell;
        class system_color;
        class unit;
        class virtual_key;
        class widget;


        /*!
            The class for a detail implementation set of GUI.
        */
        class gui_impl_set : private boost::noncopyable
        {
        public:
            // constructors and destructor

            /*!
                \brief Destroys the detail implementation set.
            */
            virtual ~gui_impl_set();


            // functions

            /*!
                \brief Returns the detail implementation of alert.

                \return The detail implementation.
            */
            const alert& alert_() const;

            /*!
                \brief Returns the detail implementation of alert.

                \return The detail implementation.
            */
            const cursor& cursor_() const;

            /*!
                \brief Creates a detail implementation of GUI fixture.

                \return A unique pointer to a detail implementation.
            */
            std::unique_ptr<gui_fixture> create_gui_fixture() const;

            /*!
                \brief Returns the detail implementation of icon.

                \return The detail implementation.
            */
            const icon& icon_() const;

            /*!
                \brief Returns the detail implementation of shell.

                \return The detail implementation.
            */
            const shell& shell_() const;

            /*!
                \brief Returns the detail implementation of system color.

                \return The detail implementation.
            */
            const system_color& system_color_() const;

            /*!
                \brief Returns the detail implementation of unit.

                \return The detail implementation.
            */
            const unit& unit_() const;

            /*!
                \brief Returns the detail implementation of virtual key.

                \return The detail implementation.
            */
            const virtual_key& virtual_key_() const;

            /*!
                \brief Returns the detail implementation of widget.

                \return The detail implementation.
            */
            const widget& widget_() const;


        protected:
            // constructors

            /*!
                \brief Creates a detail implementation set.
            */
            gui_impl_set();


        private:
            // virtual functions

            virtual const alert& alert_impl() const = 0;

            virtual const cursor& cursor_impl() const = 0;

            virtual std::unique_ptr<gui_fixture> create_gui_fixture_impl() const = 0;

            virtual const icon& icon_impl() const = 0;

            virtual const shell& shell_impl() const = 0;

            virtual const system_color& system_color_impl() const = 0;

            virtual const unit& unit_impl() const = 0;

            virtual const virtual_key& virtual_key_impl() const = 0;

            virtual const widget& widget_impl() const = 0;
        };
    }


    /*!
        \brief Returns the detail implementation set of GUI.

        \return The detail implementation set.

        \throw std::logic_error When no implementation set is set yet.
    */
    const base::gui_impl_set& gui_detail_impl_set();

    /*!
        \brief Sets a detail implementation set of GUI.

        \param impl_set_ A detail implementation set.
    */
    void set_gui_detail_impl_set(const base::gui_impl_set& impl_set_);
}


#endif
