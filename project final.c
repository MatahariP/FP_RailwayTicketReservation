#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

typedef struct{
    char namaa[50];
}Nama;

typedef struct{
    int statiun[5][5];
}graph;
graph jalur;

typedef struct{
    int bangku[5][5];
}data_statiun;

typedef struct{
    data_statiun waktu[3];
}jam;

typedef struct{
    jam jadwal[3];
}date;

typedef struct{
    date Terminus[3];
} buntu;

buntu kumpulan_statiun[6];
buntu cek_kursi;

Nama waktu_pergi_A;
Nama waktu_pulang_A;
Nama waktu_pergi_B;
Nama waktu_pulang_B;

Nama nama_Statiun[6]={"", "Gambir", "Bandung",  "Cirebon", "Solo Balapan", "Surabaya Pasarturi"};
Nama waktu_A_1[6]={"","5:40","7:00","9:20","10:40"};
Nama waktu_A_2[6]={"","18:20","19:20","21:20","23:30"};
Nama waktu_B_1[6]={"","23:00","21:20","19:00","18:00"};
Nama waktu_B_2[6]={"","10:20","9:40","7:40","5:20"};


void header1(){
    printf("\n==========================================================================\n");
    printf(" MENU > PESAN TIKET");
    printf("\n==========================================================================\n");
}

