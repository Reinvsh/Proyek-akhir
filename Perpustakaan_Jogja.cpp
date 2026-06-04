#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// menyimpan data buku dalam satu kesatuan
struct Buku {
    
    string judulBuku;
    string namaPenulis;
    string namaPenerbit;
    int tahunTerbit;
};

const int    MAX_BUKU  = 30;
const string NAMA_FILE = "arsipPerpustakaan.txt";

//deklarasi fungsi
void bacaDataBukuDariFile(Buku daftarBuku[], int &jumlahBuku);
void simpanDataBukuKeFile(Buku daftarBuku[], int jumlahBuku);
void tambahBuku          (Buku daftarBuku[], int &jumlahBuku);
void tampilkanDaftarBuku (Buku daftarBuku[], int jumlahBuku);
void cariBuku            (Buku daftarBuku[], int jumlahBuku);
void urutkanBuku	     (Buku daftarBuku[], int jumlahBuku);

void bacaDataBukuDariFile(Buku daftarBuku[], int *jumlahBuku) {
    ifstream file(NAMA_FILE);
    if (!file.is_open()) {
        *jumlahBuku = 0;
        return;
    }

    *jumlahBuku = 0;
    string tahunStr;
    while (*jumlahBuku < MAX_BUKU &&
           getline(file, daftarBuku[*jumlahBuku].judulBuku)   &&
           getline(file, daftarBuku[*jumlahBuku].namaPenulis)  &&
           getline(file, daftarBuku[*jumlahBuku].namaPenerbit) &&
           getline(file, tahunStr)) {
        daftarBuku[*jumlahBuku].tahunTerbit = stoi(tahunStr);
        (*jumlahBuku)++; //ubah string ke int
    }

    file.close();
}

void simpanDataBukuKeFile(Buku daftarBuku[], int jumlahBuku) {
    ofstream file(NAMA_FILE);
    if (!file.is_open()) {
        cout << "Gagal menyimpan data ke file!" << endl;
        return;
    }

    for (int i = 0; i < jumlahBuku; i++) {
        file << daftarBuku[i].judulBuku   << endl;
        file << daftarBuku[i].namaPenulis  << endl;
        file << daftarBuku[i].namaPenerbit << endl;
        file << daftarBuku[i].tahunTerbit  << endl;
    }

    file.close();
}

void tambahBuku(Buku daftarBuku[], int *jumlahBuku) {
    system("cls");
    cout << "=======================================================" << endl;
    cout << "                    TAMBAH BUKU BARU                   " << endl;
    cout << "=======================================================" << endl;

    if (*jumlahBuku >= MAX_BUKU) {
        cout << "Tidak dapat menambah buku baru" << endl;
        cout << "Press any key to continue...";
        cin.get();
        return;
    }

    Buku bukuBaru;

    cout << "Judul Buku    : "; getline(cin, bukuBaru.judulBuku);
    cout << "Nama Penulis  : "; getline(cin, bukuBaru.namaPenulis);
    cout << "Nama Penerbit : "; getline(cin, bukuBaru.namaPenerbit);
    cout << "Tahun Terbit  : "; cin  >> bukuBaru.tahunTerbit;
    cin.ignore();

    daftarBuku[*jumlahBuku] = bukuBaru; 
    (*jumlahBuku)++;

    simpanDataBukuKeFile(daftarBuku, *jumlahBuku);

    cout << "Buku berhasil ditambahkan" << endl;
    cout << "Press any key to continue...";
    cin.get();
}

void tampilkanDaftarBuku(Buku daftarBuku[], int jumlahBuku) {
    system("cls");
    cout << "=======================================================" << endl;
    cout << "                DAFTAR BUKU PERPUSTAKAAN               " << endl;
    cout << "=======================================================" << endl;

    if (jumlahBuku == 0) {
        cout << "Tidak ada data buku yang tersimpan" << endl;
    } else {
        for (int i = 0; i < jumlahBuku; i++) {
            cout << "Buku ke-" << (i + 1) << endl;
            cout << "-------------------------------------------------------" << endl;
            cout << "Judul Buku    : " << daftarBuku[i].judulBuku   << endl;
            cout << "Nama Penulis  : " << daftarBuku[i].namaPenulis  << endl;
            cout << "Nama Penerbit : " << daftarBuku[i].namaPenerbit << endl;
            cout << "Tahun Terbit  : " << daftarBuku[i].tahunTerbit  << endl;
            cout << endl;
        }
        cout << "=======================================================" << endl;
        cout << "  Total buku: " << jumlahBuku << endl;
    }

    cout << "Press any key to continue...";
    cin.get();
}

