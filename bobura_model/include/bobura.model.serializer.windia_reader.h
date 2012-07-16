/*! \file
    \brief The definition of bobura::model::serializer::windia_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WINDIA2READER_H)
#define BOBURA_MODEL_SERIALIZER_WINDIA2READER_H

#include <cassert>
#include <stdexcept>
#include <utility>

#include <boost/throw_exception.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a WinDIA reader.

        \tparam ForwardIterator A forward iterator type.
        \tparam Timetable       A timetable type.
        \tparam Encoder         An encoder type.
    */
    template <typename ForwardIterator, typename Timetable, typename Encoder>
    class windia_reader : public reader<ForwardIterator, Timetable>
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The base type.
        typedef reader<iterator, timetable_type> base_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates a WinDIA reader.
        */
        windia_reader()
        :
        base_type()
        {}

        /*!
            \brief Destroys the windia_reader.
        */
        virtual ~windia_reader()
        {}


    private:
        // types

        typedef typename iterator::value_type input_char_type;

        typedef std::basic_string<input_char_type> input_string_type;

        typedef typename timetable_type::string_type string_type;

        class state
        {
        public:
            virtual ~state()
            {}

            virtual void parse(const string_type& line)
            const = 0;

        };

        class initial_state : public state
        {
        public:
            virtual ~initial_state()
            {}

            virtual void parse(const string_type& line)
            const
            {
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Cannot parse any line in the initial state."));
            }

        };

        class windia_state : public state
        {
        public:
            explicit windia_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~windia_state()
            {}

            virtual void parse(const string_type& line)
            const
            {
                m_timetable.set_title(line);
            }

        private:
            timetable_type& m_timetable;

        };

        class station_state : public state
        {
        public:
            explicit station_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~station_state()
            {}

            virtual void parse(const string_type& line)
            const
            {

            }

        private:
            timetable_type& m_timetable;

        };

        class line_kind_state : public state
        {
        public:
            explicit line_kind_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~line_kind_state()
            {}

            virtual void parse(const string_type& line)
            const
            {

            }

        private:
            timetable_type& m_timetable;

        };

        class down_train_state : public state
        {
        public:
            explicit down_train_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~down_train_state()
            {}

            virtual void parse(const string_type& line)
            const
            {

            }

        private:
            timetable_type& m_timetable;

        };

        class up_train_state : public state
        {
        public:
            explicit up_train_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~up_train_state()
            {}

            virtual void parse(const string_type& line)
            const
            {

            }

        private:
            timetable_type& m_timetable;

        };


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static const input_string_type& windia_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[WinDIA]"));
            return singleton;
        }

        static const input_string_type& station_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[\x89\x77]")); // "eki"
            return singleton;
        }

        static const input_string_type& line_kind_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[\x90\xFC\x8E\xED]")); // "senshu"
            return singleton;
        }

        static const input_string_type& down_train_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[\x89\xBA\x82\xE8]")); // "kudari"
            return singleton;
        }

        static const input_string_type& up_train_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[\x8F\xE3\x82\xE8]")); // "nobori"
            return singleton;
        }

        static input_string_type next_line(iterator& first, const iterator last)
        {
            input_string_type line;
            for (;;)
            {
                skip_line_breaks(first, last);
                const iterator next_line_break = std::find_if(first, last, line_break);
                line += input_string_type(first, next_line_break);

                first = next_line_break;
                if (!line.empty() && line_contination(line.back()))
                    line.pop_back();
                else
                    break;
            }

            return line;
        }

        static void skip_line_breaks(iterator& first, const iterator last)
        {
            while (first != last && (line_break(*first) || tab(*first)))
                ++first;
        }

        static bool line_break(const input_char_type character)
        {
            return
                character == input_char_type(TETENGO2_TEXT('\r')) ||
                character == input_char_type(TETENGO2_TEXT('\n'));
        }

        static bool line_contination(const input_char_type character)
        {
            return character == input_char_type(TETENGO2_TEXT('\\'));
        }

        static bool tab(const input_char_type character)
        {
            return
                character == input_char_type(TETENGO2_TEXT('\t'));
        }


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            iterator mutable_first = first;
            return next_line(mutable_first, last) == windia_section_label();
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last)
        {
            std::unique_ptr<timetable_type> p_timetable = tetengo2::make_unique<timetable_type>();

            std::unique_ptr<state> p_state = tetengo2::make_unique<initial_state>();
            iterator next_line_first = first;
            for (;;)
            {
                const input_string_type input_line = next_line(next_line_first, last);
                if (next_line_first == last)
                    break;

                if      (input_line == windia_section_label())
                    p_state = tetengo2::make_unique<windia_state>(*p_timetable);
                else if (input_line == station_section_label())
                    p_state = tetengo2::make_unique<station_state>(*p_timetable);
                else if (input_line == line_kind_section_label())
                    p_state = tetengo2::make_unique<line_kind_state>(*p_timetable);
                else if (input_line == down_train_section_label())
                    p_state = tetengo2::make_unique<down_train_state>(*p_timetable);
                else if (input_line == up_train_section_label())
                    p_state = tetengo2::make_unique<up_train_state>(*p_timetable);
                else
                    p_state->parse(encoder().decode(input_line));
            }

            return std::move(p_timetable);
        }


    };


}}}


#endif
