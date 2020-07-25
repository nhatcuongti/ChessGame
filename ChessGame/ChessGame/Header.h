#ifndef  _HEADER_H_
#define _HEADER_H_
#include <iostream>
#include <string>
using namespace std;

extern int dlr[4];
extern int dlc[4];

extern int dhr[4];
extern int dhc[4];

extern int dKr[8];
extern int dKc[8];

extern string boardChess[20][20];


struct Move {
	int row; // Hang
	int column;// Cot
};

struct Chessman {
	int row, column;  // Hang va Cot
	int type; // 0: Xe, 1: Ngua, 2: Tinh, 3 : Vua, 4: Hau, 5: Tot
};

class Board {
private:
	int n; // kich thuoc o vuong co vua
	string** data; // Ma tran n * n chua tat ca thong tin tren ban co
public:
	Board(); // Khoi tao du lieu vao data;
	~Board();
	void show(); // Show thong tin tren ban co
	int checkMove(Move first, Move final, int turn); // Check xem nuoc di co hop le hay khong
	void updateData(Move first, Move final); // Cap nhat du lieu tren ban co 
	friend void assignDataToPlayer(Chessman &Pos, int &n, Board B, int turn); // Dua du lieu cua data vao mang Pos
	void Get_data(string a[8][8]);
};

class Player {
private:
	Chessman* PosOpposite; // Mang chua thong tin vi tri quan co cua doi thu
	int nO; // So luong quan co cua doi thu tren ban co
	Chessman* PosMySelf; // MAng chua thong tin vi tri quan co cua minh
	int nM; // So luong quan co cua minh tren ban co
	int turn; // turn = 1 : quan co nam duoi, turn = 2 : quan co nam o tren
public:
	Player(int turn) {
		this->turn = turn;
		PosMySelf = NULL;
		PosOpposite = NULL;
	}
	~Player();
	void takePos();
	void takePos(Board& Chess);
	void killPos();
	bool checkMove(Move firstMove, Move nextMove);
	bool checkWin(); // Check xem minh da thang chua = checkKmove && checkROadWin
	bool checkKMove(); // Check xem quan co cua doi thu con di duoc khong. True: Quan co cua doi thu khong con duong di
	//	bool checkRoadWin();// True: Neu doi phuong khong con nuoc di de bao ve VUA
};

int typeChessman(int row, int column, string data[20][20]);
bool checkOutside(int row, int column); //False : Neu vi tri nam o ngoai ban co

void GameChess();
#endif // ! _HEADER_H_
