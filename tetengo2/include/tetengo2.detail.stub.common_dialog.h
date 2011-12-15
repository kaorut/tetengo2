/*! \file
    \brief The definition of tetengo2::detail::stub::common_dialog.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_COMMONDIALOG_H)
#define TETENGO2_DETAIL_STUB_COMMONDIALOG_H


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class template for a detail implementation of a file open
                   dialog box.
        
        \tparam Widget  A widget type.
        \tparam String  A string type.
        \tparam Path    A path type.
        \tparam Encoder An encoder type.
    */
    template <
        typename Widget,
        typename String,
        typename Path,
        typename Encoder
    >
    class file_open
    {
    public:
        // types

        //! The widget type.
        typedef Widget widget_type;

        //! The string type.
        typedef String string_type;

        //! The path type.
        typedef Path path_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a file open dialog box.

            \param parent A parent widget.
        */
        file_open(widget_type& parent)
        :
        m_parent(parent),
        m_path()
        {}


        // functions

        /*!
            \brief Returns the result.
        */
        const path_type& result()
        const
        {
            return m_result;
        }

        /*!
            \brief Shows the dialog box as modal.
        */
        void do_modal()
        {}


    private:
        // variables

        widget_type& m_parent;

        path_type m_path;


    };


}}}


#endif
