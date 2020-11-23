#pragma once

template<typename Head_, typename Tail_>
struct TypeList{
    typedef Head_ Head;
    typedef Tail_ Tail;

};

struct NullType {};