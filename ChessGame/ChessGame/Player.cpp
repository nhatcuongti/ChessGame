#include "Header.h"

int Ma_r[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int Ma_c[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

int Vua_r[8] = { -1,-1,-1,0,0,1,1,1 };
int Vua_c[8] = { -1,0,1,-1,1,-1,0,1 };


Player::Player(int num) {
	turn = num;
	nM = 0;
	nO = 0;
	
}
Player::~Player() {

}
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
