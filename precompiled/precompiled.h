/*! \file
    \brief The precompiled header for Visual C++.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(PRECOMPILED_H)
#define PRECOMPILED_H //!< !! Include Guard !!

// The standard library headers

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <cwchar>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <istream>
#include <iterator>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>


// Boost library headers

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include <boost/concept_check.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/function.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/next_prior.hpp>
#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/scope_exit.hpp>
#include <boost/scoped_array.hpp>
#include <boost/signal.hpp>
#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tokenizer.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility.hpp>


#if defined(_MSC_VER)

// Windows headers

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>
#include <commctrl.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <gdiplus.h>
#undef min
#undef max

#endif


#endif
