//
// Created by Ahmad Beirkdar on 2020-12-20.
// Named DTS for the reverse of STD
// Implementations of small things not added to libcxx yet

#ifndef SIDH_CPP_DTS_H
#define SIDH_CPP_DTS_H

#include <memory>

namespace DTS{


    // Implementation of std::make_unique_for_overwrite following libcxx format of std::make_unique found: https://github.com/llvm/llvm-project/blob/0985a8bfea46272561d2a261b10f308a5841f18a/libcxx/include/memory#L2054
    // Papers: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1020r0.html
    //          http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2042r0.html
    template<class _Tp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename std::__unique_if<_Tp>::__unique_single
    make_unique_for_overwrite(){
        return std::unique_ptr<_Tp>(new _Tp);;
    }

    template<class _Tp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename std::__unique_if<_Tp>::__unique_array_unknown_bound
    make_unique_for_overwrite(size_t __n){
        typedef typename std::remove_extent<_Tp>::type _Up;
        return std::unique_ptr<_Tp>(new _Up[__n]);
    }

    template<class _Tp, class... _Args>
    typename std::__unique_if<_Tp>::__unique_array_known_bound
    make_unique_for_overwrite(_Args&&...) = delete;
}

#endif //SIDH_CPP_DTS_H
