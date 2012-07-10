/*! \file
    \brief The definition of bobura::model::timetable_info::train_kind_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_TRAINKINDLIST_H)
#define BOBURA_MODEL_TIMETABLEINFO_TRAINKINDLIST_H


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class template for a train kind list.

        \tparam TrainKind A meterage type.
    */
    template <typename TrainKind>
    class train_kind_list : private boost::equality_comparable<train_kind_list<TrainKind>>
    {
    public:
        // types

        //! The train kind list type.
        typedef TrainKind train_kind_type;


        // constructors and destructor

        /*!
            \brief Creates a train kind list.
        */
        train_kind_list()
        {}


        // functions

        /*!
            \brief Checks whether one train kind list is equal to another.

            \param one     One train kind list.
            \param another Another train kind list.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const train_kind_list& one, const train_kind_list& another)
        {
            return true;
        }


    private:
        // variables


    };


}}}


#endif