void pesan_tiket(){
    int u,v,a, b, c, tanggal, jamber, check_uv=0, pilih, batal;
    int milih_kursi_1[6], milih_kursi_2[6], jum_penumpang, perjalanan;
    int kd_pembayaran[3], total_harga=0, bayar, harga[4]={135000, 130000, 145000, 110000};

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    for(int m=1;m<=2;m++)
        for(int i=1;i<=5;i++){
            for(int j=1;j<=5;j++){
                kumpulan_statiun[i].Terminus[m].jadwal[m].waktu[m].bangku[i][j]=0;
            }
        }

    getch();

    cp_milih_tanggal:
    system("cls");
    header1();
    printf("\n TANGGAL YANG TERSEDIA");
    printf("\n\t          ==================================");
    printf("\n\t          | No |\t Tanggal           |");
    printf("\n\t          ==================================");
    printf("\n\t          | 1  |\t %d-%d-%d         |", tm.tm_mday+1, tm.tm_mon+1, tm.tm_year+1900);
    printf("\n\t          | 2  |\t %d-%d-%d         |", tm.tm_mday+2, tm.tm_mon+1, tm.tm_year+1900);
    printf("\n\t          ==================================");
    printf("\n\n Pilih tanggal\t: ");
    scanf("%d", &tanggal);
    if(tanggal != 1 && tanggal != 2){
        printf("\n Tidak ada pilihan tersebut\n");
        getch();
        goto cp_milih_tanggal;
    }
    cp_perjalanan:
    system("cls");
    header1();
    printf("\n TENTUKAN PERJALANAN");
    printf("\n\t\t=================================");
    printf("\n \t\t\t1. Sekali Perjalanan        ");
    printf("\n \t\t\t2. Pulang Pergi            ");
    printf("\n\t\t=================================");
    printf("\n\n Pilih perjalanan\t: "), scanf("%d", &perjalanan);
    if(perjalanan != 1 && perjalanan != 2){
        printf("\nTidak ada pilihan tersebut\n");
        getch();
        goto cp_perjalanan;
    }
    cp_PilihStatiun:
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            jalur.statiun[i][j]=0;
        }
    }
    system("cls");
    header1();
    printf("\n STASIUN YANG TERSEDIA");
    printf("\n\t          ====================================");
    printf("\n\t          | No |\t Stasiun             |");
    printf("\n\t          ====================================");
    printf("\n\t          | 1  |\t Gambir              |");
    printf("\n\t          | 2  |\t Bandung             |");
    printf("\n\t          | 3  |\t Cirebon             |");
    printf("\n\t          | 4  |\t Solo Balapan        |");
    printf("\n\t          | 5  |\t Surabaya Pasarturi  |");
    printf("\n\t          ====================================\n");
    printf("\n Pilih stasiun keberangkatan : "),scanf("%d", &u);
    if(u<0||u>5){
        printf("Tidak ada Pilihan tersebut! ");
        getch();
        goto cp_PilihStatiun;
    }
    printf("\n STASIUN YANG TERSEDIA");
    printf("\n\t          ====================================");
    printf("\n\t          | No |\t Stasiun             |");
    printf("\n\t          ====================================");
    printf("\n\t          | 1  |\t Gambir              |");
    printf("\n\t          | 2  |\t Bandung             |");
    printf("\n\t          | 3  |\t Cirebon             |");
    printf("\n\t          | 4  |\t Solo Balapan        |");
    printf("\n\t          | 5  |\t Surabaya Pasarturi  |");
    printf("\n\t          ====================================\n");
    printf("\n Pilih stasiun tujuan\t: "),scanf("%d", &v);
    if(v<0||v>5){
        printf("Tidak ada Pilihan tersebut!");
        getch();
        goto cp_PilihStatiun;
    }
    if(u==v){
        printf("\nStasiun keberangkatan dan tujuan tidak boleh sama!!\n\n");
        getch();
        goto cp_PilihStatiun;
    } else if(u<v){
        a=u;
        b=v;
        c=1;
    }else if(u>v){
        a=v;
        b=u;
        c=2;
    }

    cp_milih_jamber:
    system("cls");
    header1();
    printf("\n WAKTU YANG TERSEDIA");
    if(perjalanan==1){
        if(u<v){
            printf("\n       ===============================================================");
            printf("\n       | No |\t    Tujuan \t\t|         Waktu              |");
            printf("\n       ===============================================================");
            printf("\n       | 1  |\t%s -> %s\t| \t%s -> %s\t     |", nama_Statiun[u], nama_Statiun[v], waktu_A_1[a], waktu_A_1[b]);
            printf("\n       | 2  |\t%s -> %s\t| \t%s -> %s\t     |", nama_Statiun[u], nama_Statiun[v], waktu_A_2[a], waktu_A_2[b]);
            printf("\n       ===============================================================");
        }
        else if(u>v){
            printf("\n       ===============================================================");
            printf("\n       | No |\t    Tujuan \t\t|         Waktu              |");
            printf("\n       ===============================================================");
            printf("\n       | 1  |\t%s -> %s\t| \t%s -> %s\t     |", nama_Statiun[v], nama_Statiun[u], waktu_B_1[a], waktu_B_1[b]);
            printf("\n       | 2  |\t%s -> %s\t| \t%s -> %s\t     |", nama_Statiun[v], nama_Statiun[u], waktu_B_2[a], waktu_B_2[b]);
            printf("\n       ===============================================================");
        }
    }
    else if(perjalanan==2){
        if(u<v){
            printf("\n       ===============================================================");
            printf("\n       | No |\t    Tujuan \t\t|         Waktu              |");
            printf("\n       ===============================================================");
            printf("\n       | 1  |\t%s -> %s\t| \t%s -> %s\t     |", nama_Statiun[u], nama_Statiun[v], waktu_A_1[b], waktu_A_1[a]);
            printf("\n       |    |\t%s -> %s\t| \t%s -> %s\t     |", nama_Statiun[v], nama_Statiun[u], waktu_B_1[a], waktu_B_1[b]);
            printf("\n       ===============================================================");
        }
        else if(u>v){
            printf("\n       ===============================================================");
            printf("\n       | No |\t    Tujuan \t\t|         Waktu              |");
            printf("\n       ===============================================================");
            printf("\n       | 1  |\t%s -> %s\t| \t%s -> %s\t     |", nama_Statiun[u], nama_Statiun[v], waktu_B_2[b], waktu_B_2[a]);
            printf("\n       |    |\t%s -> %s\t| \t%s -> %s\t     |", nama_Statiun[v], nama_Statiun[u], waktu_A_2[a], waktu_A_2[b]);
            printf("\n       ===============================================================");
        }
    }
    printf("\n\n Pilih Waktu Keberangkatan Dari Stasiun %s\t: ", nama_Statiun[u]);
    scanf("%d", &jamber);
        if(jamber==1){
            waktu_pergi_A=waktu_A_1[a];
            waktu_pulang_A=waktu_A_1[b];
            waktu_pergi_B=waktu_B_1[b];
            waktu_pulang_B=waktu_B_1[a];
        }
        else if(jamber==2){
            waktu_pergi_A=waktu_A_2[a];
            waktu_pulang_A=waktu_A_2[b];
            waktu_pergi_B=waktu_B_2[b];
            waktu_pulang_B=waktu_B_2[a];
        }
        else if((perjalanan==2)&&(jamber!=1)){
            printf("\nTidak ada pilihan tersebut");
            getch();
            goto cp_milih_jamber;
        }else{
            printf("\nTidak ada pilihan tersebut");
            getch();
            goto cp_milih_jamber;
        }

        for(int i=a;i<=b;i++)
            for(int j=a;j<=b;j++)
                if((i<j || i==j)&& perjalanan==1&&u<v)
                    jalur.statiun[i][j]=1;
                else if((i>j || i==j)&& perjalanan==1&&u>v)
                    jalur.statiun[i][j]=1;
                else if(perjalanan==2)
                    jalur.statiun[i][j]=1;

    system("cls");
    header1();
            printf("\n RUTE PERJALANAN\n");
            printf("   1  2  3  4  5");
            for(int i=1;i<=5;i++){
                printf("\n%d ", i);
                for(int j=1;j<=5;j++){
                    printf(" %d ", jalur.statiun[i][j]);
                }
            }
            printf("\n\n Jalur yang akan ditempuh:\n");
            int i=a;
            for(int j=1;j<=5;j++){
                if(jalur.statiun[i][j]==1){
                    if(perjalanan==1){
                        if(j==1)
                            printf("[ %s ] ", nama_Statiun[i]);
                        else
                            printf("-> [ %s ] ", nama_Statiun[i]);
                    }
                    else if(perjalanan==2){
                        if(j==1)
                            printf("[ %s ] ", nama_Statiun[i]);
                        else
                            printf("<-> [ %s ] ", nama_Statiun[i]);
                    }
                    i++;
                }
            }
            cp_validasi_tujuan:
            printf("\n\n\t\t======================================");
            printf("\n\t\t| Apakah tujuan Anda sudah benar?    |");
            printf("\n\t\t|\t\t1. YA                |");
            printf("\n\t\t|\t\t2. TIDAK             |");
            printf("\n\t\t======================================");
            printf("\n\t Pilihan\t: ");
            int pilihan;
            scanf("%d", &pilihan);
            if(pilihan== 1){
                system("cls");
                header1();
                printf("\n PEMESANAN KURSI\n");
                cp_jumlah_penumpang:
                printf("\n Jumlah kursi yang ingin di pesan : ");
                scanf("%d", &jum_penumpang);
                if(jum_penumpang>=5||jum_penumpang<=0){
                    printf("\nPesan kursi tidak boleh 0 atau lebih dari 5!!");
                    getch();
                    goto cp_jumlah_penumpang;
                }
                for(int m=1;m<=perjalanan;m++){
                    int k=a;
                    while(k<=b){
                        for(int i=1;i<=5;i++)
                            for(int j=1;j<=5;j++){
                                if((kumpulan_statiun[k].Terminus[c].jadwal[tanggal].waktu[c].bangku[i][j] == 1) || (kumpulan_statiun[k+1].Terminus[c].jadwal[tanggal].waktu[c].bangku[i][j]==1)){
                                    cek_kursi.Terminus[c].jadwal[tanggal].waktu[c].bangku[i][j]= 1;
                                    kumpulan_statiun[k+1].Terminus[c].jadwal[tanggal].waktu[c].bangku[i][j]=1;
                                }
                                else if((kumpulan_statiun[k].Terminus[c].jadwal[tanggal].waktu[c].bangku[i][j]==0) && (kumpulan_statiun[k+1].Terminus[c].jadwal[tanggal].waktu[c].bangku[i][j]==0)){
                                    cek_kursi.Terminus[c].jadwal[tanggal].waktu[c].bangku[i][j]= 0;
                                }
                            }
                        k++;
                    }
                    printf("\n KONFIGURASI TEMPAT DUDUK");
                    printf("\n   1  2  3  4  5");
                    for(int i=1;i<=5;i++){
                        printf("\n%d ",i);
                        for(int j=1;j<=5;j++){
                            printf(" %d ",cek_kursi.Terminus[c].jadwal[tanggal].waktu[c].bangku[i][j]);
                        }
                    }
                    printf("\n\n KET : 1 (TERISI)");
                    printf("\n       0 (BELUM TERISI)");

                    cp_pilih_bangku:
                    if(m==1){
                        printf("\n\n Pilih kursi yang ingin di pesan saat keberangkatan:\n");
                    }else if(m==2){
                        printf("\n Pilih kursi yang ingin di pesan saat pulang:\n");
                    }
                    for(int i= 1;i<= jum_penumpang;i++){
                        printf("%d. ", i);
                        scanf("%d %d", &milih_kursi_1[i], &milih_kursi_2[i]);
                        if((milih_kursi_1[i]>5)|| (milih_kursi_2[i]>5)){
                            printf("\nTidak ada kursi dengan nomor tersebut!\n");
                            if(i==1){
                                getch();
                                goto cp_pilih_bangku;
                            }
                            else{
                                for(int k=a;k<=b;k++){
                                    for(int j=1;j<=i;j++){
                                        kumpulan_statiun[k].Terminus[c].jadwal[tanggal].waktu[c].bangku[milih_kursi_1[j]][milih_kursi_2[j]]=0;
                                    }
                                }
                            }
                            getch();
                            goto cp_pilih_bangku;
                        }
                        k=a;
                        while(k<=b){
                            if(kumpulan_statiun[k].Terminus[c].jadwal[tanggal].waktu[c].bangku[milih_kursi_1[i]][milih_kursi_2[i]] == 1 ){
                                printf("\nKursi sudah terisi!!! silahkan pilih ulang!");
                                for(k=a;k<=b;k++){
                                    for(int j=1;j<i;j++){
                                        kumpulan_statiun[k].Terminus[c].jadwal[tanggal].waktu[c].bangku[milih_kursi_1[j]][milih_kursi_2[j]]=0;
                                    }
                                }
                                getch();
                                goto cp_pilih_bangku;
                            }
                            else if (kumpulan_statiun[k].Terminus[c].jadwal[tanggal].waktu[c].bangku[milih_kursi_1[i]][milih_kursi_2[i]] == 0){
                                kumpulan_statiun[k].Terminus[c].jadwal[tanggal].waktu[c].bangku[milih_kursi_1[i]][milih_kursi_2[i]]=1;
                            }
                            k++;
                        }
                    }
                    if(u<v)
                        c++;
                    else if(u>v)
                        c--;
                }
            }
            else if(pilihan==2){
                goto cp_PilihStatiun;
            }
            else{
                printf("\nTidak ada pilihan tersebut");
                getch();
                goto cp_validasi_tujuan;
            }
    for(int i=a; i<b;i++)
        total_harga=total_harga+harga[a];
    system("cls");
    printf("\n==========================================================================\n");
    printf(" MENU > PESAN TIKET > PEMBAYARAN");
    printf("\n==========================================================================\n");
    printf("                         DETAIL PEMESANAN TIKET\n");
    printf("\n Stasiun Keberangkatan\t: %s", nama_Statiun[u]);
    printf("\n Stasiun Tujuan\t\t: %s", nama_Statiun[v]);
    printf("\n Jenis Perjalanan\t: %d  (1 = Sekali Perjalanan, 2 = Pulang Pergi)", perjalanan);
    if(tanggal==1)
        printf("\n Tanggal Pergi\t\t: %d-%d-%d", tm.tm_mday+1, tm.tm_mon+1, tm.tm_year+1900);
    else if(tanggal==2)
        printf("\n Tanggal Pergi\t\t: %d-%d-%d", tm.tm_mday+2, tm.tm_mon+1, tm.tm_year+1900);
    printf("\n Waktu Pergi\t\t: %s-%s", waktu_pergi_A, waktu_pulang_A);
    if(perjalanan==2)
        printf("\n Waktu Pulang\t\t: %s-%s", waktu_pergi_B, waktu_pulang_B);
    printf("\n Jumlah Kursi\t\t: %d", jum_penumpang*perjalanan);
    printf("\n Rincian Harga\t\t: %d x %d", jum_penumpang*perjalanan, total_harga);
    printf("\n =======================================================");
    printf("\n | TOTAL HARGA\t\t:                    Rp.%d |", (jum_penumpang*perjalanan)*total_harga);
    printf("\n =======================================================");
    printf("\n\n Pilih Metode Pembayaran : ");
    printf("\n\n\t\t\t1. BRI-Mobile\n");
    printf("\t\t\t2. Klik BCA\n");
    printf("\t\t\t3. LinkAja\n");
    printf("\t\t\t4. BNI Mobile Banking\n\n");
    printf(" Pilihan\t: ");
    scanf("%d", &bayar);

    srand(time(0));
    for(int i = 0; i<3; i++)
        kd_pembayaran[i]=rand();
    cp_pembayaran:
    system("cls");
    printf("\n==========================================================================\n");
    printf(" MENU > PESAN TIKET > PEMBAYARAN");
    printf("\n==========================================================================\n");
    printf("\n \t=====================================================");
    printf("\n \t| KODE PEMBAYARAN: %d %d %d                 |", kd_pembayaran[0],kd_pembayaran[1],kd_pembayaran[2]);
    printf("\n \t|                                                   |");
    printf("\n \t=====================================================\n");
    printf("\n \t==============                       ================");
    printf("\n \t| 1. SELESAI |                       | 2. BATALKAN  |");
    printf("\n \t==============                       ================");
    printf("\n\n Pilihan\t: ");
    scanf("%d", &pilih);
    switch(pilih){
        case 1: printf("\n\t========================================================\n");
                printf("                      Pemesanan Tiket Berhasil! ");
                printf("\n\t========================================================\n");
                getch();
                break;
        case 2: cp_tiket_batal:
                printf("\n\n\t====================================================");
                printf("\n\t| Apakah Anda yakin akan membatalkan pesanan?      |");
                printf("\n\t|\t\t1. YA                              |");
                printf("\n\t|\t\t2. TIDAK                           |");
                printf("\n\t====================================================");
                printf("\n\t Pilihan\t: ");
                scanf("%d", &batal);
                if(batal == 1){
                    printf("\n\t========================================================\n");
                    printf("                       Pemesanan Tiket Dibatalkan! ");
                    printf("\n\t========================================================\n");
                    if(u<v)
                        c=1;
                    else if(u>v)
                        c=2;
                    for(int m=1;m<=perjalanan;m++){
                        for(int j=1;j<=jum_penumpang;j++){
                            for(int k=a;k<=b;k++){
                                kumpulan_statiun[k].Terminus[c].jadwal[tanggal].waktu[c].bangku[milih_kursi_1[j]][milih_kursi_2[j]]=0;
                            }
                        }
                        if(u<v)
                            c++;
                        else if(u>v)
                            c--;
                    }
                        getch();
                }
                else if(batal==2)
                    goto cp_pembayaran;
                else{
                    printf("\nTidak ada pilihan tersebut");
                    getch();
                    goto cp_tiket_batal;
                }
    }
}


