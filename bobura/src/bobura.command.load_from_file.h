/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for a load-from-file command.

        \tparam Model           A model type.
        \tparam AbstractWindow  An abstract window type.
        \tparam LoadFromFile    A file loading type.
    */
    template <typename Model, typename AbstractWindow, typename LoadFromFile>
    class load_from_file
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The file loading type.
        typedef LoadFromFile load_from_file_type;


        // constructors and destructor

        /*!
            \brief Creates a load-from-file command.

            \param load_from_file A file loading.
        */
        explicit load_from_file(const load_from_file_type& load_from_file)
        :
        m_load_from_file(load_from_file)
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
            m_load_from_file(model, parent);
        }


    private:
        // variables

        const load_from_file_type& m_load_from_file;


    };


}}


#endif
