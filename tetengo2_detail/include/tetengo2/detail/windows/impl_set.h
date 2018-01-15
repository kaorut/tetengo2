/*! \file
    \brief The definition of tetengo2::detail::windows::impl_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_IMPLSET_H)
#define TETENGO2_DETAIL_WINDOWS_IMPLSET_H

#include <memory>

#include <tetengo2/detail/base/impl_set.h>

namespace tetengo2 { namespace detail { namespace base
{
    class alert;
    class cursor;
    class gui_fixture;
    class unit;
}}}


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        The class for a detail implementation set.
    */
    class impl_set : public base::impl_set
    {
    public:
        // static functions

        /*!
            \brief Returns the instance of the detail implementation set.

            \return The instance.
        */
        static const impl_set& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation set.
        */
        virtual ~impl_set();


    private:
        // constructors

        impl_set();


        // virtual functions

        virtual const base::alert& alert_impl()
        const override;

        virtual const base::cursor& cursor_impl()
        const override;

        virtual std::unique_ptr<base::gui_fixture> create_gui_fixture_impl()
        const override;

        virtual const base::unit& unit_impl()
        const override;


    };


}}}


#endif