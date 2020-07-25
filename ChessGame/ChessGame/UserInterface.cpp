#include "Header.h"

void GameChess() {
	Board chessBoard;
	int turn = 1;	 // Luot di
	bool checkMove = true;	 // Check xem nuoc di co hop le hay khong
	while (true)
	{
		Player PlayerMan(turn);
		chessBoard.show(); // Hien ra bang co 
		Move oldPos, newPos;
		//Nhap vi tri hien tai				
		if (!checkMove) // Neu nhu nuoc di truoc do khong hop le
			cout << "Your choice isn't valid !! Choose again" << endl;
		cout << "It is Turn " << turn << endl;
		cout << "Press first position " << endl;
		cout << "Row: "; cin >> oldPos.row;
		cout << "Column: "; cin >> oldPos.column;
		//Nhap vi tri muon di toi				
		cout << endl;
		cout << "Press new position you want to move " << endl;
		cout << "Row: "; cin >> newPos.row;
		cout << "Column: "; cin >> newPos.column;
		checkMove = PlayerMan.checkMove(oldPos, newPos);
		if (checkMove)
		{
			chessBoard.updateData(oldPos, newPos);
			turn = (turn % 2) + 1; // Luot di tiep theo
		}
		if (PlayerMan.checkWin() && PlayerMan.checkKMove())
			cout << "Player " << (turn % 2) + 1 << " WIN !!!" << endl;
		system("CLS");
	}
}