#pragma once

#include "stack_massive.h"
#include "edge.h"
#include "disjoint_set.h"

namespace core {
    template <std::size_t N,
            typename T = int,
            typename = positive<N>,
            typename = integral <T>>
    void read_input_file(stack_massive<N, edge<T>>&);

    template <std::size_t N,
            typename T = int,
            typename = positive<N>,
            typename = integral <T>>
    void fill_output_file(const stack_massive<N,edge<T>>&);

    template <typename T = int, typename = integral <T>>
    edge<T> get_edge(std::istream&);

    template <std::size_t N,
            typename T = int,
            typename = positive <N>,
            typename = integral <T>>
    void insertion_sort(stack_massive<N, edge<T>>&);

    template <std::size_t V, typename T = int>
    void kruskal_algorithm();
}

template<typename T, typename>
edge<T> core::get_edge(std::istream &stream) {
    if (!stream.good()) {
        return edge<T>{};
    }

    std::string name1;
    std::getline(stream, name1, ' ');

    if (name1.empty() || !stream.good()) {
        return edge<T>{};
    }

    std::string name2;
    std::getline(stream, name2, ' ');

    if (name2.empty() || !stream.good()) {
        return edge<T>{};
    }

    std::string num;
    std::getline(stream, num);

    T n;
    std::istringstream num_stream(num);
    num_stream >> n;

    if (num_stream.fail() || !num_stream.eof()) {
        return edge<T>{};
    }

    return edge<T>(name1, name2, n);
}

template<std::size_t N, typename T, typename, typename>
void core::read_input_file(stack_massive<N, edge<T>> &massive) {
    std::ifstream input(input_file);
    edge<T> current;
    std::size_t position;
    bool insertion_needed;

    while (input.good() && !massive.full()) {
        current = core::get_edge(input);//достаём ребро из файла
        debug << current;
        if (current.empty() || current.loop()) {//пропускаем пустые рёбра и петли
            debug << "ignoring empty edge or loop\n";
            continue;
        }

        position = 0;
        insertion_needed = true;
        for (std::size_t i = massive.size(); i > 0; --i) {
            if (position == 0) {
                if (massive.at(i - 1).weight() <= current.weight()) {
                    position = i;
                }
            }

            if (same_vertexes(massive.at(i - 1), current)) {
                debug << "maybe rewriting weight on position" << i - 1 << "in" << massive.at(i - 1) << '\n';
                massive.at(i - 1).maybe_assign_weight(current.weight());
                insertion_needed = false;
                break;
            }
        }

        if (insertion_needed) {
            debug << "inserting on position" << position << '\n';
            massive.insert(position, std::move(current));
        }
    }
}

template<std::size_t N, typename T, typename, typename>
void core::insertion_sort(stack_massive<N, edge<T>> &c) {
    if (c.size() < 2) {
        return;
    }

    edge<T> tmp;
    for (std::size_t i = 1; i < c.size(); ++i) {
        for (std::size_t j = i; j > 0 && !name_correct(c.at(j - 1), c.at(j)); --j) {
            tmp = std::move(c.at(j));
            c.at(j) = std::move(c.at(j - 1));
            c.at(j - 1) = std::move(tmp);
        }
    }
}

template<std::size_t V, typename T>
void core::kruskal_algorithm() {
    stack_massive<cmn::sum(V - 1), edge<T>> massive;
    core::read_input_file(massive);

    disjoint_set<std::string> ds;

    std::size_t i = 0;
    while (i < massive.size()) {
        if (ds.are_together(massive.at(i).name1(), massive.at(i).name2())) {
            debug << "discarding edge" << massive.at(i);
            massive.erase(i);
        } else {
            ds.union_any(massive.at(i).name1(), massive.at(i).name2());
            ++i;
        }
    }

    core::insertion_sort(massive);
    core::fill_output_file(massive);
}

template<std::size_t N, typename T, typename, typename>
void core::fill_output_file(const stack_massive<N, edge<T>> &m) {
    std::ofstream output(output_file);
    T count = 0;
    for (std::size_t i = 0; i < m.size(); ++i) {
        count += m.at(i).weight();
        m.at(i).write_vertexes(output);
        output << '\n';
    }
    output << count;
}
