#include <graphics.h>
#include <conio.h>
#include <Windows.h>


#pragma comment (lib,"Winmm.lib")
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


struct bullet_s
{
	int pos_x;
	int pos_y;
	DIRECTION direction;
	int status;
};


void menu();
void init_map();
void play();
int tank_walk(tank_s *tank, DIRECTION direction, IMAGE *img, int step);
void set_prop_map(int x, int y, int val);
void bullet_action(bullet_s *bullet);

int map[26][26] = 
{
	
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
	{ 2, 2, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 2, 2},
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

int tank_walk(tank_s *tank, DIRECTION direction, IMAGE *img, int step)
{
	int new_x = tank->x;
	int new_y = tank->y;
	if (step == 1)
	{
		if (direction == UP)
		{
			new_y -= 1;
		}
		else if (direction == DOWN)
		{
			new_y += 1;
		}
		else if (direction == LEFT)
		{
			new_x -= 1;
		}
		else if (direction == RIGHT)
		{
			new_x += 1;
		}
		else
			return 0;

		set_prop_map(tank->x, tank->y, 0);
	}
	

	setfillcolor(BLACK);
	solidrectangle(tank->x * 25, tank->y * 25, tank->x * 25 + 50, tank->y * 25 + 50);
	if (step)
	{
		set_prop_map(new_x, new_y, 200);

		tank->x = new_x;
		tank->y = new_y;

	}
	
	putimage(tank->x * 25, tank->y * 25, img);
	return 1;
}


void bullet_action(bullet_s *bullet)
{
	int x; int y; int x1; int y1;

	x = bullet->pos_x / 25;
	y = bullet->pos_y / 25;


	setfillcolor(BLACK);
	solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x + 3, bullet->pos_y + 3);
	
	if (bullet->direction == UP)
	{
		bullet->pos_y -= 2;
		x1 = x + 1;
		y1 = y;
	}else if (bullet->direction == DOWN)
	{
		bullet->pos_y += 2;
		x1 = x + 1;
		y1 = y;
	}
	else if (bullet->direction == LEFT)
	{
		bullet->pos_x -= 2;
		x1 = x;
		y1 = y + 1;
	}
	else if (bullet->direction == RIGHT)
	{
		bullet->pos_x += 2;
		x1 = x;
		y1 = y + 1;
	}
	else
	{
		return;
	}

	if (bullet->pos_x < 0 || bullet->pos_x>650 || bullet->pos_y > 650 || bullet->pos_y < 0)
	{
		bullet->status = 0;
		return;
	}

	if (map[y][x] == 4 || map[y1][x1] == 4)
	{
		return;
	}

	
	if (map[y][x] == 1 )
	{
		map[y][x] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x * 25, y * 25, x * 25 + 25, y * 25 + 25);
		
	}
	else if (map[y][x] == 2)
	{
		bullet->status = 0;
	}

	if (map[y1][x1] == 1)
	{
		map[y1][x1] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x1 * 25, y1 * 25, x1 * 25 + 25, y1 * 25 + 25);

	}
	else if (map[y1][x1] == 2)
	{
		bullet->status = 0;
	}
	if (bullet->status == 1)
	{
		setfillcolor(WHITE);
		solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x + 3, bullet->pos_y + 3);
	}
	
}


void play()
{
	tank_s my_tank;
	bullet_s my_bullet;
	IMAGE my_tank_img[4];
	int key;

	my_bullet.status = 0;

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
				if (my_tank.direction == LEFT && (my_tank.x-1) >=0 && map[my_tank.y][my_tank.x-1] == 0 && map[my_tank.y+1][my_tank.x-1] ==0)
				{
					
					tank_walk(&my_tank, LEFT, &my_tank_img[my_tank.direction],1);
				}
				else if(my_tank.direction != LEFT)
				{
					my_tank.direction = LEFT;
					tank_walk(&my_tank, LEFT, &my_tank_img[my_tank.direction], 0);
				}
				break;
			case 'w':
				if (my_tank.direction == UP && (my_tank.y - 1) >= 0 && map[my_tank.y-1][my_tank.x ] == 0 && map[my_tank.y - 1][my_tank.x + 1] == 0)
				{
					
					tank_walk(&my_tank, UP, &my_tank_img[my_tank.direction],1);
				}
				else if (my_tank.direction != UP)
				{
					my_tank.direction = UP;
					tank_walk(&my_tank, UP, &my_tank_img[my_tank.direction], 0);
				}
				break;
			case 's':
				if (my_tank.direction == DOWN && (my_tank.y + 2) <= 25 && map[my_tank.y + 2][my_tank.x] == 0 && map[my_tank.y + 2][my_tank.x + 1] == 0)
				{
					
					tank_walk(&my_tank, DOWN, &my_tank_img[my_tank.direction],1);
				}
				else if (my_tank.direction != DOWN)
				{
					my_tank.direction = DOWN;
					tank_walk(&my_tank, DOWN, &my_tank_img[my_tank.direction], 0);
				}
				break;
			case 'd':
				if (my_tank.direction == RIGHT && (my_tank.x+2) <=25 && map[my_tank.y][my_tank.x + 2] == 0 && map[my_tank.y + 1][my_tank.x + 2] == 0)
				{
					
					tank_walk(&my_tank, RIGHT, &my_tank_img[my_tank.direction],1);
				}
				else if (my_tank.direction != RIGHT)
				{
					my_tank.direction = RIGHT;
					tank_walk(&my_tank, RIGHT, &my_tank_img[my_tank.direction], 0);
				}
				break;
			case 'j':
				if (my_bullet.status == 0)
				{
					PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);
					if (my_tank.direction == UP)
					{
						my_bullet.pos_x = my_tank.x * 25 + 23;
						my_bullet.pos_y = my_tank.y * 25 - 3;
					}else if (my_tank.direction == LEFT)
					{
						my_bullet.pos_x = my_tank.x * 25 - 3;
						my_bullet.pos_y = my_tank.y * 25 + 23;
					}
					else if (my_tank.direction == DOWN)
					{
						my_bullet.pos_x = my_tank.x * 25 + 23;
						my_bullet.pos_y = my_tank.y * 25 + 50;
					}
					else if (my_tank.direction == RIGHT)
					{
						my_bullet.pos_x = my_tank.x * 25 + 50;
						my_bullet.pos_y = my_tank.y * 25 + 23;
					}
					my_bullet.direction = my_tank.direction;
					my_bullet.status = 1;
				}
				break;
			case 'p':

				system("pause");
				break;
			default:

				break;
			}
		}
		if (my_bullet.status == 1)
		{
			bullet_action(&my_bullet);
		}
		
		Sleep(10);
	}
}