/*! \file
    \brief The definition of tetengo2::gui::common_dialog::font.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_FONT_H)
#define TETENGO2_GUI_COMMONDIALOG_FONT_H

#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include "tetengo2.text.h"


namespace tetengo2 { namespace gui { namespace common_dialog
{
    /*!
        \brief The class template for a font dialog.

        \tparam AbstractWindow      An abstract window type.
        \tparam String              A string type.
        \tparam Font                A font type.
        \tparam Encoder             An encoder type.
        \tparam CommonDialogDetails A detail implementation type of common dialogs.
    */
    template <typename AbstractWindow, typename String, typename Font, typename Encoder, typename CommonDialogDetails>
    class font : private boost::noncopyable
    {
    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The string type.
        typedef String string_type;

        //! The font type.
        typedef Font font_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The detail implementation type of common dialogs.
        typedef CommonDialogDetails common_dialog_details_type;

        //! The detail implementation type.
        typedef typename common_dialog_details_type::font_dialog_details_type details_type;

        //! The detail implementaiton pointer type;
        typedef typename common_dialog_details_type::font_dialog_details_ptr_type details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a font dialog.

            \tparam S  A string type.

            \param title  A title.
            \param font   A font.
            \param parent A parent widget.
        */
        template <typename S>
        font(S&& title, const boost::optional<font_type>& font, abstract_window_type& parent)
        :
        m_p_details(common_dialog_details_type::create_font_dialog(parent, std::forward<S>(title), encoder())),
        m_result(font ? *font : font_type::dialog_font())
        {}


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const font_type& result()
        const
        {
            return m_result;
        }

        /*!
            \brief Shows the dialog as model.

            \retval true  When the OK button is pressed.
            \retval false Otherwise.
        */
        bool do_modal()
        {
            const boost::optional<font_type> result =
                common_dialog_details_type::template show_font_dialog<font_type>(*m_p_details, encoder());
            if (!result)
                return false;

            m_result = *result;
            return true;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
        {
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            return *m_p_details;
        }


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        details_ptr_type m_p_details;

        font_type m_result;


    };


}}}


#endif
