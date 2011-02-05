/*! \file
    \brief The definition of stub_tetengo2::gui::window.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_WINDOW_H)
#define STUBTETENGO2_GUI_WINDOW_H

#include "stub_tetengo2.gui.abstract_window.h"
#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class window : public abstract_window<typename Traits::base_type>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef abstract_window<typename traits_type::base_type> base_type;


        // constructors and destructor

        window()
        :
        base_type()
        {}

        explicit window(const base_type& parent)
        :
        base_type()
        {}

        virtual ~window()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    private:
        // virtual functions

        virtual typename window::handle_type handle_impl()
        const
        {
            return 0;
        }


    };


}}

#endif
