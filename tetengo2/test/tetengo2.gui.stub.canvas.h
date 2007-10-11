/*! \file
    \brief The definition of tetengo2::gui::stub::canvas.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_STUB_CANVAS_H)
#define TETENGO2_GUI_STUB_CANVAS_H

#include <utility>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "tetengo2.StringConcept.h"
#include "tetengo2.gui.HandleConcept.h"


namespace tetengo2 { namespace gui { namespace stub
{
    /*!
        \brief The class template for a canvas for testing.

        \param Handle       A handle type for the native interface. It must
                            conform to tetengo2::gui::HandleConcept<Handle>.
        \param Size         A size type. It must conform to
                            boost::IntegerConcept<Size>.
        \param String       A string type. It must conform to
                            tetengo2::StringConcept<String>.
        \param Encode       An encoding unary functor type. The type
                            Encode<std::wstring, String> must conform to
                            boost::UnaryFunctionConcept<Encode, std::wstring, String>.
        \param WindowHandle A window handle type for the native interface. It
                            must conform to
                            tetengo2::gui::HandleConcept<WindowHandle>.
    */
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

        //! The handle type for the native interface.
        typedef Handle handle_type;

        //! The size type.
        typedef Size size_type;

        //! The point type.
        typedef std::pair<size_type, size_type> point_type;

        //! The rectangle type.
        typedef std::pair<point_type, point_type> rectangle_type;

        //! The string type.
        typedef String string_type;

        //! The unary functor type for encoding to the native.
        typedef Encode<String, String> encode_to_native_type;

        //! The window handle type for the native interface.
        typedef WindowHandle window_handle_type;


        // constructors and destructor

        /*!
            \brief Creates a canvas.

            \param window_handle A window handle.
        */
        canvas(const window_handle_type window_handle)
        {}

        /*!
            \brief Destroys the canvas.
        */
        ~canvas()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the handle.

            \return The handle. Always 0.
        */
        handle_type handle()
        const
        {
            return 0;
        }

        /*!
            \brief Draws a text.

            Does nothing actually.

            \param text  A text to draw.
            \param point A point where the text is drawn.
        */
        void draw_text(const string_type& text, const point_type& point)
        {}


    };


}}}

#endif
