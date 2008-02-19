/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLE_H)
#define BOBURA_MODEL_TIMETABLE_H


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
    */
    template <
        typename Station
    >
    class timetable
    {
    private:
        // concept checks


    public:
        // types

        //! The station type.
        typedef Station station_type;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.
        */
        timetable()
        {}

        /*!
            \brief Copies a timetable.

            \param another Another timetable object.
        */
        timetable(const timetable& another)
        {}

        /*!
            \brief Destroys the timetable.
        */
        ~timetable()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another timetable object.

            \param another Another timetable object.
        */
        void swap(timetable& another)
        throw ()
        {
        }

        /*!
            \brief Assigns another timetable object.

            \param another Another timetable object.

            \return this object.
        */
        timetable& operator=(const timetable& another)
        {
            timetable(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther timetable object.

            \param another Another timetable object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const timetable& another)
        const
        {
            return false;
        }


    private:
        // variables


    };


}}

namespace std
{
    /*!
        \brief Swaps two timetable objects.

        \param timetable1 A timetable object #1.
        \param timetable2 A timetable object #2.
    */
    template <typename Stations>
    void swap(
        bobura::model::timetable<Stations>& timetable1,
        bobura::model::timetable<Stations>& timetable2
    )
    throw ()
    {
        timetable1.swap(timetable2);
    }


}


#endif
