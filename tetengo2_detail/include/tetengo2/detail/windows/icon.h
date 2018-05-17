/*! \file
    \brief The definition of tetengo2::detail::windows::icon.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ICON_H)
#define TETENGO2_DETAIL_WINDOWS_ICON_H

#include <cassert>
#include <ios> // IWYU pragma: keep
#include <memory> // IWYU pragma: keep
#include <type_traits> // IWYU pragma: keep
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/base/icon.h>
#include <tetengo2/gui/measure.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of an icon.
    */
    class icon : public base::icon
    {
    public:
        // types

        //! The dimension type.
        using dimension_type = base::icon::dimension_type;

        //! The icon details type.
        using icon_details_type = base::icon::icon_details_type;

#if !defined(DOCUMENTATION)
        struct icon_deleter_type
        {
            void operator()(const ::HICON handle) const
            {
                if (handle)
                    ::DestroyIcon(handle);
            }
        };

        using icon_handle_type = std::unique_ptr<typename std::remove_pointer<::HICON>::type, icon_deleter_type>;
#endif

        //! The icon details type.
        struct icon_details_impl_type : public base::icon::icon_details_type
        {
#if !defined(DOCUMENTATION)
            const icon_handle_type big_icon_handle;
            const icon_handle_type small_icon_handle;

            icon_details_impl_type(icon_handle_type big_icon_handle_, icon_handle_type small_icon_handle_)
            : big_icon_handle{ std::move(big_icon_handle_) }, small_icon_handle{ std::move(small_icon_handle_) }
            {
                assert(big_icon_handle);
                assert(small_icon_handle);
            }

            virtual ~icon_details_impl_type() {}
#endif
        };

        //! The icon details pointer type.
        using icon_details_ptr_type = base::icon::icon_details_ptr_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const icon& instance();


        // constructors and destructor

        /*!
            \brief Destroys the instance.
        */
        virtual ~icon();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        icon();


        // virtual functions

        virtual dimension_type default_dimension_impl() const override;

        virtual icon_details_ptr_type
        create_impl(const tetengo2::stdalt::filesystem::path& path, const dimension_type& dimension) const override;
    };
}


#endif
