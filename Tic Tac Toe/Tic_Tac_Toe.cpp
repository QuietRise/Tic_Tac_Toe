#include <stdio.h>
#include <graphics.h>

void game_board();	//��������
void create_piece(int i, int j, int board[3][3], int* n);	//��������
void draw_piece(int x, int y, int a, int b, int* p, int board[3][3]);	//��������
void determine(const int* n, int board[3][3]); //ʤ���ж�
void create_text(const TCHAR* msg); //����ʤ���ı�

int main()
{
	int board[3][3] = { 0 }; // �����鴴�����̣�0��ʾ�գ�1��ʾx��2��ʾo
	int n = 0;	//���Ӵ���
	ExMessage msg;	//�����Ϣ�ṹ��

	initgraph(350, 350, 1); // ��������

	game_board();
	while (1) {	//ѭ������
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)	//���������
			{
				create_piece(msg.x, msg.y, board, &n);	//��������
				determine(&n, board);
				//printf("%d %d\n", msg.x, msg.y);	//��������λ��

				//for (int i = 0; i < 3; i++) {	//�����������
				//	for (int j = 0; j < 3; j++) {
				//		printf("%d ", board[j][i]);
				//	}
				//	printf("\n");
				//}
			}
		}
	}
	closegraph();	// �رմ���
	return 0;
}

void game_board()
{
	setbkcolor(RGB(204, 238, 255));	//���̱�����ɫ
	cleardevice();

	setlinecolor(RGB(148, 168, 207));	//����������ɫ
	setlinestyle(PS_SOLID, 5);	//���̱߿���
	rectangle(25, 25, 325, 325);	//������߿�

	setlinestyle(PS_SOLID, 2);	//�������߿��
	int i;
	for (i = 1; i <= 2; i++) {
		line(25, 25 + 100 * i, 25 + 3 * 100, 25 + 100 * i);	//�ڲ�����
	}
	int j;
	for (j = 1; j <= 2; j++) {
		line(25 + 100 * j, 25, 25 + 100 * j, 25 + 3 * 100);	//�ڲ�����
	}
}

void create_piece(int i, int j, int board[3][3], int* n)
{
	int x = (i - 25) / 100; //�������ڵ���
	int y = (j - 25) / 100; //�������ڵ���
	int a = 25 + x * 100 + 50; //�������ĵ������
	int b = 25 + y * 100 + 50; //�������ĵ�������

	if (i < 25 || i > 325 || j < 25 || j > 325) { return; }	//�������̷�Χ���
	if (board[x][y] != 0) { return; }	//��λ���������Ӽ��
	draw_piece(x, y, a, b, n, board);	//����

}

void draw_piece(int x, int y, int a, int b, int* p, int board[3][3])
{
	int i = *p;
	setlinecolor(RGB(165, 103, 207));

	if (i % 2 == 1) {
		board[x][y] = 1;	//����o
		setlinestyle(PS_SOLID, 10);
		circle(a, b, 25);	//����o
	}
	else {
		setlinestyle(PS_SOLID, 10);
		board[x][y] = 2;	//����x
		line(a - 21, b - 21, a + 21, b + 21);	//����x
		line(a - 21, b + 21, a + 21, b - 21);
	}
	*p = i + 1;	//���Ӵ���+1
}

void determine(int const* n, int board[3][3])
{
	int i;
	int m = *n;
	if (m < 5) { return; }	//������С��5�����ֳܷ�ʤ��
	for (i = 0; i < 3; i++) {	//�����ж�
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) {
			if (board[i][0] == 1) {
				create_text(_T("O��ʤ��"));
				exit(0);
			}
			else {
				create_text(_T("X��ʤ��"));
				exit(0);
			}
		}
	}
	for (i = 0; i < 3; i++) {	//�����ж�
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0) {
			if (board[0][i] == 1) {
				create_text(_T("O��ʤ��"));
				exit(0);
			}
			else {
				create_text(_T("X��ʤ��"));
				exit(0);
			}
		}
	}
	for (i = 0; i < 3; i++) {	//��б�ж�
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) {
			if (board[0][0] == 1) {
				create_text(_T("O��ʤ��"));
				exit(0);
			}
			else {
				create_text(_T("X��ʤ��"));
				exit(0);
			}
		}
	}
	for (i = 0; i < 3; i++) {	//��б�ж�
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0) {
			if (board[0][2] == 1) {
				create_text(_T("O��ʤ��"));
				exit(0);
			}
			else {
				create_text(_T("X��ʤ��"));
				exit(0);
			}
		}
	}

	if (m == 9) {	//ƽ��
		create_text(_T("ƽ�֣�"));
		exit(0);
	}
}

void create_text(const TCHAR* msg)
{
	setbkcolor(RGB(204, 238, 255));	//���̱�����ɫ
	cleardevice();
	settextcolor(RGB(255, 0, 0));
	settextstyle(40, 0, _T("����"));
	outtextxy(130, 150, msg);
	Sleep(2000);
}