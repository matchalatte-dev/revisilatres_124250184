#include <iostream>
#include <iomanip>
#include <limits> //[Revisi] Untuk validasi input
using namespace std;
// Struct untuk menyimpan data bagasi
 struct Bagasi
 {
    int flightTime;
    float berat;
 };
// Struct node PTB / Binary Search Tree
 struct PtbNode
 {
    Bagasi data;
    PtbNode *left, *right;
    // Constructor node PTB
    PtbNode(Bagasi val)
     {
        data  = val;
        left  = right = nullptr;
     }
 };
  PtbNode *root = nullptr;
// Struct node Queue
 struct QueueNode
 {
    Bagasi data;
    QueueNode *next;
 };
  QueueNode *depan    = nullptr;
   QueueNode *belakang = nullptr;
// Struct node Stack
 struct StackNode
 {
    Bagasi data;
    StackNode *next;
 };
 StackNode *stackawal = nullptr;
// [Revisi] Menambahkan pause agar output tidak langsung terlewat
 void pauseProgram()
 {
    cout << "\nTekan Enter untuk melanjutkan...";
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
     cin.get();
 }
// Function untuk mencetak data bagasi
 void cetakBagasi(Bagasi b)
 {
    cout << "[Flight:"
         << setfill('0') << setw(4) << b.flightTime
         << " | Berat:"
         << fixed << setprecision(1)
         << b.berat << "kg]";
 }
// Validasi flight time format 24 jam
  bool validFlight(int waktu)
    {
    int jam   = waktu / 100;
    int menit = waktu % 100;
    if (jam < 0 || jam > 23)
    {
        return false;
    }
    if (menit < 0 || menit > 59)
    {
        return false;
      }
    return true;
   }
// Mengecek flight time agar unik
   bool cekUnik(PtbNode *root, int value)
   {
    if (root == nullptr)
    {
        return true;
    }
    if (value == root->data.flightTime)
     {
        return false;
     }
    if (value < root->data.flightTime)
    {
        return cekUnik(root->left, value);
    }

    return cekUnik(root->right, value);
 }
// Insert data ke PTB/BST
  void insert(PtbNode *&root, Bagasi value)
  {
    if (root == nullptr)
    {
        root = new PtbNode(value);
        return;
    }
    PtbNode *curr = root;
        while (true)
      {
        // Jika lebih kecil masuk kiri
        if (value.flightTime < curr->data.flightTime)
        {
           if (curr->left == nullptr)
            {
                curr->left = new PtbNode(value);
                return;
           }
               curr = curr->left;
         } else {
            // Jika lebih besar masuk kanan
            if (curr->right == nullptr)
               {
                curr->right = new PtbNode(value);
                return;
            }
            curr = curr->right;
         }
      }
   }
// Traversal inorder untuk menampilkan data terurut
   void inorder(PtbNode *root)
   {
    if (root == nullptr)
    {
        return;
    }
    inorder(root->left);
    cout << " -> ";
    cetakBagasi(root->data);
    cout << endl;
    inorder(root->right);
  }
