#include <stdlib.h>
#include <stdio.h>

char bottle[2] = {0};//桶状态

char action_num[6][2]={{0,3},{0,5},{3,5},{5,3},{3,0},{5,0}};//六种动作，3取水，5取水，3->5(倒满即停),5->3(倒满即停)，3倒掉，5倒掉

char action_list[100][3] = {0};//记录动作和相应状态

char bottle_state[100][3]= {0};//记录出现过的状态和状态的深度

int bottle_state_cnt = 0;//历史状态的计数

int step_cnt = 0;//深度计数

int way_cnt = 0;//广度计数

char stop = 0;

unsigned char act_temp = 0;

void action(char from,char to)
{
	if(from == 0)//取水
	{
		if(to == 3)
		{
			bottle[0] = 3;
			printf("0->3 ");
		}
		else
		{
			bottle[1] = 5;
			printf("0->5 ");
		}
	}
	else if (from == 3)//拿起3桶
	{
		if(to == 0)//倒掉
		{
			bottle[0] = 0;
			printf("3->0 ");
		}
		else//到给5桶
		{
			char possible = 5 - bottle[1];//还能倒进多少水

			if(possible >= bottle[0])//全能倒进
			{
				bottle[1] += bottle[0];
				bottle[0] = 0;
				

				printf("3->5 ",possible);
			}
			else
			{
				bottle[0] -= possible;//倒满还剩水
				bottle[1] += possible;
				printf("3->5 ",possible);
			}
		}
	}
	else if (from == 5)//拿起5桶
	{

		if(to == 0)//倒掉
		{
			bottle[1] = 0;
			printf("5->0 ");
		}
		else//到给3桶
		{
			char possible = 3 - bottle[0];//还能倒进多少水，5给3倒肯定剩

			if(possible >= bottle[1])//全能倒进
			{
				bottle[0] += bottle[1];
				bottle[1] = 0;
				
				printf("5->3 ",possible);
			}
			else
			{
				bottle[1] -= possible;//倒满还剩水
				bottle[0] += possible;
				printf("5->3 ",possible);
			}
		}
	}

	printf("(%d,%d) ", bottle[0],bottle[1]);
}

char check_if_ok()
{
	return bottle[1]==4;
}

char check_if_same_as_history_or_save_state()//1:same 2:new
{
	for(int i=0;i<bottle_state_cnt;i++)
	{
		if(bottle[0]==bottle_state[i][0]&&bottle[1]==bottle_state[i][1]&&step_cnt>bottle_state[i][2])
		{
			return 1;
		}
	}

	bottle_state[bottle_state_cnt  ][2]=step_cnt;
	bottle_state[bottle_state_cnt  ][0]=bottle[0];
	bottle_state[bottle_state_cnt++][1]=bottle[1];
	
	return 2;
}

void step_back()
{
	step_cnt --;
	action_list[step_cnt][0]++;
	act_temp =  action_list[step_cnt][0];
	bottle[0] = action_list[step_cnt][1];
	bottle[1] = action_list[step_cnt][2];

	if(action_list[step_cnt][0]>5)
	{
		if(action_list[0][0]==6)
		{
			stop = 1;
		}
		else
		{
			step_back();
		}
	}
}

void search_the_tree()
{

	while(stop==0)
	{
		//printf("(%d,%d)", bottle[0],bottle[1]);

		action_list[ step_cnt  ][0] = act_temp;					//记录动作
		action_list[ step_cnt  ][1] = bottle[0];
		action_list[ step_cnt++][2] = bottle[1];
		action( action_num[act_temp][0] , action_num[act_temp][1] );//进行act_temp动作
		
		if(check_if_ok())//1:ok
		{
			way_cnt ++;
			step_back();
			printf("get!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			for(int i=0;i<step_cnt;i++)
			{
				printf("           ");
			}
			continue;
		}

		if(check_if_same_as_history_or_save_state()==1)//1:same 2:new//返回上一步
		{
			step_back();
			printf("same,step_back\n");
			for(int i=0;i<step_cnt;i++)
			{
				printf("           ");
			}
		}
		else//继续
		{
			//step_cnt ++;
			act_temp = 0;
			//printf("step_next\n");

		}
	}
}


int main(void)
{
	search_the_tree();
	return 0;
}
