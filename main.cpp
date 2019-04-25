#include <graphics.h>
#include <conio.h>
#include <Windows.h>



enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct tank_s
{
	int x;
	int y;
	DIRECTION direction;
	int live;
};

void menu();
void init_map();
void play();
int tank_walk(tank_s *tank, DIRECTION direction, IMAGE *img);
void set_prop_map(int x, int y, int val);


int map[26][26] = 
{
	
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
	{ 2, 2, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 2, 2},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	
};





int main()
{
	initgraph(650, 650);//画布
	menu();

	init_map();

	play();




	return 0;
}


void menu()
{
	

	IMAGE logo_img;
	loadimage(&logo_img, _T("logo.bmp"), 433, 147);
	putimage(110, 20, &logo_img);

	//实现导航按钮
	setlinecolor(WHITE);
	setfillcolor(BLACK);

	fillrectangle(230, 200, 310, 240);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(240, 210, _T("说 明"));

	fillrectangle(350, 200, 430, 240);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(360, 210, _T("开 始"));

	//鼠标事件监听实现
	MOUSEMSG mouse;
	
	while (true)
	{
		mouse = GetMouseMsg();

		switch (mouse.uMsg)
		{
		case WM_MOUSEMOVE:
			if (mouse.x > 230 && mouse.x < 310 && mouse.y>200 && mouse.y < 240)
			{
				//显示说明
				IMAGE illustrate_img;
				loadimage(&illustrate_img, _T("illustrate.jpg"), 300, 300);
				putimage(150, 250, &illustrate_img);
			}
			else
			{
				solidrectangle(150, 250, 450, 550);
			}
			break;
		case WM_LBUTTONDOWN:
			if (mouse.x > 350 && mouse.x < 430 && mouse.y>200 && mouse.y < 240)
			{
				cleardevice();
				return;
			}
		}
	}
}


void init_map()
{
	int i, j;
	IMAGE img_home, img_wall_1, img_wall_2;

	loadimage(&img_home, _T("home.jpg"), 50, 50);
	loadimage(&img_wall_1, _T("wall1.jpg"), 25, 25);
	loadimage(&img_wall_2, _T("wall2.jpg"), 25, 25);
	
	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			if (map[i][j] == 1) {
				putimage(25 * j, 25 * i, &img_wall_2);
			}
			else if (map[i][j] == 2) {
				putimage(25 * j, 25 * i, &img_wall_1);
			}
			else if (map[i][j] == 3) {
				putimage(25 * j, 25 * i, &img_home);
				map[i    ][j    ] = 4;
				map[i    ][j + 1] = 4;
				map[i + 1][j    ] = 4;
				map[i + 1][j + 1] = 4;
			}
		}
	}
}

void set_prop_map(int x, int y,int val)
{
	map[y][x] = val;
	map[y][x + 1] = val;
	map[y + 1][x] = val;
	map[y + 1][x + 1] = val;
}

int tank_walk(tank_s *tank, DIRECTION direction, IMAGE *img)
{
	int new_x = tank->x;
	int new_y = tank->y;

	if (direction == UP)
	{
		new_y -= 1;
	}else if (direction == DOWN)
	{
		new_y += 1;
	}else if (direction == LEFT)
	{
		new_x -= 1;
	}else if (direction == RIGHT)
	{
		new_x += 1;
	}
	else
		return 0;

	set_prop_map(tank->x, tank->y, 0);

	setfillcolor(BLACK);
	solidrectangle(tank->x * 25, tank->y * 25, tank->x * 25 + 50, tank->y * 25 + 50);

	set_prop_map(new_x, new_y, 200);

	tank->x = new_x;
	tank->y = new_y;
	
	putimage(tank->x * 25, tank->y * 25, img);
	return 1;
}

void play()
{
	tank_s my_tank;
	IMAGE my_tank_img[4];
	int key;

	loadimage(&my_tank_img[UP], _T("tank_up.jpg"), 50, 50);
	loadimage(&my_tank_img[DOWN], _T("tank_down.jpg"), 50, 50);
	loadimage(&my_tank_img[LEFT], _T("tank_left.jpg"), 50, 50);
	loadimage(&my_tank_img[RIGHT], _T("tank_right.jpg"), 50, 50);
	my_tank.x = 8;
	my_tank.y = 24;
	my_tank.live = 1;
	my_tank.direction = UP;
	set_prop_map(my_tank.x, my_tank.y, 200);
	putimage(my_tank.x * 25, my_tank.y * 25, &my_tank_img[my_tank.direction]);

	while (true)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 'a':
				if ((my_tank.x-1) >=0 && map[my_tank.y][my_tank.x-1] == 0 && map[my_tank.y+1][my_tank.x-1] ==0)
				{
					my_tank.direction = LEFT;
					tank_walk(&my_tank, LEFT, &my_tank_img[my_tank.direction]);
				}
				break;
			case 'w':
				if ((my_tank.y - 1) >= 0 && map[my_tank.y-1][my_tank.x ] == 0 && map[my_tank.y - 1][my_tank.x + 1] == 0)
				{
					my_tank.direction = UP;
					tank_walk(&my_tank, UP, &my_tank_img[my_tank.direction]);
				}
				break;
			case 's':
				if ((my_tank.y + 2) <= 25 && map[my_tank.y + 2][my_tank.x] == 0 && map[my_tank.y + 2][my_tank.x + 1] == 0)
				{
					my_tank.direction = DOWN;
					tank_walk(&my_tank, DOWN, &my_tank_img[my_tank.direction]);
				}
				break;
			case 'd':
				if ((my_tank.x+2) <=25 && map[my_tank.y][my_tank.x + 2] == 0 && map[my_tank.y + 1][my_tank.x + 2] == 0)
				{
					my_tank.direction = RIGHT;
					tank_walk(&my_tank, RIGHT, &my_tank_img[my_tank.direction]);
				}
				break;
			case 'j':

				break;
			case 'p':

				system("pause");
				break;
			default:

				break;
			}
		}
		Sleep(10);
	}
}