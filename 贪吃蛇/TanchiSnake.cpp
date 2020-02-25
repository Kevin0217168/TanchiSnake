#include "TanchiSnake.h"

TanchiSnake::TanchiSnake(int width, int hight, int cell)
{
	this->WIDTH = width;
	this->HIGHT = hight;
	this->CELL = cell;
	this->ROW = (int)((this->WIDTH - 30) / CELL);
	this->COL = (int)((this->HIGHT - 70) / CELL);
}

// ���ɴ�MIX��MIN�������
int TanchiSnake::randint(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

// ���³�ʼ��ʳ�����꣬���ض���ָ��
TanchiSnake::Pos* TanchiSnake::init_food(vector<Pos>& snake)
{
A:
	Pos* food_pos = new Pos;
	food_pos->poses[0] = randint(0, ROW);
	food_pos->poses[1] = randint(0, COL);
	for (vector<Pos>::iterator it = snake.begin(); it < snake.end(); ++it)
	{
		if (if_overlap(*food_pos, *it))
		{
			goto A;
		}
	}
	return food_pos;
}

// ��Ϸ��ͼˢ��
void TanchiSnake::draw(RECT& fenshu_rect, RECT& title_rect, vector<Pos>& snake, Pos* food_pos)
{
	// ��յ�ǰ��Ļ
	cleardevice();

	// ������ left top   bottom      right
	rectangle(10, 50, WIDTH - 10, HIGHT - 10);// �����Ͻǵ����½ǻ�һ����

	// ����Ļ���Ͻ�������⣬�������
	drawtext(_T("̰���� [��ذ�]"), &title_rect, DT_LEFT);

	// ����Ļ���Ͻ������ǰ�������������
	drawtext(stringToLPCWSTR(string("����: ") + to_string(fenshu)), &fenshu_rect, DT_LEFT);

	// �����ߵ�λ��
	for (unsigned int i = 0; i < snake.size(); i++)
	{
		if (i == 0) {
			// �������ɫΪ��ɫ
			setfillcolor(BLUE);
		}
		else if (i == 1) {
			// �������ɫΪ��ɫ
			setfillcolor(RGB(255, 255, 255));
		}
		else if (i == snake.size() - 1) {
			// �������ɫΪ��ɫ
			setfillcolor(GREEN);
		}
		// ��������
		solidrectangle(10 + (snake[i].poses[0]) * 10, 50 + (snake[i].poses[1]) * 10, 10 + (snake[i].poses[0]) * 10 + 10, 50 + (snake[i].poses[1]) * 10 + 10);
	}

	// �������ɫΪ��ɫ
	setfillcolor(RED);
	// ����ʳ���λ��
	solidrectangle(10 + (food_pos->poses[0]) * 10, 50 + (food_pos->poses[1]) * 10, 10 + (food_pos->poses[0]) * 10 + 10, 50 + (food_pos->poses[1]) * 10 + 10);
}
bool TanchiSnake::if_hit_wall(vector<Pos>& snake)
{
	if (snake[0].poses[0] < 0 || snake[0].poses[0] > ROW || snake[1].poses[1] < 0 || snake[1].poses[1] > COL) {
		return true;
	}
	else {
		return false;
	}
}
bool TanchiSnake::if_overlap(Pos& a, Pos& b)
{
	if (a.poses[0] == b.poses[0] && a.poses[1] == b.poses[1]) {
		return true;
	}
	else {
		return false;
	}
}

bool TanchiSnake::if_hit_self(vector<Pos>& snake)
{
	for (vector<Pos>::iterator it = snake.begin() + 1; it < snake.end(); ++it)
	{
		if (if_overlap(snake[0], *it))
		{
			return true;
		}
	}
	return false;
}

bool TanchiSnake::if_reseve_xiang(string headxiang, string xiang)
{
	if (headxiang == "��" && xiang != "��" || headxiang == "��" && xiang != "��" || headxiang == "��" && xiang != "��" || headxiang == "��" && xiang != "��") {
		return false;
	}
	else
	{
		return true;
	}
}

// �����ƶ�����
int TanchiSnake::chage(vector<Pos>& snake, Pos& head_pos)
{
	// ��ͷ������һ���µ�Ԫ��
	snake.insert(snake.begin(), head_pos);
	// �ж��Ƿ�Ե�ʳ��
	if (if_overlap(head_pos, *p_food_pos))
	{
		// ��֮ǰ������Ӷ����ͷ�
		delete p_food_pos;
		// �Ե�ʳ�ʳ��λ�������趨���������β
		p_food_pos = init_food(snake);
		fenshu += 1;
	}
	else
	{
		// δ�Ե�ʳ������β
		snake.pop_back();
	}
	// �ж���ͷ��ײ�������ײ��ǽ��
	if (if_hit_self(snake) | if_hit_wall(snake))
	{
		// �رջ�ͼ����
		//closegraph();
		return 1;
	}
	return 0;
}

string TanchiSnake::move(vector<Pos>& snake, string xiang, string headxiang)
{
	Pos head_pos = snake[0];
	if (!(if_reseve_xiang(headxiang, xiang))) {
		if (xiang == "��") {
			head_pos.poses[1] -= 1;
		}
		else if (xiang == "��") {
			head_pos.poses[1] += 1;
		}
		else if (xiang == "��") {
			head_pos.poses[0] -= 1;
		}
		else if (xiang == "��") {
			head_pos.poses[0] += 1;
		}
		if (chage(snake, head_pos))
		{
			return "gameover";
		}
		return xiang;
	}
	else {
		// chage(snake, head_pos);
		return headxiang;
	}
}

// stringת��LPCWSTR����ʾ�ı�ʱʹ��
LPCWSTR TanchiSnake::stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
	return LPCWSTR();
}

