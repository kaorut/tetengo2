/*! \file
    \brief The definition of bobura::model::serializer::bzip2_reader.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_BZIP2READER_H)
#define BOBURA_MODEL_SERIALIZER_BZIP2READER_H

//#include <iterator>
//#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a bzip2 reader.

        \tparam ForwardIterator A forward iterator type.
        \tparam Timetable       A timetable type.
    */
    template <typename ForwardIterator, typename Timetable>
    class bzip2_reader : public reader<ForwardIterator, Timetable>
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


        // constructors and destructor

        /*!
            \brief Creates a bzip2 reader.

            \param p_reader A unique pointer to a reader.
        */
        explicit bzip2_reader(std::unique_ptr<base_type> p_reader)
        :
        base_type(),
        m_p_reader(std::move(p_reader))
        {}

        /*!
            \brief Destroys the bzip2_reader.
        */
        virtual ~bzip2_reader()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef std::basic_string<typename iterator::value_type> input_string_type;

        typedef std::basic_istringstream<typename iterator::value_type> input_stream_type;


        // variables

        const std::unique_ptr<base_type> m_p_reader;


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            const input_string_type input_string(first, last);
            if (input_string.length() < 2)
                return false;
            if (input_string.substr(0, 2) != input_string_type(TETENGO2_TEXT("BZ")))
                return false;

            std::istringstream input_stream(input_string);
            boost::iostreams::filtering_istream filtering_input_stream;
            filtering_input_stream.push(boost::iostreams::bzip2_decompressor());
            filtering_input_stream.push(input_stream);

            try
            {
                return
                    m_p_reader->selects(
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>(filtering_input_stream)
                        ),
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>()
                        )
                    );
            }
            catch (const boost::iostreams::bzip2_error&)
            {
                return false;
            }
            catch (...)
            {
                throw;
            }
        }

        virtual std::unique_ptr<timetable_type> read_impl(
            const iterator               first,
            const iterator               last,
            typename error_type::enum_t& error
        )
        {
            std::istringstream input_stream(input_string_type(first, last));
            boost::iostreams::filtering_istream filtering_input_stream;
            filtering_input_stream.push(boost::iostreams::bzip2_decompressor());
            filtering_input_stream.push(input_stream);

            try
            {
                return
                    m_p_reader->read(
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>(filtering_input_stream)
                        ),
                        boost::spirit::make_default_multi_pass(
                            std::istreambuf_iterator<typename iterator::value_type>()
                        ),
                        error
                    );
            }
            catch (const boost::iostreams::bzip2_error&)
            {
                error = error_type::corrupted;
                return std::unique_ptr<timetable_type>();
            }
            catch (...)
            {
                throw;
            }
        }


    };


}}}


#endif
