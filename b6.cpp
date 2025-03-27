#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ds {
    int tuoi, diem;
    char name[100];
    struct ds *next;
} ds;

ds *taosvmoi(char ten[], int t, int diemtb) {
    ds *svmoi = (ds*)malloc(sizeof(ds));
    if (!svmoi) return NULL;
    svmoi->tuoi = t;
    svmoi->diem = diemtb;
    strcpy(svmoi->name, ten);
    svmoi->next = NULL;
    return svmoi;
}

void themvaocuoi(ds **head, char ten[], int t, int diemtb) {
    ds* svmoi = taosvmoi(ten, t, diemtb);
    if (!(*head)) {
        *head = svmoi;
        return;
    }
    ds* k = *head;
    while (k->next) k = k->next;
    k->next = svmoi;
}

void themvaodau(ds **head, char ten[], int t, int diemtb) {
    ds *svmoi = taosvmoi(ten, t, diemtb);
    svmoi->next = *head;
    *head = svmoi;
}

int size(ds *head) {
    int count = 0;
    for (; head; head = head->next) count++;
    return count;
}

void themvaogiua(ds **head, char ten[], int t, int diemtb, int k) {
    int n = size(*head);
    if (k < 1 || k > n + 1) {
        printf("Vi tri chen khong hop le!\n");
        return;
    }
    if (k == 1) return themvaodau(head, ten, t, diemtb);
    if (k == n + 1) return themvaocuoi(head, ten, t, diemtb);

    ds *p = *head;
    for (int i = 1; i < k - 1; i++) p = p->next;

    ds *newsv = taosvmoi(ten, t, diemtb);
    newsv->next = p->next;
    p->next = newsv;
}

void nhapThongTin(char name[], int *tuoi, int *diem) {
    printf("Nhap ten: ");
    fflush(stdin);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  // Xoa '\n' o cuoi chuoi

    printf("Nhap tuoi: "); scanf("%d", tuoi);
    printf("Nhap diem: "); scanf("%d", diem);
}

void nhap(ds **head) {
    char name[100];
    int tuoi, diem;
    nhapThongTin(name, &tuoi, &diem);
    themvaocuoi(head, name, tuoi, diem);
}

void duyet(ds *head) {
    printf("\nDanh sach sinh vien:\n");
    printf("Ten\t\tTuoi\tDiem\n");
    while (head) {
        printf("%s\t%d\t%d\n", head->name, head->tuoi, head->diem);
        head = head->next;
    }
}

void giaiPhong(ds *head) {
    while (head) {
        ds *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    ds *head = NULL;
    int n, lc;
    
    printf("Nhap so luong sinh vien: "); scanf("%d", &n);
    for (int i = 0; i < n; i++) nhap(&head);

    while (1) {
        printf("\n--- QUAN LY SINH VIEN ---\n");
        printf("1. Nhap sinh vien\n");
        printf("2. In danh sach sinh vien\n");
        printf("3. Them sinh vien vao cuoi\n");
        printf("4. Them sinh vien vao dau\n");
        printf("5. Them sinh vien vao giua\n");
        printf("0. Thoat\n");
        printf("--------------------------\n");
        printf("Chon: "); scanf("%d", &lc);

        if (lc == 1) nhap(&head);
        else if (lc == 2) duyet(head);
        else if (lc == 3) nhap(&head);
        else if (lc == 4) {
            char newname[100];
            int newtuoi, newdiem;
            nhapThongTin(newname, &newtuoi, &newdiem);
            themvaodau(&head, newname, newtuoi, newdiem);
        } 
        else if (lc == 5) {
            int k;
            char newname[100];
            int newtuoi, newdiem;
            printf("Nhap vi tri can chen: "); scanf("%d", &k);
            nhapThongTin(newname, &newtuoi, &newdiem);
            themvaogiua(&head, newname, newtuoi, newdiem, k);
        }
        else if (lc == 0) break;
    }
    giaiPhong(head);  
    return 0;
}
