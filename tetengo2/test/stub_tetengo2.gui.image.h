/*! \file
    \brief The definition of stub_tetengo2::gui::image.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_IMAGE_H)
#define STUBTETENGO2_GUI_IMAGE_H

//#include <boost/scoped_ptr.hpp>

#include "stub_tetengo2.gui.control.h"
#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class image : public control<typename Traits::base_type>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef control<typename traits_type::base_type> base_type;

        typedef typename base_type::base_type widget_type;

        typedef typename traits_type::picture_type picture_type;


        // constructors and destructor

        template <typename PictureReader>
        image(widget_type& parent, PictureReader& picture_reader)
        :
        base_type(),
        m_p_picture(picture_reader.read())
        {}

        virtual ~image()
        TETENGO2_NOEXCEPT
        {}


        // functions

        void fit_to_content()
        {}


    private:
        // variables

        const boost::scoped_ptr<picture_type> m_p_picture;


    };


}}

#endif
