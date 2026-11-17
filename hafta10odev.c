#include <stdio.h>
#include <stdbool.h>

#define SEHIR_SAYISI 5


const char* sehirler[SEHIR_SAYISI] = {
    "Istanbul", 
    "Ankara", 
    "Izmir", 
    "Bursa", 
    "Antalya"
};


int graf[SEHIR_SAYISI][SEHIR_SAYISI] = {0};


void baglantiEkle(int u, int v) {
    graf[u][v] = 1;
    graf[v][u] = 1;
}

void BFS(int baslangic) {
    bool ziyaretEdildi[SEHIR_SAYISI] = {false};
    int kuyruk[SEHIR_SAYISI];
    int on = 0, arka = 0;

    
    ziyaretEdildi[baslangic] = true;
    kuyruk[arka++] = baslangic;

    printf("BFS Dolasim Sirasi (Baslangic: %s):\n", sehirler[baslangic]);

    while (on < arka) {
        int mevcut = kuyruk[on++];
        printf("%s", sehirler[mevcut]);

        
        for (int i = 0; i < SEHIR_SAYISI; i++) {
            if (graf[mevcut][i] == 1 && !ziyaretEdildi[i]) {
                ziyaretEdildi[i] = true;
                kuyruk[arka++] = i;
            }
        }

        if (on < arka) {
            printf(" -> ");
        }
    }
    printf("\n\n");
}


void DFSYardimci(int mevcut, bool ziyaretEdildi[]) {
    ziyaretEdildi[mevcut] = true;
    printf("%s ", sehirler[mevcut]);

    for (int i = 0; i < SEHIR_SAYISI; i++) {
        if (graf[mevcut][i] == 1 && !ziyaretEdildi[i]) {
            printf("-> ");
            DFSYardimci(i, ziyaretEdildi);
        }
    }
}

void DFS(int baslangic) {
    bool ziyaretEdildi[SEHIR_SAYISI] = {false};
    printf("DFS Dolasim Sirasi (Baslangic: %s):\n", sehirler[baslangic]);
    DFSYardimci(baslangic, ziyaretEdildi);
    printf("\n\n");
}

int main() {
    
    baglantiEkle(0, 1); 
    baglantiEkle(0, 3); 
    baglantiEkle(1, 2); 
    baglantiEkle(1, 4); 
    baglantiEkle(3, 4); 

    
    BFS(0);
    DFS(0);

    return 0;
}