/*! \file
    \brief The definition of tetengo2::detail::windows::impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GUIIMPLSET_H)
#define TETENGO2_DETAIL_WINDOWS_GUIIMPLSET_H

#include <memory>

#include <tetengo2/detail/base/gui_impl_set.h>

namespace tetengo2::detail::base {
    class alert;
    class cursor;
    class gui_fixture;
    class icon;
    class shell;
    class system_color;
    class unit;
}


namespace tetengo2::detail::windows {
    /*!
        The class for a detail implementation set.
    */
    class gui_impl_set : public base::gui_impl_set
    {
    public:
        // static functions

        /*!
            \brief Returns the instance of the detail implementation set.

            \return The instance.
        */
        static const gui_impl_set& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation set.
        */
        virtual ~gui_impl_set();


    private:
        // constructors

        gui_impl_set();


        // virtual functions

        virtual const base::alert& alert_impl() const override;

        virtual const base::cursor& cursor_impl() const override;

        virtual std::unique_ptr<base::gui_fixture> create_gui_fixture_impl() const override;

        virtual const base::icon& icon_impl() const override;

        virtual const base::shell& shell_impl() const override;

        virtual const base::system_color& system_color_impl() const override;

        virtual const base::unit& unit_impl() const override;
    };
}


#endif
