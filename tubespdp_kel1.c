/**********************************************************************
 * KELOMPOK 1
 *  1. Irene Delarosa Situmorang 241402044
 *  2. Nazwa Khairunnisa Manalu 241402067
 *  3. ⁠Lukas Alonso Lubis 241402061
 *  4. Winson Pardede 241402054
 *  6. Farel Reza Saputra 241402007
 * 
 * Tugas Besar Praktikum Pemrograman Dasar
 * Program ini untuk meminta user menginput nama user serta jurusannya
 * tergantung menu yang dipilih oleh user.
 * Program menyediakan fitur tambah mahasiswa, tampilkan mahasiswa, 
 * perbarui, dan hapus data.
 **********************************************************************/

#include <stdio.h>

void tambahMahasiswa();
void tampilkanMahasiswa();
void perbaruiMahasiswa();
void hapusMahasiswa();

// Struktur untuk data mahasiswa
typedef struct {
    int id;     
    char nama[50];
    char jurusan[50];
} Mahasiswa;

// Fungsi utama (menu utama)
int main() {
    int pilihan;
    do {
        printf("\n=== Menu Mahasiswa ===\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Tampilkan Mahasiswa\n");
        printf("3. Perbarui Mahasiswa\n");
        printf("4. Hapus Mahasiswa\n");
        printf("5. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahMahasiswa();
                break;
            case 2:
                tampilkanMahasiswa();
                break;
            case 3:
                perbaruiMahasiswa();
                break;
            case 4:
                hapusMahasiswa();
                break;
            case 5:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 5);

    return 0;
}
// Fungsi untuk menambahkan data mahasiswa
void tambahMahasiswa() {
    FILE *file = fopen("mahasiswa.txt", "a");
    if (!file) {
        printf("Gagal membuka file.\n");
        return;
    }

    Mahasiswa mhs;
    int validInput = 0;

    // Input ID dengan validasi
    while (!validInput) {
        printf("Masukkan ID (hanya angka): ");
        if (scanf("%d", &mhs.id) == 1) {
            validInput = 1;
        } else {
            printf("Input ID salah. Masukkan angka yang valid!\n");
            while (getchar() != '\n'); // Bersihkan buffer
        }
    }
    while (getchar() != '\n'); // Bersihkan buffer

    // Input nama dan jurusan
    printf("Masukkan Nama: ");
    scanf(" %[^\n]", mhs.nama);
    printf("Masukkan Jurusan: ");
    scanf(" %[^\n]", mhs.jurusan);

    // Tulis ke file
    fprintf(file, "%d|%s|%s\n", mhs.id, mhs.nama, mhs.jurusan);
    fclose(file);

    printf("Data berhasil ditambahkan!\n");
}

// Fungsi untuk membaca data mahasiswa
void tampilkanMahasiswa() {
    FILE *file = fopen("mahasiswa.txt", "r");
    if (!file) {
        printf("Gagal membuka file atau file belum dibuat.\n");
        return;
    }

    Mahasiswa mhs;
    int isEmpty = 1;

    printf("\nData Mahasiswa:\n\n");
    printf("+---------------+------------------------------+------------------------------+\n");
    printf("|%-15s|%-30s|%-30s|\n", "ID", "Nama", "Jurusan");
    printf("+---------------+------------------------------+------------------------------+\n");

        while (fscanf(file, "%d|%[^|]|%[^\n]", &mhs.id, mhs.nama, mhs.jurusan) != EOF) {
        isEmpty = 0;        
            printf("|%-15d|%-30.30s|%-30.30s|\n", mhs.id, mhs.nama, mhs.jurusan);
            printf("+---------------+------------------------------+------------------------------+\n");
        }

        if (isEmpty) {
            printf("Tidak ada data untuk ditampilkan.\n");
        }

    fclose(file);
}

// Fungsi untuk memperbarui data mahasiswa
void perbaruiMahasiswa() {
    FILE *file = fopen("mahasiswa.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Gagal membuka file.\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    int id, found = 0;
    Mahasiswa mhs;
    printf("Masukkan ID yang ingin diperbarui: ");
    scanf("%d", &id);

    while (fscanf(file, "%d|%[^|]|%[^\n]\n", &mhs.id, mhs.nama, mhs.jurusan) != EOF) {
        if (mhs.id == id) {
            found = 1;
            printf("Masukkan Nama Baru: ");
            scanf(" %[^\n]", mhs.nama);
            printf("Masukkan Jurusan Baru: ");
            scanf(" %[^\n]", mhs.jurusan);
        }
        fprintf(temp, "%d|%s|%s\n", mhs.id, mhs.nama, mhs.jurusan);
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("mahasiswa.txt");
        rename("temp.txt", "mahasiswa.txt");
        printf("Data berhasil diperbarui!\n");
    } else {
        remove("temp.txt");
        printf("Data dengan ID %d tidak ditemukan.\n", id);
    }
}

// Fungsi untuk menghapus data mahasiswa
void hapusMahasiswa() {
    FILE *file = fopen("mahasiswa.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Gagal membuka file.\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    int id, found = 0;
    Mahasiswa mhs;
    printf("Masukkan ID yang ingin dihapus: ");
    scanf("%d", &id);

    while (fscanf(file, "%d|%[^|]|%[^\n]\n", &mhs.id, mhs.nama, mhs.jurusan) != EOF) {
        if (mhs.id == id) {
            found = 1;
            continue; // Abaikan data yang ingin dihapus
        }
        fprintf(temp, "%d|%s|%s\n", mhs.id, mhs.nama, mhs.jurusan);
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("mahasiswa.txt");
        rename("temp.txt", "mahasiswa.txt");
        printf("Data berhasil dihapus!\n");
    } else {
        remove("temp.txt");
        printf("Data dengan ID %d tidak ditemukan.\n", id);
    }
}