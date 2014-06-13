/*! \file
    \brief The definition of tetengo2::detail::unixos::config.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_UNIXOS_CONFIG_H)
#define TETENGO2_DETAIL_UNIXOS_CONFIG_H

#include <cstdlib>
#include <string>
#include <unordered_map>

#include <boost/filesystem.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/variant.hpp>

#include <tetengo2/text.h>
#include <tetengo2/utility.h>


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
            suppress_unused_variable_warning(group_name, key, encoder);

            return boost::none;
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
            const values<String, UInt> values_{ { key, std::move(value) } };
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
            suppress_unused_variable_warning(group_name, encoder);
        }


    private:
        // types

        template <typename String, typename UInt>
        using values = std::unordered_map<String, boost::variant<String, UInt>>;


        // static functions

        template <typename String>
        static boost::filesystem::path make_setting_file_path(const String& group_name)
        {
#if BOOST_OS_WINDOWS
            const boost::filesystem::path base{ "F:\\temp" };
#else
            const auto* const p_home_directory = std::getenv("HOME");
            const boost::filesystem::path base{ p_home_directory ? p_home_directory : "" };
#endif
            return base / (String(TETENGO2_TEXT(".")) + group_name);
        }

        template <typename String, typename UInt, typename Encoder>
        static void save_to_file(const String& group_name, const values<String, UInt>& values_, const Encoder& encoder)
        {
            const auto setting_file_path = make_setting_file_path(group_name);
            boost::filesystem::ofstream stream{ setting_file_path };

            stream << "{\n";

            bool first_time = true;
            for (const auto& value : values_)
            {
                if (!first_time)
                    stream << "\n";

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
