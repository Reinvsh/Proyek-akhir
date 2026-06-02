#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Buku {
    
    string judulBuku;
    string namaPenulis;
    string namaPenerbit;
    int tahunTerbit;
};

const int    MAX_BUKU  = 30;
const string NAMA_FILE = "arsipPerpustakaan.txt";

// ============================================================
// DEKLARASI FUNGSI
// ============================================================
void bacaDataBukuDariFile(Buku daftarBuku[], int &jumlahBuku);
void simpanDataBukuKeFile(Buku daftarBuku[], int jumlahBuku);
void tambahBuku          (Buku daftarBuku[], int &jumlahBuku);
void tampilkanDaftarBuku (Buku daftarBuku[], int jumlahBuku);
void cariBuku            (Buku daftarBuku[], int jumlahBuku);
void urutkanBuku	     (Buku daftarBuku[], int jumlahBuku);

// ============================================================
// BACA DATA DARI FILE
// ============================================================
void bacaDataBukuDariFile(Buku daftarBuku[], int &jumlahBuku) {
    ifstream file(NAMA_FILE);
    if (!file.is_open()) {
        // File belum ada, mulai dengan data kosong
        jumlahBuku = 0;
        return;
    }

    jumlahBuku = 0;
    string tahunStr;
    while (jumlahBuku < MAX_BUKU &&
           getline(file, daftarBuku[jumlahBuku].judulBuku)   &&
           getline(file, daftarBuku[jumlahBuku].namaPenulis)  &&
           getline(file, daftarBuku[jumlahBuku].namaPenerbit) &&
           getline(file, tahunStr)) {
        daftarBuku[jumlahBuku].tahunTerbit = stoi(tahunStr);
        jumlahBuku++;
    }

    file.close();
}

// ============================================================
// SIMPAN DATA KE FILE
// ============================================================
void simpanDataBukuKeFile(Buku daftarBuku[], int jumlahBuku) {
    ofstream file(NAMA_FILE);
    if (!file.is_open()) {
        cout << "  [!!] Gagal menyimpan data ke file!" << endl;
        return;
    }

    for (int i = 0; i < jumlahBuku; i++) {
        file << daftarBuku[i].judulBuku   << "\n"
             << daftarBuku[i].namaPenulis  << "\n"
             << daftarBuku[i].namaPenerbit << "\n"
             << daftarBuku[i].tahunTerbit  << "\n";
    }

    file.close();
}

// ============================================================
// TAMBAH BUKU
// ============================================================
void tambahBuku(Buku daftarBuku[], int &jumlahBuku) {
    system("cls");
    cout << "=======================================================" << endl;
    cout << "                   TAMBAH BUKU BARU                   " << endl;
    cout << "=======================================================" << endl;

    if (jumlahBuku >= MAX_BUKU) {
        cout << "  [!!] Kapasitas penuh! Tidak dapat menambah buku baru." << endl;
        cout << "  Tekan Enter untuk kembali...";
        cin.get();
        return;
    }

    Buku bukuBaru;

    cout << "Judul Buku    : ";
    getline(cin, bukuBaru.judulBuku);

    cout << "Nama Penulis  : ";
    getline(cin, bukuBaru.namaPenulis);

    cout << "Nama Penerbit : ";
    getline(cin, bukuBaru.namaPenerbit);

    cout << "Tahun Terbit  : ";
    cin  >> bukuBaru.tahunTerbit;
    cin.ignore();

    daftarBuku[jumlahBuku] = bukuBaru;
    jumlahBuku++;

    simpanDataBukuKeFile(daftarBuku, jumlahBuku);

    cout << "\n  [OK] Buku berhasil ditambahkan!" << endl;
    cout << "  Tekan Enter untuk kembali...";
    cin.get();
}

// ============================================================
// TAMPILKAN DAFTAR BUKU
// ============================================================
void tampilkanDaftarBuku(Buku daftarBuku[], int jumlahBuku) {
    system("cls");
    cout << "=======================================================" << endl;
    cout << "                  DAFTAR BUKU PERPUSTAKAAN            " << endl;
    cout << "=======================================================" << endl;

    if (jumlahBuku == 0) {
        cout << "  (Belum ada data buku yang tersimpan)" << endl;
    } else {
        for (int i = 0; i < jumlahBuku; i++) {
            cout << "\n  Buku ke-" << (i + 1) << endl;
            cout << "  -------------------------------------------------------" << endl;
            cout << "  Judul Buku    : " << daftarBuku[i].judulBuku   << endl;
            cout << "  Nama Penulis  : " << daftarBuku[i].namaPenulis  << endl;
            cout << "  Nama Penerbit : " << daftarBuku[i].namaPenerbit << endl;
            cout << "  Tahun Terbit  : " << daftarBuku[i].tahunTerbit  << endl;
        }
        cout << "\n=======================================================" << endl;
        cout << "  Total buku: " << jumlahBuku << endl;
    }

    cout << "\n  Tekan Enter untuk kembali...";
    cin.get();
}

