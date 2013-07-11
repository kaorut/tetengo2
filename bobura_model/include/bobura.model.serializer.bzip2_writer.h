/*! \file
    \brief The definition of bobura::model::serializer::bzip2_writer.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_BZIP2WRITER_H)
#define BOBURA_MODEL_SERIALIZER_BZIP2WRITER_H

#include <memory>
#include <utility>

#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include <tetengo2.stdalt.h>
#include <tetengo2.text.h>

#include "bobura.model.serializer.writer.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a bzip2 writer.

        \tparam OutputStream A output stream type.
        \tparam Timetable    A timetable type.
        \tparam Path         A path type.
    */
    template <typename OutputStream, typename Timetable, typename Path>
    class bzip2_writer : public writer<OutputStream, Timetable, Path>
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path type.
        typedef Path path_type;

        //! The base type.
        typedef writer<output_stream_type, timetable_type, path_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a bzip2 writer.

            \param p_writer A unique pointer to a writer.
        */
        explicit bzip2_writer(std::unique_ptr<base_type> p_writer)
        :
        base_type(),
        m_p_writer(std::move(p_writer)) 
        {}

        /*!
            \brief Destroys the bzip2 writer.
        */
        virtual ~bzip2_writer()
        TETENGO2_STDALT_NOEXCEPT
        {}


    private:
        // variables

        const std::unique_ptr<base_type> m_p_writer;


        // virtual functions

        virtual path_type extension_impl()
        const override
        {
            return
                path_type(m_p_writer->extension().native() + typename path_type::string_type(TETENGO2_TEXT("_bz2")));
        }

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        override
        {
            boost::iostreams::filtering_ostream filtering_output_stream;
            filtering_output_stream.push(boost::iostreams::bzip2_compressor());
            filtering_output_stream.push(output_stream);

            m_p_writer->write(timetable, filtering_output_stream);
        }


    };


}}}


#endif
