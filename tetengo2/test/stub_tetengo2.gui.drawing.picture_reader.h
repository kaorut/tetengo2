/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::picture_reader.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DRAWING_PICTUREREADER_H)
#define STUBTETENGO2_GUI_DRAWING_PICTUREREADER_H

#include <memory>
#include <utility>

#include <boost/noncopyable.hpp>


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <typename Picture, typename Path>
    class picture_reader : private boost::noncopyable
    {
    public:
        // types

        typedef Picture picture_type;

        typedef Path path_type;


        // constructors and destructor

        template <typename P>
        picture_reader(P&& path)
        :
        m_path(std::forward<P>(path))
        {}


        // functions

        std::auto_ptr<picture_type> read()
        {
            return std::auto_ptr<picture_type>();
        }


    private:
        // variables

        const path_type m_path;


    };


}}}


#endif
