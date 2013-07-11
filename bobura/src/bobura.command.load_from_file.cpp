/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <tetengo2.stdalt.h>

#include "bobura.command.load_from_file.h"


namespace bobura { namespace command
{
    class load_from_file::impl
    {
    public:
        // types

        typedef load_from_file::model_type model_type;

        typedef load_from_file::abstract_window_type abstract_window_type;

        typedef load_from_file::load_from_file_type load_from_file_type;


        // constructors and destructor

        explicit impl(const load_from_file_type& load_from_file)
        :
        m_load_from_file(load_from_file)
        {}


        // functions

        bool enabled(const model_type& model)
        const
        {
            return m_load_from_file.reloadable(model);
        }

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            m_load_from_file(model, parent);
        }


    private:
        // variables

        const load_from_file_type& m_load_from_file;


    };


    load_from_file::load_from_file(const load_from_file_type& load_from_file)
    :
    m_p_impl(tetengo2::make_unique<impl>(load_from_file))
    {}

    load_from_file::~load_from_file()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    bool load_from_file::enabled_impl(const model_type& model)
    const
    {
        return m_p_impl->enabled(model);
    }

    void load_from_file::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
