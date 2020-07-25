#include "Header.h"

string boardChess[20][20];

string Board_defaultChess(int column) // Tra ve quan co mac dinh ban dau
{
	if (column == 0 || column == 7)
		return "X";
	if (column == 1 || column == 6)
		return "M";
	if (2 == column || 5 == column)
		return "T";
	if (3 == column)
		return "K";
	if (4 == column)
		return "Q";
	return NULL;
}

void swap(string& a, string& b)
{
	string tam = a;
	a = b;
	b = tam;
}

Board::Board()
{
	this->n = 8;
	data = new string * [8];
	for (int i = 0; i < n; i++)
		data[i] = new string[8];

	// Khoi tao cac gia tri '-' cho mang 2 chieu data
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			data[i][j] = "|";
			boardChess[i][j] = "|";
		}

	// Tao quan co mac dinh ban dau
	for (int column = 0; column < 8; column++) // Duyet cot
	{
		string chessman = Board_defaultChess(column);
		data[0][column] = chessman + '2'; // O tren
		boardChess[0][column] = data[0][column];
		data[7][column] = chessman + '1'; // Quan co o duoi
		boardChess[7][column] = data[7][column];
		data[1][column] = "t2";
		boardChess[1][column] = data[1][column];
		data[6][column] = "t1";
		boardChess[6][column] = "t1";
	}
}

Board::~Board()
{
	for (int i = 0; i < n; i++)
		delete[] data[i];
	delete[] data;
}

void Board::show()
{
	cout << "  ";
	for (int i = 0; i < 8; i++)
		cout << i << "  ";
	cout << endl << endl;

	for (int row = 0; row < n; row++)
	{
		cout << row << " ";
		for (int column = 0; column < n; column++)
		{
			cout << data[row][column];
			if (data[row][column] == "|")
				cout << data[row][column]; // In ra them mot dau '|' nua de can bang voi phan tren
			if (column == 7) // Neu nhu o cot cuoi cung thi nen xuong dong
				cout << endl;
			else
				cout << " ";
		}
		cout << endl; // Moi lan chay het hang cot thi phai cach.
	}
}

void Board::updateData(Move first, Move final)
{
	data[final.row][final.column] = data[first.row][first.column]; //Vi tri moi se la vi tri cua con co
	data[first.row][first.column] = "|"; // Vi tri cu se doi thanh '|'
	boardChess[final.row][final.column] = boardChess[first.row][first.column];
	boardChess[first.row][first.column] = "|";
}

int typeChessman(int row, int column, string data[20][20])
{
	string checkChess = data[row][column];
	if (checkChess == "|")
		return 0;
	int numberCheck = (checkChess[1] - '0');
	return numberCheck;
}

bool checkOutside(int row, int column) //False : Neu vi tri nam o ngoai ban co
{
	if (row < 0 || row > 7)
		return false;
	if (column < 0 || column > 7)
		return false;
	return true;
}

void Board::Get_data(string a[8][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			a[i][j] = data[i][j];
}

