/*
Арифметику реализовать в виде стандартного набора переопределённых операций с
арифметической интерпретацией. Результат операции -- новый объект. Разработать
конструктор копирования, переопределить арифметические операции, присваивание,
сравнение, ввод и вывод в стандартные потоки.
*/
#include "matr.h" /* Матрица и iostream */

int main(void)
{
	Matrix m{ };
	std::cin >> m;
	/*int n;
	std::cin >> n*/;
	std::cout << m;
	//std::cout << n;
	
	return EXIT_SUCCESS;
}
