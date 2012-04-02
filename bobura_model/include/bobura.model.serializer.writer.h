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
        \tparam PathString   A path string type.
    */
    template <typename OutputStream, typename Timetable, typename PathString>
    class writer : private boost::noncopyable
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path string type.
        typedef PathString path_string_type;


        // constructors and destructor

        /*!
            \brief Destroys the writer.
        */
        virtual ~writer()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the extention.

            The extention does not include the first dot;
            not ".txt" but "txt".

            \return The extention.
        */
        path_string_type extention()
        const
        {
            return extention_impl();
        }

        /*!
            \brief Checks whether this writer selects a file type.

            The extention must not include the first dot;
            not ".txt" but "txt".

            \param extention An extention.

            \retval true  When this writer selects the file type.
            \retval false Otherwise.
        */
        bool selects(const path_string_type& extention)
        const
        {
            return extention == extention_impl();
        }

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

        virtual path_string_type extention_impl()
        const = 0;

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        = 0;


    };


}}}


#endif
