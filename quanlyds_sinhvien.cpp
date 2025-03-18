#include <iostream>
#include <string>
using namespace std;

struct SinhVien {
    string maSV;
    string hoTen;
    float diem;
    SinhVien* left;
    SinhVien* right;
};

SinhVien* themSinhVien(SinhVien* root, string maSV, string hoTen, float diem) {
    if (root == NULL) {
        return new SinhVien{maSV, hoTen, diem, NULL, NULL};
    }
    if (maSV < root->maSV)
        root->left = themSinhVien(root->left, maSV, hoTen, diem);
    else
        root->right = themSinhVien(root->right, maSV, hoTen, diem);
    return root;
}

SinhVien* timKiem(SinhVien* root, string maSV) {
    if (root == NULL || root->maSV == maSV)
        return root;
    if (maSV < root->maSV)
        return timKiem(root->left, maSV);
    return timKiem(root->right, maSV);
}

SinhVien* timMin(SinhVien* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

SinhVien* xoaSinhVien(SinhVien* root, string maSV) {
    if (root == NULL) return root;
    
    if (maSV < root->maSV)
        root->left = xoaSinhVien(root->left, maSV);
    else if (maSV > root->maSV)
        root->right = xoaSinhVien(root->right, maSV);
    else {
        if (root->left == NULL) {
            SinhVien* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            SinhVien* temp = root->left;
            delete root;
            return temp;
        }
        
        SinhVien* temp = timMin(root->right);
        root->maSV = temp->maSV;
        root->hoTen = temp->hoTen;
        root->diem = temp->diem;
        root->right = xoaSinhVien(root->right, temp->maSV);
    }
    return root;
}

void inDanhSach(SinhVien* root) {
    if (root != NULL) {
        inDanhSach(root->left);
        cout << "MSSV: " << root->maSV << " | Ten: " << root->hoTen << " | Diem: " << root->diem << endl;
        inDanhSach(root->right);
    }
}

int main() {
    SinhVien* root = NULL;
    root = themSinhVien(root, "SV001", "Nguyen Van A", 8.5);
    root = themSinhVien(root, "SV002", "Tran Thi B", 7.0);
    root = themSinhVien(root, "SV003", "Le Van C", 9.0);
    
    cout << "Danh sach sinh vien:\n";
    inDanhSach(root);
    
    cout << "\nTim kiem sinh vien SV002:\n";
    SinhVien* sv = timKiem(root, "SV002");
    if (sv != NULL)
        cout << "Tim thay: " << sv->hoTen << " - Diem: " << sv->diem << endl;
    else
        cout << "Khong tim thay!" << endl;
    
    cout << "\nXoa sinh vien SV002:\n";
    root = xoaSinhVien(root, "SV002");
    inDanhSach(root);
    
    return 0;
}