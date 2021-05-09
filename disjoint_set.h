#pragma once

#include "common.h"

template <typename T>
class disjoint_set {
    std::map<T,T> data{};

    T force_union(T, T);

public:
    T delegate(T);

    T union_delegates(T, T);

    T union_any(T, T);

    bool are_together(T, T);

    friend std::ostream &operator<<(std::ostream &s, const disjoint_set &set) {
        for (auto i = set.data.cbegin(); i != set.data.cend(); ++i) {
            s << i->first << ' ';
        }
        s << '\n';
        for (auto i = set.data.cbegin(); i != set.data.cend(); ++i) {
            s << i->second << ' ';
        }
        return s;
    }
};

template<typename T>
T disjoint_set<T>::delegate(T t) {
    auto i = data.find(t);
    if (i != data.end()) {
        return i->second;
    }

    auto itr = data.insert(std::make_pair(t,t));
    if (itr.second) {
        return itr.first->second;
    }

    cmn::throw_x<std::logic_error>("disjoint_set: insertion failed for some reason");
}

template<typename T>
T disjoint_set<T>::union_delegates(T d1, T d2) {
    if (data.find(d1) == data.end()) {
        cmn::throw_x<std::logic_error>("disjoint_set: making union with nonexistent delegate");
    }

    return force_union(d1, d2);
}

template<typename T>
T disjoint_set<T>::union_any(T t1, T t2) {
    T d1 = delegate(t1);
    T d2 = delegate(t2);
    return force_union(d1, d2);
}

template<typename T>
T disjoint_set<T>::force_union(T d1, T d2) {
    if (d1 == d2) {
        return d1;
    }

    for (auto i = data.begin(); i != data.end(); ++i) {
        if (i->second == d2) {
            i->second = d1;
        }
    }

    return d1;
}

template<typename T>
bool disjoint_set<T>::are_together(T t1, T t2) {
    return delegate(t1) == delegate(t2);
}
