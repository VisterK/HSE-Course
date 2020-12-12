#pragma once

#include "typelist.h"
template <class TList>
struct Length;


template <>
struct Length<NullType>
{
    enum {
        length = 0
    };
};


template <class Head, class Tail>
struct Length< TypeList<Head, Tail> >
{
    enum {
        length = 1 + Length<Tail>::length
    };
};