//
// Created by 12096 on 2023/1/13.
//

#ifndef MYCRT_ITERATOR_HPP
#define MYCRT_ITERATOR_HPP

namespace std {
    template <class I>
    struct iterator_traits {
        typedef typename I::iterator_categoty iterator_categoty;
        typedef typename I::value_type value_type;
        typedef typename I::difference_type difference_type;
        typedef typename I::pointer pointer;
        typedef typename I::reference reference;
    };
//    template <class T>
//    struct iterator_traits<T*> {
//        typedef randmom_access_iterator_tag iterator_categoty;
//        typedef T value_type;
//        typedef size_t difference_type;
//        typedef T* pointer;
//        typedef T& reference;
//    };
//    template <class T>
//    struct iterator_traits<const T*> {
//        typedef randmom_access_iterator_tag iterator_categoty;
//        typedef T value_type;
//        typedef size_t difference_type;
//        typedef const T* pointer;
//        typedef const T& reference;
//    };
}

#endif //MYCRT_ITERATOR_HPP
