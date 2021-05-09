#pragma once

#include "common.h"

template <std::size_t N, typename T, typename dummy = positive<N>>
class stack_massive {
    T data[N];
    std::size_t sz = 0;

    void check_size() const;
    void check_insert_pos(std::size_t) const;
    void check_access_pos(std::size_t) const;

public:
    void push_back(T);
    void insert(std::size_t, T);
    T erase(std::size_t);

    const T &at(std::size_t) const;
    T &at(std::size_t);

    [[nodiscard]] std::size_t size() const {
        return sz;
    }
    [[nodiscard]] bool empty() const {
        return sz == 0;
    }
    [[nodiscard]] bool full() const {
        return sz == N;
    }
};

template<std::size_t N, typename T, typename dummy>
void stack_massive<N, T, dummy>::push_back(T t) {
    check_size();
    data[sz] = std::move(t);
    ++sz;
}

template<std::size_t N, typename T, typename dummy>
void stack_massive<N, T, dummy>::insert(std::size_t pos, T t) {
    check_insert_pos(pos);
    if (pos == sz) {
        push_back(std::move(t));
        return;
    }
    for (std::size_t i = sz; i > pos; --i) {
        data[i] = std::move(data[i-1]);
    }
    data[pos] = std::move(t);
    ++sz;
}

template<std::size_t N, typename T, typename dummy>
void stack_massive<N, T, dummy>::check_size() const {
    if (sz == N) {
        cmn::throw_x<std::length_error>("pushing too many elements to stack massive");
    }
}

template<std::size_t N, typename T, typename dummy>
void stack_massive<N, T, dummy>::check_insert_pos(std::size_t pos) const {
    if (pos > sz) {
        cmn::throw_x<std::length_error>("inserting element on invalid position");
    }
}

template<std::size_t N, typename T, typename dummy>
void stack_massive<N, T, dummy>::check_access_pos(std::size_t pos) const {
    if (pos >= sz) {
        cmn::throw_x<std::length_error>("trying to access element on invalid position");
    }
}

template<std::size_t N, typename T, typename dummy>
const T &stack_massive<N, T, dummy>::at(std::size_t pos) const {
    check_access_pos(pos);
    return data[pos];
}

template<std::size_t N, typename T, typename dummy>
T &stack_massive<N, T, dummy>::at(std::size_t pos) {
    check_access_pos(pos);
    return data[pos];
}

template<std::size_t N, typename T, typename dummy>
T stack_massive<N, T, dummy>::erase(std::size_t pos) {
    check_access_pos(pos);
    T del = std::move(data[pos]);
    for (std::size_t i = pos; i < sz - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --sz;
    return del;
}
