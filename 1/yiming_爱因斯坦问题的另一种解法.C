
#include <stdlib.h>
#include <stdio.h>

#define Empty   0

#define UK      1//国籍
#define SW      2
#define GM      3
#define DM      4
#define NW      5

#define R       6//颜色
#define Y       7
#define G       8
#define W       9
#define B      10 

#define Dog    11//动物
#define Bird   12
#define Cat    13
#define Horse  14

#define Beer   15//喝的
#define Tea    16
#define Cafe   17
#define Milk   18
#define Water  19

#define bl     20//烟
#define pm     21
#define dh     22
#define bm     23
#define pc     24


typedef struct 
{
    char x1;
    char y1;
    char sth1;

    char x2;
    char y2;
    char sth2;
}block_struct;

block_struct blocks[13]={{1,1,UK,    1,2,R},     //0  整理后的13个方块组合
                         {1,1,SW,    1,3,Dog},   //1
                         {1,3,Bird,  1,5,pm},    //2
                         {1,2,Y,     1,5,dh},    //3
                         {1,4,Beer,  1,5,bm},    //4
                         {1,1,GM,    1,5,pc},    //5
                         {1,1,DM,    1,4,Tea},   //6
                         {1,5,bl,    2,3,Cat},   //7
                         {1,3,Cat,   2,5,bl},    //8
                         {1,5,dh,    2,3,Horse}, //9
                         {1,3,Horse, 2,5,dh},    //10
                         {1,5,bl,    2,4,Water}, //11
                         {1,4,Water, 2,5,bl}};   //12


char map[6][6]= {0} ;         //表
char motion_list[13] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} ;  //记录的每个block平移量
char block_num = 0 ;          //被处理block的编号
char stop = 0 ;               //是否停止
char temp_offset = 0 ;        //偏移量
int  time_cnt = 0;

void print_map()//debug打印图标用
{
	for(int y=1;y<6;y++)
	{
		for(int x=1;x<6;x++)
		{
			printf("%2d ", map[y][x]);
		}
		printf("\n");
	}
}

void print_path()//打印路径
{
	char print_cnt = 0;
	while(print_cnt<13)
	{
		printf("[%2d]%2d ",print_cnt,motion_list[print_cnt] );
		print_cnt++;
	}
	
	printf("\n");
}

void print_log()//打印log
{
	for(int i=0;i<block_num;i++)
	{
		if(i==7||i==9||i==11);
		else
		printf("             ");
	}
	printf("no.%-3d[%2d]%2d \n",time_cnt,block_num,temp_offset);
}

char fill(block_struct temp,char offset)//把某块填入表，判断是否成立
{
	time_cnt ++ ;//累计搜索次数
	if((    map[temp.y1][temp.x1 + offset] == Empty || map[temp.y1][temp.x1 + offset] == temp.sth1 )//如果准备填入的方块是空白或者已经是自己
		&& (map[temp.y2][temp.x2 + offset] == Empty || map[temp.y2][temp.x2 + offset] == temp.sth2 )
		&& temp.x1 + offset<6 																		//边界控制
		&& temp.x2 + offset<6)
	{
		map[temp.y1][temp.x1 + offset] = temp.sth1;//将方块填入map
		map[temp.y2][temp.x2 + offset] = temp.sth2;

		print_log();
		return 1;
	}
	else
	{
		print_log();
		return 0;
	}
}

void step_back()//如果当前情况不满足，增加平移量，如果平移量溢出，就退回到上一个节点
{
	if(temp_offset >= 4)
	{
		if(block_num == 0)
		{
			printf("over \n");
			stop = 1;//已经遍历完了
			return;
		}
		else if(block_num == 7 || block_num == 9 || block_num == 11)//对于7 9 11 号如果自己的4种平移无法继续，还可以尝试自己的镜像进平移
		{
			motion_list[block_num] = -2;//表示此方块不参与搜索,也没填入map
			motion_list[block_num+1] = 0;//安全操作，避免-2的干扰
			block_num++;
			temp_offset = 0;
		}
		else
		{
			if(motion_list[--block_num] == -2)//如果上一个编号的方块没参与填入，就再往前跳一个编号（如block10,往前处理上一个节点肯定不是block9，是8或者7）
			{
				
				block_num--;
				temp_offset = motion_list[block_num];

				if(motion_list[block_num] != -2)
				{	
					map[blocks[block_num].y1][blocks[block_num].x1+temp_offset] = 0;//清空上个block在map的占位
					map[blocks[block_num].y2][blocks[block_num].x2+temp_offset] = 0;
				}
				step_back();//递归继续判断
			}
			else//直接处理上一个节点的方块
			{
				temp_offset = motion_list[block_num];
				map[blocks[block_num].y1][blocks[block_num].x1+temp_offset] = 0;//清空上个block在map的占位
				map[blocks[block_num].y2][blocks[block_num].x2+temp_offset] = 0;
				step_back();
			}
			
		}
	}
	else if(motion_list[block_num] == -2)//承接递归的功能，判断这次是不是依然是没参与的方块
	{
		block_num--;
		temp_offset = motion_list[block_num];
		temp_offset = motion_list[block_num];
		map[blocks[block_num].y1][blocks[block_num].x1+temp_offset] = 0;//清空上个block在map的占位
		map[blocks[block_num].y2][blocks[block_num].x2+temp_offset] = 0;
		step_back() ;//如果此方块没有参与填入，就跳过
	}
	else
	{
		temp_offset ++;//啥说道都没有的，直接平移量++
	}
}

void sweep_the_path()
{
	if(stop == 0)
	{
		while(fill(blocks[block_num],temp_offset)==0 && stop == 0)
		{
			step_back();//深度优先搜索
		}

		motion_list[block_num] = temp_offset;

		if(block_num == 7 || block_num == 9 || block_num == 11)//如果这几个方块找到了填入方法，它的镜像方块就不用再考虑了
		{
			motion_list[block_num+1] = -2;
			block_num += 2 ;
			temp_offset = 0;
			motion_list[block_num] = 0;
		}
		else
		{
			motion_list[block_num+1] = 0;//各种往复操作导致下一位可能是-2，此状态应清零
			block_num ++ ;
			temp_offset = 0;
		}

		if(block_num == 13)//已经有一次结果了
		{
			block_num -- ;
			print_map();
			step_back();
		}
		sweep_the_path();
	}
}





int main(void)
{
	map[1][1] = NW; //把已知的方块填入map
	map[2][2] = B;
	map[4][3] = Milk;
	map[2][4] = G;
	map[2][5] = W;
	map[4][5] = Cafe;

	sweep_the_path();
	return 0;
}
