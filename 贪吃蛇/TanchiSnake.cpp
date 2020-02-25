#include "TanchiSnake.h"

TanchiSnake::TanchiSnake(int width, int hight, int cell)
{
	this->WIDTH = width;
	this->HIGHT = hight;
	this->CELL = cell;
	this->ROW = (int)((this->WIDTH - 30) / CELL);
	this->COL = (int)((this->HIGHT - 70) / CELL);
}

// 生成从MIX到MIN的随机数
int TanchiSnake::randint(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

// 重新初始化食物坐标，返回堆中指针
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

// 游戏绘图刷新
void TanchiSnake::draw(RECT& fenshu_rect, RECT& title_rect, vector<Pos>& snake, Pos* food_pos)
{
	// 清空当前屏幕
	cleardevice();

	// 画矩形 left top   bottom      right
	rectangle(10, 50, WIDTH - 10, HIGHT - 10);// 从左上角到右下角画一个框

	// 在屏幕左上角输出标题，并左对齐
	drawtext(_T("贪吃蛇 [典藏版]"), &title_rect, DT_LEFT);

	// 在屏幕右上角输出当前分数，并左对齐
	drawtext(stringToLPCWSTR(string("分数: ") + to_string(fenshu)), &fenshu_rect, DT_LEFT);

	// 绘制蛇的位置
	for (unsigned int i = 0; i < snake.size(); i++)
	{
		if (i == 0) {
			// 设置填充色为蓝色
			setfillcolor(BLUE);
		}
		else if (i == 1) {
			// 设置填充色为白色
			setfillcolor(RGB(255, 255, 255));
		}
		else if (i == snake.size() - 1) {
			// 设置填充色为绿色
			setfillcolor(GREEN);
		}
		// 画填充矩形
		solidrectangle(10 + (snake[i].poses[0]) * 10, 50 + (snake[i].poses[1]) * 10, 10 + (snake[i].poses[0]) * 10 + 10, 50 + (snake[i].poses[1]) * 10 + 10);
	}

	// 设置填充色为绿色
	setfillcolor(RED);
	// 绘制食物的位置
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
	if (headxiang == "上" && xiang != "下" || headxiang == "下" && xiang != "上" || headxiang == "左" && xiang != "右" || headxiang == "右" && xiang != "左") {
		return false;
	}
	else
	{
		return true;
	}
}

// 蛇身移动函数
int TanchiSnake::chage(vector<Pos>& snake, Pos& head_pos)
{
	// 向头部插入一个新的元素
	snake.insert(snake.begin(), head_pos);
	// 判断是否吃到食物
	if (if_overlap(head_pos, *p_food_pos))
	{
		// 将之前的坐标从堆内释放
		delete p_food_pos;
		// 吃到食物，食物位置重新设定，不清除蛇尾
		p_food_pos = init_food(snake);
		fenshu += 1;
	}
	else
	{
		// 未吃到食物，清除蛇尾
		snake.pop_back();
	}
	// 判断蛇头碰撞到蛇身或撞上墙壁
	if (if_hit_self(snake) | if_hit_wall(snake))
	{
		// 关闭绘图窗口
		//closegraph();
		return 1;
	}
	return 0;
}

string TanchiSnake::move(vector<Pos>& snake, string xiang, string headxiang)
{
	Pos head_pos = snake[0];
	if (!(if_reseve_xiang(headxiang, xiang))) {
		if (xiang == "上") {
			head_pos.poses[1] -= 1;
		}
		else if (xiang == "下") {
			head_pos.poses[1] += 1;
		}
		else if (xiang == "左") {
			head_pos.poses[0] -= 1;
		}
		else if (xiang == "右") {
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

// string转换LPCWSTR，显示文本时使用
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

// 绘制开始界面
void TanchiSnake::draw_start(void)
{
	// 清空当前屏幕
	cleardevice();

	// 设置页眉文字矩形区域
	static RECT yemei_rect = { 10,10,WIDTH - 10,45 };
	// 设置标题文字矩形区域
	static RECT title_rect = { 100,(HIGHT / 2) - 100,WIDTH - 100,(HIGHT / 2) - 50 };
	// 设置页脚文字矩形区域
	static RECT yejiao_rect = { 10,HIGHT - 35,WIDTH - 10,HIGHT - 10 };

	// 设置字体大小
	settextstyle(25, 0, _T("微软雅黑"));
	// 绘制右上方的页眉
	drawtext(_T("凯文的第一个C++游戏"), &yemei_rect, DT_LEFT);

	settextstyle(50, 0, _T("微软雅黑"));
	// 绘制大大的标题
	drawtext(_T("贪 吃 蛇"), &title_rect, DT_CENTER);

	settextstyle(25, 0, _T("微软雅黑"));
	// 绘制左下方的页脚
	drawtext(_T("按下空格键来开始游戏"), &yejiao_rect, DT_RIGHT);
}

// 绘制结束界面
void TanchiSnake::draw_gameover(void)
{
	static RECT over_rect = { 100,(HIGHT / 2) - 100,WIDTH - 100,(HIGHT / 2) - 50 };
	static RECT text_rect = { 50, (HIGHT / 2), WIDTH - 50,(HIGHT / 2) + 30 };

	// 清空当前屏幕
	cleardevice();

	// 设置字体颜色为红色
	settextcolor(RED);
	// 设置字体大小
	settextstyle(50, 0, _T("微软雅黑"));
	// 绘制大大的GameOver
	drawtext(_T("Game Over"), &over_rect, DT_CENTER);

	// 设置字体颜色为白色
	settextcolor(RGB(255, 255, 255));
	// 设置字体大小
	settextstyle(30, 0, _T("微软雅黑"));
	// 绘制重新提示
	drawtext(_T("啊哦，游戏结束啦，按下空格键重来"), &text_rect, DT_CENTER);
}

int TanchiSnake::start_the_game(void)
{
	// 初始化画图窗口
	//          x      y      不显示控制台
	initgraph(WIDTH, HIGHT);
	// 字体类型
	LOGFONT f;
	// 获得当前字体
	gettextstyle(&f);
	// 设置字体格式为抗锯齿
	f.lfQuality = ANTIALIASED_QUALITY;
start:
	// 开始页面
	fps_limit fps1(60);
	while (1)
	{
		draw_start();
		// 键盘事件判断
		if (_kbhit()) {
			// 按下空格键继续
			if (_getch() == 32) {
				break;
			}
		}
		fps1.delay();
	}
	// 设置字体
	settextstyle(25, 0, _T("微软雅黑"));

	// 键盘码临时存储
	int ch;
	// 文字绘制区域
	RECT title_rect = { 10, 10, 300, 40 };
	RECT fenshu_rect = { WIDTH - 100, 10, WIDTH - 10, 40 };

	// 初始化小蛇位置
	int middle_row = (int)(ROW / 2);
	int middle_col = (int)(COL / 2);
	vector<Pos> snake_pos(4);
	for (unsigned int i = 0; i < snake_pos.size(); i++)
	{
		snake_pos[i].poses[0] = middle_row - i + 1;
		snake_pos[i].poses[1] = middle_col;
	}

	// 初始化蛇头朝向
	string headxiang = "右";

	// 初始化食物位置
	p_food_pos = init_food(snake_pos);

	// 帧数记次
	int times = 0;
	// 游戏主循环
	fps_limit fps2(60);
	while (1) {
		// 帧数自增1
		times++;

		// 蛇身自动行走
		if (times % 10 == 0) {
			if (headxiang == "左") {
				headxiang = move(snake_pos, "左", headxiang);
			}
			else if (headxiang == "右") {
				headxiang = move(snake_pos, "右", headxiang);
			}
			else if (headxiang == "上") {
				headxiang = move(snake_pos, "上", headxiang);
			}
			else if (headxiang == "下") {
				headxiang = move(snake_pos, "下", headxiang);
			}
		}

		// 键盘事件判断
		if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
			//使用_getch()函数获取按下的键值
			ch = _getch();
			// 上：72
			if (ch == 72) {
				//cout << "上" << endl
				headxiang = move(snake_pos, "上", headxiang);
			}
			// 下：80
			else if (ch == 80) {
				//cout << "下" << endl
				headxiang = move(snake_pos, "下", headxiang);
			}
			// 左：75
			else if (ch == 75) {
				//cout << "左" << endl;
				headxiang = move(snake_pos, "左", headxiang);
			}
			// 右：77
			else if (ch == 77) {
				//cout << "右" << endl;
				headxiang = move(snake_pos, "右", headxiang);
			}
			//当按下ESC时退出，ESC键的键值为27.
			else if (ch == 27) {
				// 关闭绘图窗口
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
	// 结束页面
	fps_limit fps3(60);
	while (1)
	{
		draw_gameover();
		// 键盘事件判断
		if (_kbhit()) {
			// 按下空格键继续
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
