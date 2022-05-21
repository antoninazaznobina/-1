// Зазнобина А.В. КИ20-06Б
// Алгоритм шифрования Хилла
#include <iostream>		// Работа со стандартным вводом-выводом C++
#include <cstdlib>		// Работа со стандартной билиотекой C
#include <iomanip>		// Библиотека для форматирования вывода текста
#include <Windows.h>	// Для использования кодировки кириллицы в Windows


using namespace std;

void FMatrMinor(int **A, int **B, int i, int j, int m);	// Вспомогательная функция для FDet
int FDet(int **A, int m);								// Вычисление определителя
void FMatrInvers(int **A, int **Ainv, int m);			// Вычисление обратной матрицы
//void FPrintMatr(int **A, int m);						// Вывод матрицы на экран

int main()
{
	setlocale(LC_ALL, "rus");		// Установка кириллицы для консоли
	SetConsoleCP(1251);				// Установка кириллицы для ввода
	SetConsoleOutputCP(1251);		// Установка кириллицы для вывода
//------------------------------------------------------------------------
	const int Nalf = 37;			// Количество символов в алфавите
	int i, j, k;					// Индексы для циклов

	// Алфавит: символы
	const char AlfSmb[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя.,- ";
	cout << "Алфавит (символы): |";
	for (i = 0; i < Nalf; i++)
	{
		cout << AlfSmb[i] << " ";
	}
	cout << "|" << endl;
	// Алфавит: коды
	int AlfCod[Nalf];				// Алфавит в виде кодов
	for (i = 0; i < Nalf; i++)
	{
		AlfCod[i] = i;
	}
	cout << "Алфавит (коды):";
	for (i = 0; i < Nalf; i++)
	{
		cout << AlfCod[i] << " ";
	}
	cout << endl;

	// Ключ шифра - матрица
	int Ncod = 2;
	int KeyCod[2][2] = { 2, 5, 3, 8 };
	cout << "Ключ шифра - Матрица:" << endl;
	cout.setf(ios::right);
	for (i = 0; i < Ncod; i++)
	{
		for (j = 0; j < Ncod; j++)
		{
			cout << setw(3) << KeyCod[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	// Исходный текст для шифрования
	char TxtVecSmb[200];
	cout << "Исходный текст для шифрования (в конце поставить !): ";
	cin.get(TxtVecSmb, 200);

	// Подсчёт числа символов во введённом тексте
	int Ntxt = 0;					//Число символов во введённом тексте
	while (TxtVecSmb[Ntxt] != '!')
	{
		Ntxt++;
	}

	// Кодирование исходного текста
	int *TxtVecCod;					// Объявление указателя массива для кодированного текста для последующего создания динамического массива
	TxtVecCod = new int[Ntxt];		// Создание динамического массива для кодов исходного текста в соответствии с его реальным размером
	for (k = 0; k < Ntxt; k++)
	{
		for (j = 0; j < Nalf; j++)
		{
			if (TxtVecSmb[k] == AlfSmb[j])
			{
				TxtVecCod[k] = AlfCod[j];
				break;
			}
		}
	}
	cout << "Закодированный исходный текст:" << endl;
	for (i = 0; i < Ntxt; i++)
	{
		cout << TxtVecCod[i] << " ";
	}
	cout << endl;

	// ШИФРОВАНИЕ ЗАДАННОГО ИСХОДНОГО ТЕКСТА

	// Формирование матрицы кодов исходного текста
	int NtxtMtr = 1 + Ntxt / 3;			// Число строк в матрице кодов исходного текста
	int **TxtMtrCod;					// Указатель на указатели для формирования 2-мерного массива из одномерного
	TxtMtrCod = new int*[NtxtMtr];		// Создание динамического массива для матрицы (пока одномерного массива)

	int ktxt;							// Счётчик символов кодов исходного текста
	for (i = 0; i < NtxtMtr; i++)
	{
		TxtMtrCod[i] = new int[3];		// Создание динамического одномерного массива i-той строки матрицы
		for (j = 0; j < 3; j++)
		{
			ktxt = i * 3 + j;			// Расчёт очередного номера кода символа в строке исходного текста
			if (ktxt < Ntxt) TxtMtrCod[i][j] = TxtVecCod[ktxt];	// Если коды в строке исходного текста не закончились, то записывается очередной код
			if (ktxt >= Ntxt) TxtMtrCod[i][j] = Nalf - 1;		// Если коды закончились, то оставшиеся позициии заполняются последним кодом алфавита
		}
	}

	// Шифрование исходного текста умножением матрицы кода текста на матрицу-ключ
	int **TxtMtrCfr;
	TxtMtrCfr = new int*[NtxtMtr * 3];
	int d;
	for (k = 0; k < NtxtMtr; k++)
	{
		TxtMtrCfr[k] = new int[3];
		for (j = 0; j < 3; j++)
		{
			d = 0;
			for (i = 0; i < 3; i++)
			{
				d = d + TxtMtrCod[k][i] * KeyCod[i][j];
			}
			TxtMtrCfr[k][j] = d % Nalf;						// Деление каждого кода по модулю Nalf (размер алфавита)
		}
	}
	cout << "Матрица кодов исходного текста:" << "  ";
	cout << "Матрица кодов текста после шифрования:" << endl;

	for (k = 0; k < NtxtMtr; k++)
	{
		for (j = 0; j < Ncod; j++)
		{
			cout << setw(3) << TxtMtrCod[k][j] << " ";
		}
		cout << "                      ";
		for (j = 0; j < Ncod; j++)
		{
			cout << setw(3) << TxtMtrCfr[k][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;


	// Преобразование матрицы кодов зашифрованного текста в вектор кодов
	int *TxtVecCfr;
	int NtxtVec = NtxtMtr * 3;
	TxtVecCfr = new int[NtxtVec];
	for (i = 0; i < NtxtMtr; i++)
	{
		for (j = 0; j < 3; j++)
		{
			TxtVecCfr[i * 3 + j] = TxtMtrCfr[i][j];
		}
	}

	// Декодирование зашифрованного текста
	char *TxtStrCfr;
	TxtStrCfr = new char[NtxtVec];
	for (i = 0; i < NtxtVec; i++)
	{
		for (j = 0; j < Nalf; j++)
		{
			if (TxtVecCfr[i] == AlfCod[j])
			{
				TxtStrCfr[i] = AlfSmb[j];
				break;
			}
		}
	}

	cout << "Исходный текст:      |";
	for (i = 0; i < Ntxt; i++)
	{
		cout << TxtVecSmb[i];
	}
	cout << "|" << endl;

	cout << "Зашифрованный текст: |";
	for (i = 0; i < NtxtVec; i++)
	{
		cout << TxtStrCfr[i];
	}
	cout << "|" << endl;

	// ДЕШИФРОВАНИЕ ЗАДАННОГО ШИФРОВАННОГО ТЕКСТА

	// Обратная матрица-ключ
	int **KeyCodInv;
	int **A;
	int m = 3;
	KeyCodInv = new int*[m];
	A = new int*[m];
	for (i = 0; i < 3; i++) KeyCodInv[i] = new int[m];
	for (i = 0; i < 3; i++)
	{
		A[i] = new int[3];
		for (j = 0; j < 3; j++)
		{
			A[i][j] = KeyCod[i][j];
		}
	}
	FMatrInvers(A, KeyCodInv, m);
	cout << "Ключ шифра - Обратная матрица по модулю 37:" << endl;
	for (i = 0; i < Ncod; i++)
	{
		for (j = 0; j < Ncod; j++)
		{
			cout << setw(3) << KeyCodInv[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;


	// Умножение матрицы зашифрованного текста на обратную матрицу-ключ
	int **TxtMtrDec;
	TxtMtrDec = new int*[NtxtMtr];
	for (k = 0; k < NtxtMtr; k++)
	{
		TxtMtrDec[k] = new int[3];
		for (j = 0; j < 3; j++)
		{
			d = 0;
			for (i = 0; i < 3; i++)
			{
				d = d + TxtMtrCfr[k][i] * KeyCodInv[i][j];
			}
			TxtMtrDec[k][j] = d % Nalf;						// Деление каждого кода по модулю Nalf (размер алфавита)
			if (TxtMtrDec[k][j] < 0) TxtMtrDec[k][j] = Nalf + TxtMtrDec[k][j];
		}
	}

	// Преобразование матрицы кодов зашифрованного текста в вектор кодов
	int *TxtVecDec;
	TxtVecDec = new int[NtxtVec];
	for (i = 0; i < NtxtMtr; i++)
	{
		for (j = 0; j < 3; j++)
		{
			TxtVecDec[i * 3 + j] = TxtMtrDec[i][j];
		}
	}

	// Декодирование дешифрованного текста
	char *TxtStrDec;
	TxtStrDec = new char[NtxtVec];
	for (i = 0; i < NtxtVec; i++)
	{
		for (j = 0; j < Nalf; j++)
		{
			if (TxtVecDec[i] == AlfCod[j])
			{
				TxtStrDec[i] = AlfSmb[j];
				break;
			}
		}
	}
	cout << "Дешифрованный текст: |";
	for (i = 0; i < NtxtVec; i++)
	{
		cout << TxtStrDec[i];
	}
	cout << "|" << endl;
	cin.get(); cin.get();
	return 0;
}

// Формирование матрицы для вычисления минора
void FMatrMinor(int **A, int **B, int i, int j, int m)
{
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < m - 1; ki++)			// Исключение строки
	{
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < m - 1; kj++)		// Исключение столбца
		{
			if (kj == j) dj = 1;
			B[ki][kj] = A[ki + di][kj + dj];
		}
	}
}

// Вычисление определителя матрицы
int FDet(int **A, int m)
{
	int i, j, d, k, n;
	int **B;
	B = new int*[m];
	for (i = 0; i < m; i++) B[i] = new int[m];
	j = 0; d = 0;
	k = 1;
	n = m - 1;
	if (m == 1)
	{
		d = A[0][0];			// В матрице 1 элемент
		return(d);
	}
	if (m == 2)					// В матрице 2 элемента
	{
		d = (A[0][0] * A[1][1]) - (A[1][0] * A[0][1]);
		return(d);
	}
	if (m > 2)					// В матрице более 2 элементов
	{
		for (i = 0; i < m; i++)	// Вычисление по первому столбцу
		{
			FMatrMinor(A, B, i, 0, m);
			d = d + k * A[i][0] * FDet(B, n);	// Рекурсивный вызов этой же функции.
			k = -k;
		}
	}
	return(d);
}

// Формирование обратной матрицы
void FMatrInvers(int **A, int **Ainv, int m)
{
	int i, j, k, d;
	int **B;
	int **Adop;
	d = FDet(A, m);
	B = new int*[m];
	for (i = 0; i < m; i++) B[i] = new int[m];
	Adop = new int*[m];
	for (i = 0; i < m; i++) Adop[i] = new int[m];
	k = 1;
	for (i = 0; i < m; i++)
	{
		Adop[i] = new int[m];
		for (j = 0; j < m; j++)
		{
			FMatrMinor(A, B, i, j, m);
			Adop[i][j] = k * FDet(B, m - 1);
			k = -k;
		}
	}
	for (i = 0; i < m; i++)
	{
		Ainv[i] = new int[m];
		for (j = 0; j < m; j++)
		{
			Ainv[i][j] = Adop[j][i] / d;
		}
	}

	return;
}