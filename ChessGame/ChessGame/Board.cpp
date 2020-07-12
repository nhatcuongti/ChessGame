#include "Header.h"

int dlr[4] = { 1, -1, 0, 0 };
int dlc[4] = { 0, 0, -1, 1 };

int dhr[4] = { 1, -1, 1, -1 };
int dhc[4] = { 1, 1, -1, -1 };

int dKr[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int dKc[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

string Board_defaultChess(int column) // Tra ve quan co mac dinh ban dau
{
	if (column == 0 || column == 7)
		return "X";
	if (column == 1 || column == 6)
		return "M";
	if (2 == column || 5 == column)
		return "T";
	if (3 == column )
		return "K";
	if (4 == column)
		return "Q";
	return NULL;
}

Board::Board()
{
	this->n =  8;
	data = new string * [8];
	for (int i = 0; i < n; i++)
		data[i] = new string[8];

	// Khoi tao cac gia tri '-' cho mang 2 chieu data
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			data[i][j] = "|";

	// Tao quan co mac dinh ban dau
	for (int column = 0; column < 8; column++) // Duyet cot
	{
		string chessman = Board_defaultChess(column);
		data[0][column] = chessman + '2'; // O tren
		data[7][column] = chessman + '1'; // Quan co o duoi
		data[1][column] = "t2";
		data[6][column] = "t1";
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
}

int typeChessman(int row, int column, string**data)
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

bool checkMove_checkXe(Move first, Move final, string** data, int turn)
{
	for (int i = 0; i < 4; i++)
	{
		int rowCheck = first.row;
		int columnCheck = first.column;
		while (true)
		{
			rowCheck += dlr[i];
			columnCheck += dlc[i];
			if (data[rowCheck][columnCheck] != "|")
			{
				if (typeChessman(rowCheck, columnCheck, data) != turn && (rowCheck == final.row && columnCheck == final.column))
					return true;
				break;
			}
			if (!checkOutside(rowCheck, columnCheck))
				break;
			if (rowCheck == final.row && columnCheck == final.column)
				return true;
		}
	}
	return false;
}

bool checkMove_checkTinh(Move first, Move final, string** data, int turn)
{
	for (int i = 0; i < 4; i++)
	{
		int rowCheck = first.row;
		int columnCheck = first.column;
		while (true)
		{
			rowCheck += dhr[i];
			columnCheck += dhc[i];
			if (data[rowCheck][columnCheck] != "|")
			{
				if (typeChessman(rowCheck, columnCheck, data) != turn && (rowCheck == final.row && columnCheck == final.column))
					return true;
				break;
			}
			if (!checkOutside(rowCheck, columnCheck))
				break;
			if (rowCheck == final.row && columnCheck == final.column)
				return true;
		}
	}
	return false;
}

bool checkMove_checkNgua(Move first, Move final, string** data, int turn)
{
	for (int i = 0; i < 8; i++)
	{
		int rowCheck = first.row + dKr[i];
		int columnCheck = first.column + dKc[i];
		if (typeChessman(rowCheck, columnCheck, data) != turn)
			return true;
	}
	return false;
}

bool checkMove_checkHau(Move first, Move final, string** data, int turn)
{
	return (checkMove_checkXe(first, final, data, turn) || checkMove_checkTinh(first, final, data, turn));
}

bool checkMove_checkTot(Move first, Move final, string** data, int turn)
{
	int dr[2] = { -1, 1 }; // Nuoc di thang
	int drK[2][2] = { -1, -1, 1, 1 };  // Nuoc di an duoc quan co
	int dcK[2][2] = { 1, -1, 1, -1 };  // Nuoc di an duoc quan co

	int k = turn - 1;
	int rowCheck = first.row + dr[k];
	int columnCheck = first.column;
	if (rowCheck == final.row && columnCheck == final.column)
		if (typeChessman(rowCheck, columnCheck, data) == 0)
			return true;
	//Check duong an cua quan tot
	for (int i = 0; i < 2; i++)
	{
		rowCheck = first.row + drK[k][i];
		columnCheck = first.column + dcK[k][i];
		if (rowCheck == final.row && columnCheck == final.column)
			if (typeChessman(rowCheck, columnCheck, data) != turn)
				return true;
	}
	return false;
}

bool isCheckmate(int row, int column, int turn, string** data) // True : neu tai vi tri nay con vua bi chieu
{
	// xet duong di cua xe
	for (int i = 0; i < 4; i++)
	{
		int rowCheck = row;
		int columnCheck = column;
		while (true)
		{
			rowCheck += dlr[i];
			columnCheck += dlc[i];
			if (data[rowCheck][columnCheck] != "|")
			{
				if (typeChessman(rowCheck, columnCheck, data) != turn )
					if (data[rowCheck][columnCheck][0] == 'Q' || data[rowCheck][columnCheck][0] == 'X')
						return true;
				break;
			}
			if (!checkOutside(rowCheck, columnCheck))
				break;
		}
	}
	//Xet duong an cua ngua
}

int Board::checkMove(Move first, Move final, int turn)// 0: Di duoc, 1: KHong di duoc boi vi bi chieu, 2: Di sai , 3 : Chon sai quan co
{
	// TH chon sai quan co
	string checkChess = data[first.row][final.column];
	int numberCheck = (checkChess[1] - '0');
	if (numberCheck != turn)
		return 3;
	//TH vt moi cung quan								
	if (typeChessman(final.row, final.column, data) == turn)//Vi tri moi co quan cua minh hay khong
		return 2;
	//Vi tri moi bi sai
	
	
}