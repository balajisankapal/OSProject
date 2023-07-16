#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>

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

normalUser getNormalUser(int Id)
{
    int i = Id - 1000;
    normalUser user;
    int fd = open("UserFile", O_RDONLY, 0744);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(normalUser);
    lock.l_len = sizeof(normalUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);
    //getchar();
    lseek(fd, (i) * sizeof(normalUser), SEEK_SET);
    read(fd, &user, sizeof(normalUser));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return user;
}

jointUser getJointUser(int Id)
{
    int i = Id - 1000;
    jointUser user;
    int fd = open("JointUserFile", O_RDONLY, 0744);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(jointUser);
    lock.l_len = sizeof(jointUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);
    //getchar();
    lseek(fd, (i) * sizeof(jointUser), SEEK_SET);
    read(fd, &user, sizeof(jointUser));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return user;
}

admin getAdmin(int Id)
{
    int i = Id-1000;
    admin user;
    int fd = open("AdminFile", O_RDONLY, 0744);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(admin);
    lock.l_len = sizeof(admin);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);
    //getchar();
    lseek(fd, (i) * sizeof(admin), SEEK_SET);
    read(fd, &user, sizeof(admin));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return user;
}

bool verifyNormalUser(normalUser user)
{
    int i = user.userId - 1000;
    int fd = open("UserFile", O_RDONLY, 0744);
    bool res;
    normalUser tempUser;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(normalUser);
    lock.l_len = sizeof(normalUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);
    //getchar();

    lseek(fd, (i) * sizeof(normalUser), SEEK_SET);
    read(fd, &tempUser, sizeof(normalUser));
    if (!strcmp(tempUser.password, user.password) && !strcmp(tempUser.acc_status, "ACTIVE"))
        res = true;
    else
        res = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return res;
}

bool verifyJointUser(jointUser user)
{
    int i = user.userId - 1000;
    int fd = open("JointUserFile", O_RDONLY, 0744);
    bool res;
    jointUser tempUser;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(jointUser);
    lock.l_len = sizeof(jointUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);
    //getchar();
    lseek(fd, (i) * sizeof(jointUser), SEEK_SET);
    read(fd, &tempUser, sizeof(jointUser));
    if (!strcmp(tempUser.password, user.password) && !strcmp(tempUser.acc_Status, "ACTIVE"))
        res = true;
    else
        res = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return res;
}

bool verifyAdmin(admin user)
{
    int i = user.userId - 1000;
    int fd = open("AdminFile", O_RDONLY, 0744);
    bool res;
    admin tempUser;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(admin);
    lock.l_len = sizeof(admin);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);
    //getchar();
    lseek(fd, (i) * sizeof(admin), SEEK_SET);
    read(fd, &tempUser, sizeof(admin));
    if (!strcmp(tempUser.password, user.password))
        res = true;
    else
        res = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return res;
}

bool deposit(int accType, int ID, float amount)
{
    int i;
    if (accType == 1)
    {
        // Normal User
        i = ID - 1000;
        int fd = open("UserFile", O_RDWR, 0744);
        bool res;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (i) * sizeof(normalUser);
        lock.l_len = sizeof(normalUser);
        lock.l_pid = getpid();

        int filelock = fcntl(fd, F_SETLKW, &lock);
        getchar();

        normalUser user;
        lseek(fd, (i) * sizeof(normalUser), SEEK_SET);
        read(fd, &user, sizeof(normalUser));

        if (!strcmp(user.acc_status, "ACTIVE"))
        {
            user.acc_Balance += amount;
            lseek(fd, sizeof(normalUser) * (-1), SEEK_CUR);
            write(fd, &user, sizeof(normalUser));
            res = true;
        }
        else
            res = false;
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);

        close(fd);
        return res;
    }
    else if (accType == 2)
    {
        // JOINT USER
        i = ID - 1000;
        int fd = open("JointUserFile", O_RDWR, 0744);
        bool res;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (i) * sizeof(jointUser);
        lock.l_len = sizeof(jointUser);
        lock.l_pid = getpid();

        int filelock = fcntl(fd, F_SETLKW, &lock);
        jointUser user;
        lseek(fd, (i) * sizeof(jointUser), SEEK_SET);
        read(fd, &user, sizeof(jointUser));

        if (!strcmp(user.acc_Status, "ACTIVE"))
        {
            user.acc_Balance += amount;
            lseek(fd, sizeof(jointUser) * (-1), SEEK_CUR);
            write(fd, &user, sizeof(jointUser));
            res = true;
        }
        else
            res = false;
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);

        close(fd);
        return res;
    }
    return false;
}

