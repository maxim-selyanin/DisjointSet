#pragma once

#include "pch.h"
//#define NO_DEBUG

template <typename T>
using integral = std::enable_if_t <std::is_integral_v<T>>;

template <std::size_t N>
using positive = std::enable_if_t <(N != 0)>;

//project constants
constexpr char input_file[] = "D:/study/programming/3_semester/aads/course_work_files/input.txt";
constexpr char output_file[] = "D:/study/programming/3_semester/aads/course_work_files/output.txt";
constexpr std::size_t max_vertexes = 50;

class s_debug;

s_debug &no_space(s_debug&);
s_debug &enable_space(s_debug&);
s_debug &no_newline(s_debug&);
s_debug &enable_newline(s_debug&);

class s_debug {
#ifndef NO_DEBUG
    bool space = true;
    bool newline = true;
#endif
public:
    template <typename T>
    s_debug &operator<<(T t) {
#ifndef NO_DEBUG
        std::cout << t;
        if (space) {
            std::cout << ' ';
        }
#endif
        return *this;
    }

    template <>
    s_debug &operator<< (s_debug &(*t)(s_debug&)) {
#ifndef NO_DEBUG
        if (t == ::no_space) {
            space = false;
        }
        if (t == ::enable_space) {
            space = true;
        }
        if (t == ::no_newline) {
            newline = false;
        }
        if (t == ::enable_newline) {
            newline = true;
        }
#endif
        return *this;
    }

    s_debug &no_space();
    s_debug &enable_space();
    s_debug &no_newline();
    s_debug &enable_newline();
    ~s_debug();
};
#define debug s_debug()

namespace cmn {
    template <typename T = int, typename dummy = integral<T>>
    constexpr T sum(T);

    template <typename T = int, typename dummy = integral<T>>
    constexpr T positive_sum(T);

    template <typename X = std::exception,
            typename dummy = std::enable_if_t<std::is_base_of_v<std::exception, X>>,
            typename dummy1 = std::enable_if_t<std::is_constructible_v<X, const char*>>>
    [[noreturn]] void throw_x(const char*);

    template <typename X = std::exception,
            typename dummy = std::enable_if_t<std::is_base_of_v<std::exception, X>>,
            typename dummy1 = std::enable_if_t<std::is_default_constructible_v<X>>>
    [[noreturn]] void throw_x();
}

template<typename T, typename dummy>
constexpr T cmn::sum(T n) {
    return (n > 0)
    ? positive_sum(n)
    : (
        n == std::numeric_limits<T>::min()
            ? 0
            : -positive_sum(-n)
      );
}

template<typename T, typename dummy>
constexpr T cmn::positive_sum(T n) {
    return (n == std::numeric_limits<T>::max())
    ? 0
    : (
        n % 2 == 0 //n - чётное
            ? ( //если n чётное
                n/2 <= std::numeric_limits<T>::max()/(n+1) //если значение не выходит за диапазон
                    ? n*(n+1)/2 //возвращаем найденное значение
                    : 0 //при выходе за диапазон возвращаем 0
              )
            : ( //если n нечётное -> n + 1 чётное
                (n+1)/2 <= std::numeric_limits<T>::max()/n //если значение не выходит за диапазон
                    ? n*(n+1)/2 //возвращаем найденное значение
                    : 0 //при выходе за диапазон возвращаем 0
              )
      );
}

template<typename X, typename dummy, typename dummy1>
void cmn::throw_x(const char *text) {
    if (text) {
        std::cerr << text << '\n';
    } else {
        std::cerr << typeid(X).name() << " is thrown\n";
    }
    throw X(text);
}

template<typename X, typename dummy, typename dummy1>
void cmn::throw_x() {
    std::cerr << typeid(X).name() << " is thrown\n";
    throw X{};
}