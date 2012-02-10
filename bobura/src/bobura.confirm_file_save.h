/*! \file
    \brief The definition of bobura::confirm_file_save.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_CONFIRMFILESAVE_H)
#define BOBURA_CONFIRMFILESAVE_H


namespace bobura
{
    /*!
        \brief The class template for the file save confirmation.

        \tparam Model A model type.
    */
    template <typename Model>
    class confirm_file_save
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;


        // constructors and destructor

        /*!
            \brief Creates a file save confirmation.

            \param model A model
        */
        confirm_file_save(const model_type& model)
        :
        m_model(model)
        {}


        // functions

        /*!
            \brief Confirms file save, and if necessary, save the model.

            \retval true  When the model is saved or there is no need to save
                          it.
            \retval false Otherwise.
        */
        bool operator()()
        {
            return false;
        }


    private:
        // variables

        const model_type& m_model;


    };


}

#endif
