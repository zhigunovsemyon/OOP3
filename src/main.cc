/*
Арифметику реализовать в виде стандартного набора переопределённых операций с
арифметической интерпретацией. Результат операции -- новый объект. Разработать
конструктор копирования, переопределить арифметические операции, присваивание,
сравнение, ввод и вывод в стандартные потоки.
*/
#include "matr.h" /* Матрица и iostream */

int main(void)
{
	// Создание прямоугольной матрицы
	int m, n;
	std::cout << "Число строк: ";
	std::cin >> m;
	std::cout << "Число столбцов: ";
	std::cin >> n;

	/*Проверка на корректность ввода*/
	if (!std::cin.good()) {
		std::cout << "Некорректный ввод!\n";
		return EXIT_FAILURE;
	}

	for (auto i{0}; i < 1000; ++i) {
		Matrix & m1 = *new Matrix{m, n};
		m1.randomise(10);

		std::cout << "Матрица 1:\n" << m1 << '\n';

		m1[-1][-1] = 0; // Замена значения на ноль
		std::cout << "Элемент справа внизу: " << m1[-1][-1] << '\n';

		delete &m1;
	}
	return EXIT_SUCCESS;
}
