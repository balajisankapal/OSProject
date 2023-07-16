#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <stdbool.h>

typedef struct normal_user
{
	int userId;
	char userName[30];
	char password[20];
	int acc_Number;
	float acc_Balance;
	char acc_status[20];
} normalUser;

typedef struct joint_user
{
	int userId;
	char userName1[30];
	char userName2[30];
	char password[20];
	int acc_Number;
	float acc_Balance;
	char acc_Status[20];
} jointUser;

typedef struct admin
{
	int userId;
	char userName[30];
	char password[20];
} admin;

void NormalUserLogin(int sd);
void JointUserLogin(int sd);
void AdminLogin(int sd);
void Menu(int sd);
void Deposit(int sd);
void Withdraw(int sd);
void BalanceEnquiry(int sd);
void ChangePassword(int sd);
void ViewDetails(int sd);
void AddAccount(int sd);
void DeleteAccount(int sd);
void ModifyAccount(int sd);
void SearchAccount(int sd);

int login_option;
int UserId;

void LoginOption(int sd)
{
	while (1)
	{
		write(1, "Choose an option : \n", sizeof("Choose an option : \n"));
		write(1, "1 :Login as Normal-User \n", sizeof("1 :Login as Normal-User \n"));
		write(1, "2 :Login as Joint Account-User\n", sizeof("2 :Login as Joint Account-User\n"));
		write(1, "3 :Login as Admin\n", sizeof("3 :Login as Admin\n"));

		scanf("%d", &login_option);
		printf("Login Option Choosen is : %d\n", login_option);

		if (login_option == 1)
		{
			NormalUserLogin(sd);
			break;
		}
		else if (login_option == 2)
		{
			JointUserLogin(sd);
			break;
		}
		else if (login_option == 3)
		{
			AdminLogin(sd);
			break;
		}
		else write(1,"Invalid Login Option\n",sizeof("Invalid Login Option\n"));
	}
	return;
}

void Menu(int sd)
{
	int select_operation;
	if (login_option == 1)
	{
		write(1, "1 : Normal User Account - Deposit\n", sizeof("1 : Normal User Account - Deposit\n"));
		write(1, "2 : Normal User Account - Withdraw\n", sizeof("2 : Normal User Account - Withdraw\n"));
		write(1, "3 : Normal User Account - Balance Enquiry\n", sizeof("3 : Normal User Account - Balance Enquiry\n"));
		write(1, "4 : Normal User Account - Password Change\n", sizeof("4 : Normal User Account - Password Change\n"));
		write(1, "5 : Normal User Account - View Details\n", sizeof("5 : Normal User Account - View Details\n"));
		write(1, "6 : Normal User Account - Exit\n", sizeof("6 : Normal User Account - Exit\n"));

		write(1, "Choose an Operation of Normal User Account: ", sizeof("Choose an Operation of Normal User Account: "));
		scanf("%d", &select_operation);
		printf("Option : %d\n", select_operation);

		switch (select_operation)
		{
		case 1:
			Deposit(sd);
			break;
		case 2:
			Withdraw(sd);
			break;
		case 3:
			BalanceEnquiry(sd);
			break;
		case 4:
			ChangePassword(sd);
			break;
		case 5:
			ViewDetails(sd);
			break;
		case 6:
			write(sd, &select_operation, sizeof(int));
			write(1, "Thank you\n", sizeof("Thank you\n"));
			exit(0);
		default:
			write(1, "Invalid option!!\n\n", sizeof("Invalid option!!\n\n"));
			Menu(sd);
			break;
		}
	}
	else if (login_option == 2)
	{
		write(1, "1 : Joint User Account - Deposit\n", sizeof("1 : Joint User Account - Deposit\n"));
		write(1, "2 : Joint User Account - Withdraw\n", sizeof("2 : Joint User Account - Withdraw\n"));
		write(1, "3 : Joint User Account - Balance Enquiry\n", sizeof("3 : Joint User Account - Balance Enquiry\n"));
		write(1, "4 : Joint User Account - Password Change\n", sizeof("4 : Joint User Account - Password Change\n"));
		write(1, "5 : Joint User Account - View Details\n", sizeof("5 : Joint User Account - View Details\n"));
		write(1, "6 : Joint User Account - Exit\n", sizeof("6 : Joint User Account - Exit\n"));

		write(1, "Choose an Operation of Joint User Account: ", sizeof("Choose an Operation of Joint User Account: "));
		scanf("%d", &select_operation);
		printf("Option : %d\n", select_operation);

		switch (select_operation)
		{
		case 1:
			Deposit(sd);
			break;
		case 2:
			Withdraw(sd);
			break;
		case 3:
			BalanceEnquiry(sd);
			break;
		case 4:
			ChangePassword(sd);
			break;
		case 5:
			ViewDetails(sd);
			break;
		case 6:
			write(sd, &select_operation, sizeof(int));
			write(1, "Thank you\n", sizeof("Thank you\n"));
			exit(0);
		default:
			write(1, "Invalid option!!\n\n", sizeof("Invalid option!!\n\n"));
			Menu(sd);
			break;
		}
	}
	else if (login_option == 3)
	{
		write(1, "1 : Admin - Add Account\n", sizeof("1 : Admin - Add Account\n"));
		write(1, "2 : Admin - Delete Account\n", sizeof("2 : Admin - Delete Account\n"));
		write(1, "3 : Admin - Modify Account\n", sizeof("3 : Admin - Modify Account\n"));
		write(1, "4 : Admin - Search Account\n", sizeof("4 : Admin - Search Account\n"));
		write(1, "5 : Admin - Exit\n", sizeof("6 : Admin - Exit\n"));

		write(1, "Choose an Operation as Admin: ", sizeof("Choose an Operation as Admin: "));
		scanf("%d", &select_operation);
		printf("Option : %d\n", select_operation);

		switch (select_operation)
		{
		case 1:
			AddAccount(sd);
			break;
		case 2:
			DeleteAccount(sd);
			break;
		case 3:
			ModifyAccount(sd);
			break;
		case 4:
			SearchAccount(sd);
			break;
		case 5:
			write(sd, &select_operation, sizeof(int));
			write(1, "Thank you\n", sizeof("Thank you\n"));
			exit(0);
		default:
			write(1, "Invalid option!!\n", sizeof("Invalid option!!\n"));
			Menu(sd);
			break;
		}
	}
}

