/*! \file
    \brief The definition of tetengo2::gui::widget::link_label.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LINKLABEL_H)
#define TETENGO2_GUI_WIDGET_LINKLABEL_H

#include <memory>

#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a link label.
    */
    class link_label : public label
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a link label.

            \param parent A parent widget.
        */
        explicit link_label(widget& parent);

        /*!
            \brief Destroys the link label.
        */
        virtual ~link_label();


        // functions

        /*!
            \brief Returns the target.

            \return The target.
        */
        const string_type& target() const;

        /*!
            \brief Sets a target.

            \param target a target.
        */
        void set_target(string_type target);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
