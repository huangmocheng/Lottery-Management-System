/*
文件名称：彩票管理系统
帐号说明：管理员唯一帐号和密码：admin
     	 公证员唯一帐号和密码：notary
		 新用户使用时需注册
*/
#include<stdio.h>
#include"node.h"
#include"user.h"
extern int flag;
int main(){
	ReadAllData();
	int choose;
	do{
		choose=home();		//首页
		switch(choose){
		case 1:			
			addNewUser();	//注册
			SaveAllData();
			break;
		case 2:			
			login();	//登录界面
			break;
		default:
			printf("\t是否保存(Y/N)？");
			char ch;
			getchar();
			scanf("%c",&ch);
			if(ch=='y' || ch=='Y'){
				SaveAllData();
				return 0;
			}else{
				return 0;
			}
			
		}
	}while(choose>=1 || choose<=2);
	return 0;
}
