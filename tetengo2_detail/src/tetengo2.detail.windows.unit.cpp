/*! \file
    \brief The definition of tetengo2::detail::windows::unit.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <system_error> // IWYU pragma: keep
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/preprocessor.hpp>
#include <boost/rational.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/font.h>
#include <tetengo2/detail/windows/unit.h>


namespace tetengo2::detail::windows {
    class unit::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = unit::size_type;

        using difference_type = unit::difference_type;


        // static functions

        static const unit& instance()
        {
            static const unit singleton;
            return singleton;
        }


        // functions

        boost::rational<size_type> pixel_size_to_em_impl(const size_type pixel_size) const
        {
            const auto& message_font = get_message_font();
            return boost::rational<size_type>{ pixel_size, static_cast<size_type>(-message_font.lfHeight) };
        }

        boost::rational<difference_type> pixel_difference_to_em_impl(const difference_type pixel_difference) const
        {
            const auto& message_font = get_message_font();
            return boost::rational<difference_type>{ pixel_difference,
                                                     static_cast<difference_type>(-message_font.lfHeight) };
        }

        boost::rational<size_type> pixel_size_to_point_impl(const size_type pixel_size) const
        {
            return boost::rational<size_type>{ pixel_size * 72, dpi().second };
        }

        boost::rational<difference_type> pixel_difference_to_point_impl(const difference_type pixel_difference) const
        {
            return boost::rational<difference_type>{ pixel_difference * 72, dpi().second };
        }

        size_type em_size_to_pixel_impl(const boost::rational<size_type>& em_size) const
        {
            const auto& message_font = get_message_font();
            return boost::rational_cast<size_type>(em_size * boost::rational<size_type>{ -message_font.lfHeight });
        }

        difference_type em_difference_to_pixel_impl(const boost::rational<difference_type>& em_difference) const
        {
            const auto& message_font = get_message_font();
            return boost::rational_cast<difference_type>(
                em_difference * boost::rational<difference_type>{ -message_font.lfHeight });
        }

        size_type point_size_to_pixel_impl(const boost::rational<size_type>& point_size) const
        {
            return boost::rational_cast<size_type>(
                point_size * boost::rational<size_type>{ dpi().second } / boost::rational<size_type>{ 72 });
        }

        difference_type point_difference_to_pixel_impl(const boost::rational<difference_type>& point_difference) const
        {
            return boost::rational_cast<difference_type>(
                point_difference * boost::rational<difference_type>{ dpi().second } /
                boost::rational<difference_type>{ 72 });
        }


    private:
        // static functions

        static const std::pair<int, int>& dpi()
        {
            static const auto singleton = get_dpi();
            return singleton;
        }

        static std::pair<int, int> get_dpi()
        {
            const auto device_context = ::GetDC(nullptr);
            if (!device_context)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get the desktop device context." }));
            }
            BOOST_SCOPE_EXIT((device_context))
            {
                ::ReleaseDC(nullptr, device_context);
            }
            BOOST_SCOPE_EXIT_END;

            const auto dpi_x = ::GetDeviceCaps(device_context, LOGPIXELSX);
            assert(dpi_x != 0);
            const auto dpi_y = ::GetDeviceCaps(device_context, LOGPIXELSY);
            assert(dpi_y != 0);
            return std::make_pair(dpi_x, dpi_y);
        }
    };


    const unit& unit::instance()
    {
        return impl::instance();
    }

    unit::~unit() = default;

    unit::unit() : m_p_impl{ std::make_unique<impl>() } {}

    boost::rational<unit::size_type> unit::pixel_size_to_em_impl(const size_type pixel_size) const
    {
        return m_p_impl->pixel_size_to_em_impl(pixel_size);
    }

    boost::rational<unit::difference_type>
    unit::pixel_difference_to_em_impl(const difference_type pixel_difference) const
    {
        return m_p_impl->pixel_difference_to_em_impl(pixel_difference);
    }

    boost::rational<unit::size_type> unit::pixel_size_to_point_impl(const size_type pixel_size) const
    {
        return m_p_impl->pixel_size_to_point_impl(pixel_size);
    }

    boost::rational<unit::difference_type>
    unit::pixel_difference_to_point_impl(const difference_type pixel_difference) const
    {
        return m_p_impl->pixel_difference_to_point_impl(pixel_difference);
    }

    unit::size_type unit::em_size_to_pixel_impl(const boost::rational<size_type>& em_size) const
    {
        return m_p_impl->em_size_to_pixel_impl(em_size);
    }

    unit::difference_type unit::em_difference_to_pixel_impl(const boost::rational<difference_type>& em_difference) const
    {
        return m_p_impl->em_difference_to_pixel_impl(em_difference);
    }

    unit::size_type unit::point_size_to_pixel_impl(const boost::rational<size_type>& point_size) const
    {
        return m_p_impl->point_size_to_pixel_impl(point_size);
    }

    unit::difference_type
    unit::point_difference_to_pixel_impl(const boost::rational<difference_type>& point_difference) const
    {
        return m_p_impl->point_difference_to_pixel_impl(point_difference);
    }
}