// Menghapus seluruh node PTB
   void deleteTree(PtbNode *&root)
   {
    if (root == nullptr)
    {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
   }
// Membuat node Queue baru
   QueueNode *buatQueueNode(Bagasi IB)
   {
    QueueNode *newnode = new QueueNode;
    newnode->data = IB;
    newnode->next = nullptr;
    return newnode;
  }
// Menambahkan data ke Queue
   void enqueue(Bagasi IB)
   {
    QueueNode *newnode = buatQueueNode(IB);
    if (depan == nullptr)
    {
        depan = belakang = newnode;
    } else {
        belakang->next = newnode;
        belakang       = newnode;
      }
   }
// Menghapus data Queue dari depan
  void dequeue()
    {
    if (depan == nullptr)
    {
        cout << "Queue kosong!\n";
      }else{
        QueueNode *hapus = depan;
        depan = depan->next;
        delete hapus;
        // Jika queue habis
        if (depan == nullptr)
        {
            belakang = nullptr;
          }
       }
   }
// Menampilkan isi Queue
    void tampilQueue()
    {
    QueueNode *bantu = depan;
    if (bantu == nullptr)
       {
        cout << "(Queue kosong)\n";
        return;
        }
    while (bantu != nullptr)
       {
        cout << " -> ";
        cetakBagasi(bantu->data);
        cout << endl;
        bantu = bantu->next;
      }
   }
// [Revisi] Push stack diperbaiki
// Data baru masuk ke DEPAN stack, bukan ke ujung belakang
   void push(Bagasi IB)
   {
    StackNode *NS = new StackNode;
    NS->data = IB;
    NS->next = stackawal; // [Revisi] Node baru menunjuk ke node lama (depan)
    stackawal = NS;       // [Revisi] stackawal sekarang adalah node baru
   }
// [Revisi] Pop stack diperbaiki
// Menghapus dari depan stack, bukan dari belakang
   void pop()
   {
    if (stackawal == nullptr)
       {
        cout << "Stack kosong!\n";
       }else {
        StackNode *hapus = stackawal;
        stackawal = stackawal->next; // [Revisi] Geser stackawal ke node berikutnya
        delete hapus;
     }
    }
// Menampilkan isi Stack
   void cetakStack()
   {
    StackNode *bantu = stackawal;
    if (bantu == nullptr)
       {
        cout << "(Stack kosong)\n";
        return;
          }
    while (bantu != nullptr)
       {
        cout << " -> ";
        cetakBagasi(bantu->data);
        cout << endl;
        bantu = bantu->next;
    }
       }
// Memindahkan data PTB ke Queue menggunakan inorder
   void pindahKeQueue(PtbNode *root)
   {
    if (root == nullptr)
    {
        return;
    }
    pindahKeQueue(root->left);
    enqueue(root->data);
    pindahKeQueue(root->right);
   }
   int main()
    {
    int pilih;
    do
    {
        cout << "\n========== SISTEM KEAMANAN BANDARA ==========\n";
        cout << "1. [PTB] Check-In Bagasi\n";
        cout << "2. [PTB] Lihat Database Bagasi\n";
        cout << "3. [PTB -> Queue] Pindahkan Semua ke Konveyor\n";
        cout << "4. [Queue] Lihat Antrian Konveyor\n";
        cout << "5. [Queue -> Stack] Proses Scanning X-Ray\n";
        cout << "6. [Stack] Lihat Tumpukan Overweight\n";
        cout << "7. [Stack Process] Pemeriksaan Manual\n";
        cout << "0. Keluar\n";
        cout << "Pilihan : ";
        // [Revisi] Validasi input menu, user diberi kesempatan input ulang
        while (!(cin >> pilih))
            {
            cout << "Input harus berupa angka!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan : ";
        }
    switch (pilih)
            {
            case 1:
                {
                Bagasi b;
                cout << "\n=== CHECK-IN BAGASI ===\n";
  
                // [Revisi] Menambahkan informasi format input
                // Agar user tahu format waktu dan batas berat
                cout << "Format Flight Time : HHMM (format 24 jam)\n";
                cout << "Contoh             : 0830 untuk jam 08:30\n";
                cout << "                   : 1545 untuk jam 15:45\n";
                cout << "Berat bagasi       : harus lebih dari 0 kg\n";

                // Input dan validasi flight time
                // [Revisi] Looping validasi flight time
                // User tidak keluar ke main menu jika salah input
                    do
                   {
                    cout << "Input Flight Time  : ";
                    while (!(cin >> b.flightTime))
                    {
                        cout << "Input harus berupa angka!\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Input Flight Time  : ";
                        }
                    if (!validFlight(b.flightTime))
                       {
                        cout << "Flight time tidak valid! Gunakan format HHMM (misal: 0830).\n";
                    }else if (!cekUnik(root, b.flightTime)) {
                        cout << "Flight time sudah ada! Masukkan flight time yang berbeda.\n";
                      }
                   } while (!validFlight(b.flightTime) || !cekUnik(root, b.flightTime));
   
                // [Revisi] Looping validasi berat
                // User tidak keluar ke main menu jika salah input  
                do
                {
                    cout << "Input Berat Bagasi : ";
                    while (!(cin >> b.berat))
                       {
                        cout << "Input harus berupa angka!\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Input Berat Bagasi : ";
                       }
                    if (b.berat <= 0)
                         {
                        cout << "Berat harus lebih dari 0 kg!\n";
                      }
                   }     while (b.berat <= 0);
                insert(root, b);
                cout << " Data Bagasi berhasil masuk ke Database PTB.\n";
                pauseProgram();
                break;
            }
               case 2:
                {
                cout << "\n=== DATABASE BAGASI ===\n";
                // Mengecek apakah PTB kosong
                if (root == nullptr)
                {
                    cout << "(Database kosong)\n";
                }else{
                    inorder(root);
                }
                pauseProgram();
                break;
             }
            case 3:
              {
                cout << "\n=== PINDAH KE KONVEYOR ===\n";
                // Validasi jika PTB kosong
                if (root == nullptr)
                   {
                    cout << " GAGAL: PTB kosong! Input data dulu di Menu 1.\n";
                }else{
                    // Memindahkan data PTB ke Queue
                    pindahKeQueue(root);
                    // Menghapus PTB setelah dipindahkan
                    deleteTree(root);
                    cout << " SUKSES: Semua bagasi berhasil dipindahkan dari PTB ke Queue Konveyor!\n";
                    cout << " INFO  : Database PTB sekarang telah dikosongkan.\n";
                 }
                pauseProgram();
                break;
            }
            case 4:
            {
                cout << "\n=== ANTRIAN KONVEYOR ===\n";
                tampilQueue();
                pauseProgram();
                break;
             }
            case 5:
             {
                cout << "\n=== SCANNING X-RAY ===\n";
                // Validasi jika Queue kosong
                  if (depan == nullptr)
                     {
                    cout << " GAGAL: Konveyor kosong! Load data dulu di Menu 3.\n";
                    pauseProgram();
                    break;
                   }
                   
                // [Revisi] Scan dilakukan PER ITEM
                // Setiap item ditampilkan satu per satu dengan pause
                // Bukan seluruh item sekaligus    
                while (depan != nullptr)
                {
                    Bagasi temp = depan->data;
                    cout << "\nScanning Item : ";
                    cetakBagasi(temp);
                   
                    // [Revisi] Menambahkan informasi status aman / overweight
                    // Batas berat aman adalah <= 9.3 kg                  
                    if (temp.berat <= 9.3)
                     {
                        cout << " --> STATUS : AMAN (Berat normal, lanjut ke pesawat)\n";
                         }else{
                            cout << " --> STATUS : OVERWEIGHT (Berat melebihi batas, masuk isolasi)\n";
                        push(temp);
                        }
                        dequeue();
                    // [Revisi] Pause per item agar output tidak terlewat
                    pauseProgram();
                 }
                break;
               }
            case 6:
            {
                cout << "\n=== ISI AREA ISOLASI (TUMPUKAN STACK) ===\n";
                cetakStack();
                pauseProgram();
                break;
            }
              case 7:
                {
                   cout << "\n=== PEMERIKSAAN MANUAL (Pop Stack sampai habis) ===\n";
                if (stackawal == nullptr)
                 {
                    cout << " INFO: Stack kosong. Tidak ada bagasi overweight.\n";
                  }else{
                    // Pemeriksaan manual sampai stack habis
                    while (stackawal != nullptr)
                    {
                        cout << "Petugas memeriksa : ";
                        cetakBagasi(stackawal->data);
                        cout << " --> SELESAI DIPERIKSA.\n";
                        pop();
                       }
                   cout << "\n-> Semua bagasi overweight telah diperiksa. ";
                    cout << "Tumpukan kosong.\n";
                }
                   pauseProgram();
                break;
               }
            case 0:
               {
                // Menghapus seluruh node sebelum keluar program
                deleteTree(root);
                cout << " Keluar dari Program ...\n";
                cout << " Terima kasih!\n";
                pauseProgram();
                break;
               }
            default:
            {
                cout << "Pilihan tidak valid!\n";
                pauseProgram();
            }
               }
   } while (pilih != 0);
 return 0;
}
