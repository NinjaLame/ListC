/**
    ADT List Eksplisit
    keyword : Next, First, Info
    Fungsi2 utama: Create, Alokasi,
                    AddVFirst, AddFirst,
                    DelVFirst, DelFirst
                    PrintList
    Perhatian: Baca Seluruh komentar
                untuk lebih paham list
*/
#include <stdio.h>
#include <stdlib.h>

#define Nil NULL


typedef int infotype; //tipe data dari elemen List
typedef struct tElmList * address; //pointer elemen
//Struktur List
typedef struct tElmList{
    infotype Info; //isi sebuah elemen
    //alamat elemen berikutnya
    //struct tElmList * Next;     //cara 1 membuat next elemen =>
    address Next; //cara 2 buat address terlebih dahulu.
}ElmList;

//List berisi elemen List (address)
typedef struct{
    address First; //alamat elemen pertama
} List;

/**
    Belajar Menggunakan makro.

    1. Harus diawali dengan #define

    2. Tanda () adalah tempat untuk
        variable yang ingin dimasukan
        contoh:
        deklarasi variabel.
        address Elemen;
        cara biasa untuk mengakses info: Elemen->Info;
        dengan makro: Info(Elemen)

    3. Perhatikan Spasi
        Benar => #define Info(P) (P)->Info
        Salah => #define Info  (P) (P)->Info

*/
#define Info(P) (P)->Info //P adalah variabel bertipe address
#define Next (P) (P)->Next //Menggunakan panah karena address adalah pointer (cek typedef diatas)
#define First(L) (L).First //L adalah variabel bertipe List

void createEmpty(List *L){
    /**
         ________
        | First |____\ Nil
        |_______|    /
    */
    First(*L) = Nil; //sama seperti L->First = Nil
}

address Alokasi(infotype X){
    address P; //elemen yang dikembalikan
    P = (address)malloc(sizeof(address)); //alokasi sebesar memori address
    if (P!=Nil) { //jika P berhasil dialokasi
        Info(P) = X; //P->Info
        Next(P) = Nil; //P->Next
    }
}

void InserFirst(List *L, address P){ //memasukkan elemen (address) kedalam list
    if (P!=Nil) { //Jika tidak kosong
    /**
         ________                   _______________
        | First |______XXXXXXXXX__ | Info    |Next |_____\ Nil
        |_______|                  |_________|_____|     /
                \                  /
                 \_______________ /
                 | Info    |Next |
                 |_________|_____|
    */
        Next(P) = First(*L); ///Next P menunjuk elemen yang ditunjuk first
        First(*L) = P;  ///first sekarang menunjuk P
    }
}


void InserValFirst(List *L, infotype X){
    address P; //elemen yang ingin dimasukkan
    P = Alokasi(X); //alokasi elemen
    if (P!=Nil) {
        InserFirst(&(*L),P); //insert elemen kedalam list
    }
}

void delFirst(List *L, address *P){
    /**
         ________                    _______________
        | First |_________________\ | Info    |Next |___\Nil
        |_______|                 / |_________|_____|   /

         _______________
        | Info    |Next |_______\ Nil
        |_________|_____|       /
        (Tadinya) elemen pertama
    */
    if (First(*L) != Nil) { ///Jika list tidak kosong
        (*P) = First(*L); ///P akan menampung elemen pertama
        First(*L) = Next(First(*L)); ///elemen pertama list menunjuk ke elemen berikutnya
        Next(*P) = Nil; ///Next P dijadikan nil agar tidak menunjuk apa2
    }
    else {
        printf("Kosong");
    }

}

void delValFirst(List *L, infotype *X){
    if (First(*L)!=Nil) { //Jika list tidak kosong
        address P; //Menampung elemen yang dihapus
        delFirst(L, &P); //Del First
        (*X) = Info(P); //X menyimpan info elemen yang dihapus
    }
    else {
        printf("Kosong");
    }
}

void printList(List L){
    address temp = First(L); //menampung elemen pertama
    while(temp!=Nil){ //jika elemen tidak kosong, looping berjalan
        printf("[%d]", Info(temp)); //info elemen
         //menampung elemen setelahnya.
        temp = Next(temp);//Pada looping biasa, sama seperti i++
    }
}

int main()
{
    address P,P2;
    List L1;
    createEmpty(&L1);
    InserValFirst(&L1, 10);
    InserValFirst(&L1, 120);
    InserValFirst(&L1, 130);
    InserValFirst(&L1, 140);
    InserValFirst(&L1, 150);
    InserValFirst(&L1, 160);
    printList(L1);

    int X;

    puts("");

    delValFirst(&L1, &X);

    printf("\n!!! Yang dihapus %d !!!\n",X);

    InserValFirst(&L1, 120);
    printList(L1);
    return 0;
}
