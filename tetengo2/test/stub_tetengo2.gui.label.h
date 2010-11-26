/*! \file
    \brief The definition of stub_tetengo2::gui::label.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_LABEL_H)
#define STUBTETENGO2_GUI_LABEL_H

#include "stub_tetengo2.gui.widget.h"
#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class label : public widget<typename Traits::base_type>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef widget<typename traits_type::base_type> base_type;


        // constructors and destructor

        explicit label(base_type& parent)
        :
        base_type()
        {}

        virtual ~label()
        TETENGO2_NOEXCEPT
        {}


    private:
        // virtual functions

        virtual typename label::handle_type handle_impl()
        const
        {
            return 0;
        }


    };


}}

#endif
