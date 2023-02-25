#include<stdio.h>
#include<stdlib.h>
#include"user.h"
#include<string.h>

UserInfoNode *head=NULL;
UserInfoNode *current=NULL;

void saveUserInfoNode(){
	FILE *fp=fopen("user.bat","w");
	UserInfoNode *temp=head;
	while(temp != NULL){
		fwrite(temp->data,sizeof(UserInfo),1,fp);
		temp=temp->next;
	}
	fclose(fp);
}

void readUserInfoNode(){
	int len;
	FILE *fp=fopen("user.bat","r");
	if(fp == NULL){
		printf("\t载入用户数据失败！\n");
		return;
	}
	UserInfo *user=malloc(sizeof(UserInfo));
	len=fread(user,sizeof(UserInfo),1,fp);
	while(len>0){	
		addUserInfoNode(user);
		user=malloc(sizeof(UserInfo));
		len=fread(user,sizeof(UserInfo),1,fp);
	}
	fclose(fp);
}

void addUserInfoNode(UserInfo *data){
	UserInfoNode *newNode=malloc(sizeof(UserInfoNode));
	newNode->data=data;
	newNode->next=NULL;
	if(head == NULL){
		head=newNode;
		current=newNode;
		return;
	}
	current->next=newNode;
	current=newNode;

}

void addNewUser(){	//彩民注册帐号
	char userAccount[100];
	char userPassword1[100];
	char userPassword2[200];
	char admin[100]="admin";
	char notary[100]="notary";
	do{
		printf("\n\t\t请输入帐号：");
		scanf("%s",userAccount);
		int newUser=findUser(userAccount);
		if(newUser==1){
			printf("\n\t%s该帐号已被注册，请重新输入！\n",userAccount);
			break;
		}	
		printf("\t\t请输入密码：");
		scanf("%s",userPassword1);
		printf("\t\t请确认密码：");
		scanf("%s",userPassword2);
		UserInfo *temp=malloc(sizeof(UserInfo));
		if(strcmp(userAccount,admin)!=0 && strcmp(userAccount,notary)!=0){
			if(strcmp(userPassword1,userPassword2)==0){
				strcpy(temp->userAccount,userAccount);
				strcpy(temp->userPassword,userPassword1);
				temp->userSurplus=0;
				addNewUserToNode(temp);
				temp->CumulativeWinnAmount=0;
				printf("\n\t帐号注册成功，请牢记您的密码！\n");
			}else{
				printf("\n\t两次输入密码不一致，请重新输入！\n");
			}
		}else{
			printf("\n\t该帐号禁止注册！\n");
		}	
	}while(strcmp(userPassword1,userPassword2)!=0);
}

void addNewUserToNode(UserInfo *data){	//添加彩民注册帐号至链表中
	UserInfoNode *newNode=malloc(sizeof(UserInfoNode));
	newNode->data=data;
	newNode->next=NULL;
	if(head==NULL){
		head=newNode;
		current=newNode;
		return;
	}
	current->next=newNode;
	current=newNode;

} 

int userLogin(char account[100],char password[100]){	//判断用户输入帐号及密码与注册帐号密码是否一致
	UserInfoNode *temp=head;
	while(temp!=NULL){
		if(strcmp(temp->data->userAccount,account)==0 && strcmp(temp->data->userPassword,password)==0){
			return 1;
		}
		temp=temp->next;
	}
	return 0;
}

