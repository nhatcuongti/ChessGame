#ifndef  _HEADER_H_
#define _HEADER_H_
#include <iostream>
#include <string>
using namespace std;

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
	Chessman PosOpposite[16]; // Mang chua thong tin vi tri quan co cua doi thu
	int nO; // So luong quan co cua doi thu tren ban co
	Chessman PosMySelf[16]; // MAng chua thong tin vi tri quan co cua minh
	int nM; // So luong quan co cua minh tren ban co
	int turn; // turn = 1 : quan co nam duoi, turn = 2 : quan co nam o tren
public:
	Player(int turn);
	~Player();
	void takePos(Board& Chess);
	bool checkWin(); // Check xem minh da thang chua

	bool checkKMove(); // Check xem quan co cua doi thu con di duoc khong. True: Quan co cua doi thu khong con duong di
//	bool checkRoadWin();// True: Neu doi phuong khong con nuoc di de bao ve VUA
};

void GameChess();
#endif // ! _HEADER_H_
