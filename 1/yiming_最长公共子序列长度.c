//动态规划
int main(void)
{

	char str1[]="abcdefghijklmn";
	char str2[]="klmabcdefghijk";

	int s[MAX_STRING_LEN][MAX_STRING_LEN]={0};
    int i,j;

    for(i = 1; i <= sizeof(str1)-1; i++)
    {
    	
        for(j = 1; j <= sizeof(str2)-1; j++)
        {
            if((str1[i - 1] == str2[j - 1]))
            {
                s[i][j] = s[i - 1][j - 1] + 1; 
            }
            else
            {
                s[i][j] = max(s[i - 1][j], s[i][j - 1]); 
            }
            printf("%d ",s[i][j]);
        }
        printf("\n");
    }

    while(1);
}
