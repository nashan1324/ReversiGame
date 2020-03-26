#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace std;

/*
盤面9x9
*/
const int ROW = 8;
const int COL = 8;
const int PLAYERONE = 1;
const int PLAYERTWO = -1;


//盤の描画
void drawField(vector<vector<int>> field) {
	system("cls");
for (int i = 0; i < ROW+1; ++i) {
	for (int j = 0; j < COL+1; ++j) {
		//列番号
		if (i == 0) {
			//どうしても9まで書き込んじゃう。
			cout << " " << j + 1;

		}
		//行番号
		else if (j == 0) {
			cout << i;

		}
		//盤の表示
		else {
			//駒なし
			if (field[i-1][j-1] == 0) {
				cout << " .";
			}
			//駒白
			else if (field[i-1][j-1] == PLAYERONE) {
				cout << "◯";
			}
			//駒黒
			else {
				cout << "●";
			}
		}
	}
	cout << endl;
}
}

//プレイヤー入力時のチェック
bool validCheck(int playerNum,int row,int col,vector<vector<int>> field) {
	//入力が盤に収まっているか
	if (row < 1 || row > ROW || col < 1 || col > COL) {
		cout << "値が不正" << endl;
		return false;
	}
	//駒と重なっていないか
	if (field[row - 1][col - 1] != 0) {
		cout << "他の駒と重複" << endl;
		return false;
	}
	//周りに相手の駒があるかチェック
	bool isValid = false;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			//上3マス除外
			if (row == 1) {
				if (col == 1) {
					if (field[row + i][col + j] == -playerNum) {
						isValid = true;
					}
				}
				else if (col == 8) {
					if (field[row + i][col + j - 2] == -playerNum) {
						isValid = true;
					}
				}
				else {
					if (field[row + i][col + j - 1] == -playerNum) {
						isValid = true;
					}
				}
			}
			//下3マス
			else if (row == 8) {
				if (col == 1) {
					if (field[row + i - 2][col + j] == -playerNum) {
						isValid = true;
					}
				}
				else if (col == 8) {
					if (field[row + i - 2][col + j - 2] == -playerNum) {
						isValid = true;
					}
				}
				else {
					if (field[row + i - 2][col + j - 1] == -playerNum) {
						isValid = true;
					}
				}
			}
			//右3マス
			else if (col == 1) {
				if (row == 1) {
					if (field[row + i][col + j] == -playerNum) {
						isValid = true;
					}
				}
				else if (row == 8) {
					if (field[row + i - 2][col + j] == -playerNum) {
						isValid = true;
					}
				}
				else {
					if (field[row + i - 1][col + j] == -playerNum) {
						isValid = true;
					}
				}
			}
			//左3マス
			else if (col == 8) {
				if (row == 1) {
					if (field[row + i][col + j - 2] == -playerNum) {
						isValid = true;
					}
				}
				else if (row == 8) {
					if (field[row + i - 2][col + j - 2] == -playerNum) {
						isValid = true;
					}
				}
				else {
					if (field[row + i - 1][col + j - 2] == -playerNum) {
						isValid = true;
					}
				}
			}
			//それ以外
			else {
				if (field[row + i - 1][col + j - 1] == -playerNum) {
					isValid = true;
				}
			}
		}
	}
	if (isValid) {
		return true;
	}
	else {
		cout << "周りに敵の駒がありません" << endl;
		return false;
	}
}