bool withdraw(int accType, int ID, float amount)
{
    int i;
    if (accType == 1)
    {
        i = ID - 1000;
        int fd = open("UserFile", O_RDWR, 0744);
        bool res;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (i) * sizeof(normalUser);
        lock.l_len = sizeof(normalUser);
        lock.l_pid = getpid();

        int filelock = fcntl(fd, F_SETLKW, &lock);

        normalUser user;
        lseek(fd, (i) * sizeof(normalUser), SEEK_SET);
        read(fd, &user, sizeof(normalUser));

        if (!strcmp(user.acc_status, "ACTIVE") && user.acc_Balance >= amount)
        {
            user.acc_Balance -= amount;
            lseek(fd, sizeof(normalUser) * (-1), SEEK_CUR);
            write(fd, &user, sizeof(normalUser));
            res = true;
        }
        else
            res = false;
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);

        close(fd);
        return res;
    }
    else if (accType == 2)
    {
        i = ID - 1000;
        int fd = open("JointUserFile", O_RDWR, 0744);
        bool res;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (i) * sizeof(jointUser);
        lock.l_len = sizeof(jointUser);
        lock.l_pid = getpid();

        int filelock = fcntl(fd, F_SETLKW, &lock);

        jointUser user;
        lseek(fd, (i) * sizeof(jointUser), SEEK_SET);
        read(fd, &user, sizeof(jointUser));

        if (!strcmp(user.acc_Status, "ACTIVE") && user.acc_Balance >= amount)
        {
            user.acc_Balance -= amount;
            lseek(fd, sizeof(jointUser) * (-1), SEEK_CUR);
            write(fd, &user, sizeof(jointUser));
            res = true;
        }
        else
            res = false;
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);

        close(fd);
        return res;
    }
    return false;
}

float getBalance(int accType, int ID)
{
    int i;
    float res;
    if (accType == 1)
    {
        i = ID - 1000;
        int fd = open("UserFile", O_RDONLY, 0744);
        normalUser user;

        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (i) * sizeof(normalUser);
        lock.l_len = sizeof(normalUser);
        lock.l_pid = getpid();

        int filelock = fcntl(fd, F_SETLKW, &lock);

        lseek(fd, (i) * sizeof(normalUser), SEEK_SET);
        read(fd, &user, sizeof(normalUser));
        if (!strcmp(user.acc_status, "ACTIVE"))
            res = user.acc_Balance;
        else
            res = 0;

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);

        close(fd);
        return res;
    }
    else if (accType == 2)
    {
        i = ID - 1000;
        int fd = open("JointUserFile", O_RDONLY, 0744);
        jointUser user;

        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (i) * sizeof(jointUser);
        lock.l_len = sizeof(jointUser);
        lock.l_pid = getpid();

        int filelock = fcntl(fd, F_SETLKW, &lock);

        lseek(fd, (i) * sizeof(jointUser), SEEK_SET);
        read(fd, &user, sizeof(jointUser));
        if (!strcmp(user.acc_Status, "ACTIVE"))
            res = user.acc_Balance;
        else
            res = 0;

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);

        close(fd);
        return res;
    }
    return 0;
}

