#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace std;

/*
�Ֆ�9x9
*/
const int ROW = 8;
const int COL = 8;
const int PLAYERONE = 1;
const int PLAYERTWO = -1;


//�Ղ̕`��
void drawField(vector<vector<int>> field) {
	system("cls");
for (int i = 0; i < ROW+1; ++i) {
	for (int j = 0; j < COL+1; ++j) {
		//��ԍ�
		if (i == 0) {
			//�ǂ����Ă�9�܂ŏ������񂶂Ⴄ�B
			cout << " " << j + 1;

		}
		//�s�ԍ�
		else if (j == 0) {
			cout << i;

		}
		//�Ղ̕\��
		else {
			//��Ȃ�
			if (field[i-1][j-1] == 0) {
				cout << " .";
			}
			//�
			else if (field[i-1][j-1] == PLAYERONE) {
				cout << "��";
			}
			//�
			else {
				cout << "��";
			}
		}
	}
	cout << endl;
}
}

//�v���C���[���͎��̃`�F�b�N
bool validCheck(int playerNum,int row,int col,vector<vector<int>> field) {
	//���͂��ՂɎ��܂��Ă��邩
	if (row < 1 || row > ROW || col < 1 || col > COL) {
		cout << "�l���s��" << endl;
		return false;
	}
	//��Əd�Ȃ��Ă��Ȃ���
	if (field[row - 1][col - 1] != 0) {
		cout << "���̋�Əd��" << endl;
		return false;
	}
	//����ɑ���̋���邩�`�F�b�N
	bool isValid = false;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			//��3�}�X���O
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
			//��3�}�X
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
			//�E3�}�X
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
			//��3�}�X
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
			//����ȊO
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
		cout << "����ɓG�̋����܂���" << endl;
		return false;
	}
}

//���܂�Ă����𗠕Ԃ�
void turnOver(int playerNum, int row, int col, vector<vector<int>>& field) {
	int srow, scol;
	//�� 
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
	//�E
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
	//��
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
	//��
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
	//�΂ߍ���
	bool isBreak = false;
	for (int i = row - 1; i >= 0; --i) {
		for (int j = col - 1; j >= 0; --j) {
			if (i - j == row - col) {
				if (field[i][j] == playerNum) {
					srow = i, scol = j;
					//���Ԃ�
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
	//�΂ߍ���
	for (int i = row + 1; i < ROW; ++i) {
		for (int j = col + 1; j < COL; ++j) {
			if (i - j == row - col) {
				if (field[i][j] == playerNum) {
					srow = i, scol = j;
					//���Ԃ�
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
	//�E��
	for (int i = row - 1; i >= 0; --i) {
		for (int j = col + 1; j < COL; ++j) {
			if (i + j == row + col) {
				if (field[i][j] == playerNum) {
					srow = i, scol = j;
					//���Ԃ�
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
	//�E��
	for (int i = row + 1; i < ROW; ++i) {
		for (int j = col - 1; j >= 0; --j) {
			if (i + j == row + col) {
				if (field[i][j] == playerNum) {
					srow = i, scol = j;
					//���Ԃ�
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

//�v���C���[�̃R���g���[���[
void playerControler(int playerNum,vector<vector<int>>& field) {
	int row = 1, col = 1;
	if (playerNum == PLAYERONE) {
		while (1) {
			cout << "���v���C���[�P�F" << flush;
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
			cout << "���v���C���[�Q�F" << flush;
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

//�Q�[���̏I������
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
	cout << "�Q�[���I��" << endl;
	cout << "�v���C���[�P�̋:" << playerCounter[0] << endl;
	cout << "�v���C���[�Q�̋:" << playerCounter[1] << endl;
	return false;
}

int main() {
	//�I�Z���̔Ղ��i�[����z��
	vector<vector<int>> field(ROW, vector<int>(COL, 0));

	//�Ղ̏�Ԃ�������
	field[3][3] = PLAYERONE, field[4][4] = PLAYERONE;
	field[3][4] = PLAYERTWO, field[4][3] = PLAYERTWO;

	//�Q�[���̃��C�����[�v
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