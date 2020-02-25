#include <graphics.h> // ����ͼ�ο�ͷ�ļ�
#include <conio.h> // drow
#include <chrono> // Key
#include <vector> // list
#include <cstdlib> // Header file needed to use srand and rand
#include <ctime> // Header file needed to use time
#include <cstdlib>// system
#include <string> // string
#include "Fps.h"

using namespace std;

class TanchiSnake
{
public:
	// ���캯��
	TanchiSnake(int, int, int);
	// ��Ϸ���
	int start_the_game(void);

private:
	// ��
	int WIDTH = 520;
	// ��
	int HIGHT = 520;
	// ÿ����λ����Ĵ�С
	int CELL = 10;
	// �����������
	int ROW = (int)((WIDTH - 20) / CELL);
	// �����������
	int COL = (int)((HIGHT - 60) / CELL);
	// ������������ṹ
	struct Pos {
		// �÷������Ͻ�����
		int poses[2];
	};
	// ʳ������ָ��
	Pos* p_food_pos;
	// �Ʒְ�
	int fenshu = 0;

	// ���ɴ�MIX��MIN�������
	int randint(int, int);
	// ������Ϸ�����к���
	void draw(RECT&, RECT&, vector<Pos>&, Pos*);
	// ����ʳ��λ��
	Pos* init_food(vector<Pos>&);
	// �ж��Ƿ�ײ��ǽ��
	bool if_hit_wall(vector<Pos>&);
	// �ж��������Ƿ��ص�
	bool if_overlap(Pos&, Pos&);
	// �ж��Ƿ�ײ���Լ�
	bool if_hit_self(vector<Pos>&);
	// �жϷ����Ƿ��෴
	bool if_reseve_xiang(string, string);
	// ��̰���߸���λ��
	int chage(vector<Pos>&, Pos&);
	// stringת��LPCWSTR����ʾ�ı�ʱʹ��
	LPCWSTR stringToLPCWSTR(string);
	// ����̰�����ƶ�����
	string move(vector<Pos>&, string, string);
	// ���ƿ�ʼ����
	void draw_start(void);
	// ���ƽ�������
	void draw_gameover(void);
};