bool changePassword(int accType, int ID, char updatedPwd[20])
{
    int i;
    if (accType == 1)
    {
        i = ID - 1000;
        int fd = open("UserFile", O_RDWR, 0744);
        bool res;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (i) * sizeof(normalUser);
        lock.l_len = sizeof(normalUser);
        lock.l_pid = getpid();

        int filelock = fcntl(fd, F_SETLKW, &lock);

        normalUser user;
        lseek(fd, (i) * sizeof(normalUser), SEEK_SET);
        read(fd, &user, sizeof(normalUser));

        if (!strcmp(user.acc_status, "ACTIVE"))
        {
            strcpy(user.password, updatedPwd);
            lseek(fd, sizeof(normalUser) * (-1), SEEK_CUR);
            write(fd, &user, sizeof(normalUser));
            res = true;
        }
        else
            res = false;
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);

        close(fd);
        return res;
    }
    else if (accType == 2)
    {
        i = ID - 1000;
        int fd = open("JointUserFile", O_RDWR, 0744);
        bool res;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (i) * sizeof(jointUser);
        lock.l_len = sizeof(jointUser);
        lock.l_pid = getpid();

        int filelock = fcntl(fd, F_SETLKW, &lock);

        jointUser user;
        lseek(fd, (i) * sizeof(jointUser), SEEK_SET);
        read(fd, &user, sizeof(jointUser));

        if (!strcmp(user.acc_Status, "ACTIVE"))
        {
            strcpy(user.password, updatedPwd);
            lseek(fd, sizeof(jointUser) * (-1), SEEK_CUR);
            write(fd, &user, sizeof(jointUser));
            res = true;
        }
        else
            res = false;
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);

        close(fd);
        return res;
    }
    return false;
}

bool addNormalUser(normalUser newUser)
{
    int fd = open("UserFile", O_RDWR, 0744);
    bool res;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = (-1) * sizeof(normalUser);
    lock.l_len = sizeof(normalUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);

    // User Entry at last of the file
    normalUser LastUser;
    lseek(fd, (-1) * sizeof(normalUser), SEEK_END);
    read(fd, &LastUser, sizeof(normalUser));

    newUser.userId = LastUser.userId + 1;
    newUser.acc_Number = LastUser.acc_Number + 1;
    strcpy(newUser.acc_status, "ACTIVE");

    int j = write(fd, &newUser, sizeof(normalUser));
    if (j != 0)
        res = true;
    else
        res = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return res;
}

bool addJointUser(jointUser newUser)
{
    int fd = open("JointUserFile", O_RDWR, 0744);
    bool res;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = (-1) * sizeof(jointUser);
    lock.l_len = sizeof(jointUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);

    jointUser LastUser;
    lseek(fd, (-1) * sizeof(jointUser), SEEK_END);
    read(fd, &LastUser, sizeof(jointUser));

    newUser.userId = LastUser.userId + 1;
    newUser.acc_Number = LastUser.acc_Number + 1;
    strcpy(newUser.acc_Status, "ACTIVE");

    int j = write(fd, &newUser, sizeof(jointUser));
    if (j != 0)
        res = true;
    else
        res = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return res;
}

