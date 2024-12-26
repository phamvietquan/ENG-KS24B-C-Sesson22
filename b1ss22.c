#include <stdio.h>
#include <string.h>

typedef struct {
    char id[50];
    char name[50];
    int age;
} SinhVien;

void insinhvien(SinhVien sv[100], int n);
void addsinhvien(SinhVien sv[100], int *n);
void deletesinhvien(SinhVien sv[100], int *n);
void searchsinhvien(SinhVien sv[100], int n);
void sortbysinhvien(SinhVien sv[100], int n);

int main() {
    SinhVien sv[100];
    int n, menu;
    printf("Moi ban nhap vao so luong sinh vien: ");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        printf("Moi ban nhap thong tin sinh vien thu %d\n", i + 1);
        printf("Id: ");
        fgets(sv[i].id, sizeof(sv[i].id), stdin);
        sv[i].id[strcspn(sv[i].id, "\n")] = '\0';
        printf("Ten: ");
        fgets(sv[i].name, sizeof(sv[i].name), stdin);
        sv[i].name[strcspn(sv[i].name, "\n")] = '\0';
        printf("Tuoi: ");
        scanf("%d", &sv[i].age);
        getchar();
    }
    FILE *file = fopen("students.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo FILE\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "ID: %s, Name: %s, Tuoi: %d\n", sv[i].id, sv[i].name, sv[i].age);
    }
    fclose(file);
    printf("Luu thong tin vao file thanh cong!\n");
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Tim kiem sinh vien\n");
        printf("5. Sap xep danh sach sinh vien\n");
        printf("6. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &menu);
        getchar();

        switch (menu) {
            case 1:
                insinhvien(sv, n);
                break;
            case 2:
                addsinhvien(sv, &n);
                break;
            case 3:
                deletesinhvien(sv, &n);
                break;
            case 4:
                searchsinhvien(sv, n);
                break;
            case 5:
                sortbysinhvien(sv, n);
                break;
            case 6:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Moi nhap lai!\n");
        }
    } while (menu != 6);

    return 0;
}

void insinhvien(SinhVien sv[100], int n) {
    printf("\nDanh sach sinh vien:\n");
    FILE *file = fopen("students.bin", "rb");
    if (file == NULL) {
        printf("Khong the mo FILE\n");
        return;
    }
    char line[150];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void addsinhvien(SinhVien sv[100], int *n) {
    SinhVien new_sv;
    printf("Nhap thong tin sinh vien muon them:\n");
    printf("Id: ");
    fgets(new_sv.id, sizeof(new_sv.id), stdin);
    new_sv.id[strcspn(new_sv.id, "\n")] = '\0';
    printf("Ten: ");
    fgets(new_sv.name, sizeof(new_sv.name), stdin);
    new_sv.name[strcspn(new_sv.name, "\n")] = '\0';
    printf("Tuoi: ");
    scanf("%d", &new_sv.age);
    getchar();

    sv[*n] = new_sv;
    (*n)++;

    FILE *file = fopen("students.bin", "ab");
    if (file == NULL) {
        printf("Khong the mo FILE\n");
        return;
    }
    fprintf(file, "ID: %s, Name: %s, Tuoi: %d\n", new_sv.id, new_sv.name, new_sv.age);
    fclose(file);
    printf("Them sinh vien thanh cong va luu vao file!\n");
}

void deletesinhvien(SinhVien sv[100], int *n) {
    char id[50];
    printf("Nhap ID sinh vien can xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(sv[i].id, id) == 0) {
            found = 1;
            for (int j = i; j < *n - 1; j++) {
                sv[j] = sv[j + 1];
            }
            (*n)--;
            break;
        }
    }

    if (found==1) {
        FILE *file = fopen("students.bin", "wb");
        for (int i = 0; i < *n; i++) {
            fprintf(file, "ID: %s, Name: %s, Tuoi: %d\n", sv[i].id, sv[i].name, sv[i].age);
        }
        fclose(file);
        printf("Xoa sinh vien thanh cong!\n");
    } else {
        printf("Khong tim thay sinh vien voi ID: %s\n", id);
    }
}

void searchsinhvien(SinhVien sv[100], int n) {
    char name[50];
    printf("Nhap ten sinh vien can tim: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Ket qua tim kiem:\n");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(sv[i].name, name) != NULL) {
            printf("ID: %s, Name: %s, Tuoi: %d\n", sv[i].id, sv[i].name, sv[i].age);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien voi ten: %s\n", name);
    }
}

void sortbysinhvien(SinhVien sv[100], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(sv[i].name, sv[j].name) > 0) {
                SinhVien temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    printf("Sap xep danh sach sinh vien thanh cong!\n");
    FILE *file = fopen("students.bin", "wb");
    for (int i = 0; i < n; i++) {
        fprintf(file, "ID: %s, Name: %s, Tuoi: %d\n", sv[i].id, sv[i].name, sv[i].age);
    }
    fclose(file);
}

