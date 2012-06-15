/*! \file
    \brief The definition of bobura::command::new_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_NEWFILE_H)
#define BOBURA_COMMAND_NEWFILE_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for a new-file command.

        \tparam Model           A model type.
        \tparam AbstractWindow  An abstract window type.
        \tparam NewFile         A file initialization type.
    */
    template <typename Model, typename AbstractWindow, typename NewFile>
    class new_file
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The file initialization type.
        typedef NewFile new_file_type;


        // constructors and destructor

        /*!
            \brief Creates a new-file command.

            \param new_file A file initialization type.
        */
        explicit new_file(const new_file_type& new_file)
        :
        m_new_file(new_file)
        {}


        // functions

        /*!
            \brief Returns the enabled status.

            \retval true  When the command is enabled.
            \retval false Otherwise.
        */
        bool enabled()
        const
        {
            return true;
        }

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void operator()(model_type& model, abstract_window_type& parent)
        const
        {
            m_new_file(model, parent);
        }


    private:
        // variables

        const new_file_type& m_new_file;


    };


}}


#endif
