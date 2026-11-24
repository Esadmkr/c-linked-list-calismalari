#include <stdio.h>
#include <stdbool.h>

#define N 6 


void dereceleriHesapla(int matris[N][N]) {
    int toplamDerece = 0;
    printf("\n--- Dugum Dereceleri ---\n");
    for (int i = 0; i < N; i++) {
        int derece = 0;
        for (int j = 0; j < N; j++) {
            derece += matris[i][j];
        }
        printf("Dugum %d derecesi: %d\n", i + 1, derece);
        toplamDerece += derece;
    }
    printf("Grafin Genel (Toplam) Derecesi: %d\n", toplamDerece);
}


bool bipartiteKontrol(int matris[N][N], int baslangic) {
    int renk[N];
    for (int i = 0; i < N; i++) {
        renk[i] = -1; 
    }

    int kuyruk[N];
    int on = 0, arka = 0;

    
    renk[baslangic] = 0;
    kuyruk[arka++] = baslangic;

    bool isBipartite = true;

    while (on < arka) {
        int u = kuyruk[on++];

        for (int v = 0; v < N; v++) {
            if (matris[u][v] == 1) {
                
                if (renk[v] == -1) {
                    renk[v] = 1 - renk[u];
                    kuyruk[arka++] = v;
                } 
                
                else if (renk[v] == renk[u]) {
                    isBipartite = false;
                }
            }
        }
    }

    printf("\n--- Renklendirme (0: Mavi/Cift, 1: Kirmizi/Tek) ---\n");
    for (int i = 0; i < N; i++) {
        printf("Dugum %d -> Renk: %d (%s)\n", i + 1, renk[i], (renk[i] == 0 ? "Mavi" : "Kirmizi"));
    }

    return isBipartite;
}

int main() {
    
    int komsulukMatrisi[N][N] = {0};

    
    int kenarlar[][2] = {
        {1, 2}, {1, 4}, {2, 3}, {3, 4}, {3, 6}, {4, 5}, {5, 6}
    };
    int kenarSayisi = sizeof(kenarlar) / sizeof(kenarlar[0]);

    for (int i = 0; i < kenarSayisi; i++) {
        int u = kenarlar[i][0] - 1;
        int v = kenarlar[i][1] - 1;
        komsulukMatrisi[u][v] = 1;
        komsulukMatrisi[v][u] = 1; 
    }

    printf("=== ILK DURUM (Orijinal Graf) ===\n");
    dereceleriHesapla(komsulukMatrisi);
    
    
    if (bipartiteKontrol(komsulukMatrisi, 0)) {
        printf("Sonuc: Graf IKI PARCALIDIR (Bipartite).\n");
    } else {
        printf("Sonuc: Graf IKI PARCALI DEGILDIR (Bipartite degil).\n");
    }

    
    printf("\n=== DINAMIK TEST: (2, 4) Kenari Eklendikten Sonra ===\n");
    komsulukMatrisi[1][3] = 1; 
    komsulukMatrisi[3][1] = 1;

    dereceleriHesapla(komsulukMatrisi);

    if (bipartiteKontrol(komsulukMatrisi, 0)) {
        printf("Sonuc: Graf IKI PARCALIDIR (Bipartite).\n");
    } else {
        printf("Sonuc: Graf IKI PARCALI DEGILDIR (Bipartite degil).\n");
    }

    return 0;
}

//SORU 2 


