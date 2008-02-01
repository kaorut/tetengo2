/*! \file
    \brief The definition of stub_tetengo2::gui::canvas.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_CANVAS_H)
#define STUBTETENGO2_GUI_CANVAS_H

#include <utility>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "tetengo2.StringConcept.h"
#include "tetengo2.gui.HandleConcept.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Handle,
        typename Size,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename WindowHandle
    >
    class canvas : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Handle, tetengo2::gui, HandleConcept);
        BOOST_CLASS_REQUIRE(Size, boost, IntegerConcept);
        BOOST_CLASS_REQUIRE(String, tetengo2, StringConcept);
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CLASS_REQUIRE3(
                encode_to_native_type,
                native_string_type,
                String,
                boost,
                UnaryFunctionConcept
            );
        };
        BOOST_CLASS_REQUIRE(WindowHandle, tetengo2::gui, HandleConcept);


    public:
        // types

        typedef Handle handle_type;

        typedef Size size_type;

        typedef std::pair<size_type, size_type> point_type;

        typedef std::pair<point_type, point_type> rectangle_type;

        typedef String string_type;

        typedef Encode<String, String> encode_to_native_type;

        typedef WindowHandle window_handle_type;


        // constructors and destructor

        canvas(const window_handle_type window_handle)
        {}

        ~canvas()
        throw ()
        {}


        // functions

        handle_type handle()
        const
        {
            return 0;
        }

        void draw_text(const string_type& text, const point_type& point)
        {}


    };


}}

#endif
