#include<stdio.h>
#include"admin.h"
#include<stdlib.h>
#include"lottery.h"
#include"user.h"

Admin *adminNodehead=NULL;
Admin *adminNodecurrent=NULL;

void saveAdmin(){
	FILE *fp=fopen("admin.bat","w");
	Admin *temp=adminNodehead;
	while(temp != NULL){
		fwrite(temp->data,sizeof(Publish),1,fp);
		temp=temp->next;
	}
	fclose(fp);
}

void readAdmin(){
	int len;
	FILE *fp=fopen("admin.bat","r");
	if(fp == NULL){
		printf("\t载入管理员数据失败！\n");
		return;
	}
	Publish *publish=malloc(sizeof(Publish));
	len=fread(publish,sizeof(Publish),1,fp);
	while(len>0){	
		addAdminNode(publish);
		publish=malloc(sizeof(Publish));
		len=fread(publish,sizeof(Publish),1,fp);
	}
	fclose(fp);
}

void addAdminNode(Publish *data){
	Admin *newNode=malloc(sizeof(Admin));
	newNode->data=data;
	newNode->next=NULL;
	if(adminNodehead == NULL){
		adminNodehead=newNode;
		adminNodecurrent=newNode;
		return;
	}
	adminNodecurrent->next=newNode;
	adminNodecurrent=newNode;

}
void adminPublishLottery(){	//管理员发布彩票
	int lotterState=userCanBuyLottery();
	if(lotterState == 1){
		int number,price;
		printf("\n\t请输入8位需发布彩票期号：");
		scanf("%d",&number);
		printf("\t请输入本期彩票单价：");
		scanf("%d",&price);
	
		Publish *newPublish=malloc(sizeof(Publish));
		newPublish->number=number;
		newPublish->price=price;
		newPublish->state=0;
		newPublish->total=0;
		newPublish->prize=0;
		newPublish->issueNumber[0]=0;

		Admin *temp=adminNodehead;
		while(temp!=NULL){
			if(temp->data->number == number){
				printf("\n\t彩票期号发布重复，请重新发布！\n");
				return;	
			}
			temp=temp->next;
		}
		Admin *newNode=malloc(sizeof(Admin));
		newNode->data=newPublish;
		newNode->next=NULL;
		if(adminNodehead==NULL){
			adminNodehead=newNode;
			adminNodecurrent=newNode;
			printf("\n\t%d期彩票发行成功！\n",number);
			return;
		}
		adminNodecurrent->next=newNode;
		adminNodecurrent=newNode;
		newNode->data->prize+=PreviousPrize(newNode);
		printf("\n\t%d期彩票发行成功！\n",number);
	}else{
		printf("\n\t等待上期彩票开奖后才能发布下一期彩票！\n");
	}
}
void displayadminPublishLottery(){		//管理员显示已发布彩票信息
	Admin *temp=adminNodehead;
	printf("\n\t彩票期号\t彩票单价\t开奖状态\t 开奖号码\t\t售出总数\t奖池金额\n");
	while(temp!=NULL){
		printf("\t%d\t%d\t\t%d\t  %02d-%02d-%02d-%02d-%02d-%02d---%02d\t%d\t\t%.2f\n",temp->data->number,temp->data->price,temp->data->state,temp->data->issueNumber[0],temp->data->issueNumber[1],temp->data->issueNumber[2],temp->data->issueNumber[3],temp->data->issueNumber[4],temp->data->issueNumber[5],temp->data->issueNumber[6],temp->data->total,temp->data->prize);
		temp=temp->next;
	}
}

int findLotteryBets(int number){		//查询彩票单注金额
	Admin *temp=adminNodehead;
	while(temp!=NULL){
		if(temp->data->number==number){
			return temp->data->price;
		}
		temp=temp->next;
	}
}
int userCanBuyLottery(){		//判断彩票是否已开奖
	Admin *temp=adminNodehead;
	while(temp!=NULL){
		if(temp->data->state == 0){ 	//0代表未开奖
			return temp->data->number;
		}
		temp=temp->next;
	}
	return 1;
}
void ModifyLotteryState(int number){		//彩票开奖后修改其开奖状态
	Admin *temp=adminNodehead;
	while(temp!=NULL){
		if(temp->data->number == number){ 	
			temp->data->state=1;
		}
		temp=temp->next;
	}
}
int lotterySoldTotal(int number){		//增加彩票售出数量
	Admin *temp=adminNodehead;
	while(temp!=NULL){
		if(temp->data->number == number){ 	
			temp->data->total++;
			return temp->data->total;
		}
		temp=temp->next;
	}
}
void addLotterPrize(int number,int userSpend){	//增加奖池金额
	Admin *temp=adminNodehead;
	while(temp!=NULL){
		if(temp->data->number == number){ 	
			temp->data->prize+=userSpend;
		}
		temp=temp->next;
	}
}

int findLotterPrize(int number){	//查找奖池金额
	Admin *temp=adminNodehead;
	while(temp!=NULL){
		if(temp->data->number == number){ 	
			return temp->data->prize;
		}
		temp=temp->next;
	}
}

void reduceLotterPrize(int number,int userSpend){	//增加奖池金额
	Admin *temp=adminNodehead;
	while(temp!=NULL){
		if(temp->data->number == number){ 	
			temp->data->prize+=userSpend;
		}
		temp=temp->next;
	}
}

void PrizePoolUpdates(int number,float userWin){	//用户中奖后减少奖池金额
	Admin *temp=adminNodehead;
	while(temp!=NULL){
		if(temp->data->number == number){ 	
			temp->data->prize-=userWin;
		}
		temp=temp->next;
	}
}

float PreviousPrize(Admin *newNode){			//返回上一期奖池金额
	Admin *temp=adminNodehead;
	if(newNode == adminNodehead){
		return 0;
	}
	while(temp != NULL){
		if(temp->next != NULL){
			if(temp->next == newNode){
				return temp->data->prize;
			}
		}
		temp=temp->next;
	}
}

void UpdateDrawNumberAfterTheDraw(int number,int issueNumber[7]){
	Admin *temp=adminNodehead;
	while(temp!=NULL){
		if(temp->data->number == number){ 	
			for(int i=0;i<7;i++){
				temp->data->issueNumber[i]=issueNumber[i];
			}
		}
		temp=temp->next;
	}

}
void addPrize(){
	int canBuy=userCanBuyLottery();
	if(canBuy!=1){
		int num;
		printf("\n\t请输入本期奖池需增加金额：");
		scanf("%d",&num);
		reduceLotterPrize(canBuy,num);
	}else{
		printf("\n\t当前无彩票期号需增加奖池金额！\n");
	}
}
