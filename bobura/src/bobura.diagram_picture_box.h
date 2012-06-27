/*! \file
    \brief The definition of bobura::diagram_picture_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMPICTUREBOX_H)
#define BOBURA_DIAGRAMPICTUREBOX_H

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the diagram picture box.

        \tparam DiagramPictureBox     A picture box type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename DiagramPictureBox, typename AbstractWindow>
    class diagram_picture_box : public DiagramPictureBox
    {
    public:
        // types

        //! The base type.
        typedef DiagramPictureBox base_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram picture box.

            \param parent A parent.
        */
        explicit diagram_picture_box(abstract_window_type& parent)
        :
        base_type(parent, base_type::scroll_bar_style_both)
        {}

        /*!
            \brief Destroys the diagram picture box.
        */
        virtual ~diagram_picture_box()
        {}


        // functions


    private:


    };


}

#endif
