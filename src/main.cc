/*
Арифметику реализовать в виде стандартного набора переопределённых операций с
арифметической интерпретацией. Результат операции -- новый объект. Разработать
конструктор копирования, переопределить арифметические операции, присваивание,
сравнение, ввод и вывод в стандартные потоки.
*/
#include "matr.h" /* Матрица и iostream */

int main(void)
{
	Matrix m{2};
	std::cin >> m;
	std::cout << m;
	
	return EXIT_SUCCESS;
}
