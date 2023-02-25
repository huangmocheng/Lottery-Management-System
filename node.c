#include<stdio.h>
#include"node.h"
#include<string.h>
int flag=0;
int home(){		//首页
	printf("\n\t\t****彩票管理系统****\n");
	printf("----------------------------------------------------\n");
	printf("\t欢迎使用本系统，请按提示完成输入！\n");
	printf("\n\t\t1.注册帐号\n");
	printf("\t\t2.登录帐号\n");
	printf("\n\t请选择(输入其他任意字符退出)：");
	int choose;
	scanf("%d",&choose);
	return choose;	
}
void login(){		//登录
	char account[100];
	char password[100];
	char admin[100]="admin";	//管理员帐号及密码
	char notary[100]="notary";	//公证员帐号及密码
	int cnt=0;
	do{	
		printf("\n\t\t****彩票管理系统****\n");
		printf("----------------------------------------------------\n");
		printf("\t欢迎使用本系统，请输入帐号及密码！\n");
		printf("\n\t\t帐号：");
		scanf("%s",account);
		printf("\t\t密码：");
		scanf("%s",password);
		int userLog=userLogin(account,password);
		if(strcmp(account,admin)==0 && strcmp(password,admin)==0){	//管理员界面	
			int choose=adminMenu();
			if(choose==0){
				return;
			}
		}else if(strcmp(account,notary)==0 && strcmp(password,notary)==0){//公证员界面	
			int choose=notaryMenu();
			if(choose==0){
				return;
			}
		}else if(userLog!=0){	//彩民界面
			int choose=userMenu(account);
			if(choose==0){
				return;
			}	
		}else{						
			cnt++;
			if(cnt<3){
				printf("\n\t第%d次帐号或密码输入错误，请重新输入！\n",cnt);
			}else{
				printf("\n\t第%d次帐号或密码输入错误，程序退出！\n",cnt);
			}
		}
	}while(cnt<3);
}
int adminMenu(){		//管理员操作界面
	int choose;
	printf("\n\t\t****彩票管理系统****\n");
	printf("----------------------------------------------------\n");
	printf("\t亲爱的管理员，欢迎您使用本系统！\n");
	do{	
		printf("\n\t\t1.发行新一期彩票\n");
		printf("\t\t2.显示所有彩票信息\n");
		printf("\t\t3.显示所有用户信息\n");
		printf("\t\t4.查询彩民信息\n");
		printf("\t\t5.排序彩民信息\n");
		printf("\t\t6.增加奖池金额\n");
		printf("\t\t7.保存\n");
		printf("\t\t请选择(输入0返回首页)：");
		scanf("%d",&choose);
		switch(choose){
			case 1:
				adminPublishLottery();
				flag=1;
				break;
			case 2:
				displayadminPublishLottery();
				break;
			case 3:
				displayAllUserInfo();
				break;
			case 4:
				findUserMean();
				break;
			case 5:
				sortUserMean();
				break;
			case 6:
				addPrize();
				flag=1;
				break;
			case 7:
				SaveAllData();
				flag=0;
				break;
			default:
				if(0>choose || 7<choose){
					printf("\n\t\t输入错误，请重新输入！\n");
					continue;
				}
		}
	}while(choose != 0);
	if(flag==1){
		printf("\n\t检测到数据修改，是否保存(Y/N)？");
		char ch;
		getchar();
		scanf("%c",&ch);
		if(ch=='y' || ch== 'Y'){
			SaveAllData();
			flag=0;
			return 0;
		}
	}
}
int notaryMenu(){		//公证员操作界面
	int choose;
	printf("\n\t\t****彩票管理系统****\n");
	printf("----------------------------------------------------\n");
	printf("\t亲爱的公证员，欢迎您使用本系统！\n");
	do{
		printf("\n\t\t1.本期彩票随机开奖\n");
		printf("\t\t2.查询彩票中奖信息\n");
		printf("\t\t3.显示所有彩票信息\n");
		printf("\t\t4.指定本期开奖号\n");
		printf("\t\t5.保存\n");
		printf("\t\t请选择(输入0返回首页)：");
		scanf("%d",&choose);
		switch(choose){
			case 1:
				doubleBull();
				flag=1;
				break;
			case 2:
				findLotterInfo();
				break;
			case 3:
				displayadminPublishLottery();
				break;
			case 4:
				SpecifyTheDrawNumber();
				flag=1;
				break;
			case 5:
				SaveAllData();
				flag=0;
				break;
			default:
				if(0>choose || 5<choose){
					printf("\n\t\t输入错误，请重新输入！\n");
					continue;;
				}
		
		}
	}while(choose != 0);
	if(flag==1){
		printf("\n\t检测到数据修改，是否保存(Y/N)？");
		char ch;
		getchar();
		scanf("%c",&ch);
		if(ch=='y' || ch== 'Y'){
			SaveAllData();
			flag=0;
			return 0;
		}
	}
}
int userMenu(char account[100]){		//用户操作界面
	int choose;
	printf("\n\t\t****彩票管理系统****\n");
	printf("----------------------------------------------------\n");
	printf("\t亲爱的用户，欢迎您使用本系统！\n");
	do{
		printf("\n\t\t1.查看个人信息\n");
		printf("\t\t2.彩票购买历史\n");
		printf("\t\t3.账户充值\n");
		printf("\t\t4.购买彩票\n");
		printf("\t\t5.修改密码\n");
		printf("\t\t6.注销帐号\n");
		printf("\t请选择(输入0返回首页)：");
		scanf("%d",&choose);
		switch(choose){
			case 1:
				displayMyInfo(account);
				break;
			case 2:
				displayLotteryPurchaseHistory(account);
				break;
			case 3:
				userSurplusRecharge(account);
				flag=1;
				break;
			case 4:
				userBuyLotterMean(account);
				break;
			case 5:
				userModifyPassword(account);
				flag=1;
				break;
			case 6:
				printf("\n\t账户注销后，将无法恢复，请您再次确认是否注销%s该帐号(Y/N)？",account);
				char choose;
				getchar();
				scanf("%c",&choose);
				if(choose=='Y' || choose=='y'){
					deleteUserInfo(account);
					return 0;
				}else{
					printf("\n\t已取消注销该帐号，感谢您的使用，愿我们携手创造更美好的明天！^v^\n");
					break;
				}
			default:
				if(0<choose || 6<choose){
					printf("\n\t\t输入错误，请重新输入！\n");
					continue;;
				}
		}
	}while(choose != 0);
	if(flag==1){
		printf("\n\t检测到数据修改，是否保存(Y/N)？");
		char ch;
		getchar();
		scanf("%c",&ch);
		if(ch=='y' || ch== 'Y'){
			SaveAllData();
			flag=0;
			return 0;
		}
	}
}

