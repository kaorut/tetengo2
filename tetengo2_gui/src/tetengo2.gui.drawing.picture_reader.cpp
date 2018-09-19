/*! \file
    \brief The definition of tetengo2::gui::drawing::picture_reader.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/drawing/picture.h> // IWYU pragma: keep
#include <tetengo2/gui/drawing/picture_reader.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::drawing {
    class picture_reader::impl : private boost::noncopyable
    {
    public:
        // types

        using drawing_details_type = picture_reader::drawing_details_type;

        using picture_type = picture_reader::picture_type;


        // constructors and destructor

        impl(const drawing_details_type& drawing_details, tetengo2::stdalt::filesystem::path path)
        : m_drawing_details{ drawing_details }, m_path{ std::move(path) }
        {}

        explicit impl(tetengo2::stdalt::filesystem::path path)
        : m_drawing_details{ detail::gui_detail_impl_set().drawing_() }, m_path{ std::move(path) }
        {}


        // functions

        std::unique_ptr<picture_type> read()
        {
            picture_details_ptr_type p_picture{ m_drawing_details.read_picture(m_path) };
            return std::make_unique<picture_type>(m_drawing_details, std::move(p_picture));
        }

        const drawing_details_type& drawing_details() const
        {
            return m_drawing_details;
        }


    private:
        // types

        using picture_details_ptr_type = drawing_details_type::picture_details_ptr_type;


        // variables

        const drawing_details_type& m_drawing_details;

        const tetengo2::stdalt::filesystem::path m_path;
    };


    picture_reader::picture_reader(const drawing_details_type& drawing_details, tetengo2::stdalt::filesystem::path path)
    : m_p_impl{ std::make_unique<impl>(drawing_details, std::move(path)) }
    {}

    picture_reader::picture_reader(tetengo2::stdalt::filesystem::path path)
    : m_p_impl{ std::make_unique<impl>(std::move(path)) }
    {}

    picture_reader::~picture_reader() = default;

    std::unique_ptr<picture_reader::picture_type> picture_reader::read()
    {
        return m_p_impl->read();
    }

    const picture_reader::drawing_details_type& picture_reader::drawing_details() const
    {
        return m_p_impl->drawing_details();
    }
}
