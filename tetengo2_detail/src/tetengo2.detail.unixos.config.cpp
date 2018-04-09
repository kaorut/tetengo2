/*! \file
    \brief The definition of tetengo2::detail::unixos::config.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/none.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits.hpp>
#include <boost/variant.hpp>

#include <tetengo2/detail/unixos/config.h>
#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/text/grammar/json.h>
#include <tetengo2/text/push_parser.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace detail { namespace unixos {
    class config::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = config::string_type;

        using uint_type = config::uint_type;

        using value_type = config::value_type;


        // constructors and destructor

        impl() {}


        // functions

        virtual boost::optional<value_type> get_impl(const string_type& group_name, const string_type& key) const
        {
            value_map_type value_map{};
            load_from_file(group_name, value_map);

            const auto found = value_map.find(key);
            return found != value_map.end() ? boost::make_optional(found->second) : boost::none;
        }

        virtual void set_impl(const string_type& group_name, const string_type& key, value_type value) const
        {
            value_map_type value_map{};
            load_from_file(group_name, value_map);

            value_map[key] = std::move(value);

            save_to_file(group_name, value_map);
        }

        virtual void clear_impl(const string_type& group_name) const
        {
            const auto setting_file_path = make_setting_file_path(group_name);
            if (tetengo2::stdalt::filesystem::exists(setting_file_path))
                tetengo2::stdalt::filesystem::remove(setting_file_path);
        }


    private:
        // types

        using native_string_type = std::string;

        using encoder_type =
            text::encoder<text::encoding::locale<string_type>, text::encoding::locale<native_string_type>>;

        using value_map_type = std::map<string_type, value_type>;

        using input_stream_iterator_type =
            tetengo2::iterator::observable_forward_iterator<boost::spirit::multi_pass<std::istreambuf_iterator<char>>>;

        using json_type = text::grammar::json<input_stream_iterator_type>;

        using parser_type = text::push_parser<input_stream_iterator_type>;

        using attribute_map_type = parser_type::attribute_map_type;

        using parser_value_type = parser_type::value_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{ encoder_type::internal_encoding_type{},
                                                 encoder_type::external_encoding_type{} };
            return singleton;
        }

        static tetengo2::stdalt::filesystem::path make_setting_file_path(const string_type& group_name)
        {
            const auto* const                        p_home_directory = std::getenv("HOME");
            const tetengo2::stdalt::filesystem::path base{ p_home_directory ? p_home_directory : "" };
            return base / encoder().encode(string_type(TETENGO2_TEXT(".")) + group_name);
        }

        static void load_from_file(const string_type& group_name, value_map_type& value_map)
        {
            const auto    setting_file_path = make_setting_file_path(group_name);
            std::ifstream stream{ setting_file_path };
            if (!stream)
                return;

            const auto first = tetengo2::iterator::make_observable_forward_iterator(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ stream }));
            const auto last = tetengo2::iterator::make_observable_forward_iterator(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
            auto        p_grammer = std::make_unique<json_type>();
            parser_type parser(first, last, std::move(p_grammer));

            std::stack<std::pair<native_string_type, native_string_type>> structure_stack{};
            parser.on_structure_begin().connect(
                [&structure_stack](const native_string_type& name, const attribute_map_type& attributes) {
                    if (name != "object" && name != "member")
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                    if (name == "object" && !structure_stack.empty())
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                    if (name == "member" && structure_stack.top().first != "object")
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));

                    structure_stack.push({ name, get_key(attributes) });

                    return true;
                });
            parser.on_structure_end().connect(
                [&structure_stack](const native_string_type& name, const attribute_map_type&) {
                    if (structure_stack.top().first != name)
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                    structure_stack.pop();

                    return true;
                });
            parser.on_value().connect([&structure_stack, &value_map](const parser_value_type& value) {
                if (structure_stack.top().first != "member")
                    BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                if (value.which() == 2)
                {
                    value_map[encoder().decode(structure_stack.top().second)] =
                        boost::get<type_list::integer_type>(value);
                }
                else if (value.which() == 4)
                {
                    value_map[encoder().decode(structure_stack.top().second)] =
                        encoder().decode(boost::get<native_string_type>(value));
                }
                else
                {
                    BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                }

                return true;
            });

            parser.parse();
        }

        static native_string_type get_key(const attribute_map_type& attributes)
        {
            const auto found = attributes.find("name");
            if (found == attributes.end())
                return {};

            assert(found->second.which() == 4);
            return boost::get<native_string_type>(found->second);
        }

        static void save_to_file(const string_type& group_name, const value_map_type& value_map)
        {
            const auto    setting_file_path = make_setting_file_path(group_name);
            std::ofstream stream{ setting_file_path };
            if (!stream)
                return;

            stream << "{\n";

            bool first_time = true;
            for (const auto& value : value_map)
            {
                if (!first_time)
                    stream << ",\n";

                stream << "    \"" << encoder().encode(boost::get<string_type>(value.first)) << "\": ";
                if (value.second.which() == 0)
                {
                    stream << "\"" << encoder().encode(boost::get<string_type>(value.second)) << "\"";
                }
                else
                {
                    assert(value.second.which() == 1);
                    stream << boost::get<uint_type>(value.second);
                }

                first_time = false;
            }
            if (!first_time)
                stream << "\n";
            stream << "}\n";

            stream << std::flush;
        }
    };


    const config& config::instance()
    {
        static const config singleton{};
        return singleton;
    }

    config::~config() = default;

    config::config() : m_p_impl{ std::make_unique<impl>() } {}


    // virtual functions

    boost::optional<config::value_type> config::get_impl(const string_type& group_name, const string_type& key) const
    {
        return m_p_impl->get_impl(group_name, key);
    }

    void config::set_impl(const string_type& group_name, const string_type& key, value_type value) const
    {
        m_p_impl->set_impl(group_name, key, std::move(value));
    }

    void config::clear_impl(const string_type& group_name) const
    {
        m_p_impl->clear_impl(group_name);
    }


}}}
