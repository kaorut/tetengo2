/*! \file
    \brief The definition of bobura::model::serializer::oudia_reader.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_OUDIAREADER_H)
#define BOBURA_MODEL_SERIALIZER_OUDIAREADER_H

#include <algorithm>
//#include <cstddef>
#include <ios>
//#include <iterator>
//#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
//#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for an OuDia reader.

        \tparam ForwardIterator     A forward iterator type.
        \tparam Timetable           A timetable type.
        \tparam StationGradeTypeSet A station grade type set type.
        \tparam DiagramSelector     A diagram selector type.
        \tparam Encoder             An encoder type.
    */
    template <
        typename ForwardIterator,
        typename Timetable,
        typename StationGradeTypeSet,
        typename DiagramSelector,
        typename Encoder
    >
    class oudia_reader : public reader<ForwardIterator, Timetable>
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The base type.
        typedef reader<iterator, timetable_type> base_type;

        //! The error type.
        typedef typename base_type::error_type error_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The diagram selector type.
        typedef DiagramSelector diagram_selector_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates a WinDIA reader.

            \param p_diagram_selector A unique pointer to a diagram selector.

            \throw std::invalid_argument When p_diagram_selector is NULL.
        */
        explicit oudia_reader(std::unique_ptr<diagram_selector_type> p_diagram_selector)
        :
        base_type(),
        m_p_diagram_selector(std::move(p_diagram_selector))
        {
            if (!m_p_diagram_selector)
                BOOST_THROW_EXCEPTION(std::invalid_argument("Diagram selector is NULL."));
        }

        /*!
            \brief Destroys the oudia_reader.
        */
        virtual ~oudia_reader()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename iterator::value_type input_char_type;

        typedef std::basic_string<input_char_type> input_string_type;

        typedef typename timetable_type::string_type string_type;

        typedef typename string_type::value_type char_type;

        typedef typename timetable_type::station_location_type station_location_type;

        typedef typename station_location_type::station_type station_type;

        typedef typename station_type::grade_type station_grade_type;

        typedef typename station_location_type::meterage_type meterage_type;

        typedef typename timetable_type::train_kind_type train_kind_type;

        typedef typename train_kind_type::color_type color_type;

        struct is_splitter
        {
            char_type m_splitter;

            explicit is_splitter(const char_type splitter)
            :
            m_splitter(splitter)
            {}

            bool operator()(const char_type character)
            const
            {
                return character == m_splitter;
            }

        };

        struct file_type
        {
            string_type m_name;
            int         m_major_version;
            int         m_minor_version;

            file_type(string_type name, int major_version, int minor_version)
            :
            m_name(std::move(name)),
            m_major_version(major_version),
            m_minor_version(minor_version)
            {}

        };

        class state
        {
        public:
            virtual ~state()
            {}

            bool parse(const string_type& line)
            {
                std::pair<string_type, string_type> key_value = parse_line(line);
                if (key_value.first.empty())
                    return false;

                return parse_impl(key_value.first, std::move(key_value.second));
            }

            void entered()
            {
                entered_impl();
            }

            void leaving()
            {
                leaving_impl();
            }

        private:
            virtual bool parse_impl(const string_type& key, string_type value)
            = 0;

            virtual void entered_impl()
            = 0;

            virtual void leaving_impl()
            = 0;

        };

        class unknown_state : public state
        {
        public:
            virtual ~unknown_state()
            {}

        private:
            virtual bool parse_impl(const string_type& key, string_type value)
            {
                return true;
            }

            virtual void entered_impl()
            {}

            virtual void leaving_impl()
            {}

        };

        class initial_state : public state
        {
        public:
            explicit initial_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~initial_state()
            {}

        private:
            timetable_type& m_timetable;

            virtual bool parse_impl(const string_type& key, string_type value)
            {
                if (key == string_type(TETENGO2_TEXT("Comment")))
                    m_timetable.set_note(std::move(value));

                return true;
            }

            virtual void entered_impl()
            {}

            virtual void leaving_impl()
            {}

        };

        class rosen_state : public state
        {
        public:
            explicit rosen_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~rosen_state()
            {}

        private:
            timetable_type& m_timetable;

            virtual bool parse_impl(const string_type& key, string_type value)
            {
                if (key == string_type(TETENGO2_TEXT("Rosenmei")))
                    m_timetable.set_line_name(std::move(value));

                return true;
            }

            virtual void entered_impl()
            {}

            virtual void leaving_impl()
            {}

        };

        class eki_state : public state
        {
        public:
            explicit eki_state(timetable_type& timetable)
            :
            m_timetable(timetable),
            m_ekimei(),
            m_ekijikokukeisiki(),
            m_ekikibo()
            {}

            virtual ~eki_state()
            {}

        private:
            static const station_grade_type& to_station_grade(
                const string_type& ekijikokukeisiki,
                const string_type& ekikibo
            )
            {
                const bool both_arrival_and_departure =
                    ekijikokukeisiki == string_type(TETENGO2_TEXT("Jikokukeisiki_Hatsuchaku"));
                const bool principal = ekikibo == string_type(TETENGO2_TEXT("Ekikibo_Syuyou"));

                if (both_arrival_and_departure)
                {
                    if (principal)
                        return station_grade_type_set_type::principal_terminal_type::instance();
                    else
                        return station_grade_type_set_type::local_terminal_type::instance();
                }
                else
                {
                    if (principal)
                        return station_grade_type_set_type::principal_type::instance();
                    else
                        return station_grade_type_set_type::local_type::instance();
                }
            }

            static bool shows_down_arrival_times(const string_type& ekijikokukeisiki)
            {
                return ekijikokukeisiki == string_type(TETENGO2_TEXT("Jikokukeisiki_KudariChaku"));
            }

            static bool shows_up_arrival_times(const string_type& ekijikokukeisiki)
            {
                return ekijikokukeisiki == string_type(TETENGO2_TEXT("Jikokukeisiki_NoboriChaku"));
            }

            timetable_type& m_timetable;

            string_type m_ekimei;

            string_type m_ekijikokukeisiki;

            string_type m_ekikibo;

            virtual bool parse_impl(const string_type& key, string_type value)
            {
                if (key == string_type(TETENGO2_TEXT("Ekimei")))
                    m_ekimei = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("Ekijikokukeisiki")))
                    m_ekijikokukeisiki = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("Ekikibo")))
                    m_ekikibo = std::move(value);

                return true;
            }

            virtual void entered_impl()
            {}

            virtual void leaving_impl()
            {
                m_timetable.insert_station_location(
                    m_timetable.station_locations().end(),
                    station_location_type(
                        station_type(
                            std::move(m_ekimei),
                            to_station_grade(m_ekijikokukeisiki, m_ekikibo),
                            shows_down_arrival_times(m_ekijikokukeisiki),
                            shows_up_arrival_times(m_ekijikokukeisiki)
                        ),
                        m_timetable.station_locations().empty() ?
                            0 : m_timetable.station_locations().back().meterage() + 1
                    )
                );
            }

        };

        class ressyasyubetsu_state : public state
        {
        public:
            explicit ressyasyubetsu_state(timetable_type& timetable)
            :
            m_timetable(timetable),
            m_syubetsumei(),
            m_ryakusyou(),
            m_diagram_sen_color(),
            m_diagram_sen_style(),
            m_diagram_sen_is_bold()
            {}

            virtual ~ressyasyubetsu_state()
            {}

        private:
            typedef typename train_kind_type::weight_type weight_type;

            typedef typename train_kind_type::line_style_type line_style_type;

            static typename weight_type::enum_t to_weight(const string_type& weight_string)
            {
                if (weight_string == string_type(TETENGO2_TEXT("1")))
                    return weight_type::bold;
                else
                    return weight_type::normal;
            }

            static typename line_style_type::enum_t to_line_style(const string_type& line_style_string)
            {
                if      (line_style_string == string_type(TETENGO2_TEXT("SenStyle_Hasen")))
                    return line_style_type::dashed;
                else if (line_style_string == string_type(TETENGO2_TEXT("SenStyle_Tensen")))
                    return line_style_type::dotted;
                else if (line_style_string == string_type(TETENGO2_TEXT("SenStyle_Ittensasen")))
                    return line_style_type::dot_dashed;
                else
                    return line_style_type::solid;
            }

            timetable_type& m_timetable;

            string_type m_syubetsumei;

            string_type m_ryakusyou;

            string_type m_diagram_sen_color;

            string_type m_diagram_sen_style;

            string_type m_diagram_sen_is_bold;

            virtual bool parse_impl(const string_type& key, string_type value)
            {
                if (key == string_type(TETENGO2_TEXT("Syubetsumei")))
                    m_syubetsumei = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("Ryakusyou")))
                    m_ryakusyou = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("DiagramSenColor")))
                    m_diagram_sen_color = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("DiagramSenStyle")))
                    m_diagram_sen_style = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("DiagramSenIsBold")))
                    m_diagram_sen_is_bold = std::move(value);

                return true;
            }

            virtual void entered_impl()
            {}

            virtual void leaving_impl()
            {
                string_type abbreviation = m_ryakusyou.empty() ? m_syubetsumei : std::move(m_ryakusyou);
                m_timetable.insert_train_kind(
                    m_timetable.train_kinds().end(),
                    train_kind_type(
                        std::move(m_syubetsumei),
                        std::move(abbreviation),
                        to_color(m_diagram_sen_color),
                        to_weight(m_diagram_sen_is_bold),
                        to_line_style(m_diagram_sen_style)
                    )
                );
            }

        };

        class dia_state : public state
        {
        public:
            explicit dia_state(string_type& current_diagram_name)
            :
            m_current_diagram_name(current_diagram_name)
            {}

            virtual ~dia_state()
            {}

        private:
            string_type& m_current_diagram_name;

            virtual bool parse_impl(const string_type& key, string_type value)
            {
                if (key == string_type(TETENGO2_TEXT("DiaName")))
                    m_current_diagram_name = std::move(value);

                return true;
            }

            virtual void entered_impl()
            {}

            virtual void leaving_impl()
            {}

        };

        class kudari_state : public state
        {
        public:
            explicit kudari_state(bool& down)
            :
            m_down(down)
            {}

            virtual ~kudari_state()
            {}

        private:
            bool& m_down;

            virtual bool parse_impl(const string_type& key, string_type value)
            {
                return true;
            }

            virtual void entered_impl()
            {
                m_down = true;
            }

            virtual void leaving_impl()
            {}

        };

        class nobori_state : public state
        {
        public:
            explicit nobori_state(bool& down)
            :
            m_down(down)
            {}

            virtual ~nobori_state()
            {}

        private:
            bool& m_down;

            virtual bool parse_impl(const string_type& key, string_type value)
            {
                return true;
            }

            virtual void entered_impl()
            {
                m_down = false;
            }

            virtual void leaving_impl()
            {}

        };

        class ressya_state : public state
        {
        public:
            explicit ressya_state(timetable_type& timetable, const bool down)
            :
            m_timetable(timetable),
            m_down(down),
            m_syubetsu(),
            m_ressyabangou(),
            m_ressyamei(),
            m_gousuu(),
            m_eki_jikoku()
            {}

            virtual ~ressya_state()
            {}

        private:
            typedef typename timetable_type::train_type train_type;

            typedef typename train_type::stop_type stop_type;

            typedef typename stop_type::time_type time_type;

            struct insert_stop
            {
                train_type& m_train;

                explicit insert_stop(train_type& train)
                :
                m_train(train)
                {}

                void operator()(stop_type& stop)
                {
                    m_train.insert_stop(m_train.stops().end(), std::move(stop));
                }

            };

            static std::vector<stop_type> parse_stops(const string_type& stops_string, const bool direction_down)
            {
                const std::vector<string_type> stop_strings = split(stops_string, char_type(TETENGO2_TEXT(',')));

                std::vector<stop_type> stops;
                stops.reserve(stop_strings.size());
                std::transform(stop_strings.begin(), stop_strings.end(), std::back_inserter(stops), parse_stop);

                if (!direction_down)
                    std::reverse(stops.begin(), stops.end());

                return stops;
            }

            static stop_type parse_stop(const string_type& stop_string)
            {
                const std::vector<string_type> kind_time = split(stop_string, char_type(TETENGO2_TEXT(';')));
                if (kind_time.empty())
                    return stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type());

                const bool stopping = kind_time[0] == string_type(TETENGO2_TEXT("1")) && kind_time.size() >= 2;
                const bool operational = !stopping && kind_time.size() >= 2;
                if (!stopping && !operational)
                    return stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type());

                const std::vector<string_type> arrival_departure = split(kind_time[1], char_type(TETENGO2_TEXT('/')));
                if (arrival_departure.empty())
                    return stop_type(time_type::uninitialized(), time_type::uninitialized(), false, string_type());

                time_type arrival = time_type::uninitialized();
                time_type departure = time_type::uninitialized();
                if (arrival_departure.size() < 2)
                {
                    departure = parse_time(arrival_departure[0]);
                }
                else
                {
                    arrival = parse_time(arrival_departure[0]);
                    departure = parse_time(arrival_departure[1]);
                }

                return stop_type(std::move(arrival), std::move(departure), operational, string_type());
            }

            static time_type parse_time(const string_type& time_string)
            {
                if (time_string.size() != 4)
                    return time_type::uninitialized();

                const unsigned int hours = to_number<unsigned int>(time_string.substr(0, 2));
                if (hours >= 24)
                    return time_type::uninitialized();
                const unsigned int minutes = to_number<unsigned int>(time_string.substr(2, 2));
                if (minutes >= 60)
                    return time_type::uninitialized();

                return time_type(hours, minutes, 0);
            }

            timetable_type& m_timetable;

            const bool m_down;

            string_type m_houkou;

            string_type m_syubetsu;

            string_type m_ressyabangou;

            string_type m_ressyamei;

            string_type m_gousuu;

            string_type m_eki_jikoku;

            string_type m_bikou;

            virtual bool parse_impl(const string_type& key, string_type value)
            {
                if      (key == string_type(TETENGO2_TEXT("Houkou")))
                    m_houkou = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("Syubetsu")))
                    m_syubetsu = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("Ressyabangou")))
                    m_ressyabangou = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("Ressyamei")))
                    m_ressyamei = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("Gousuu")))
                    m_gousuu = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("EkiJikoku")))
                    m_eki_jikoku = std::move(value);
                else if (key == string_type(TETENGO2_TEXT("Bikou")))
                    m_bikou = std::move(value);

                return true;
            }

            virtual void entered_impl()
            {}

            virtual void leaving_impl()
            {
                const typename timetable_type::train_kind_index_type train_kind_index =
                    to_number<typename timetable_type::train_kind_index_type>(m_syubetsu);
                if (train_kind_index >= m_timetable.train_kinds().size())
                    return;

                train_type train(m_ressyabangou, train_kind_index, m_ressyamei, m_gousuu, m_bikou);

                std::vector<stop_type> stops =
                    parse_stops(m_eki_jikoku, m_houkou == string_type(TETENGO2_TEXT("Kudari")));
                if (stops.size() != m_timetable.station_locations().size())
                    return;
                std::for_each(stops.begin(), stops.end(), insert_stop(train));

                if (m_down)
                    m_timetable.insert_down_train(m_timetable.down_trains().end(), std::move(train));
                else
                    m_timetable.insert_up_train(m_timetable.up_trains().end(), std::move(train));
            }

        };


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static std::vector<string_type> collect_diagram_names(const iterator first, const iterator last)
        {
            std::vector<string_type> names;

            iterator next_line_first = first;
            for (;;)
            {
                const string_type input_line = next_line(next_line_first, last);
                if (next_line_first == last)
                    break;

                std::pair<string_type, string_type> key_value = parse_line(input_line);
                if (key_value.first.empty() || key_value.second.empty())
                    continue;
                if (key_value.first != string_type(TETENGO2_TEXT("DiaName")))
                    continue;

                names.push_back(std::move(key_value.second));
            }

            return names;
        }

        static string_type next_line(iterator& first, const iterator last)
        {
            skip_line_breaks(first, last);
            const iterator next_line_break = std::find_if(first, last, line_break);
            string_type line = encoder().decode(input_string_type(first, next_line_break));
            first = next_line_break;
            return line;
        }

        static void skip_line_breaks(iterator& first, const iterator last)
        {
            while (first != last && line_break(*first))
                ++first;
        }

        static bool line_break(const input_char_type character)
        {
            return
                character == input_char_type(TETENGO2_TEXT('\r')) ||
                character == input_char_type(TETENGO2_TEXT('\n'));
        }

        template <typename T>
        static T to_number(const string_type& number_string)
        {
            try
            {
                return boost::lexical_cast<T>(number_string);
            }
            catch (const boost::bad_lexical_cast&)
            {
                return 0;
            }
        }

        static color_type to_color(const string_type& color_string)
        {
            if (color_string.length() != 8)
                return color_type(0, 0, 0);

            return
                color_type(
                    static_cast<unsigned char>(from_hex_string<unsigned int>(color_string.substr(2, 2))),
                    static_cast<unsigned char>(from_hex_string<unsigned int>(color_string.substr(4, 2))),
                    static_cast<unsigned char>(from_hex_string<unsigned int>(color_string.substr(6, 2)))
                );
        }

        template <typename T>
        static T from_hex_string(const string_type& hex_string)
        {
            std::basic_istringstream<char_type> stream(hex_string);
            T result = 0;
            stream >> std::hex >> result;
            return result;
        }

        static std::unique_ptr<state> dispatch(
            const string_type& line,
            timetable_type&    timetable,
            const string_type& selected_diagram_name,
            string_type&       current_diagram_name,
            bool&              down
        )
        {
            if (line.empty() || line[line.length() - 1] != char_type(TETENGO2_TEXT('.')))
                return std::unique_ptr<state>();

            const string_type name = line.substr(0, line.length() - 1);
            if (name.empty())
            {
                return tetengo2::make_unique<initial_state>(timetable);
            }
            else if (name == string_type(TETENGO2_TEXT("Rosen")))
            {
                return tetengo2::make_unique<rosen_state>(timetable);
            }
            else if (name == string_type(TETENGO2_TEXT("Eki")))
            {
                return tetengo2::make_unique<eki_state>(timetable);
            }
            else if (name == string_type(TETENGO2_TEXT("Ressyasyubetsu")))
            {
                return tetengo2::make_unique<ressyasyubetsu_state>(timetable);
            }
            else if (name == string_type(TETENGO2_TEXT("Dia")))
            {
                return tetengo2::make_unique<dia_state>(current_diagram_name);
            }
            else if (!current_diagram_name.empty() && current_diagram_name == selected_diagram_name)
            {
                if      (name == string_type(TETENGO2_TEXT("Kudari")))
                    return tetengo2::make_unique<kudari_state>(down);
                else if (name == string_type(TETENGO2_TEXT("Nobori")))
                    return tetengo2::make_unique<nobori_state>(down);
                else if (name == string_type(TETENGO2_TEXT("Ressya")))
                    return tetengo2::make_unique<ressya_state>(timetable, down);
                else
                    return tetengo2::make_unique<unknown_state>();
            }
            else
            {
                return tetengo2::make_unique<unknown_state>();
            }
        }

        static std::pair<string_type, string_type> parse_line(const string_type& line)
        {
            std::vector<string_type> splitted = split(line, char_type(TETENGO2_TEXT('=')));
            if (splitted.size() < 2)
                return std::make_pair(line, string_type());

            return std::make_pair(std::move(splitted[0]), remove_escape_sequences(std::move(splitted[1])));
        }

        static std::vector<string_type> split(const string_type& string, const char_type splitter)
        {
            std::vector<string_type> result;
            boost::split(result, string, is_splitter(splitter));
            return result;
        }

        static string_type remove_escape_sequences(string_type string)
        {
            boost::replace_all(string, string_type(TETENGO2_TEXT("\\r\\n")), string_type(TETENGO2_TEXT(" ")));
            boost::replace_all(string, string_type(TETENGO2_TEXT("\\r")), string_type(TETENGO2_TEXT(" ")));
            boost::replace_all(string, string_type(TETENGO2_TEXT("\\n")), string_type(TETENGO2_TEXT(" ")));

            boost::replace_all(string, string_type(TETENGO2_TEXT("\\")), string_type());

            return string;
        }

        static file_type parse_file_type(const string_type& file_type_string)
        {
            std::vector<string_type> splitted = split(file_type_string, char_type(TETENGO2_TEXT('.')));
            string_type name = splitted.size() >= 1 ? std::move(splitted[0]) : string_type();
            const int major_version = splitted.size() >= 2 ? to_number<int>(splitted[1]) : 0;
            const int minor_version = splitted.size() >= 3 ? to_number<int>(splitted[2]) : 0;
            return file_type(std::move(name), major_version, minor_version);
        }


        // variables

        const std::unique_ptr<diagram_selector_type> m_p_diagram_selector;


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            iterator mutable_first = first;
            const std::pair<string_type, string_type> key_value = parse_line(next_line(mutable_first, last));
            const file_type file_type_ = parse_file_type(key_value.second);

            return
                key_value.first == string_type(TETENGO2_TEXT("FileType")) &&
                file_type_.m_name == string_type(TETENGO2_TEXT("OuDia")) &&
                file_type_.m_major_version == 1 &&
                file_type_.m_minor_version == 2;
        }

        virtual std::unique_ptr<timetable_type> read_impl(
            const iterator               first,
            const iterator               last,
            typename error_type::enum_t& error
        )
        {
            if (!selects(first, last))
            {
                error = error_type::failed;
                return std::unique_ptr<timetable_type>();
            }
            
            const boost::optional<string_type> selected_diagram_name = select_diagram(first, last);
            if (!selected_diagram_name)
            {
                error = error_type::canceled;
                return std::unique_ptr<timetable_type>();
            }

            return read_timetable(first, last, error, *selected_diagram_name);
        }


        // functions

        boost::optional<string_type> select_diagram(const iterator first, const iterator last)
        {
            std::vector<string_type> diagram_names = collect_diagram_names(first, last);
            if (diagram_names.empty())
                return string_type();

            const typename std::vector<string_type>::const_iterator found =
                m_p_diagram_selector->select(diagram_names);
            if (found == diagram_names.end())
                return boost::none;

            return std::move(*found);
        }

        std::unique_ptr<timetable_type> read_timetable(
            const iterator               first,
            const iterator               last,
            typename error_type::enum_t& error,
            const string_type&           selected_diagram_name
        )
        {
            std::unique_ptr<timetable_type> p_timetable = tetengo2::make_unique<timetable_type>();
            string_type current_diagram_name;
            bool down = true;

            std::unique_ptr<state> p_state = tetengo2::make_unique<initial_state>(*p_timetable);
            iterator next_line_first = first;
            for (;;)
            {
                const string_type input_line = next_line(next_line_first, last);
                if (next_line_first == last)
                    break;

                std::unique_ptr<state> p_new_state =
                    dispatch(input_line, *p_timetable, selected_diagram_name, current_diagram_name, down);
                if (p_new_state)
                {
                    p_state->leaving();
                    p_state = std::move(p_new_state);
                    p_state->entered();
                }
                else
                {
                    if (!p_state->parse(input_line))
                    {
                        error = error_type::failed;
                        return std::unique_ptr<timetable_type>();
                    }
                }
            }

            if (!dynamic_cast<initial_state*>(p_state.get()))
            {
                error = error_type::failed;
                return std::unique_ptr<timetable_type>();
            }

            return std::move(p_timetable);
        }


    };


}}}


#endif
