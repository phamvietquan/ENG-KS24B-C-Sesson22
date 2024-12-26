#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[100];
    char password[100];
} accounts;

int loadAccounts(accounts tk[], int maxAccounts) {
    FILE *file = fopen("accounts.bin", "rb");
    if (!file) {
        return 0; 
    }
    int count = 0;
    while (count < maxAccounts && fread(&tk[count], sizeof(accounts), 1, file)) {
        count++;
    }
    fclose(file);
    return count;
}

void saveAccounts(accounts tk[], int count) {
    FILE *file = fopen("accounts.bin", "wb");
    if (!file) {
        printf("Khong the mo FILE.\n");
        return;
    }

    fwrite(tk, sizeof(accounts), count, file);
    fclose(file);
}

int accountExists(accounts tk[], int count, const char *username) {
    for (int i = 0; i < count; i++) {
        if (strcmp(tk[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void registerAccount(accounts tk[], int *count, int maxAccounts) {
    if (*count >= maxAccounts) {
        printf("Khong the dang ky them tai khoan.\n");
        return;
    }

    char username[50], password[50], confirmPassword[50];

    printf("Nhap ten tai khoan: ");
    scanf("%s", username);

    if (accountExists(tk, *count, username)) {
        printf("Tai khoan da ton tai.\n");
        return;
    }

    printf("Nhap mat khau: ");
    scanf("%s", password);

    printf("Xac nhan mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Mat khau khong khop.\n");
        return;
    }

    strcpy(tk[*count].username, username);
    strcpy(tk[*count].password, password);
    (*count)++;

    saveAccounts(tk, *count);
    printf("Dang ky thanh cong!\n");
}

void login(accounts tk[], int count) {
    char username[100], password[100];

    printf("NNhap ten tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < count; i++) {
        if (strcmp(tk[i].username, username) == 0 &&
            strcmp(tk[i].password, password) == 0) {
            printf("Dang nhap thanh cong.\n");
            return;
        }
    }

    printf("Dang nhap that bai.\n");
}

int main() {
    int maxAccounts = 100;
    accounts tk[maxAccounts];
    int count = loadAccounts(tk, maxAccounts);

    int menu;
    do {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                login(tk, count);
                break;
            case 2:
                registerAccount(tk, &count, maxAccounts);
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua cho khong co.\n");
        }
    } while (menu != 3);

    return 0;
}

