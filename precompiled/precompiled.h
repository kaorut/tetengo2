/*! \file
    \brief The precompiled header for Visual C++.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(PRECOMPILED_H)
#define PRECOMPILED_H

// The standard library headers

#include <algorithm>
#include <cassert>
#include <cerrno>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <cwchar>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <ios>
#include <istream>
#include <iterator>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <queue>
#include <ratio>
#include <shared_mutex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <system_error>
#include <thread>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>
#if __has_include(<filesystem>)
#   include <filesystem>
#elif __has_include(<experimental/filesystem>)
#   include <experimental/filesystem>
#endif
#if __has_include(<optional>)
#   include <optional>
#elif __has_include(<experimental/optional>)
#   include <experimental/optional>
#endif
#if __has_include(<string_view>)
#   include <string_view>
#elif __has_include(<boost/utility/string_view.hpp>)
#   include <boost/utility/string_view.hpp>
#endif
#if __has_include(<variant>)
#   include <variant>
#elif __has_include(<boost/variant.hpp>)
#   include <boost/variant.hpp>
#endif


// The Boost library headers

#include <boost/algorithm/string.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/core/swap.hpp>
#include <boost/exception/all.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/operators.hpp>
#include <boost/predef.h>
#include <boost/preprocessor.hpp>
#include <boost/proto/operators.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/rational.hpp>
#include <boost/scope_exit.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits.hpp>


#if BOOST_COMP_MSVC

// Windows headers

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <d2d1.h>
#include <dwrite.h>
#include <dxgiformat.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max
#include <ShObjIdl.h>
#include <ShTypes.h>
#include <Unknwn.h>
#include <wincodec.h>

#endif


#endif
