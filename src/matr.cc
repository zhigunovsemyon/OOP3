#include "matr.h"
#include <cstring>  /*std::memcpy()*/
#include <iostream> /*std::size_t; std::rand(); std::cout*/
#include <utility>  /*swap() */

// Вывод трассировки
std::ostream & trace = std::cout;

void Matrix::constructor_(long const lines, long const rows) {
	::trace << "Адрес созданного объекта: " << this << '\n';

	if (lines <= 0 || rows <= 0) {
		this->row_count_ = this->line_count_ = 0;
		this->ptr_ = nullptr;
		return;
	}

	// Задание числа строк
	this->line_count_ = lines;
	this->row_count_ = rows;

	// Выделение памяти под вектор указателей
	this->ptr_ = new int *[static_cast<std::size_t>(lines)];
	::trace << "Адрес созданной памяти: " << this->ptr_ << '\n';

	// Выделение памяти под каждую строку
	for (long i = 0; i < lines; i++) {
		this->ptr_[i] = new int[static_cast<std::size_t>(rows)];
		::trace << "Выделение памяти под строку " << i
			<< " по адресу: " << this->ptr_[i] << '\n';
	}
}

// Конструктор квадратной матрицы, либо пустой
Matrix::Matrix(long const size) {
	// Вызов конструктора
	this->constructor_(size, size);
	// Зануление матрицы
	this->zero();
}

// Конструктор прямоугольной матрицы матрицы
Matrix::Matrix(long const lines, long const columns) {
	// Вызов конструктора
	this->constructor_(lines, columns);
	// Зануление матрицы
	this->zero();
}

Matrix::Matrix(Matrix const & other) {
	// Создание новой матрицы с идентичной размерностью
	this->constructor_(other.line_count_, other.row_count_);

	/*Копирование содержимого другой матрицы в данную*/
	for (long i = 0; i < other.line_count_; ++i) {
		std::memcpy(this->ptr_[i], other.ptr_[i],
			    sizeof(ptr_[i][0]) * (std::size_t)other.row_count_);
	}
}

// Деструктор
Matrix::~Matrix() {
	while (this->line_count_--) {
		// Трассировка каждой удаляемой строки
		::trace << "Номер удаляемой строки: " //
			<< this->line_count_	      //
			<< "; Её адрес: " << this->ptr_[this->line_count_]
			<< '\n';
		delete[] this->ptr_[this->line_count_];
	}

	// Трассировка удаляемой матрицы
	::trace << "Адрес удаляемой памяти: " //
		<< this->ptr_ << ';'	      //
		<< " В объекте под адресом: " << this << '\n';
	delete[] this->ptr_;
}

// Вывод матрицы в stdout
void Matrix::print() const {
	for (long i = 0; i < this->line_count_; i++) {
		for (long j = 0; j < this->row_count_; j++)
			std::cout << ptr_[i][j] << ' ';

		std::cout << '\n';
	}
}

/*Метод для заполнения матрицы случайными числами*/
Matrix & Matrix::randomise(int max, int min) {
	/*Переворот значений min и max*/
	if (min > max)
		std::swap(max, min);

	for (long i = 0; i < this->line_count_; i++) {
		for (long j = 0; j < this->row_count_; j++)
			this->ptr_[i][j] = min + std::rand() % (max + 1 - min);
	}

	return *this;
}

/*Метод зануления матрицы*/
Matrix & Matrix::fill_with(int const num) {
	for (long i = 0; i < this->line_count_; i++) {
		for (long j = 0; j < this->row_count_; j++)
			ptr_[i][j] = num;
	}

	return *this;
}

/*Доступ к определённой строке line матрицы*/
int & Matrix::get_element(long line, long column) const {
	/*Если пользователь запросил отрицательный элемент, отсчитывается
	 *соответствующий элемент с конца*/
	if (column < 0)
		column = this->row_count_ + column;
	if (line < 0)
		line = this->line_count_ + line;

	// Возврат ссылки на соответствующую ячейку
	return this->ptr_[line][column];
}

// Возврат false при неудаче, true при успехе
bool Matrix::set_element(long line, long column, int num) {
	/*Если пользователь указал отрицательный элемент, отсчитывается
	 *соответствующий элемент с конца*/
	if (column < 0)
		column = this->row_count_ + column;
	if (line < 0)
		line = this->line_count_ + line;

	/*Если итоговый индекс отрицательный, запись не осуществляется*/
	if (line < 0 || column < 0)
		return false;

	/*Если итоговый индекс за пределами матрицы, запись не осуществляется*/
	if (line >= this->line_count_ || column >= this->row_count_)
		return false;

	/*Запись элемента, возврат флага успешной записи*/
	this->ptr_[line][column] = num;
	return true;
}

