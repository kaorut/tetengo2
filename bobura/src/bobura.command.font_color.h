/*! \file
    \brief The definition of bobura::command::font_color.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FONTCOLOR_H)
#define BOBURA_COMMAND_FONTCOLOR_H

//#include <memory>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a font and color command.
    */
    class font_color : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;


        // constructors and destructor

        /*!
            \brief Create a font and color command.
        */
        font_color();

        /*!
            \brief Destroys a font and color command.
        */
        ~font_color();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const;


    };


}}


#endif