void cariBuku(Buku daftarBuku[], int jumlahBuku) {
    system("cls");
    cout << "=======================================================" << endl;
    cout << "                       CARI BUKU                       " << endl;
    cout << "=======================================================" << endl;

    if (jumlahBuku == 0) {
        cout << "Tidak ada data buku yang tersimpan" << endl;
        cout << "Press any key to continue...";
        cin.get();
        return;
    }

    cout << "Masukkan judul yang dicari: ";
    string kataCari;
    getline(cin, kataCari);

    // konverensi kata ke huruf kecil
    string kataCariLower = kataCari;
    for (char &c : kataCariLower) c = tolower(c); // ubah karakter ke lowercase

    cout << "Hasil pencarian untuk " << kataCari << " : ";
    cout << "-------------------------------------------------------" << endl;

    int jumlahDitemukan = 0;
    for (int i = 0; i < jumlahBuku; i++) {
        string judulLower = daftarBuku[i].judulBuku;
        for (char &c : judulLower) c = tolower(c);

        if (judulLower.find(kataCariLower) != string::npos) {
			cout << endl;
            cout << "Buku ke-" << (i + 1) << endl;
            cout << "Judul Buku    : " << daftarBuku[i].judulBuku   << endl;
            cout << "Nama Penulis  : " << daftarBuku[i].namaPenulis  << endl;
            cout << "Nama Penerbit : " << daftarBuku[i].namaPenerbit << endl;
            cout << "Tahun Terbit  : " << daftarBuku[i].tahunTerbit  << endl;
            jumlahDitemukan++;
        }cout << endl;
    }

    if (jumlahDitemukan == 0) {
        cout << "Buku dengan judul " << kataCari << " tidak ditemukan" << endl;
    } else {
        cout << "-------------------------------------------------------" << endl;
        cout << "Total ditemukan: " << jumlahDitemukan << " buku" << endl;
    }

    cout << "Press any key to continue...";
    cin.get();
}

void urutkanBuku(Buku daftarBuku[], int jumlahBuku){
    if (jumlahBuku <= 1) return;

    for (int i = 0; i < jumlahBuku - 1; i++) {
        for (int j = 0; j < jumlahBuku - i - 1; j++) { //bandingkan elemen berdekat
            
            if (daftarBuku[j].judulBuku > daftarBuku[j + 1].judulBuku) {
                
                Buku temp = daftarBuku[j];
                daftarBuku[j] = daftarBuku[j + 1];
                daftarBuku[j + 1] = temp;
                
            }
        }
    }

    simpanDataBukuKeFile(daftarBuku, jumlahBuku);

    cout << "Daftar buku berhasil diurutkan berdasarkan judul" << endl;
    cout << "Press any key to continue...";
    cin.get();
}

int main() {
    Buku daftarBuku[MAX_BUKU];
    int  jumlahBukuSekarang = 0;

    bacaDataBukuDariFile(daftarBuku, &jumlahBukuSekarang);

    // Welcome Screen
    cout << "=======================================================" << endl;
    cout << "         SELAMAT DATANG DI PERPUSTAKAAN JOGJA          " << endl;
    cout << "=======================================================" << endl;
    cout << "Press any key to continue...";
    cin.get();

    int pilihan;
    system("cls");
    do {
        cout << "=======================================================" << endl;
        cout << "                     MENU UTAMA                        " << endl;
        cout << "=======================================================" << endl;
        cout << "1. Tambah Buku"          << endl;
        cout << "2. Tampilkan Daftar Buku" << endl;
        cout << "3. Cari Buku"            << endl;
        cout << "4. Urutkan Buku"               << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin  >> pilihan;
        cin.ignore();

        system("cls");
        switch (pilihan) {
            case 1:
                tambahBuku(daftarBuku, &jumlahBukuSekarang);
                break;
            case 2:
                tampilkanDaftarBuku(daftarBuku, jumlahBukuSekarang);
                break;
            case 3:
                cariBuku(daftarBuku, jumlahBukuSekarang);
                break;
            case 4:
				urutkanBuku(daftarBuku, jumlahBukuSekarang);
				break;
            case 5:
                cout << "Terima kasih telah mengunjungi Perpustakaan Jogja" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
                cout << "Press any key to continue...";
                cin.get();
        }

        if (pilihan != 5) system("cls");

    } while (pilihan != 5);

    return 0;
}
