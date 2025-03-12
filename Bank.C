#include<stdio.h>
#include<string.h>

void create_account();
void deposite_money();
void withdraw_money();
void check_balance();

const char* ACCOUNT_FILE= "account.dat";

typedef struct{
    char name[50];
    int acc_no;
    float balance;
} Account;

int main(){
    while(1){
    int choice;
    printf("\n\n***** Welcome to the Bank Management System *****");
    printf("\n1. Create Account");
    printf("\n2. Deposite Money");
    printf("\n3. Withdraw Money");
    printf("\n4. Check Balance");
    printf("\n5. Exit");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);


    switch (choice)
    {
    case 1:
        create_account();
        break;
    case 2:
        deposite_money();
        break;
    case 3:
        withdraw_money();
        break;
    case 4:
        check_balance();
        break;
    case 5:
        printf("\nClosing the bank, Thanks for visiting the bank");
        return 0;
        break;
    
    default:
        printf("\nInvalid Choice, Please try again..!");
        break;
    }

    }
    return 0;
}

void create_account(){
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if (file == NULL)
    {
        printf("\nUnable to open the file!!");
    }

    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
    
    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int index = strcspn(acc.name, "\n");
    acc.name[index] = '\0';

    printf("\nEnter your account number: ");
    scanf("%d", &acc.acc_no);

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\nAccount create successfully!");
}
void deposite_money(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\nUnable to open the file!!");
    }
    int acc_no;
    float money;
    Account acc_r;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("\nEnter the money to deposite: ");
    scanf("%f", &money);

    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if (acc_r.acc_no == acc_no)
        {
            acc_r.balance += money;
            fseek(file, -sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r, sizeof(acc_r), 1, file);
            fclose(file);
            printf("\nWelcome %s!", acc_r.name);
            printf("\nSuccessfully Deposite Rs: %.2f and Now, your current balance is Rs: %.2f", money, acc_r.balance);
            return;
        }
        
    }
    fclose(file);
    printf("\nMoney cannot be deposite as the account number %d was not found in the records.", acc_no);
}
void withdraw_money(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\nUnable to open the file!!");
    }
    int acc_no;
    float money;
    Account acc_r;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("\nEnter the money do you want to withdraw: ");
    scanf("%f", &money);

    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if (acc_r.acc_no ==acc_no)
        {
            if (acc_r.balance >= money)
            {
                acc_r.balance -= money;
                fseek(file, -sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                printf("\nWelcome %s!", acc_r.name);
                printf("\nSuccessfully Withdraw Rs: %.2f and Now, Your current balance is Rs: %.2f", money, acc_r.balance);
            }else{
                printf("\nWelcome %s!", acc_r.name);
                printf("\nInsufficient Balance..!");
                printf("\nYour current balance is Rs: %.2f",acc_r.balance);
            }
            fclose(file);
            return;
        }
        
    }
    fclose(file);
    printf("\nMoney cannot be withdraw as the account number %d was not found in the records.", acc_no);
}
void check_balance(){
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\nUnable to open the file!!");
    }

    int acc_no;
    Account acc_read;

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            printf("\nWelcome %s!", acc_read.name);
            printf("\nYour current balnce is Rs: %.2f", acc_read.balance);
            fclose(file);
            return;
        }
        
    }

    fclose(file);
    printf("\nAccount number %d was not found in the records", acc_no);
}