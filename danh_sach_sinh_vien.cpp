#include <iostream>
#include <iomanip>
using namespace std;

struct SVBK{
    string ho_ten;
    long mssv;
    int nam_sinh;
    float gpa;
    SVBK* next;
};
struct DSSV{
    SVBK* firstSV;
};
void DSSV_Init(DSSV* ds){//thiet lap danh sach
    ds->firstSV = 0;
}
void DSSV_Replace(SVBK* sv1, SVBK* sv2){// thay the 1 phan tu trong danh sach(phan tu thay the can co lien ket noi)
    sv1->ho_ten = sv2->ho_ten;
    sv1->mssv = sv2->mssv;
    sv1->nam_sinh = sv2->nam_sinh;
    sv1->gpa = sv2->gpa;
    //sv1->next = sv2->next;
}
SVBK* DSSV_GetSVfromName(DSSV* ds, string name){//lay phan tu tu ten sinh vien
    SVBK* sv = ds->firstSV;
    while (sv != 0){
        if (sv->ho_ten == name){
            return sv;
        }
        sv = sv->next;
    }
    return NULL;
}
SVBK* DSSV_GetSVfromIndex(DSSV* ds, int index){//lay phan tu tu index trong danh sach
    SVBK* sv = ds->firstSV;
    for (int i=0; i < index; i++){
        sv = sv->next;
    }
    return sv;
}

void DSSV_Swap(DSSV* ds, string name1, string name2){//doi cho 2 phan tu trong danh sach
    SVBK* sv1 = ds->firstSV;
    SVBK* sv2 = ds->firstSV;
    SVBK* svm = new SVBK;
    while (sv1 != 0){
        if (sv1->ho_ten == name1){
            while (sv2 != 0){
                if (sv2->ho_ten == name2){
                    DSSV_Replace(svm,sv1);             
                    DSSV_Replace(sv1,sv2);                
                    DSSV_Replace(sv2,svm); 
                    delete svm;
                    return;
                }
                sv2 = sv2->next;
            }
        }
        sv1 = sv1->next;
    }
}
int DSSV_Length(DSSV* ds){//tinh so luong sinh vien
    SVBK* sv = ds->firstSV;
    int j = 0;
    while (sv!=0){
        j++;
        sv = sv->next;
    }
    return j;
}
void DSSV_Display(DSSV* ds){//duyet danh sach sinh vien
    SVBK* sv = ds->firstSV;
    if (ds->firstSV == 0){
        cout << "\nDS rong!\r\n";
    }
    else {
        while (sv != 0){
            cout << "\nHo va ten: " << sv->ho_ten;
            cout << "\nMSSV: " << sv->mssv;
            cout << "\nNam sinh: " << sv->nam_sinh;
            cout << "\nGPA: " << sv->gpa;
            cout << "\n";
            sv = sv->next;
        }
    }
}
void DSSV_Add(DSSV* ds, string ho_ten, long mssv, int nam_sinh, float gpa){
    SVBK* svm = new SVBK;
    svm->ho_ten = ho_ten;
    svm->mssv = mssv;
    svm->nam_sinh = nam_sinh;
    svm->gpa = gpa;
    svm->next = ds->firstSV;
    ds->firstSV = svm;
}
int DSSV_GPA32(DSSV* ds){//tinh so sinh vien tren 3.2 GPA trong danh sach
    int count = 0;
    SVBK* sv = ds->firstSV;
    while (sv!=0)
    {
        if (sv->gpa > 3.2) count++;
        sv = sv->next;
    }
    return count;
}
void DSSV_SapXepGPA(DSSV* ds){//sap xep danh sach theo thu tu gpa tang dan
    int n = DSSV_Length(ds);
    //cout << "No.";
    //cout << setw(10) << "min\n";
    for (int i=0;i<n-1;i++){
      int min_index = i;
      //cout << i+1;
      for (int j=i+1;j<n;j++){
         if (DSSV_GetSVfromIndex(ds,j)->gpa<DSSV_GetSVfromIndex(ds,min_index)->gpa){
            min_index = j;
         }
      }
      //cout << setw(10) << DSSV_GetSVfromIndex(ds,min_index)->gpa;
      DSSV_Swap(ds,DSSV_GetSVfromIndex(ds,i)->ho_ten,DSSV_GetSVfromIndex(ds,min_index)->ho_ten);
      for (int k=0;k<n;k++){
        //cout << setw(10) << DSSV_GetSVfromIndex(ds,k)->gpa;
      }
      //cout << "\n";
   }
}
void DSSV_AddSapXepGPA(DSSV* ds, string ho_ten, long mssv, int nam_sinh, float gpa){
    //them sinh vien vao danh sach da sap xep theo gpa tang dan
    SVBK* svm = new SVBK;
    svm->ho_ten = ho_ten;
    svm->mssv = mssv;
    svm->nam_sinh = nam_sinh;
    svm->gpa = gpa;
    SVBK* sv = ds->firstSV;
    if (svm->gpa > sv->gpa){
        while (svm->gpa > sv->next->gpa){
            sv = sv->next;
        }
        svm->next = sv->next;
        sv->next = svm;
    }
    else {
        DSSV_Add(ds,ho_ten,mssv,nam_sinh,gpa);
    }
    
}

int main(){

    DSSV danh_sach;
    DSSV_Init(&danh_sach);
    DSSV_Add(&danh_sach, "Nguyen Tu Quang", 202413944, 1975, 4.0);
    DSSV_Add(&danh_sach, "Ba To Com", 202813123, 1945, 2.0);
    DSSV_Add(&danh_sach, "Benjamin Tennyson", 202413944, 1954, 3.0);
    DSSV_Add(&danh_sach, "Tokuda Shigeo", 206713579, 2019, 1.2);
    DSSV_Add(&danh_sach, "Michael Teeheeson", 200101109, 1960, 3.6);
    DSSV_Add(&danh_sach, "Phung Thanh Do", 0700212, 1989, 2.5);

    cout << "\nDanh sach ban dau:\n";
    DSSV_Display(&danh_sach);//danh sach ban dau
    DSSV_SapXepGPA(&danh_sach);//sap xep danh sach
    cout << "\nDanh sach sau khi sap xep:\n";
    DSSV_Display(&danh_sach);//danh sach sau khi sap xep
    DSSV_AddSapXepGPA(&danh_sach, "Lee Sang-hyeok", 204813579, 1996, 2.4);//them hoc sinh gpa 2.4
    cout << "\nDanh sach sau khi them hoc sinh:\n";
    DSSV_Display(&danh_sach);//danh sach sau khi them hoc sinh
    return 0;
}