void NormalUserLogin(int sd)
{
	normalUser nuser;
	write(1, "Enter Normal User ID : ", sizeof("Enter Normal User ID : "));
	scanf("%d", &nuser.userId);
	write(1, "Enter Password : ", sizeof("Enter Password : "));
	scanf("%s", nuser.password);
	UserId = nuser.userId;

	// Server
	bool ans;
	write(sd, &login_option, sizeof(int));
	write(sd, &nuser, sizeof(normalUser));
	read(sd, &ans, sizeof(ans));

	if (!ans)
	{
		write(1, "Invalid Login Credential\n", sizeof("Invalid login Credential\n"));
		LoginOption(sd);
	}
	else
	{
		write(1, "Login Successful\n", sizeof("Login Successful\n"));
	}
	return;
}

void JointUserLogin(int sd)
{
	jointUser juser;
	write(1, "Enter Joint User ID : ", sizeof("Enter Joint User ID : "));
	scanf("%d", &juser.userId);
	write(1, "Enter Password : ", sizeof("Enter Password : "));
	scanf("%s", juser.password);
	UserId = juser.userId;

	// Server
	bool ans;
	write(sd, &login_option, sizeof(int));
	write(sd, &juser, sizeof(jointUser));
	read(sd, &ans, sizeof(ans));

	if (!ans)
	{
		write(1, "Invalid Login Credential\n", sizeof("Invalid login Credential\n"));
		LoginOption(sd);
	}
	else
	{
		write(1, "Login Successful\n", sizeof("Login Successful\n"));
	}
	return;
}

void AdminLogin(int sd)
{
	admin auser;
	write(1, "Enter Admin ID : ", sizeof("Enter Admin ID : "));
	scanf("%d", &auser.userId);
	write(1, "Enter Password : ", sizeof("Enter Password : "));
	scanf("%s", auser.password);
	UserId = auser.userId;

	// Server
	bool ans;
	write(sd, &login_option, sizeof(int));
	write(sd, &auser, sizeof(admin));
	read(sd, &ans, sizeof(ans));

	if (!ans)
	{
		write(1, "Invalid Login Credential\n", sizeof("Invalid login Credential\n"));
		LoginOption(sd);
	}
	else
	{
		write(1, "Login Successful\n", sizeof("Login Successful\n"));
	}
	return;
}

void Deposit(int sd)
{
	float amount;
	int t = 1;

	write(1, "Amount to be Deposited : (in Rs)", sizeof("Amount to be Deposited : (in Rs)"));
	scanf("%f", &amount);

	// Server
	bool res;
	write(sd, &t, sizeof(int));
	write(sd, &amount, sizeof(float));
	read(sd, &res, sizeof(res));

	if (!res)
	{
		write(1, "Error\n", sizeof("Error\n"));
	}
	else
	{
		write(1, "Successfully Deposited\n", sizeof("Successfully Deposited\n"));
	}
	Menu(sd);
	return ;
}

