/*
Разработать в виде методов операции над объектами класса:
сложение, вычитание, умножение, изменение отдельных частей и
получение/изменение параметров объектов (арифметику класса).
Результат выполнения в текущем объекте.
*/

#include "matr.h" /* Матрица и iostream */
#include <ctime>  /*time()*/

int main(void) {
	// Инициализация генератора случайных чисел
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Создание прямоугольной матрицы
	int m, n;
	std::cout << "Число строк: ";
	std::cin >> m;
	std::cout << "Число столбцов: ";
	std::cin >> n;

	Matrix &m1 = *new Matrix{m, n};
	std::cin >> m1;
	Matrix m2{m1};
	
	std::cout << "Матрица 1:\n" << m1;
	std::cout << "Матрица 2:\n" << m2;
	std::cout << "Матрица 2*1:\n" << m2 * m1;
	std::cout << "Матрица 1:\n" << m1;
	std::cout << "Матрица 2:\n" << m2;

	delete &m1;
	return EXIT_SUCCESS;
}
