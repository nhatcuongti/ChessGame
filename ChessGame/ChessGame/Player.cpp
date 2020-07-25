#include "Header.h"

int Ma_r[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int Ma_c[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

int Vua_r[8] = { -1,-1,-1,0,0,1,1,1 };
int Vua_c[8] = { -1,0,1,-1,1,-1,0,1 };

int dlr[4] = { 1, -1, 0, 0 };
int dlc[4] = { 0, 0, -1, 1 };

int dhr[4] = { 1, -1, 1, -1 };
int dhc[4] = { 1, 1, -1, -1 };

int dKr[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int dKc[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };



//************************Hao**************************//
int kindChessman(int row, int column)
{
	string chessCheck = boardChess[row][column];
	if (chessCheck[0] == 'X')
		return 0;
	if (chessCheck[0] == 'M')
		return 1;
	if (chessCheck[0] == 'T')
		return 2;
	if (chessCheck[0] == 'K')
		return 3;
	if (chessCheck[0] == 'Q')
		return 4;
	return 5;
}

void Player::takePos()
{
	PosMySelf = new Chessman[20];
	PosOpposite = new Chessman[20];
	nM = 0;
	nO = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (boardChess[i][j] != "|")
			{
				if (typeChessman(i, j, boardChess) == turn)
				{
					PosMySelf[nM].row = i;
					PosMySelf[nM].column = j;
					PosMySelf[nM].type = kindChessman(i, j);
					nM++;
				}
				else
				{
					PosOpposite[nO].row = i;
					PosOpposite[nO].column = j;
					PosOpposite[nO].type = kindChessman(i, j);
					nO++;
				}
			}
}

int checkExit(int xCheck, int yCheck, Chessman* Pos, int n)
{
	for (int i = 0; i < n; i++)
	{
		if ((Pos[i].row == xCheck) && (Pos[i].column == yCheck))
		{
			return  Pos[i].type;
		}
	}
	return -1;
}

bool checkLine(Move first, Move final, int turn, string Board[20][20])
{
	for (int i = 0; i < 4; i++)
	{
		int rowCurrnet = first.row + dlr[i];
		int columnCurrent = first.column + dlc[i];
		while (true)
		{
			if (!checkOutside(rowCurrnet, columnCurrent))
				break;
			if (typeChessman(rowCurrnet, columnCurrent, Board) == turn)//Kiem tra quan dong minh khong
				break;
			if (final.row == rowCurrnet && final.column == columnCurrent)//Kiem tra xem o do co phai la o can den chua
				return true;
			if (typeChessman(rowCurrnet, columnCurrent, Board) != 0)
				break;

			rowCurrnet += dlr[i];
			columnCurrent += dlc[i];
		}
	}
	return false;
}

bool checCheo(Move first, Move final, int turn, string Board[20][20])
{
	for (int i = 0; i < 4; i++)
	{
		int rowCurrnet = first.row + dhr[i];
		int columnCurrent = first.column + dhc[i];
		while (true)
		{
			if (!checkOutside(rowCurrnet, columnCurrent))
				break;
			if (typeChessman(rowCurrnet, columnCurrent, Board) == turn)//Kiem tra quan dong minh khong
				break;
			if (final.row == rowCurrnet && final.column == columnCurrent)//Kiem tra xem o do co phai la o can den chua
				return true;
			if (typeChessman(rowCurrnet, columnCurrent, Board) != 0)
				break;

			rowCurrnet += dhr[i];
			columnCurrent += dhc[i];
		}
	}
	return false;
}

bool checkKnight(Move first, Move final, int turn, string Board[20][20])
{
	for (int i = 0; i < 8; i++)
	{
		int rowCurrent = first.row + dKr[i];
		int columnCurrent = first.column + dKc[i];
		if (!checkOutside(rowCurrent, columnCurrent))
			continue;
		if (typeChessman(rowCurrent, columnCurrent, Board) != turn)//Kiem tra quan dong minh khong
			if (final.row == rowCurrent && final.column == columnCurrent)//Kiem tra xem o do co phai la o can den chua
				return true;
	}
	return false;
}

bool checkTot(Move first, Move final, int turn, string Board[20][20])
{
	Move dTot[4];
	dTot[0].column = -1;
	dTot[1].column = 0;
	dTot[2].column = 1;
	if (turn == 1)
		dTot[0].row = dTot[1].row = dTot[2].row = -1;
	else
		dTot[0].row = dTot[1].row = dTot[2].row = 1;

	bool dd = false;
	for (int i = 0; i < 2; i++)
	{
		int rowCurrent = first.row + dTot[i].row;
		int columnCurrent = first.column + dTot[i].column;
		if (!checkOutside(first.row + dTot[i].row, first.column + dTot[i].column))
			continue;
		int type = typeChessman(rowCurrent, columnCurrent, Board);
		if (i != 1)
		{
			if (type == turn || type == 0)
				continue;
		}
		else
		{
			if (type == 0)
				dd = true;
			else
				continue;
		}
		if (rowCurrent == final.row && columnCurrent == final.column)
			return true;
	}
	int rowCheck = first.row + dTot[2].row * 2;
	int columnCheck = first.column;
	if ((rowCheck != final.row) || (columnCheck != final.column))
		return false;

	if (turn == 1)
		if (first.row != 6)
			return false;
	if (turn == 2)
		if (first.row != 1)
			return false;
	if (!checkOutside(rowCheck, columnCheck))
		return false;

	if (dd && typeChessman(rowCheck, columnCheck, Board) == 0)
		return true;
	return false;
}

bool checkKing(Move first, Move final, int turn, string Board[20][20])
{
	for (int i = 0; i < 4; i++)
		if (checkOutside(first.row + dlr[i], first.column + dlc[i]))
			if (typeChessman(first.row + dlr[i], first.column + dlc[i], Board) != turn)
				if (first.row + dlr[i] == final.row && first.column + dlc[i] == final.column)
					return true;
	for (int i = 0; i < 4; i++)
		if (checkOutside(first.row + dhr[i], first.column + dhc[i]))
			if (typeChessman(first.row + dhr[i], first.column + dhc[i], Board) != turn)
				if (first.row + dhr[i] == final.row && first.column + dhc[i] == final.column)
					return true;
	return false;
}

void Player::killPos()
{
	nM = 0;
	nO = 0;
	delete[] PosMySelf;
	delete[] PosOpposite;
	PosMySelf = NULL;
	PosOpposite = NULL;
}

bool checkRoad(Move firstMove, Move finalMove, int turn, int kindChessman, string boardChess[20][20])
{
	// Check nuoc di
	if (kindChessman == 0) // Neu la xe
	{
		if (!checkLine(firstMove, finalMove, turn, boardChess))
			return false;
	}
	else if (1 == kindChessman) // Neu la Ngua
	{
		if (!checkKnight(firstMove, finalMove, turn, boardChess))
			return false;
	}
	else if (2 == kindChessman) // Neu la tuong
	{
		if (!checCheo(firstMove, finalMove, turn, boardChess))
			return false;
	}
	else if (3 == kindChessman) // Neu la vua
	{
		if (!checkKing(firstMove, finalMove, turn, boardChess))
			return false;
	}
	else if (4 == kindChessman) // Neu la hau
	{
		if (!checkLine(firstMove, finalMove, turn, boardChess) && !checCheo(firstMove, finalMove, turn, boardChess))
			return false;
	}
	else if (5 == kindChessman)
	{
		if (!checkTot(firstMove, finalMove, turn, boardChess))
			return false;
	}
	return true;
}

bool checkEatKing(Move kingMove, Chessman* Pos, int n, int turn, string B[20][20])
{
	for (int i = 0; i < n; i++)
	{
		Move firstMove;
		firstMove.row = Pos[i].row;
		firstMove.column = Pos[i].column;
		if (checkRoad(firstMove, kingMove, turn, Pos[i].type, B))
			return false;
	}
	return true;
}

bool Player::checkMove(Move firstMove, Move finalMove)
{
	takePos();
	if (!checkOutside(finalMove.row, finalMove.column)) // check xem co lot ra ngoai ko
		return false;
	int kindChessman = checkExit(firstMove.row, firstMove.column, PosMySelf, nM);
	if (kindChessman == -1)
	{
		killPos();
		return false;
	}
	// check nuoc di
	if (!checkRoad(firstMove, finalMove, turn, kindChessman, boardChess))
		return false;
	// Lay vi tri con vua
	Move kingMove;
	if (3 == kindChessman)
	{
		kingMove.row = finalMove.row;
		kingMove.column = finalMove.column;
	}
	else
		for (int i = 0; i < nM; i++)
			if (PosMySelf[i].type == 3)
			{
				kingMove.row = PosMySelf[i].row;
				kingMove.column = PosMySelf[i].column;
				break;
			}

	string B[20][20];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			B[i][j] = boardChess[i][j];
	B[finalMove.row][finalMove.column] = B[firstMove.row][finalMove.column];
	B[firstMove.row][firstMove.column] = "|";
	Chessman Postmp[20];
	int nTmp = 0;
	for (int i = 0; i < nO; i++)
		if (finalMove.row != PosOpposite[i].row || finalMove.column != PosOpposite[i].column)
			Postmp[nTmp++] = PosOpposite[i];

	int turnOpposite = (turn == 2) ? 1 : 2;
	if (!checkEatKing(kingMove, Postmp, nTmp, turnOpposite, B))
		return false;
	return true;
	killPos();
}

Player::~Player() {
	if (PosOpposite != NULL)
		delete[]PosOpposite;
	PosOpposite = NULL;
	nO = 0;
	if (PosMySelf != NULL)
		delete[]PosMySelf;
	nM = 0;
	PosMySelf = NULL;
}
//*****************************************************//



//********************PHUOC****************************//
void Player::takePos( Board& Chess) {
	string type[6] = { "X","M","T","K","Q","t" };
	string a[8][8];
	Chess.Get_data(a);
	string s = to_string(this->turn);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (a[i][j] != "|") {

				if (a[i][j].find(s) == -1) {

					PosOpposite[nO].row = i;
					PosOpposite[nO].column = j;
					for (int k = 0; k < 6; k++) {
						if (a[i][j].find(type[k]) != -1) {
							PosOpposite[nO].type = k;
							break;
						}
					}
					nO += 1;

				}
				else {
					PosMySelf[nM].row = i;
					PosMySelf[nM].column = j;
					for (int k = 0; k < 6; k++) {
						if (a[i][j].find(type[k]) != -1) {
							PosMySelf[nM].type = k;
							break;
						}
					}
					nM += 1;
				}
			}
		}
	}
}

void Tick_Chessman(int** a, Chessman quanta[], int nM, Chessman quandich[], int nO) {
	for (int i = 0; i < nM; i++) {
		a[quanta[i].row][quanta[i].column] = -1;
	}

	for (int i = 0; i < nO; i++) {
		if (quandich[i].type == 3) continue;
		a[quandich[i].row][quandich[i].column] = -2;
	}
}

void TickRoad_Xe(int** a, const Chessman& xe) {
	int row = xe.row, column = xe.column;
	while (row > 0&&a[row - 1][xe.column] >=0) {
		a[row - 1][xe.column] = 1;
		row -= 1;
	}
	row = xe.row;
	while ( row < 7&&a[row + 1][xe.column] >=0) {
		a[row + 1][xe.column] = 1;
		row += 1;
	}
	row = xe.row;
	while (column>0&&a[xe.row][column - 1]>=0) {
		a[xe.row][column - 1] = 1;
		column -= 1;
	}
	column = xe.column;
	while (column<7&&a[xe.row][column + 1] >=0) {
		a[xe.row][column + 1] = 1;
		column += 1;
	}
	return;
}

void TickRoad_Ma(int** a, Chessman ma) {
	for (int i = 0; i < 8; i++) {
		if ( ma.row + Ma_r[i] > -1 && ma.row + Ma_r[i]<8 && ma.column + Ma_c[i]>-1 && ma.column + Ma_c[i] < 8&&a[ma.row + Ma_r[i]][ma.column + Ma_c[i]] >=0 ) {
			a[ma.row + Ma_r[i]][ma.column + Ma_c[i]] = 1;
		}
	}
}

void TickRoad_Tinh(int** a, Chessman tinh) {
	int row = tinh.row, column = tinh.column;

	while (true) {
		row += 1;
		column += 1;
		if (column<8&&row<8&&a[row][column] >=0) {
			a[row][column] = 1;
		}
		else break;
	}


	row = tinh.row;
	column = tinh.column;
	while (true) {
		row -= 1;
		column -= 1;
		if (column>-1&&row>-1&&a[row][column] >=0) {
			a[row][column] = 1;
		}
		else break;
	}

	row = tinh.row;
	column = tinh.column;
	while (true) {
		row += 1;
		column -= 1;
		if (column>-1&&row<8&&a[row][column] >=0) {
			a[row][column] = 1;
		}
		else break;
	}

	row = tinh.row;
	column = tinh.column;
	while (true) {
		row -= 1;
		column += 1;
		if (column<8 && row>-1&&a[row][column] >=0) {
			a[row][column] = 1;
		}
		else break;
	}

	return;
}

void TickRoad_Hau(int** a, const Chessman& hau) {
	TickRoad_Tinh(a, hau);
	TickRoad_Xe(a, hau);
}

void TickRoad_tot(int** a, const Chessman& tot,int type) {
	if (type == 1) {
		if (tot.row > 0 && tot.column > 0 && a[tot.row - 1][tot.column - 1] >=0) a[tot.row - 1][tot.column - 1] = 1;
		if (tot.row > 0 && tot.column <7 && a[tot.row - 1][tot.column + 1] >=0) a[tot.row - 1][tot.column + 1] = 1;
	}
	else {
		if (tot.row < 7 && tot.column > 0 && a[tot.row + 1][tot.column - 1] >= 0) a[tot.row + 1][tot.column - 1] = 1;
		if (tot.row < 7 && tot.column < 7 && a[tot.row + 1][tot.column + 1] >= 0)  a[tot.row + 1][tot.column + 1] = 1;
	}
}

void TickRoad_Vua(int** a, const Chessman& vua) {
	for (int i = 0; i < 8; i++) {
		if (vua.row + Vua_r[i] > -1 && vua.row + Vua_r[i]<8 && Vua_c[i] + vua.column > -1 && Vua_c[i] + vua.column < 8 && a[vua.row + Vua_r[i]][Vua_c[i] + vua.column] >= 0) a[vua.row + Vua_r[i]][Vua_c[i] + vua.column] = 1;
	}
}


bool Player::checkWin() { // Check xem minh da thang chua
	
	int** arr; 
	arr = new int* [8];
	for (int i = 0; i < 8; i++) {
		arr[i] = new int[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			arr[i][j] = 0;
		}
	}
	Tick_Chessman(arr, PosMySelf, nM, PosOpposite, nO);
	for (int i = 0; i < nM;i++) {
		switch (PosMySelf[i].type)
		{
		case 0: {
			TickRoad_Xe(arr, PosMySelf[i]);
			break;
		}
		case 1: {
			TickRoad_Ma(arr, PosMySelf[i]);
			break;
		}
		case 2: {
			TickRoad_Tinh(arr, PosMySelf[i]);
			break;
		}
		case 3: {
			TickRoad_Vua(arr, PosMySelf[i]);
			break;
		}
		case 4: {
			TickRoad_Hau(arr, PosMySelf[i]);
			break;
		}
		case 5: {
			TickRoad_tot(arr, PosMySelf[i], this->turn);
			break;
		}
		default:
			break;
		}
	}

	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[i][j] == 0) cout << " _ ";
			else {
				if (arr[i][j] > 0) cout <<" "<< arr[i][j] << " ";
				else cout << arr[i][j] << " ";

			}

		}
		cout << endl;
	}*/
	for (int i = 0; i < nO; i++) {
		if (PosOpposite[i].type == 3 && arr[PosOpposite[i].row][PosOpposite[i].column] == 1) return 1;
	}
	return 0;
}


