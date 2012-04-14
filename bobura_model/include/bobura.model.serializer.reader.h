/*! \file
    \brief The definition of bobura::model::serializer::reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READER_H)
#define BOBURA_MODEL_SERIALIZER_READER_H

#include <cstddef>
#include <memory>

#include <boost/noncopyable.hpp>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a reader.

        \tparam ForwardIterator A forward iterator type.
        \tparam Timetable       A timetable type.
    */
    template <typename ForwardIterator, typename Timetable>
    class reader : private boost::noncopyable
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The timetable type.
        typedef Timetable timetable_type;


        // constructors and destructor

        /*!
            \brief Destroys the reader.
        */
        virtual ~reader()
        {}


        // functions

        /*!
            \brief Checks whether this reader selects a file type.

            \param first The first position of an input.
            \param last  The last position of an input.

            \retval true  When this reader selects the file type.
            \retval false Otherwise.
        */
        bool selects(const iterator first, const iterator last)
        {
            return selects_impl(first, last);
        }

        /*!
            \brief Reads a timetable.

            When it cannot read a timetable, it returns NULL.

            \param first The first position of an input.
            \param last  The last position of an input.

            \return A unique pointer to a timetable.
        */
        std::unique_ptr<timetable_type> read(const iterator first, const iterator last)
        {
            return read_impl(first, last);
        }


    protected:
        // constructors

        /*!
            \brief Creates a reader.
        */
        reader()
        {}


    private:
        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        = 0;

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last)
        = 0;


    };


}}}


#endif
