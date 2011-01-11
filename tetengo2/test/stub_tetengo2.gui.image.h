/*! \file
    \brief The definition of stub_tetengo2::gui::image.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_IMAGE_H)
#define STUBTETENGO2_GUI_IMAGE_H

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


        // constructors and destructor

        explicit image(widget_type& parent)
        :
        base_type()
        {}

        virtual ~image()
        TETENGO2_NOEXCEPT
        {}


    };


}}

#endif