int findUser(char userAccount[100]){
	UserInfoNode *temp=head;
	while(temp!=NULL){
		UserInfo *userInfoData=malloc(sizeof(UserInfo));
		userInfoData=temp->data;
		if(strcmp(userInfoData->userAccount,userAccount)==0){
			return 1;		//该帐号已注册
		}
		temp=temp->next;
	}
	return 0;				//该帐号未注册
}
void displayMyInfo(char account[100]){		//显示用户个人信息
	UserInfoNode *temp=head;
	while(temp!=NULL){
		UserInfo *userInfoData=malloc(sizeof(UserInfo));
		userInfoData=temp->data;
		if(strcmp(userInfoData->userAccount,account)==0){
			printf("\n\t\t帐号\t\t密码\t\t\t余额\t\t\t累计中奖金额\n");
			printf("\t\t%s\t\t%s\t\t\t%.2f\t\t\t%.2f\n",userInfoData->userAccount,userInfoData->userPassword,userInfoData->userSurplus,userInfoData->CumulativeWinnAmount);
			return;		
		}
		temp=temp->next;
	}
}
void userModifyPassword(char account[100]){	//用户修改密码
	UserInfoNode *temp=head;
	while(temp!=NULL){
		UserInfo *userInfoData=malloc(sizeof(UserInfo));
		userInfoData=temp->data;
		if(strcmp(userInfoData->userAccount,account)==0){
			char oldPassword[100];
			printf("\n\t\t请输入原密码：");
			scanf("%s",oldPassword);
			if(strcmp(oldPassword,userInfoData->userPassword)==0){
				char newpassword1[100];
				char newpassword2[100];
				printf("\n\t\t请输入新密码：");
				scanf("%s",newpassword1);
				printf("\n\t\t请确认新密码：");
				scanf("%s",newpassword2);
				if(strcmp(newpassword1,newpassword2)!=0){
					printf("\n\t两次密码输入不一致，请重试！\n");
					return;
				}
				strcpy(userInfoData->userPassword,newpassword1);
				printf("\n\t新密码修改成功，请牢记您的密码！\n");
				return;
			}else{
				printf("\n\t旧密码输入错误，请重试！\n");
			}
		}
		temp=temp->next;
	}
}
void userSurplusRecharge(char account[100]){		//用户账户充值
	UserInfoNode *temp=head;
	while(temp!=NULL){
		UserInfo *userInfoData=malloc(sizeof(UserInfo));
		userInfoData=temp->data;
		if(strcmp(userInfoData->userAccount,account)==0){
			int surplus;
			printf("\n\t请输入充值金额：");
			scanf("%d",&surplus);
			userInfoData->userSurplus+=surplus;
			printf("\n\t恭喜您，账户充值成功!\n");
			return;		
		}
		temp=temp->next;
	}
}
int userSurplusDecide(char account[100]){		//查询用户账户余额
	UserInfoNode *temp=head;
	while(temp!=NULL){
		UserInfo *userInfoData=malloc(sizeof(UserInfo));
		userInfoData=temp->data;
		if(strcmp(userInfoData->userAccount,account)==0){
			return 	userInfoData->userSurplus;
		}
		temp=temp->next;
	}
}
void ModifyUserSurplus(char account[100],int spend){	//用户购买彩票后减少余额
	UserInfoNode *temp=head;
	while(temp!=NULL){
		UserInfo *userInfoData=malloc(sizeof(UserInfo));
		userInfoData=temp->data;
		if(strcmp(userInfoData->userAccount,account)==0){
			userInfoData->userSurplus-=spend;
			return;
		}
		temp=temp->next;
	}
}

void userSurplusAdd(char account[100],int surplus){		//中奖后增加用户余额
	UserInfoNode *temp=head;
	while(temp!=NULL){
		UserInfo *userInfoData=malloc(sizeof(UserInfo));
		userInfoData=temp->data;
		if(strcmp(userInfoData->userAccount,account)==0){
			userInfoData->userSurplus+=surplus;
			return;		
		}
		temp=temp->next;
	}
}
void addUserCumulativeWinnAmount(char account[100],float amount){
	UserInfoNode *temp=head;
	while(temp!=NULL){
		UserInfo *userInfoData=malloc(sizeof(UserInfo));
		userInfoData=temp->data;
		if(strcmp(userInfoData->userAccount,account)==0){
			userInfoData->CumulativeWinnAmount+=amount;
			return;		
		}
		temp=temp->next;
	}


}
void findUserInfoByAccount(){			//管理员查看某一用户信息
	char account[100];
	printf("\n\t\t请输入账户帐号：");
	scanf("%s",account);
	displayMyInfo(account);
	displayLotteryPurchaseHistory(account);
}

