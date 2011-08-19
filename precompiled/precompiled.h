/*! \file
    \brief The precompiled header for Visual C++.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(PRECOMPILED_H)
#define PRECOMPILED_H

// The standard library headers

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cwchar>
#include <exception>
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
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>


// Boost library headers

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/fusion/include/all.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/value_type.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/void.hpp>
#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include <boost/rational.hpp>
#include <boost/ref.hpp>
#include <boost/scope_exit.hpp>
#include <boost/signals2.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>
#include <boost/variant.hpp>


#if defined(_MSC_VER)

// Windows headers

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <CommCtrl.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max

#endif


#endif
