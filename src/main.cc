/*
Разработать в виде методов операции над объектами класса:
сложение, вычитание, умножение, изменение отдельных частей и
получение/изменение параметров объектов (арифметику класса).
Результат выполнения в текущем объекте.
*/

#include "matr.h"   /* Матрица */
#include <ctime>    /*time()*/
#include <iostream> /*cout*/

int main(void) {
	// Инициализация генератора случайных чисел
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Создание прямоугольной матрицы
	int m, n;
	std::cout << "Число строк: ";
	std::cin >> m;
	std::cout << "Число столбцов: ";
	std::cin >> n;
	Matrix & heapm = *new Matrix(m, n);
	std::cout << "Конечные размеры матрицы: " << heapm.get_line_count()
		  << " на " << heapm.get_row_count() << '\n';

	std::cout << "Матрица до:\n";
	heapm.randomise(0, 9).print();

	std::cout << "Матрица после:\n";
	heapm.transpose().print();

	delete &heapm;
	return EXIT_SUCCESS;
}
