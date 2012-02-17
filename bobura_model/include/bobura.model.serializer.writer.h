/*! \file
    \brief The definition of bobura::model::serializer::writer.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITER_H)
#define BOBURA_MODEL_SERIALIZER_WRITER_H

#include <boost/noncopyable.hpp>

#include <tetengo2.cpp11.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer.

        \tparam OutputStream An output stream type.
        \tparam Timetable    A timetable type.
    */
    template <typename OutputStream, typename Timetable>
    class writer : private boost::noncopyable
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;


        // constructors and destructor

        /*!
            \brief Destroys the writer.
        */
        virtual ~writer()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Writes a timetable.

            \param timetable     A timetable.
            \param output_stream An output stream.
        */
        void write(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {
            write_impl(timetable, output_stream);
        }


    protected:
        // constructors

        /*!
            \brief Creates a writer.
        */
        writer()
        {}


    private:
        // virtual functions

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        = 0;


    };


}}}


#endif