bool deleteNormalUser(int ID)
{
    int i = ID - 1000;
    int fd = open("UserFile", O_RDWR, 0744);
    bool res;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(normalUser);
    lock.l_len = sizeof(normalUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);
    normalUser user;
    lseek(fd, (i) * sizeof(normalUser), SEEK_SET);
    read(fd, &user, sizeof(normalUser));

    if (!strcmp(user.acc_status, "ACTIVE"))
    {
        strcpy(user.acc_status, "CLOSED");
        user.acc_Balance = 0;

        lseek(fd, (-1) * sizeof(normalUser), SEEK_CUR);
        int j = write(fd, &user, sizeof(normalUser));
        if (j != 0)
            res = true;
        else
            res = false;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return res;
}

bool deleteJointUser(int ID)
{
    int i = ID - 1000;
    int fd = open("JointUserFile", O_RDWR, 0744);
    bool res;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(jointUser);
    lock.l_len = sizeof(jointUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);

    jointUser user;
    lseek(fd, (i) * sizeof(jointUser), SEEK_SET);
    read(fd, &user, sizeof(jointUser));

    if (!strcmp(user.acc_Status, "ACTIVE"))
    {
        strcpy(user.acc_Status, "CLOSED");
        user.acc_Balance = 0;

        lseek(fd, (-1) * sizeof(jointUser), SEEK_CUR);
        int j = write(fd, &user, sizeof(jointUser));
        if (j != 0)
            res = true;
        else
            res = false;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return res;
}

bool modifyNormalUser(normalUser modifiedUser)
{
    int i = modifiedUser.userId - 1000;
    int fd = open("UserFile", O_RDWR, 0744);
    bool res = false;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(normalUser);
    lock.l_len = sizeof(normalUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);
    normalUser user;
    lseek(fd, (i) * sizeof(normalUser), SEEK_SET);
    read(fd, &user, sizeof(normalUser));

    if (!strcmp(user.acc_status, "ACTIVE") && (modifiedUser.acc_Number == user.acc_Number))
    {
        strcpy(modifiedUser.acc_status, "ACTIVE");
        lseek(fd, (-1) * sizeof(normalUser), SEEK_CUR);
        int j = write(fd, &modifiedUser, sizeof(normalUser));
        if (j != 0)
            res = true;
        else
            res = false;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return res;
}

bool modifyJointUser(jointUser modifiedUser)
{
    int i = modifiedUser.userId - 1000;
    int fd = open("JointUserFile", O_RDWR, 0744);
    bool res = false;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i) * sizeof(jointUser);
    lock.l_len = sizeof(jointUser);
    lock.l_pid = getpid();

    int filelock = fcntl(fd, F_SETLKW, &lock);

    jointUser user;
    lseek(fd, (i) * sizeof(jointUser), SEEK_SET);
    read(fd, &user, sizeof(jointUser));

    if (!strcmp(user.acc_Status, "ACTIVE") && (modifiedUser.acc_Number == user.acc_Number))
    {
        strcpy(modifiedUser.acc_Status, "ACTIVE");
        lseek(fd, (-1) * sizeof(jointUser), SEEK_CUR);
        int j = write(fd, &modifiedUser, sizeof(jointUser));
        if (j != 0)
            res = true;
        else
            res = false;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return res;
}

void serverTask(int nsd)
{
    int msglen, t, type, option, accType, UserID;
    bool res;
    while (1)
    {
        read(nsd, &option, sizeof(option));
        printf("Option : %d\n", option);

        if (option == 1)
        {
            normalUser user;
            accType = 1;
            msglen = read(nsd, &user, sizeof(normalUser));
            printf("UserID : %d\n", user.userId);
            printf("Password : %s\n", user.password);
            UserID = user.userId;
            res = verifyNormalUser(user);
            write(nsd, &res, sizeof(res));
        }
        else if (option == 2)
        {
            jointUser user;
            accType = 2;
            msglen = read(nsd, &user, sizeof(jointUser));
            UserID = user.userId;
            printf("UserID : %d\n", user.userId);
            printf("Password : %s\n", user.password);
            res = verifyJointUser(user);
            write(nsd, &res, sizeof(res));
        }
        else if (option == 3)
        {
            admin user;
            accType = 3;
            msglen = read(nsd, &user, sizeof(admin));
            UserID = user.userId;
            printf("Username : %d\n", user.userId);
            printf("Password : %s\n", user.password);
            res = verifyAdmin(user);
            write(nsd, &res, sizeof(res));
        }
        else
        {
            res = false;
            write(nsd, &res, sizeof(res));
        }
        if (res)
            break;
    }

    while(1)
    {
        read(nsd, &t, sizeof(int));
        if (option == 1 || option == 2)
        {
            if (t == 1)
            {
                float amount;
                read(nsd, &amount, sizeof(float));
                res = deposit(accType, UserID, amount);
                write(nsd, &res, sizeof(res));
            }
            else if (t == 2)
            {
                float amount;
                read(nsd, &amount, sizeof(float));
                res = withdraw(accType, UserID, amount);
                write(nsd, &res, sizeof(res));
            }
            else if (t == 3)
            {
                float amount;
                amount = getBalance(accType, UserID);
                write(nsd, &amount, sizeof(float));
            }
            else if (t == 4)
            {
                char password[20];
                read(nsd, password, sizeof(password));
                res = changePassword(accType, UserID, password);
                write(nsd, &res, sizeof(res));
            }
            else if (t == 5)
            {
                if (option == 1)
                {
                    normalUser user1 = getNormalUser(UserID);
                    write(nsd, &user1, sizeof(normalUser));
                }
                else if (option == 2)
                {
                    jointUser user2 = getJointUser(UserID);
                    write(nsd, &user2, sizeof(jointUser));
                }
            }
            else if (t == 6)
                break;
        }
        else if (option == 3)
        {
            read(nsd, &type, sizeof(int));
            if (t == 1)
            {
                if (type == 1)
                {
                    normalUser newUser1;
                    read(nsd, &newUser1, sizeof(normalUser));
                    res = addNormalUser(newUser1);
                    write(nsd, &res, sizeof(res));
                }
                else if (type == 2)
                {
                    jointUser newUser2;
                    read(nsd, &newUser2, sizeof(jointUser));
                    res = addJointUser(newUser2);
                    write(nsd, &res, sizeof(res));
                }
            }
            else if (t == 2)
            {
                if (type == 1)
                {
                    int deleteUID1;
                    read(nsd, &deleteUID1, sizeof(int));
                    res = deleteNormalUser(deleteUID1);
                    write(nsd, &res, sizeof(res));
                }
                else if (type == 2)
                {
                    int deleteUID2;
                    read(nsd, &deleteUID2, sizeof(int));
                    res = deleteJointUser(deleteUID2);
                    write(nsd, &res, sizeof(res));
                }
            }
            else if (t == 3)
            {
                if (type == 1)
                {
                    normalUser modifiedUser1;
                    read(nsd, &modifiedUser1, sizeof(normalUser));
                    res = modifyNormalUser(modifiedUser1);
                    write(nsd, &res, sizeof(res));
                }
                else if (type == 2)
                {
                    jointUser modifiedUser2;
                    read(nsd, &modifiedUser2, sizeof(jointUser));
                    res = modifyJointUser(modifiedUser2);
                    write(nsd, &res, sizeof(res));
                }
            }
            else if (t == 4)
            {
                if (type == 1)
                {
                    normalUser searchUser1;
                    int userID1;
                    read(nsd, &userID1, sizeof(int));
                    searchUser1 = getNormalUser(userID1);
                    write(nsd, &searchUser1, sizeof(normalUser));
                }
                else if (type == 2)
                {
                    jointUser searchUser2;
                    int userID2;
                    read(nsd, &userID2, sizeof(int));
                    searchUser2 = getJointUser(userID2);
                    write(nsd, &searchUser2, sizeof(jointUser));
                }
            }
            else if (t == 5)
                break;
        }
    }
    close(nsd);
    write(1, "Client Session Ended...\n", sizeof("Client Session Ended...\n"));
    return;
}

void *connection_handler(void *nsd)
{
    int nsfd = *(int *)nsd;
    serverTask(nsfd);
}

int main()
{
    struct sockaddr_in server, client;
    int sd, nsd, clientLen;
    pthread_t threads;
    bool result;
    sd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5573);

    bind(sd, (struct sockaddr *)&server, sizeof(server));
    listen(sd, 5);

    write(1, "Waiting For Client...\n", sizeof("Waiting For Client...\n"));
    while (1)
    {
        clientLen = sizeof(client);
        nsd = accept(sd, (struct sockaddr *)&client, &clientLen);

        write(1, "Connected To Client...\n", sizeof("Connected To Client...\n"));
        if (pthread_create(&threads, NULL, connection_handler, (void *)&nsd) < 0)
        {
            perror("Error in Thread Creation");
            return 1;
        }		
    }
    pthread_exit(NULL);
    close(sd);
    return 0;
}