// ============================================================
// CARI BUKU (berdasarkan judul, case-insensitive)
// ============================================================
void cariBuku(Buku daftarBuku[], int jumlahBuku) {
    system("cls");
    cout << "=======================================================" << endl;
    cout << "                      CARI BUKU                       " << endl;
    cout << "=======================================================" << endl;

    if (jumlahBuku == 0) {
        cout << "  (Belum ada data buku yang tersimpan)" << endl;
        cout << "\n  Tekan Enter untuk kembali...";
        cin.get();
        return;
    }

    cout << "Masukkan judul yang dicari: ";
    string kataCari;
    getline(cin, kataCari);

    // Ubah kata kunci ke huruf kecil
    string kataCariLower = kataCari;
    for (char &c : kataCariLower) c = tolower(c);

    cout << "\n  Hasil pencarian untuk \"" << kataCari << "\":\n";
    cout << "  -------------------------------------------------------" << endl;

    int jumlahDitemukan = 0;
    for (int i = 0; i < jumlahBuku; i++) {
        // Ubah judul buku ke huruf kecil untuk perbandingan
        string judulLower = daftarBuku[i].judulBuku;
        for (char &c : judulLower) c = tolower(c);

        if (judulLower.find(kataCariLower) != string::npos) {
            cout << "\n  Buku ke-" << (i + 1) << endl;
            cout << "  Judul Buku    : " << daftarBuku[i].judulBuku   << endl;
            cout << "  Nama Penulis  : " << daftarBuku[i].namaPenulis  << endl;
            cout << "  Nama Penerbit : " << daftarBuku[i].namaPenerbit << endl;
            cout << "  Tahun Terbit  : " << daftarBuku[i].tahunTerbit  << endl;
            jumlahDitemukan++;
        }
    }

    if (jumlahDitemukan == 0) {
        cout << "  Buku dengan judul \"" << kataCari << "\" tidak ditemukan." << endl;
    } else {
        cout << "\n  -------------------------------------------------------" << endl;
        cout << "  Total ditemukan: " << jumlahDitemukan << " buku" << endl;
    }

    cout << "\n  Tekan Enter untuk kembali...";
    cin.get();
}

// ============================================================
// URUTKAN BUKU
// ============================================================

void urutkanBuku(Buku daftarBuku[], int jumlahBuku){
    if (jumlahBuku <= 1) return;

    for (int i = 0; i < jumlahBuku - 1; i++) {
        for (int j = 0; j < jumlahBuku - i - 1; j++) {
            
            if (daftarBuku[j].judulBuku > daftarBuku[j + 1].judulBuku) {
                
                Buku temp = daftarBuku[j];
                daftarBuku[j] = daftarBuku[j + 1];
                daftarBuku[j + 1] = temp;
                
            }
        }
    }

    simpanDataBukuKeFile(daftarBuku, jumlahBuku);

    cout << "Daftar buku berhasil diurutkan berdasarkan judul (A-Z)!" << endl;
    cout << "Press any key to continue...";
    cin.get();
}

// ============================================================
// MAIN
// ============================================================

int main() {
    Buku daftarBuku[MAX_BUKU];
    int  jumlahBukuSekarang = 0;

    bacaDataBukuDariFile(daftarBuku, jumlahBukuSekarang);

    // Welcome Screen
    cout << "=======================================================" << endl;
    cout << "        SELAMAT DATANG DI PERPUSTAKAAN JOGJA          " << endl;
    cout << "=======================================================" << endl;
    cout << "Silakan tekan Enter untuk melanjutkan... ";
    cin.get();

    int pilihan;
    system("cls");
    do {
        cout << "=======================================================" << endl;
        cout << "                    MENU UTAMA                        " << endl;
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
                tambahBuku(daftarBuku, jumlahBukuSekarang);
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
                cout << "Terima kasih telah menggunakan aplikasi perpustakaan!" << endl;
                break;
            default:
                cout << "  [!!] Pilihan tidak valid! Silakan coba lagi." << endl;
                cout << "  Tekan Enter untuk kembali...";
                cin.get();
        }

        if (pilihan != 5) system("cls");

    } while (pilihan != 5);

    return 0;
}