int main(){
int menu;

while(1){
        system("cls");
        printf("\n==========================================================================\n");
        printf("=              SELAMAT DATANG DI PEMESANAN TIKET KERETA API              =\n");
        printf("==========================================================================\n");
        printf("                                 M E N U\n");
        printf("\n\t1. Pesan Tiket\n");
        printf("\t2. Jalur-Jalur Kereta\n");
        printf("\t3. Keluar\n");
        printf("\n==========================================================================\n");
        printf(" Masukan pilihan Anda\t: ");
        scanf("%d",&menu);
        switch(menu){
            case 1 :
                pesan_tiket();
                break;
            case 2 :
                system("cls");
                printf("\n==========================================================================\n");
                printf(" MENU > JALUR-JALUR KERETA");
                printf("\n==========================================================================\n");
                printf("\n Jalur Stasiun dari Terminus ke Terminus\n\n");
                 for(int j=1;j<=5;j++){
                    if(j==1)
                    printf("[ %s ] ", nama_Statiun[j]);
                    else
                    printf("<-> [ %s ] ", nama_Statiun[j]);
                }
                printf("\n\n");
                printf("\n \t\t=========================================");
                printf("\n \t\t|    TEKAN 1 UNTUK KEMBALI KE MENU      |");
                printf("\n \t\t=========================================\n");
                getch();
                break;
            case 3:
                system("cls");
                printf("\n\t========================================================\n");
                printf("           Terima Kasih, Semoga Perjalanan Anda Lancar... ");
                printf("\n\t========================================================\n");
                exit(1);
                break;
            default:
                printf("\nPILIHAN TIDAK TERSEDIA\n");
                getch();
                break;
        }
    }

}
