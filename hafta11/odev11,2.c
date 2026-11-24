#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 6 
#define INF INT_MAX

const char dugumIsimleri[V] = {'A', 'B', 'C', 'D', 'E', 'F'};


int minMesafeDugumu(int dist[], bool known[]) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!known[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}


void yoluYazdir(int path[], int hedef) {
    if (path[hedef] == -1) {
        printf("%c", dugumIsimleri[hedef]);
        return;
    }
    yoluYazdir(path, path[hedef]);
    printf("->%c", dugumIsimleri[hedef]);
}


int dijkstra(int graf[V][V], int kok, bool detayYazdir) {
    int dist[V];     
    bool known[V];   
    int path[V];     

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        known[i] = false;
        path[i] = -1;
    }

    dist[kok] = 0;

    for (int adim = 0; adim < V; adim++) {
        int u = minMesafeDugumu(dist, known);
        if (u == -1) break;
        known[u] = true;

        for (int v = 0; v < V; v++) {
            if (!known[v] && graf[u][v] > 0 && dist[u] != INF && dist[u] + graf[u][v] < dist[v]) {
                dist[v] = dist[u] + graf[u][v];
                path[v] = u;
            }
        }
    }

    int toplamMaliyet = 0;
    if (detayYazdir) {
        printf("\n=== Kok Dugum: %c icin Dijkstra Tablosu ===\n", dugumIsimleri[kok]);
        printf("Dugum\tKnown\tDistance\tPath\n");
        printf("-------------------------------------\n");
        for (int i = 0; i < V; i++) {
            printf("%c\t%s\t%d\t\t%c\n",
                   dugumIsimleri[i],
                   known[i] ? "True" : "False",
                   dist[i],
                   (path[i] == -1) ? '-' : dugumIsimleri[path[i]]);
        }

        
        if (kok == 0) {
            printf("\n--- A Dugumunden B ve D Dugumlerine En Kisa Rotalar ---\n");
            printf("A -> B Rotasi: ");
            yoluYazdir(path, 1);
            printf(" (Toplam Maliyet: %d)\n", dist[1]);

            printf("A -> D Rotasi: ");
            yoluYazdir(path, 3);
            printf(" (Toplam Maliyet: %d)\n", dist[3]);
        }
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] != INF) {
            toplamMaliyet += dist[i];
        }
    }

    return toplamMaliyet;
}

int main() {
    
    int graf[V][V] = {0};

    
    int kenarlar[][3] = {
        {0, 1, 7}, 
        {0, 2, 5}, 
        {0, 5, 1}, 
        {1, 2, 1}, 
        {1, 3, 1}, 
        {1, 4, 3}, 
        {2, 3, 2}, 
        {2, 4, 1}, 
        {3, 5, 7}, 
        {4, 5, 2}  
    };
    int kenarSayisi = sizeof(kenarlar) / sizeof(kenarlar[0]);

    for (int i = 0; i < kenarSayisi; i++) {
        int u = kenarlar[i][0];
        int v = kenarlar[i][1];
        int agirlik = kenarlar[i][2];
        graf[u][v] = agirlik;
        graf[v][u] = agirlik;
    }

    
    char secim;
    printf("Dijkstra analizi icin kok dugumu giriniz (A-F): ");
    scanf(" %c", &secim);

    int kokIndeks = -1;
    for (int i = 0; i < V; i++) {
        if (dugumIsimleri[i] == secim || dugumIsimleri[i] == secim - 32) {
            kokIndeks = i;
            break;
        }
    }

    if (kokIndeks != -1) {
        dijkstra(graf, kokIndeks, true);
    } else {
        printf("Gecersiz dugum girildi! Varsayilan olarak A seciliyor.\n");
        dijkstra(graf, 0, true);
    }

    
    printf("\n=== Merkezi Dugum Analizi (Tum Dugumler) ===\n");
    int enDusukToplam = INF;
    int merkeziDugum = -1;

    for (int i = 0; i < V; i++) {
        int toplam = dijkstra(graf, i, false);
        printf("Kok Dugum %c -> En Kisa Yol Agaci Toplam Maliyeti: %d\n", dugumIsimleri[i], toplam);
        if (toplam < enDusukToplam) {
            enDusukToplam = toplam;
            merkeziDugum = i;
        }
    }

    printf("\nSonuc: En dusuk toplam maliyete (%d) sahip EN MERKEZI DUGUM: %c\n",
           enDusukToplam, dugumIsimleri[merkeziDugum]);

    return 0;
}