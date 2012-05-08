/*! \file
    \brief The definition of bobura::message::diagram_picture_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H)
#define BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H

//#include <cstddef>
#include <memory>
//#include <type_traits>
//#include <utility>

#include <tetengo2.gui.measure.h>


namespace bobura { namespace message { namespace diagram_picture_box
{
    /*!
        \brief The class template for a paint observer of the picture box.

        \tparam Canvas        A canvas type.
        \tparam Position      A position type.
        \tparam PictureReader A picture reader type.
    */
    template <typename Canvas, typename Position, typename PictureReader>
    class paint_paint
    {
    public:
        // types

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The position type.
        typedef Position position_type;

        //! The picture reader type.
        typedef PictureReader picture_reader_type;

        //! The path type.
        typedef typename picture_reader_type::path_type path_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer of the picture box.

            \tparam P A path type.

            \param image_directory_path An image directory path.
        */
        template <typename P>
        explicit paint_paint(
            P&& image_directory_path,
            typename std::enable_if<std::is_convertible<P, path_type>::value>::type* = NULL
        )
        :
        m_image_directory_path(std::forward<P>(image_directory_path))
        {}


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas)
        const
        {
            picture_reader_type reader(
                m_image_directory_path / typename path_type::string_type(TETENGO2_TEXT("kumakuma.jpg"))
            );
            const std::unique_ptr<typename canvas_type::picture_type> p_pic2(reader.read());
            canvas.paint_picture(*p_pic2, position_type(left_type(0), top_type(0)));

            const font_type& dialog_font = font_type::dialog_font();
            canvas.draw_text(dialog_font.family(), position_type(left_type(2), top_type(2)));

            canvas.set_font(font_type(string_type(TETENGO2_TEXT("Times New Roman")), 64, false, true, true, false));
            canvas.draw_text(string_type(TETENGO2_TEXT("Hello, world")), position_type(left_type(4), top_type(4)));
        }


    private:
        // types

        typedef typename canvas_type::string_type string_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename canvas_type::font_type font_type;


        // variables

        path_type m_image_directory_path;


    };


}}}


#endif