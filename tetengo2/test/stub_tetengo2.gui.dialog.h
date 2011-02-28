/*! \file
    \brief The definition of stub_tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DIALOG_H)
#define STUBTETENGO2_GUI_DIALOG_H

#include "stub_tetengo2.gui.abstract_window.h"
#include "tetengo2.cpp0x.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class dialog : public abstract_window<typename Traits::base_type>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef abstract_window<typename traits_type::base_type> base_type;

        typedef typename traits_type::message_loop_type message_loop_type;

        typedef
            typename traits_type::message_loop_break_type
            message_loop_break_type;

        enum result_type
        {
            result_undecided,
            result_accepted,
            result_canceled,
        };


        // constructors and destructor

        explicit dialog(base_type& parent)
        :
        base_type()
        {}

        virtual ~dialog()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        void set_result(const result_type result)
        {}

        result_type result()
        const
        {
            return result_undecided;
        }

        result_type do_modal()
        {
            return result_canceled;
        }


    private:
        // virtual functions

        virtual typename dialog::handle_type handle_impl()
        const
        {
            return 0;
        }


    };


}}


#endif
