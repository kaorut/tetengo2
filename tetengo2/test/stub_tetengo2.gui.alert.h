/*! \file
    \brief The definition of stub_tetengo2::gui::alert.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ALERT_H)
#define STUBTETENGO2_GUI_ALERT_H

#include <cstddef>
#include <exception>
#include <functional>
#include <stdexcept>
#include <string>

#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Handle.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename WindowHandle,
        template <typename Target, typename Source> class Encode
    >
    class alert :
        public std::unary_function<std::exception, void>
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<WindowHandle>));
        struct concept_check_Encode
        {
            typedef std::wstring task_dialog_string_type;
            typedef std::string exception_what_type;
            typedef
                Encode<task_dialog_string_type, exception_what_type>
                encode_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_type, task_dialog_string_type, exception_what_type
                >
            ));
        };


    public:
        // types

        typedef WindowHandle window_handle_type;


        // constructors

        alert(const window_handle_type window_handle = NULL)
        throw ()
        {}


        // functions

        void operator()(
            const std::exception& exception =
                std::runtime_error("Unknown Error!")
        )
        const
        throw ()
        {}


    };


}}

#endif
