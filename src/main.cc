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

	Matrix m1{m,n};
	m1.randomise(80, 0).print();
	Matrix &m2 = *new Matrix{m1};
	m2.transpose();

	(m1*=m2).transpose().print();
	m1 = m2;
	m1.print();

	delete &m2;

	return EXIT_SUCCESS;
}