void findUserMean(){
	int choose;
	do{
		printf("\n\t\t1.按用户帐号查询\n");
		printf("\t\t2.按余额区间查询\n");
		printf("\t\t请选择(输入0返回上一页)：");
		scanf("%d",&choose);
		switch(choose){
			case 1:
				findUserInfoByAccount();
				break;
			case 2:
				userBalanceFindUserInfo();
				break;
			default:
				if(0>choose || 2<choose){
					printf("\n\t\t输入错误，请重新输入！\n");
					continue;
				}
		}
	}while(choose != 0);
}
void sortUserMean(){
	int choose;
	do{
		printf("\n\t\t1.按帐号排序彩民信息\n");
		printf("\t\t2.按余额排序彩民信息\n");
		printf("\t\t请选择(输入0返回上一页)：");
		scanf("%d",&choose);
		switch(choose){
			case 1:
				AccountSortingUserInfo();
				displayAllUserInfo();
				break;
			case 2:
				SurplusSortingUserInfo();
				displayAllUserInfo();
				break;
			default:
				if(0>choose || 2<choose){
					printf("\n\t\t输入错误，请重新输入！\n");
					continue;
				}
		}
	}while(choose != 0);
}

void userBuyLotterMean(char account[100]){
	int choose;
	do{
		printf("\n\t\t1.电脑帮选\n");
		printf("\t\t2.用户自选\n");
		printf("\t\t3.批量帮选\n");
		printf("\t\t请选择(输入0返回上一页)：");
		scanf("%d",&choose);
		switch(choose){
			case 1:
				AIchoose(account);
				flag=1;
				break;
			case 2:
				userBuyLottery(account);
				flag=1;
				break;
			case 3:
				batchAIchoose(account);
				flag=1;
				break;
			default:
				if(0>choose || 3<choose){
					printf("\n\t\t输入错误，请重新输入！\n");
					continue;
				}
		}
	}while(choose != 0);
}

void SaveAllData(){
	saveAdmin();
	saveUserInfoNode();
	saveUserBuy();			
	printf("\n\t数据保存成功！\n");
}

void ReadAllData(){
	readAdmin();
	readUserInfoNode();
	readUserBuy();
}
