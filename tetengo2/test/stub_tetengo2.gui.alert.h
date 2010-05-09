/*! \file
    \brief The definition of stub_tetengo2::gui::alert.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ALERT_H)
#define STUBTETENGO2_GUI_ALERT_H //!< !! Include Guard !!

#include <cstddef>
#include <exception>
#include <functional>
#include <stdexcept>

//#include <boost/concept_check.hpp>
#include <boost/exception/all.hpp>

#include "concept_tetengo2.Encoder.h"
#include "concept_tetengo2.gui.Handle.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename WindowHandle,
        typename UiEncoder,
        typename ExceptionEncoder
    >
    class alert :
        public std::unary_function<std::exception, void>
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<WindowHandle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::Encoder<UiEncoder>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::Encoder<ExceptionEncoder>));


    public:
        // types

        typedef WindowHandle window_handle_type;

        typedef UiEncoder ui_encoder_type;

        typedef ExceptionEncoder exception_encoder_type;


        // constructors

        alert(const window_handle_type window_handle = NULL)
        throw ()
        {}


        // functions

        void operator()(const boost::exception& exception)
        const
        throw ()
        {}

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
