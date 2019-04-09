
#include <stdlib.h>
#include <stdio.h>

char bank[2] = {15,0};//岸状态,0左岸，1右岸，初始都在左岸

//二进制1111 分别代表农夫 狼 羊 菜，十进制下分别是8 4 2 1
char action_num[8][2]={{0,0},{0,1},{0,2},{0,4},{1,0},{1,1},{1,2},{1,4}};//8种动作，去带啥，回来带啥

char action_list[100][2] = {0};//记录动作和相应状态

char bank_state[100][2]= {0};//记录出现过的状态和状态的深度

int bank_state_cnt = 0;//历史状态的计数

int step_cnt = 0;//深度计数

int way_cnt = 0;//广度计数

char stop = 0;

unsigned char act_temp = 0;

char action(char to,char with)
{
	action_list[ step_cnt  ][0] = act_temp;					//记录动作
	action_list[ step_cnt++][1] = bank[1];

	//printf("(%2d,%2d)", bank[0],bank[1]);
	if(to == 0)//去左岸
	{
		if((bank[1]&(with+8))==(with+8))//先看岸上有没有,农夫在不在
		{
			bank[1] -= with+8;//16是农夫自己
			bank[0] += with+8;	

			printf("->%d(%d)=",to,with );
			printf("(%2d,%2d) ", bank[0],bank[1]);
			return 1;
		}
		else
		{
			printf("->%d(%d)=",to,with );
			return 0;
		}
	}
	else//去右岸
	{
		if((bank[0]&(with+8))==(with+8))//先看岸上有没有
		{
			bank[0] -= with+8;
			bank[1] += with+8;

			printf("->%d(%d)=",to,with );
			printf("(%2d,%2d) ", bank[0],bank[1]);
			return 1;	
		}
		else
		{
			printf("->%d(%d)=",to,with );
			return 0;
		}
	}
	
}

char check_if_ok()//0:可以继续，1：目的达到，2：打架了
{
	//农夫 狼 羊 菜，十进制下分别是8 4 2 1
	if(bank[0]==6||bank[0]==3||bank[1]==6||bank[1]==3)
	{
		return 2;
	}
	return bank[1]==15;
}

char check_if_same_as_hiswithry_or_save_state()//1:same 2:new//状态记录一边就够了
{
	for(int i=0;i<bank_state_cnt;i++)
	{
		if(bank[1]==bank_state[i][0]&&step_cnt>bank_state[i][1])
		{
			//printf("bank[1]=%d bank_state=%d bank_state_cnt=%d step_cnt%d ",bank[1],bank_state[i][0],i,step_cnt);
			return 1;
		}
	}

	bank_state[bank_state_cnt  ][0]=bank[1];
	bank_state[bank_state_cnt++][1]=step_cnt;
	
	return 2;
}

void step_back()
{
	step_cnt --;
	action_list[step_cnt][0]++;
	act_temp =  action_list[step_cnt][0];
	
	bank[1] = action_list[step_cnt][1];
	bank[0] = 15-bank[1]; 

	if(action_list[step_cnt][0]>7)
	{
		if(action_list[0][0]==8)
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
		if(action( action_num[act_temp][0] , action_num[act_temp][1])==0)//进行act_temp动作
		{
			step_back();
			printf("erro\n");
			for(int i=0;i<step_cnt;i++)
			{
				printf("               ");
			}

			continue;
		}

		char result=check_if_ok();//1:ok
		if(result ==1)//目的达到了
		{
			way_cnt ++;
			step_back();
			printf("get!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			for(int i=0;i<step_cnt;i++)
			{
				printf("               ");
			}
			continue;
		}
		else if(result ==2)//打架了
		{
			step_back();
			printf("some one die\n");
			for(int i=0;i<step_cnt;i++)
			{
				printf("               ");
			}
			continue;
		}

		if(check_if_same_as_hiswithry_or_save_state()==1)//1:same 2:new//返回上一步
		{
			step_back();
			printf("same,step_back\n");
			for(int i=0;i<step_cnt;i++)
			{
				printf("               ");
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