void Withdraw(int sd)
{
	float amount;
	int t = 2;

	write(1, "Amount to Withdraw : (in Rs)", sizeof("Amount to Withdraw : (in Rs)"));
	scanf("%f", &amount);

	// Server
	bool res;
	write(sd, &t, sizeof(int));
	write(sd, &amount, sizeof(float));
	read(sd, &res, sizeof(res));

	if (!res)
	{
		write(1, "Error\n", sizeof("Error\n"));
	}
	else
	{
		write(1, "Successfully Withdrew\n", sizeof("Successfully Withdrew\n"));
	}
	Menu(sd);
	return ;
}

void BalanceEnquiry(int sd)
{
	float amount;
	int t=3;

	//Server
	write(sd,&t,sizeof(int));
	int length =read(sd,&amount,sizeof(float));	
	write(1,"Available Balance :: Rs.",sizeof("Available Balance :: Rs."));
	printf("%0.2f\n",amount);

	Menu(sd);
	return;
}

void ChangePassword(int sd)
{
	int t=4;
	char newPwd[20];
	bool res;

	write(1,"Enter New Password : ", sizeof("Enter New Password : "));
	scanf("%s",newPwd);

	//Server
	write(sd,&t,sizeof(int));
	write(sd,newPwd,sizeof(newPwd));
	read(sd,&res,sizeof(res)); 

	if(!res){
		write(1,"Error\n",sizeof("Error\n"));
	}
	else{
		write(1,"Password Changed Successfully\n",sizeof("Password Changed Successfully\n"));
	}
	Menu(sd);
	return;
}

void ViewDetails(int sd)
{
	int t=5;

	//Server
	write(sd,&t,sizeof(int));

	if(login_option==1){
		normalUser user1;
		read(sd,&user1,sizeof(normalUser));
		
		printf("User ID : %d\n",user1.userId);
		printf("Name : %s\n",user1.userName);
		printf("Account Number : %d\n",user1.acc_Number);
		printf("Available Balance : Rs.%0.2f\n",user1.acc_Balance);
		printf("Status : %s\n",user1.acc_status);
	}
	else if(login_option==2){
		jointUser user2;
		read(sd,&user2,sizeof(jointUser));
		
		printf("User Id : %d\n",user2.userId);
		printf("1st User's Name : %s\n",user2.userName1);
		printf("2nd User's Name : %s\n",user2.userName2);
		printf("Account Number : %d\n",user2.acc_Number);
		printf("Account Balance : Rs. %0.2f \n",user2.acc_Balance);
		printf("Account Status : %s\n",user2.acc_Status);
	}
	Menu(sd);
	return;
}

void AddAccount(int sd){
	int t=1;
	int acc;
	bool res;

	write(sd,&t,sizeof(int));

	write(1,"Enter Account Type\n1: Normal User Account 2: Joint User Account: ",sizeof("Enter Account Type\n1: Normal User Account 2: Joint User Account: "));
	scanf("%d",&acc);
	write(sd,&acc,sizeof(int));

	if(acc==1){
		normalUser user1;
		write(1,"Account Holder Name: ",sizeof("Account Holder Name: "));
		scanf(" %[^\n]",user1.userName);
		write(1,"Password: ",sizeof("Password: "));
		scanf("%s",user1.password);
		write(1,"Deposit: Rs.",sizeof("Deposit: Rs."));
		scanf("%f",&user1.acc_Balance);
		write(sd,&user1,sizeof(normalUser));
	}
	if(acc==2){
		jointUser user2;
		write(1,"Account Holder Name 1: ",sizeof("Account Holder Name 1: "));
		scanf(" %[^\n]",user2.userName1);
		write(1,"Account Holder Name 2 : ",sizeof("Account Holder Name 2: "));
		scanf(" %[^\n]",user2.userName2);
		write(1,"Password: ",sizeof("Password: "));
		scanf("%s",user2.password);
		write(1,"Deposit: Rs.",sizeof("Deposit: Rs."));
		scanf("%f",&user2.acc_Balance);
		write(sd,&user2,sizeof(jointUser));
	}
	read(sd,&res,sizeof(res)); 

	if(!res){
		write(1,"Error\n",sizeof("Error\n"));
	}
	else{
		write(1,"Account Added Successfully\n",sizeof("Account Added Successfully\n"));
	}
	Menu(sd);
	return;
}