// ���ƿ�ʼ����
void TanchiSnake::draw_start(void)
{
	// ��յ�ǰ��Ļ
	cleardevice();

	// ����ҳü���־�������
	static RECT yemei_rect = { 10,10,WIDTH - 10,45 };
	// ���ñ������־�������
	static RECT title_rect = { 100,(HIGHT / 2) - 100,WIDTH - 100,(HIGHT / 2) - 50 };
	// ����ҳ�����־�������
	static RECT yejiao_rect = { 10,HIGHT - 35,WIDTH - 10,HIGHT - 10 };

	// ���������С
	settextstyle(25, 0, _T("΢���ź�"));
	// �������Ϸ���ҳü
	drawtext(_T("���ĵĵ�һ��C++��Ϸ"), &yemei_rect, DT_LEFT);

	settextstyle(50, 0, _T("΢���ź�"));
	// ���ƴ��ı���
	drawtext(_T("̰ �� ��"), &title_rect, DT_CENTER);

	settextstyle(25, 0, _T("΢���ź�"));
	// �������·���ҳ��
	drawtext(_T("���¿ո������ʼ��Ϸ"), &yejiao_rect, DT_RIGHT);
}

// ���ƽ�������
void TanchiSnake::draw_gameover(void)
{
	static RECT over_rect = { 100,(HIGHT / 2) - 100,WIDTH - 100,(HIGHT / 2) - 50 };
	static RECT text_rect = { 50, (HIGHT / 2), WIDTH - 50,(HIGHT / 2) + 30 };

	// ��յ�ǰ��Ļ
	cleardevice();

	// ����������ɫΪ��ɫ
	settextcolor(RED);
	// ���������С
	settextstyle(50, 0, _T("΢���ź�"));
	// ���ƴ���GameOver
	drawtext(_T("Game Over"), &over_rect, DT_CENTER);

	// ����������ɫΪ��ɫ
	settextcolor(RGB(255, 255, 255));
	// ���������С
	settextstyle(30, 0, _T("΢���ź�"));
	// ����������ʾ
	drawtext(_T("��Ŷ����Ϸ�����������¿ո������"), &text_rect, DT_CENTER);
}

