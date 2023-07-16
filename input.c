#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

typedef struct normal_user{
    int userId;
    char userName[30];
    char password[20];
    int acc_Number;
    float acc_Balance;
    char acc_status[20];
}normalUser;

typedef struct joint_user{
    int userId;
    char userName1[30];
    char userName2[30];
    char password[20];
    int acc_Number;
    float acc_Balance;
    char acc_Status[20];
}jointUser;

typedef struct admin{
    int userId;
    char userName[30];
    char password[20];
}admin;

int getnewAdminId(){
	int fd=open("AdminFile",O_RDONLY,0744);
    admin rec;
	lseek(fd, -sizeof(admin),SEEK_END);
	read(fd,&rec,sizeof(admin));
	close(fd);
	return rec.userId+1;
}

int getnewUserId(){
	int fd=open("UserFile",O_RDONLY,0744);
	normalUser rec;
	lseek(fd,-sizeof(normalUser),SEEK_END);
	read(fd,&rec,sizeof(normalUser));
	close(fd);
	return rec.userId+1;
}

int getnewJUId(){
	int fd=open("JointUserFile",O_RDONLY,0744);
	jointUser rec;
	lseek(fd,-sizeof(jointUser),SEEK_END);
	read(fd,&rec,sizeof(jointUser));
	close(fd);
	return rec.userId+1;
}

int main()
{
    int fd = open("AdminFile", O_CREAT|O_RDWR, 0744);
    int continue_choice;
    admin Admin;
    printf("Enter Admin Name: ");
    scanf("%s", Admin.userName);
    printf("Enter Admin Password: ");
    scanf("%s", Admin.password);
    Admin.userId = 1000;
    printf("Assigned Admin userID is : %d\n",Admin.userId);
	write(fd,&Admin,sizeof(Admin));
	printf("Do you want to Continue(0/1)?");
	scanf("%d",&continue_choice);
    while(continue_choice)
    {
        printf("Enter Admin Name: ");
        scanf("%s", Admin.userName);
        printf("Enter Admin Password: ");
        scanf("%s", Admin.password);
        Admin.userId = getnewAdminId();
        printf("Assigned Admin userID is : %d\n",Admin.userId);
	    write(fd,&Admin,sizeof(Admin));
	    printf("Do you want to Continue(0/1)?");
	    scanf("%d",&continue_choice);
    }
    close(fd);

    continue_choice = 1;
    fd=open("UserFile",O_RDWR | O_CREAT,0744);
    normalUser NewUser;
    printf("Enter Normal User Name: ");
	scanf("%s",NewUser.userName);
	printf("Enter the Password: ");
	scanf("%s",NewUser.password);
	NewUser.userId=1000;
	NewUser.acc_Balance=5000;
	NewUser.acc_Number=NewUser.userId+100000-1000;
	printf("Your userID is : %d\n",NewUser.userId);
	strcpy(NewUser.acc_status, "ACTIVE");
	write(fd,&NewUser,sizeof(normalUser));
	printf("Do you want to Continue(0/1)? ");
	scanf("%d",&continue_choice);
	while(continue_choice){
		printf("Enter Normal User Name: ");
	    scanf("%s",NewUser.userName);
	    printf("Enter the Password: ");
	    scanf("%s",NewUser.password);
	    NewUser.userId=getnewUserId();
	    NewUser.acc_Balance=5000;
	    NewUser.acc_Number=NewUser.userId-1000+100000;
	    printf("Your userID is : %d\n",NewUser.userId);
	    strcpy(NewUser.acc_status, "ACTIVE");
	    write(fd,&NewUser,sizeof(normalUser));
	    printf("Do you want to Continue(0/1)? ");
	    scanf("%d",&continue_choice);
	}
	close(fd);

    continue_choice = 1;
    fd=open("JointUserFile",O_RDWR | O_CREAT,0744);
    jointUser newJointUser;
	printf("Enter 1st user's name of the Joint User: ");
	scanf("%s",newJointUser.userName1);
	printf("Enter 2nd user's name of the Joint User: ");
	scanf("%s",newJointUser.userName2);
	printf("Enter the Password: ");
	scanf("%s",newJointUser.password);
	newJointUser.userId=1000;
	newJointUser.acc_Balance=10000;
	newJointUser.acc_Number=newJointUser.userId-1000+100000;
	printf("Your userID is : %d\n",newJointUser.userId);
	strcpy(newJointUser.acc_Status,"ACTIVE");
	write(fd,&newJointUser,sizeof(jointUser));
	printf("Do you want to Continue(0/1)? ");
	scanf("%d",&continue_choice);
	while(continue_choice){
		printf("Enter 1st user's name of the Joint User: ");
	    scanf("%s",newJointUser.userName1);
	    printf("Enter 2nd user's name of the Joint User: ");
	    scanf("%s",newJointUser.userName2);
	    printf("Enter the Password: ");
	    scanf("%s",newJointUser.password);
		newJointUser.userId=getnewJUId();
		newJointUser.acc_Balance=10000;
		newJointUser.acc_Number=(newJointUser.userId-1000)+100000;
		printf("Your userID is : %d\n",newJointUser.userId);
		strcpy(newJointUser.acc_Status,"ACTIVE");
		write(fd,&newJointUser,sizeof(jointUser));
		printf("Do you want to Continue(0/1)? ");
		scanf("%d",&continue_choice);
	}
	close(fd);
	return 0;
}
