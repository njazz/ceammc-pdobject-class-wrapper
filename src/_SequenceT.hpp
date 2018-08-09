// template utility classes for tuple handling

#ifndef _SequenceT_hpp
#define _SequenceT_hpp

template <int...>
struct _sequence {
};

template <int N, int... S>
struct _genSequence : _genSequence<N - 1, N - 1, S...> {
};

template <int... S>
struct _genSequence<0, S...> {
    typedef _sequence<S...> type;
};

#endif
