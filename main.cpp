#include "core.h"
/*
 * программа читает ввод из файла и пишет результат в другой файл.
 * чтобы всё работало на компе, отличном от компа разработчика,
 * нужно указать валидные пути к для входных и выходных данных
 * в файле common.h, строчки 13, 14
 */
int main() {
    /*
     * первый параметр шаблона - максимальное количество вершин во входном графе,
     * которое определяет максимальное количество рёбер во входном графе.
     * его можно установить в файле common.h в строчке 15
     * второй параметр шаблона - тип, который достаточен для представления всего множества значений,
     * которые могут принимать веса рёбер
     */
    core::kruskal_algorithm<max_vertexes, int>();
    std::cout << "end\n";
    return 0;
}