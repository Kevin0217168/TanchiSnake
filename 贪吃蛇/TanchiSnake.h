#include <graphics.h> // 引用图形库头文件
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
	// 构造函数
	TanchiSnake(int, int, int);
	// 游戏入口
	int start_the_game(void);

private:
	// 宽
	int WIDTH = 520;
	// 高
	int HIGHT = 520;
	// 每个单位方格的大小
	int CELL = 10;
	// 方格的总行数
	int ROW = (int)((WIDTH - 20) / CELL);
	// 方格的总列数
	int COL = (int)((HIGHT - 60) / CELL);
	// 创建方格坐标结构
	struct Pos {
		// 该方格左上角坐标
		int poses[2];
	};
	// 食物坐标指针
	Pos* p_food_pos;
	// 计分板
	int fenshu = 0;

	// 生成从MIX到MIN的随机数
	int randint(int, int);
	// 绘制游戏进行中函数
	void draw(RECT&, RECT&, vector<Pos>&, Pos*);
	// 重置食物位置
	Pos* init_food(vector<Pos>&);
	// 判断是否撞上墙壁
	bool if_hit_wall(vector<Pos>&);
	// 判断两方格是否重叠
	bool if_overlap(Pos&, Pos&);
	// 判断是否撞上自己
	bool if_hit_self(vector<Pos>&);
	// 判断方向是否相反
	bool if_reseve_xiang(string, string);
	// 对贪吃蛇更新位置
	int chage(vector<Pos>&, Pos&);
	// string转换LPCWSTR，显示文本时使用
	LPCWSTR stringToLPCWSTR(string);
	// 决定贪吃蛇移动方向
	string move(vector<Pos>&, string, string);
	// 绘制开始界面
	void draw_start(void);
	// 绘制结束界面
	void draw_gameover(void);
};