//挟まれている駒を裏返す
void turnOver(int playerNum, int row, int col, vector<vector<int>>& field) {
	int srow, scol;
	//左 
	for (int i = col-1;i >= 0; --i) {
		if (field[row][i] == playerNum) {
			scol = i;
			for (int j = col - 1; j >= scol; --j) {
				field[row][j] = playerNum;
			}
			break;
		}
		else if(field[row][i] == 0){
			break;
		}
	}
	//右
	for (int i = col + 1; i < COL; ++i) {
		if (field[row][i] == playerNum) {
			scol = i;
			for (int j = col + 1; j <= scol; ++j) {
				field[row][j] = playerNum;
			}
			break;
		}
		else if(field[row][i] == 0){
			break;
		}
	}
	//上
	for (int i = row-1;i >= 0; --i) {
		if (field[i][col] == playerNum) {
			srow = i;
			for (int j = row - 1; j >= srow; --j) {
				field[j][col] = playerNum;
			}
			break;
		}
		else if(field[i][col] == 0){
			break;
		}
	}
	//下
	for (int i = row+1;i < ROW; ++i) {
		if (field[i][col] == playerNum) {
			srow = i;
			for (int j = row + 1; j <= srow; ++j) {
				field[j][col] = playerNum;
			}
			break;
		}
		else if(field[i][col] == 0){
			break;
		}
	}
	//斜め左上
	bool isBreak = false;
	for (int i = row - 1; i >= 0; --i) {
		for (int j = col - 1; j >= 0; --j) {
			if (i - j == row - col) {
				if (field[i][j] == playerNum) {
					srow = i, scol = j;
					//裏返し
					for (int i = row - 1; i > srow; --i) {
						for (int j = col - 1; j > scol; --j) {
							if (i - j == row - col) {
								field[i][j] = playerNum;
							}
						}
					}
					break;
				}
				else if (field[i][j] == 0) {
					isBreak = true;
					break;
				}
			}
		}
		if (isBreak) {
			break;
		}
	}
	isBreak = false;
	//斜め左下
	for (int i = row + 1; i < ROW; ++i) {
		for (int j = col + 1; j < COL; ++j) {
			if (i - j == row - col) {
				if (field[i][j] == playerNum) {
					srow = i, scol = j;
					//裏返し
					for (int i = row + 1; i < srow; ++i) {
						for (int j = col + 1; j < scol; ++j) {
							if (i - j == row - col) {
								field[i][j] = playerNum;
							}
						}
					}
					break;
				}
				else if (field[i][j] == 0) {
					isBreak = true;
					break;
				}
			}
		}
		if (isBreak) {
			break;
		}
	}
	isBreak = false;
	//右上
	for (int i = row - 1; i >= 0; --i) {
		for (int j = col + 1; j < COL; ++j) {
			if (i + j == row + col) {
				if (field[i][j] == playerNum) {
					srow = i, scol = j;
					//裏返し
					for (int i = row - 1; i > srow; --i) {
						for (int j = col + 1; j < scol; ++j) {
							if (i + j == row + col) {
								field[i][j] = playerNum;
							}
						}
					}
					break;
				}
				else if (field[i][j] == 0) {
					isBreak = true;
					break;
				}
			}
		}
		if (isBreak) {
			break;
		}
	}
	isBreak = false;
	//右下
	for (int i = row + 1; i < ROW; ++i) {
		for (int j = col - 1; j >= 0; --j) {
			if (i + j == row + col) {
				if (field[i][j] == playerNum) {
					srow = i, scol = j;
					//裏返し
					for (int i = row + 1; i < srow; ++i) {
						for (int j = col - 1; j > scol; --j) {
							if (i + j == row + col) {
								field[i][j] = playerNum;
							}
						}
					}
					break;
				}
				else if (field[i][j] == 0) {
					isBreak = true;
					break;
				}
			}
		}
		if (isBreak) {
			break;
		}
	}
}

//プレイヤーのコントローラー
void playerControler(int playerNum,vector<vector<int>>& field) {
	int row = 1, col = 1;
	if (playerNum == PLAYERONE) {
		while (1) {
			cout << "◯プレイヤー１：" << flush;
			cin >> row >> col;
			cout << endl;
			if (validCheck(playerNum, row, col, field)) {
				field[row-1][col-1] = PLAYERONE;
				break;
			}
		}
	}
	else {
		while (1) {
			cout << "●プレイヤー２：" << flush;
			cin >> row >> col;
			cout << endl;
			if (validCheck(playerNum, row, col, field)) {
				field[row-1][col-1] = PLAYERTWO;
				break;
			}
		}
	}
	turnOver(playerNum, row-1, col-1, field);
}

//ゲームの終了判定
bool judgeEnd(vector<vector<int>> field) {
	int playerCounter[] = { 0,0 };
	for (vector<int>& vec : field) {
		for (int& elem : vec) {
			if (elem == PLAYERONE) {
				++playerCounter[0];
			}
			else if (elem == PLAYERTWO) {
				++playerCounter[1];
			}
			else {
				return true;
			}
		}
	}
	system("cls");
	cout << "ゲーム終了" << endl;
	cout << "プレイヤー１の駒数:" << playerCounter[0] << endl;
	cout << "プレイヤー２の駒数:" << playerCounter[1] << endl;
	return false;
}

int main() {
	//オセロの盤を格納する配列
	vector<vector<int>> field(ROW, vector<int>(COL, 0));

	//盤の状態を初期化
	field[3][3] = PLAYERONE, field[4][4] = PLAYERONE;
	field[3][4] = PLAYERTWO, field[4][3] = PLAYERTWO;

	//ゲームのメインループ
	int playerNum = PLAYERONE;
	bool stillPlaying = true;
	while (stillPlaying) {
		drawField(field);
		playerControler(playerNum, field);
		playerNum *= -1;
		stillPlaying = judgeEnd(field);
	}

	return 0;
}