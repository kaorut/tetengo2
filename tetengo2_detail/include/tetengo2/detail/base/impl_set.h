/*! \file
    \brief The definition of tetengo2::detail::base::impl_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_IMPLSET_H)
#define TETENGO2_DETAIL_BASE_IMPLSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace detail { namespace base
{
    class alert;
    class cursor;
    class gui_fixture;


    /*!
        The class for a detail implementation set.
    */
    class impl_set : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the detail implementation set.
        */
        virtual ~impl_set();


        // functions

        /*!
            \brief Returns the detail implementation of alert.

            \return The detail implementation.
        */
        const alert& alert_()
        const;

        /*!
            \brief Returns the detail implementation of alert.

            \return The detail implementation.
        */
        const cursor& cursor_()
        const;

        /*!
            \brief Creates a detail implementation of GUI fixture.

            \return A unique pointer to a detail implementation.
        */
        std::unique_ptr<gui_fixture> create_gui_fixture()
        const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation set.
        */
        impl_set();


    private:
        // virtual functions

        virtual const alert& alert_impl()
        const = 0;

        virtual const cursor& cursor_impl()
        const = 0;

        virtual std::unique_ptr<gui_fixture> create_gui_fixture_impl()
        const = 0;


    };


}}}


#endif
