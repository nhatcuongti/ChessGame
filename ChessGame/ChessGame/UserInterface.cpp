#include "Header.h"

void GameChess(){
	Board chessBoard;
	while (true)
	{
		chessBoard.show(); // Hien ra bang co 
		Move oldPos, newPos;			
		//Nhap vi tri hien tai							
		cout << "Press position chessman " << endl;
		cout << "Row: "; cin >> oldPos.row;
		cout << "Column: "; cin >> oldPos.column;
		//Nhap vi tri muon di toi						
		cout << "Press new position you want to move " << endl;
		cout << "Row: "; cin >> newPos.row;
		cout << "Column: "; cin >> newPos.column;

		chessBoard.updateData(oldPos, newPos);
		system("CLS");
	}
}