void DeleteAccount(int sd){
	int t=2;
	int acc,ID;
	bool res;

	write(sd,&t,sizeof(int));
	write(1,"Enter the type account\n1: Normal Account 2: Joint Account: ",sizeof("Enter the type account\n1: Normal Account 2: Joint Account: "));
	scanf("%d",&acc);
	write(sd,&acc,sizeof(int));
	write(1,"Enter User ID: ",sizeof("Enter User ID: "));
	scanf("%d",&ID);
	write(sd,&ID,sizeof(int));
	read(sd,&res,sizeof(res)); 

	if(!res){
		write(1,"Error\n",sizeof("Error\n"));
	}
	else{
		write(1,"Deleted Account Succesfully\n",sizeof("Deleted Account Succesfully\n"));
	}
	Menu(sd);
	return;
}

void ModifyAccount(int sd)
{
	int t = 3;
	int acc;
	bool res;

	write(sd,&t,sizeof(int));

	write(1,"Enter the type account\n1: Normal Account 2: Joint Account : ",sizeof("Enter the type account\n1: Normal Account 2: Joint Account : "));
	scanf("%d",&acc);

	write(sd,&acc,sizeof(int));

	if(acc==1){
		normalUser modUser1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser1.userId);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser1.acc_Number);
		write(1,"Name of the New Account Holder : ",sizeof("Name of the New Account Holder : "));
		scanf(" %s",modUser1.userName);
		write(1,"New Password : ",sizeof("New Password : "));
		scanf("%s",modUser1.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser1.acc_Balance);
		write(sd,&modUser1,sizeof(normalUser));
	}

	if(acc==2){
		jointUser modUser2;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser2.userId);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser2.acc_Number);
		write(1,"Name of the New 1st Account Holder : ",sizeof("Name of the New 1st Account Holder : "));
		scanf(" %s",modUser2.userName1);
		write(1,"Name of the New 2nd Account Holder : ",sizeof("Name of the New 2nd Account Holder : "));
		scanf(" %s",modUser2.userName2);
		write(1,"New Password : ",sizeof("New Password : "));
		scanf("%s",modUser2.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser2.acc_Balance);
		write(sd,&modUser2,sizeof(jointUser));
	}
	
	read(sd,&res,sizeof(res)); 

	if(!res){
		write(1,"Error\n",sizeof("Error\n"));
	}
	else{
		write(1,"Modified Account Succesfully\n",sizeof("Modified Account Succesfully\n"));
	}
	Menu(sd);
	return;
}

void SearchAccount(int sd){
	int t=4;
	int acc,len;
	bool res;

	write(sd,&t,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&acc);

	write(sd,&acc,sizeof(int));

	if(acc==1){
		normalUser searchUser1;
		int userID;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID);
		write(sd,&userID,sizeof(int));
		
		len=read(sd,&searchUser1,sizeof(normalUser));
		if(len==0){
			write(1,"Invalid User ID\n",sizeof("Invalid User ID\n"));
		}
		else{
			printf("User ID : %d\n",searchUser1.userId);
			printf("User Name : %s\n",searchUser1.userName);
			printf("Account Number : %d\n",searchUser1.acc_Number);
			printf("Available Balance : Rs.%0.2f\n",searchUser1.acc_Balance);
			printf("Status : %s\n\n",searchUser1.acc_status);
		}
	}

	if(acc==2){
		jointUser searchUser2;
		int userID;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID);
		write(sd,&userID,sizeof(int));
		
		len=read(sd,&searchUser2,sizeof(jointUser));
		if(len==0){
			write(1,"Invalid User ID\n",sizeof("Invalid User ID\n"));
		}
		else{
			printf("User ID : %d\n",searchUser2.userId);
			printf("1st Account Holder's Name : %s\n",searchUser2.userName1);
			printf("2nd Account Holder's Name : %s\n",searchUser2.userName2);
			printf("Account Number : %d\n",searchUser2.acc_Number);
			printf("Available Balance : Rs.%0.2f\n",searchUser2.acc_Balance);
			printf("Status : %s\n\n",searchUser2.acc_Status);
		}
	}
	Menu(sd);
	return;
}

int main(){
	struct sockaddr_in server;
	int sd,msgLength;
	char buff[50];
	char result;

	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY; 
	server.sin_port=htons(5573);
	connect(sd,(struct sockaddr *)&server,sizeof(server));

	LoginOption(sd);
	Menu(sd);	

	close(sd);

	return 0;
}
