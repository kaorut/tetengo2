/*! \file
    \brief The definition of bobura::command::train_kind.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <algorithm>
//#include <cassert>
//#include <iterator>
//#include <utility>
//#include <vector>

//#include <boost/optional.hpp>

#include <tetengo2.cpp11.h>

#include "bobura.command.train_kind.h"


namespace bobura { namespace command
{
    class train_kind::impl
    {
    public:
        // types

        typedef train_kind::model_type model_type;

        typedef train_kind::abstract_window_type abstract_window_type;

        typedef train_kind::train_kind_dialog_type train_kind_dialog_type;

        typedef train_kind::dialog_base_type dialog_base_type;

        typedef train_kind::string_type string_type;

        typedef train_kind::message_catalog_type message_catalog_type;


        // constructors and destructor

        explicit impl(const message_catalog_type& message_catalog)
        :
        m_message_catalog(message_catalog)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            const font_color_set_type& font_color_set = model.timetable().font_color_set();
            train_kind_dialog_type dialog(
                parent, m_message_catalog, font_color_set.train_name(), font_color_set.background()
            );

            std::vector<info_set_type> info_sets = to_info_sets(model.timetable());
            dialog.set_info_sets(std::move(info_sets));

            dialog.do_modal();
            if (dialog.result() != dialog_base_type::result_type::accepted)
                return;
        
            model.timetable().assign_train_kinds(
                to_train_kinds(dialog.info_sets()),
                to_train_kind_index_map(dialog.info_sets(), model.timetable().train_kinds().size())
            );
        }


    private:
        // types

        typedef train_kind_dialog_type::int_size_type int_size_type;

        typedef train_kind_dialog_type::info_set_type info_set_type;

        typedef model_type::timetable_type timetable_type;

        typedef timetable_type::train_kinds_type train_kinds_type;

        typedef timetable_type::train_kind_index_type train_kind_index_type;

        typedef timetable_type::train_kind_type train_kind_type;

        typedef timetable_type::font_color_set_type font_color_set_type;


        // static functions

        static std::vector<info_set_type> to_info_sets(const timetable_type& timetable)
        {
            std::vector<info_set_type> info_sets;
            info_sets.reserve(timetable.train_kinds().size());

            for (
                train_kinds_type::const_iterator i = timetable.train_kinds().begin();
                i != timetable.train_kinds().end();
                ++i
            )
            {
                const int_size_type index = std::distance(timetable.train_kinds().begin(), i);
                info_sets.emplace_back(boost::make_optional(index), timetable.train_kind_referred(i), *i);
            }

            return info_sets;
        }

        static train_kinds_type to_train_kinds(const std::vector<info_set_type>& info_sets)
        {
            train_kinds_type train_kinds;
            train_kinds.reserve(info_sets.size());

            std::transform(info_sets.begin(), info_sets.end(), std::back_inserter(train_kinds), call_train_kind);

            return train_kinds;
        }

        static const train_kind_type& call_train_kind(const info_set_type& info_set)
        {
            return info_set.train_kind();
        }

        static std::vector<train_kind_index_type> to_train_kind_index_map(
            const std::vector<info_set_type>& info_sets,
            const train_kind_index_type       original_train_kind_count
        )
        {
            std::vector<train_kind_index_type> map(original_train_kind_count, 0);

            for (train_kind_index_type i = 0; i < info_sets.size(); ++i)
            {
                if (!info_sets[i].original_index())
                    continue;

                assert(*info_sets[i].original_index() < original_train_kind_count);
                map[*info_sets[i].original_index()] = i;
            }

            return map;
        }


        // variables

        const message_catalog_type& m_message_catalog;


    };


    train_kind::train_kind(const message_catalog_type& message_catalog)
    :
    m_p_impl(tetengo2::make_unique<impl>(message_catalog))
    {}

    train_kind::~train_kind()
    TETENGO2_CPP11_NOEXCEPT
    {}
    
    void train_kind::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