int TanchiSnake::start_the_game(void)
{
	// ��ʼ����ͼ����
	//          x      y      ����ʾ����̨
	initgraph(WIDTH, HIGHT);
	// ��������
	LOGFONT f;
	// ��õ�ǰ����
	gettextstyle(&f);
	// ���������ʽΪ�����
	f.lfQuality = ANTIALIASED_QUALITY;
start:
	// ��ʼҳ��
	fps_limit fps1(60);
	while (1)
	{
		draw_start();
		// �����¼��ж�
		if (_kbhit()) {
			// ���¿ո������
			if (_getch() == 32) {
				break;
			}
		}
		fps1.delay();
	}
	// ��������
	settextstyle(25, 0, _T("΢���ź�"));

	// ��������ʱ�洢
	int ch;
	// ���ֻ�������
	RECT title_rect = { 10, 10, 300, 40 };
	RECT fenshu_rect = { WIDTH - 100, 10, WIDTH - 10, 40 };

	// ��ʼ��С��λ��
	int middle_row = (int)(ROW / 2);
	int middle_col = (int)(COL / 2);
	vector<Pos> snake_pos(4);
	for (unsigned int i = 0; i < snake_pos.size(); i++)
	{
		snake_pos[i].poses[0] = middle_row - i + 1;
		snake_pos[i].poses[1] = middle_col;
	}

	// ��ʼ����ͷ����
	string headxiang = "��";

	// ��ʼ��ʳ��λ��
	p_food_pos = init_food(snake_pos);

	// ֡���Ǵ�
	int times = 0;
	// ��Ϸ��ѭ��
	fps_limit fps2(60);
	while (1) {
		// ֡������1
		times++;

		// �����Զ�����
		if (times % 10 == 0) {
			if (headxiang == "��") {
				headxiang = move(snake_pos, "��", headxiang);
			}
			else if (headxiang == "��") {
				headxiang = move(snake_pos, "��", headxiang);
			}
			else if (headxiang == "��") {
				headxiang = move(snake_pos, "��", headxiang);
			}
			else if (headxiang == "��") {
				headxiang = move(snake_pos, "��", headxiang);
			}
		}

		// �����¼��ж�
		if (_kbhit()) {//����а������£���_kbhit()����������
			//ʹ��_getch()������ȡ���µļ�ֵ
			ch = _getch();
			// �ϣ�72
			if (ch == 72) {
				//cout << "��" << endl
				headxiang = move(snake_pos, "��", headxiang);
			}
			// �£�80
			else if (ch == 80) {
				//cout << "��" << endl
				headxiang = move(snake_pos, "��", headxiang);
			}
			// ��75
			else if (ch == 75) {
				//cout << "��" << endl;
				headxiang = move(snake_pos, "��", headxiang);
			}
			// �ң�77
			else if (ch == 77) {
				//cout << "��" << endl;
				headxiang = move(snake_pos, "��", headxiang);
			}
			//������ESCʱ�˳���ESC���ļ�ֵΪ27.
			else if (ch == 27) {
				// �رջ�ͼ����
				closegraph();
				break;
			}
		}

		if (headxiang == "gameover") { break; }

		draw(fenshu_rect, title_rect, snake_pos, p_food_pos);

		if (times == 60)
		{
			times = 0;
		}
		fps2.delay();
	}
	// ����ҳ��
	fps_limit fps3(60);
	while (1)
	{
		draw_gameover();
		// �����¼��ж�
		if (_kbhit()) {
			// ���¿ո������
			if (_getch() == 32) {
				fenshu = 0;
				goto start;
			}
		}
		fps3.delay();
	}
	
	system("pause");
	return 0;
}