Matrix & Matrix::fill(long line, long column) {
	/*Если пользователь указал отрицательный элемент, отсчитывается
	 *соответствующий элемент с конца*/
	if (column < 0)
		column = this->row_count_ + column;
	if (line < 0)
		line = this->line_count_ + line;

	/*Если итоговый индекс отрицательный, запись не осуществляется*/
	if (line < 0 || column < 0)
		return *this;

	for (long i = line; i < this->line_count_; ++i) {
		for (long j = column; j < this->row_count_; ++j) {
			std::cout << '[' << i << "][" << j << "] = ";
			std::cin >> this->ptr_[i][j];
		}
	}

	return *this;
}

/*Добавление к данной матрице другой матрицы other.
 * !Матрицы должны быть одинаковых размеров!*/
Matrix & Matrix::add(Matrix const & other) {
	// Если размеры не совпадают, аварийное завершение функции
	if (other.row_count_ != this->row_count_ ||
	    other.line_count_ != this->line_count_) {
		std::cerr << "Сложение матриц разных размерностей!\n";
		return *this;
	}

	// Добавление элементов другой матрицы к данной
	for (long i = 0; i < this->line_count_; i++) {
		for (long j = 0; j < this->row_count_; j++)
			this->ptr_[i][j] += other.ptr_[i][j];
	}
	return *this;
}

/*Вычитание из данной матрицы другой матрицы other.
 * !Матрицы должны быть одинаковых размеров!*/
Matrix & Matrix::substract(Matrix const & other) {
	// Если размеры не совпадают, аварийное завершение функции
	if (other.row_count_ != this->row_count_ ||
	    other.line_count_ != this->line_count_) {
		std::cerr << "Вычитание матриц разных размерностей!\n";
		return *this;
	}

	// Вычитание элементов другой матрицы из данной матрицы.
	for (long i = 0; i < this->line_count_; i++) {
		for (long j = 0; j < this->row_count_; j++)
			this->ptr_[i][j] -= other.ptr_[i][j];
	}

	return *this;
}

void Matrix::calcCellForMult_(Matrix const & first, Matrix const & second,
			      int const line, int const row) {
	int & cell = this->ptr_[line][row];

	for (int i{0}; i < first.row_count_; ++i)
		cell += first.ptr_[line][i] * second.ptr_[i][row];
}

/*Уиножение данной матрицы на другую матрицу other.
 * !Матрицы должны быть одинаковых размеров!*/
Matrix & Matrix::multiply(Matrix const & other) {
	// Если размеры не совпадают, аварийное завершение функции
	if (this->row_count_ != other.line_count_) {
		std::cerr << "Умножение не согласованных матриц!\n";
		return *this;
	}
	// Локальная копия текущей матрицы
	// Временная матрица, в которую будет сохранятся результат
	Matrix Tmp{this->line_count_, other.row_count_};

	// Подсчёт каждой ячейки
	for (int i{0}; i < Tmp.row_count_; ++i) {
		for (int j{0}; j < Tmp.line_count_; ++j)
			Tmp.calcCellForMult_(*this, other, i, j);
	}

	// Подстановка временной матрицы на место текущей
	std::swap(Tmp.ptr_, this->ptr_);
	std::swap(Tmp.line_count_, this->line_count_);
	std::swap(Tmp.row_count_, this->row_count_);
	return *this;
}

bool Matrix::isEqualTo(Matrix const & other) const {
	// Если размеры не совпадают, значит они не совпадают априори
	if (other.row_count_ != this->row_count_ ||
	    other.line_count_ != this->line_count_) {
		return false;
	}

	// Перебор каждого элемента
	for (int i{0}; i < other.line_count_; ++i) {
		for (int j{0}; j < other.row_count_; ++j) {
			if (this->ptr_[i][j] != other.ptr_[i][j])
				return false;
		}
	}
	return true; // Матрицы равны
}

Matrix & Matrix::transposeNonSq_() {
	// Создание пустой матрицы транспонированного размера
	Matrix Tmp{this->row_count_, this->line_count_};

	// Перенос значений из старой матрицы в новую
	for (int i{0}; i < this->line_count_; ++i) {
		for (int j{0}; j < this->row_count_; ++j)
			Tmp.ptr_[j][i] = this->ptr_[i][j];
	}

	// Перестановка значений для деструкторов
	std::swap(Tmp.ptr_, this->ptr_);
	std::swap(line_count_, row_count_);
	std::swap(Tmp.line_count_, Tmp.row_count_);
	return *this;
}

Matrix & Matrix::transposeSq_() {
	for (int i{1}; i < this->row_count_; ++i) {
		for (int j{0}; j < i; ++j)
			std::swap(this->ptr_[j][i], this->ptr_[i][j]);
	}
	return *this;
}
