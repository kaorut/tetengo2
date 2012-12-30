/*! \file
    \brief The definition of bobura::model::serializer::writer.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITER_H)
#define BOBURA_MODEL_SERIALIZER_WRITER_H

#include <boost/noncopyable.hpp>
#include <boost/utility.hpp>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer.

        \tparam OutputStream An output stream type.
        \tparam Timetable    A timetable type.
        \tparam Path         A path type.
    */
    template <typename OutputStream, typename Timetable, typename Path>
    class writer : private boost::noncopyable
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path type.
        typedef Path path_type;


        // constructors and destructor

        /*!
            \brief Destroys the writer.
        */
        virtual ~writer()
        {}


        // functions

        /*!
            \brief Returns the extension.

            The extension includes the first dot; not "txt" but ".txt".

            \return The extension.
        */
        path_type extension()
        const
        {
            return extension_impl();
        }

        /*!
            \brief Checks whether this writer selects a file type.

            \param path A path.

            \retval true  When this writer selects the file type.
            \retval false Otherwise.
        */
        bool selects(const path_type& path)
        const
        {
            return selects_impl(path);
        }

        /*!
            \brief Writes a timetable.

            \param timetable     A timetable.
            \param output_stream An output stream.
        */
        void write(const timetable_type& timetable, output_stream_type& output_stream)
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

        virtual bool selects_impl(const path_type& path)
        const
        {
            typedef typename path_type::string_type path_string_type;

            const path_string_type path_string = path.native();
            const path_string_type extension_string = extension_impl().native();
            if (path_string.length() < extension_string.length())
                return false;
            
            const path_string_type path_extension_string(
                boost::prior(path_string.end(), extension_string.length()), path_string.end()
            );

            return path_extension_string == extension_string;
        }

        virtual path_type extension_impl()
        const = 0;

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        = 0;


    };


}}}


#endif
