#include <stdio.h>
#include <graphics.h>

void game_board();	//绘制棋盘
void create_piece(int i, int j, int board[3][3], int* n);	//创建棋子
void draw_piece(int x, int y, int a, int b, int* p, int board[3][3]);	//绘制棋子
void determine(const int* n, int board[3][3]); //胜负判断
void create_text(const TCHAR* msg); //创建胜负文本

int main()
{
	int board[3][3] = { 0 }; // 用数组创建棋盘，0表示空，1表示x，2表示o
	int n = 0;	//落子次数
	ExMessage msg;	//鼠标消息结构体

	initgraph(350, 350, 1); // 创建窗口

	game_board();
	while (1) {	//循环落子
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)	//鼠标左键点击
			{
				create_piece(msg.x, msg.y, board, &n);	//创建棋子
				determine(&n, board);
				//printf("%d %d\n", msg.x, msg.y);	//输出鼠标点击位置

				//for (int i = 0; i < 3; i++) {	//输出棋盘数组
				//	for (int j = 0; j < 3; j++) {
				//		printf("%d ", board[j][i]);
				//	}
				//	printf("\n");
				//}
			}
		}
	}
	closegraph();	// 关闭窗口
	return 0;
}

void game_board()
{
	setbkcolor(RGB(204, 238, 255));	//棋盘背景颜色
	cleardevice();

	setlinecolor(RGB(148, 168, 207));	//棋盘线条颜色
	setlinestyle(PS_SOLID, 5);	//棋盘边框宽度
	rectangle(25, 25, 325, 325);	//棋盘外边框

	setlinestyle(PS_SOLID, 2);	//棋盘内线宽度
	int i;
	for (i = 1; i <= 2; i++) {
		line(25, 25 + 100 * i, 25 + 3 * 100, 25 + 100 * i);	//内部横线
	}
	int j;
	for (j = 1; j <= 2; j++) {
		line(25 + 100 * j, 25, 25 + 100 * j, 25 + 3 * 100);	//内部竖线
	}
}

void create_piece(int i, int j, int board[3][3], int* n)
{
	int x = (i - 25) / 100; //棋子所在的行
	int y = (j - 25) / 100; //棋子所在的列
	int a = 25 + x * 100 + 50; //棋子中心点横坐标
	int b = 25 + y * 100 + 50; //棋子中心点纵坐标

	if (i < 25 || i > 325 || j < 25 || j > 325) { return; }	//超出棋盘范围检测
	if (board[x][y] != 0) { return; }	//该位置已有棋子检测
	draw_piece(x, y, a, b, n, board);	//落子

}

void draw_piece(int x, int y, int a, int b, int* p, int board[3][3])
{
	int i = *p;
	setlinecolor(RGB(165, 103, 207));

	if (i % 2 == 1) {
		board[x][y] = 1;	//落子o
		setlinestyle(PS_SOLID, 10);
		circle(a, b, 25);	//绘制o
	}
	else {
		setlinestyle(PS_SOLID, 10);
		board[x][y] = 2;	//落子x
		line(a - 21, b - 21, a + 21, b + 21);	//绘制x
		line(a - 21, b + 21, a + 21, b - 21);
	}
	*p = i + 1;	//落子次数+1
}

void determine(int const* n, int board[3][3])
{
	int i;
	int m = *n;
	if (m < 5) { return; }	//落子数小于5不可能分出胜负
	for (i = 0; i < 3; i++) {	//横向判断
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) {
			if (board[i][0] == 1) {
				create_text(_T("O获胜！"));
				exit(0);
			}
			else {
				create_text(_T("X获胜！"));
				exit(0);
			}
		}
	}
	for (i = 0; i < 3; i++) {	//纵向判断
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0) {
			if (board[0][i] == 1) {
				create_text(_T("O获胜！"));
				exit(0);
			}
			else {
				create_text(_T("X获胜！"));
				exit(0);
			}
		}
	}
	for (i = 0; i < 3; i++) {	//左斜判断
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) {
			if (board[0][0] == 1) {
				create_text(_T("O获胜！"));
				exit(0);
			}
			else {
				create_text(_T("X获胜！"));
				exit(0);
			}
		}
	}
	for (i = 0; i < 3; i++) {	//右斜判断
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0) {
			if (board[0][2] == 1) {
				create_text(_T("O获胜！"));
				exit(0);
			}
			else {
				create_text(_T("X获胜！"));
				exit(0);
			}
		}
	}

	if (m == 9) {	//平局
		create_text(_T("平局！"));
		exit(0);
	}
}

void create_text(const TCHAR* msg)
{
	setbkcolor(RGB(204, 238, 255));	//棋盘背景颜色
	cleardevice();
	settextcolor(RGB(255, 0, 0));
	settextstyle(40, 0, _T("黑体"));
	outtextxy(130, 150, msg);
	Sleep(2000);
}