void deleteUserInfo(char account[100]){		//用户注销帐号	
	UserInfoNode *temp=head;
	while(temp!=NULL){
		if(strcmp(temp->data->userAccount,account) == 0){
			UserInfoNode *preTemp=malloc(sizeof(UserInfoNode));
			preTemp=findPreUserInfoNode(temp);
			preTemp->next=temp->next;
			printf("\n\t%s用户您好，您的帐号已注销，非常感谢您的使用，期待与您再次相遇！^v^\n",account);
			return ;
		}
		temp=temp->next;
	}
}

UserInfoNode *findPreUserInfoNode(UserInfoNode *userInfo){	//查找链表中某一用户前一个用户
	UserInfoNode *temp=head;
	if(userInfo==head){
		return NULL;
	}
	while(temp!=NULL){
		if(temp->next!=NULL){
			if(temp->next == userInfo){
				return temp;
			}
		}
		temp=temp->next;
	}
}

void userBalanceFindUserInfo(){			//按余额查询彩民信息
	float min,max;
	printf("\n\t请输入查询余额最低值：");
	scanf("%f",&min);
	printf("\t请输入查询余额最高值：");
	scanf("%f",&max);
	printf("\n\t\t帐号\t\t密码\t\t\t余额\t\t\t累计中奖金额\n");
	UserInfoNode *temp=head;
	while(temp!=NULL){
		if(temp->data->userSurplus>=min && temp->data->userSurplus<=max){
			printf("\t\t%s\t\t%s\t\t\t%.2f\t\t\t%.2f\n",temp->data->userAccount,temp->data->userPassword,temp->data->userSurplus,temp->data->CumulativeWinnAmount);
		}
		temp=temp->next;
	}
}

void AccountSortingUserInfo(){		//按帐号排序彩民信息
	if(head==NULL || head->next==NULL){
		return;
	}
	for(UserInfoNode *t=head->next;t!=NULL;t=t->next){
		for(UserInfoNode *temp=head;temp!=t;temp=temp->next){
			if(strcmp(t->data->userAccount,temp->data->userAccount) < 0){
				UserInfoNode *prevT=findPreUserInfoNode(t);
				prevT->next=t->next;
				if(temp == head){
					t->next=head;
					head=t;
					break;
				}else{
					UserInfoNode *prevTemp=findPreUserInfoNode(temp);
					prevTemp->next=t;
					t->next=temp;
					break;
				}
			}
		}
	}
	current=head;
	while(current->next != NULL){
		current=current->next;
	}
}

void SurplusSortingUserInfo(){	//按余额排序彩民信息
	if(head==NULL || head->next==NULL){
		return;
	}
	for(UserInfoNode *t=head->next;t!=NULL;t=t->next){
		for(UserInfoNode *temp=head;temp!=t;temp=temp->next){
			if(t->data->userSurplus < temp->data->userSurplus){
				UserInfoNode *prevT=findPreUserInfoNode(t);
				prevT->next=t->next;
				if(temp == head){
					t->next=head;
					head=t;
					break;
				}else{
					UserInfoNode *prevTemp=findPreUserInfoNode(temp);
					prevTemp->next=t;
					t->next=temp;
					break;
				}
			}
		}
	}
	current=head;
	while(current->next != NULL){
		current=current->next;
	}
}

void displayAllUserInfo(){		//打印所有用户信息
	UserInfoNode *temp=head;
	printf("\n\t\t帐号\t\t密码\t\t\t余额\t\t\t累计中奖金额\n");
	while(temp!=NULL){
		
		printf("\t\t%s\t\t%s\t\t\t%.2f\t\t\t%.2f\n",temp->data->userAccount,temp->data->userPassword,temp->data->userSurplus,temp->data->CumulativeWinnAmount);
		temp=temp->next;
	}

}
