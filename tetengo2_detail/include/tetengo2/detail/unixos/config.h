/*! \file
    \brief The definition of tetengo2::detail::unixos::config.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_UNIXOS_CONFIG_H)
#define TETENGO2_DETAIL_UNIXOS_CONFIG_H

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <ios>
#include <iterator>
#include <map>
#include <ostream>
#include <stack>
#include <string>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/push_parser.h>
#include <tetengo2/text/grammar/json.h>


namespace tetengo2 { namespace detail { namespace unixos
{
    /*!
        \brief The class for a detail implementation of a configuration.
    */
    class config : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = std::string;


        // static functions

        /*!
            \brief Returns the configuration value.

            \tparam String  A string type.
            \tparam UInt    An unsigned integer type.
            \tparam Encoder An encoder type.

            \param group_name A group name.
            \param key        A key.
            \param encoder    An encoder.

            \return The value.
        */
        template <typename String, typename UInt, typename Encoder>
        static boost::optional<boost::variant<String, UInt>> get(
            const String&  group_name,
            const String&  key,
            const Encoder& encoder
        )
        {
            values<String, UInt> values_{};
            load_from_file(group_name, values_, encoder);

            const auto found = values_.find(key);
            return found != values_.end() ? boost::make_optional(found->second) : boost::none;
        }

        /*!
            \brief Sets a configuration value.

            \tparam String  A string type.
            \tparam UInt    An unsigned integer type.
            \tparam Encoder An encoder type.

            \param group_name A group_name.
            \param key        A key.
            \param value      A value.
            \param encoder    An encoder.
        */
        template <typename String, typename UInt, typename Encoder>
        static void set(
            const String&                group_name,
            const String&                key,
            boost::variant<String, UInt> value,
            const Encoder&               encoder
        )
        {
            values<String, UInt> values_{};
            load_from_file(group_name, values_, encoder);

            values_[key] = std::move(value);

            save_to_file(group_name, values_, encoder);
        }

        /*!
            \brief Clears the configuration.

            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param group_name A group_name.
            \param encoder    An encoder.
        */
        template <typename String, typename Encoder>
        static void clear(const String& group_name, const Encoder& encoder)
        {
            const auto setting_file_path = make_setting_file_path(group_name, encoder);
            if (!boost::filesystem::exists(setting_file_path))
                return;
            if (!boost::filesystem::remove(setting_file_path))
                BOOST_THROW_EXCEPTION(std::ios_base::failure("Can't remove the setting file."));
        }


    private:
        // types

        template <typename String, typename UInt>
        using values = std::map<String, boost::variant<String, UInt>>;

        using input_stream_iterator_type = std::istreambuf_iterator<char>;

        using multi_pass_stream_iterator_type = boost::spirit::multi_pass<input_stream_iterator_type>;

        using json_type = text::grammar::json<multi_pass_stream_iterator_type>;

        using parser_type = text::push_parser<multi_pass_stream_iterator_type, json_type, std::size_t, double>;

        using attribute_map_type = parser_type::attribute_map_type;

        using parser_value_type = parser_type::value_type;


        // static functions

        template <typename String, typename Encoder>
        static boost::filesystem::path make_setting_file_path(const String& group_name, const Encoder& encoder)
        {
#if BOOST_OS_WINDOWS
            const boost::filesystem::path base{ "D:\\temp" };
#else
            const auto* const p_home_directory = std::getenv("HOME");
            const boost::filesystem::path base{ p_home_directory ? p_home_directory : "" };
#endif
            return base / encoder.decode(String(TETENGO2_TEXT(".")) + group_name);
        }

        template <typename String, typename UInt, typename Encoder>
        static void load_from_file(const String& group_name, values<String, UInt>& values_, const Encoder& encoder)
        {
            const auto setting_file_path = make_setting_file_path(group_name, encoder);
            boost::filesystem::ifstream stream{ setting_file_path };
            if (!stream)
                return;

            auto p_grammer = stdalt::make_unique<json_type>();
            parser_type parser(
                boost::spirit::make_default_multi_pass(input_stream_iterator_type{ stream }),
                boost::spirit::make_default_multi_pass(input_stream_iterator_type{}),
                std::move(p_grammer)
            );

            std::stack<std::pair<string_type, string_type>> structure_stack{};
            parser.on_structure_begin().connect(
                [&structure_stack](const string_type& name, const attribute_map_type& attributes)
                {
                    if (name != "object" && name != "member")
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                    if (name == "object" && !structure_stack.empty())
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                    if (name == "member" && structure_stack.top().first != "object")
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));

                    structure_stack.push({ name, get_key(attributes) });
                }
            );
            parser.on_structure_end().connect(
                [&structure_stack](const string_type& name, const attribute_map_type&)
                {
                    if (structure_stack.top().first != name)
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                    structure_stack.pop();
                }
            );
            parser.on_value().connect(
                [&structure_stack, &values_, &encoder](const parser_value_type& value)
                {
                    if (structure_stack.top().first != "member")
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                    if      (value.which() == 2)
                    {
                        values_[encoder.decode(structure_stack.top().second)] = boost::get<std::size_t>(value);
                    }
                    else if (value.which() == 4)
                    {
                        values_[encoder.decode(structure_stack.top().second)] =
                            encoder.decode(boost::get<string_type>(value));
                    }
                    else
                    {
                        BOOST_THROW_EXCEPTION(std::ios_base::failure("Wrong setting file format."));
                    }
                }
            );

            parser.parse();
        }

        static string_type get_key(const attribute_map_type& attributes)
        {
            const auto found = attributes.find("name");
            if (found == attributes.end())
                return {};

            assert(found->second.which() == 4);
            return boost::get<string_type>(found->second);
        }

        template <typename String, typename UInt, typename Encoder>
        static void save_to_file(const String& group_name, const values<String, UInt>& values_, const Encoder& encoder)
        {
            const auto setting_file_path = make_setting_file_path(group_name, encoder);
            boost::filesystem::ofstream stream{ setting_file_path };
            if (!stream)
                return;

            stream << "{\n";

            bool first_time = true;
            for (const auto& value : values_)
            {
                if (!first_time)
                    stream << ",\n";

                stream << "    \"" << encoder.encode(boost::get<String>(value.first)) << "\": ";
                if (value.second.which() == 0)
                {
                    stream << "\"" << encoder.encode(boost::get<String>(value.second)) << "\"";
                }
                else
                {
                    assert(value.second.which() == 1);
                    stream << boost::get<UInt>(value.second);
                }

                first_time = false;
            }
            stream << "\n}\n";

            stream << std::flush;
        }


    };


}}}


#endif