bool Player::checkKMove() {
	int** arr;
	arr = new int* [8];
	for (int i = 0; i < 8; i++) {
		arr[i] = new int[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			arr[i][j] = 0;
		}
	}
	Tick_Chessman(arr, PosMySelf, nM, PosOpposite, nO);
	for (int i = 0; i < nM; i++) {
		switch (PosMySelf[i].type)
		{
		case 0: {
			TickRoad_Xe(arr, PosMySelf[i]);
			break;
		}
		case 1: {
			TickRoad_Ma(arr, PosMySelf[i]);
			break;
		}
		case 2: {
			TickRoad_Tinh(arr, PosMySelf[i]);
			break;
		}
		case 3: {
			TickRoad_Vua(arr, PosMySelf[i]);
			break;
		}
		case 4: {
			TickRoad_Hau(arr, PosMySelf[i]);
			break;
		}
		case 5: {
			TickRoad_tot(arr, PosMySelf[i], this->turn);
			break;
		}
		default:
			break;
		}
	}

	for (int i = 0; i < nO; i++) {
		if (PosOpposite[i].type == 3) {
			for (int j = 0; j < 8; j++) {
				if (PosOpposite[i].row + Vua_r[j] < 8 && PosOpposite[i].row + Vua_r[j] >= 0 && PosOpposite[i].column + Vua_c[j] < 8 && PosOpposite[i].column + Vua_c[j] >= 0 && arr[PosOpposite[i].row + Vua_r[j]][PosOpposite[i].column + Vua_c[j] == 0]) return 1;
			}
		}
	}
	return 0;
}
//*****************************************************//