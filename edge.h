#pragma once

#include "common.h"

template <typename T = int, typename dummy = integral<T>>
class edge;

template <typename T = int>
bool name_correct(const edge<T>&, const edge<T>&);

template <typename T, typename dummy>
class edge {
    std::string v1{};
    std::string v2{};
    T wgt = 0;//weight

public:
    edge(std::string name1, std::string name2, T w)
    : v1(name1 < name2
            ? std::move(name1)
            : std::move(name2)
        )
    , v2(name1 < name2
            ? std::move(name2)
            : std::move(name1)
        )
    , wgt(w)
    {}

    edge() = default;

    void write_vertexes(std::ostream&) const;
    void write_all(std::ostream&) const;

    void maybe_assign_weight(T w) {
        if (w < wgt) {
            wgt = w;
        }
    }

    [[nodiscard]] bool empty() const {
        return v1.empty() || v2.empty();
    }

    [[nodiscard]] bool loop() const {//непустая и соединяет одну и ту же вершину
        return !v1.empty() && (v1 == v2);
    }

    [[nodiscard]] T weight() const {
        return wgt;
    };

    friend bool name_correct(const edge &first, const edge &second) {
        return first.v1 < second.v1 || (first.v1 == second.v1 && first.v2 <= second.v2);
    }

    friend bool same_vertexes(const edge &first, const edge &second) {
        return !first.empty() && first.v1 == second.v1 && first.v2 == second.v2;
    }

    [[nodiscard]] std::string name1() const {
        return v1;
    }

    [[nodiscard]] std::string name2() const {
        return v2;
    }

    friend std::ostream &operator<<(std::ostream &stream, const edge &e) {
        stream.write(e.v1.c_str(), e.v1.size());
        stream << ' ';
        stream.write(e.v2.c_str(), e.v2.size());

        stream << ' ';
        stream << e.wgt;

        return stream;
    }
};

template<typename T, typename dummy>
void edge<T, dummy>::write_vertexes(std::ostream &stream) const {
    stream.write(v1.c_str(), v1.size());
    stream << ' ';
    stream.write(v2.c_str(), v2.size());
}

template<typename T, typename dummy>
void edge<T, dummy>::write_all(std::ostream &stream) const {
    write_vertexes(stream);
    stream << ' ';
    stream << wgt;
}
