/*! \file
    \brief The definition of bobura::command::save_to_file.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include "bobura.command.save_to_file.h"


namespace bobura { namespace command
{
    class save_to_file::impl
    {
    public:
        // types

        typedef save_to_file::model_type model_type;

        typedef save_to_file::abstract_window_type abstract_window_type;

        typedef save_to_file::save_to_file_type save_to_file_type;


        // constructors and destructor

        explicit impl(const save_to_file_type& save_to_file)
        :
        m_save_to_file(save_to_file)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            m_save_to_file(model, parent);
        }


    private:
        // variables

        const save_to_file_type& m_save_to_file;


    };


    save_to_file::save_to_file(const save_to_file_type& save_to_file)
    :
    m_p_impl(tetengo2::make_unique<impl>(save_to_file))
    {}

    save_to_file::~save_to_file()
    {}
    
    void save_to_file::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
