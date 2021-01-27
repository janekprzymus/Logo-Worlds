#include "mapa.h"

void write(map *m){
    int i, j;

    for(i = m->wiersze-1; i>=0; i--){
        if(i==m->wiersze-1){
            printf("   ");
            for(j=0; j<m->kolumny; j++)
                printf("%3d", j+1);
            printf("\n");
        }
        for(j=0; j<m->kolumny; j++){
            if(j==0)
                printf("%3d", i+1);
            printf("%3c", m->plansza[i][j]);
        }
        printf("\n");
    }

}

void save(map *m){
    FILE *fout = fopen("plansza.txt", "w");
    int i, j;

    fprintf(fout, "%d\n%d\n", m->wiersze, m->kolumny);

    for(i = m->wiersze-1; i>=0; i--){
        for(j=0; j<m->kolumny; j++){
            fprintf(fout, "%c", m->plansza[i][j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
}

void alloc_map_memory(map *m, int wiersze, int kolumny){
    m->wiersze=wiersze;
    m->kolumny=kolumny;
    
    m->plansza = (char**) malloc(sizeof(char*) * wiersze);
    for (int i=wiersze-1; i>=0; i--){
        m->plansza[i] = (char*) malloc(sizeof(char) * kolumny);
        for (int j=0; j<kolumny; j++){
            m->plansza[i][j] = j+1+i;
        }
    }
    
}

map *map_init(map *m){   
    m = (map*) malloc(sizeof(map));
    alloc_map_memory(m, N, N);
    m->p = 2;
    m->q = 2;

    for(int i=N-1; i>=0; i--){
        for(int j=0; j<N; j++)
            m->plansza[i][j]='.';
    }

    return m;
} 

void move_map(map *new, map *m, int dx, int dy){   
    int i, j;
    for (i = new->wiersze-1; i>=0; i--){
        for (j=0; j<new->kolumny; j++){   
            new->plansza[i][j]='.';
        }
    }

    for (i = m->wiersze-1; i>=0; i--){
        for (j=0; j < m->kolumny; j++){
            new->plansza[i+dy][j+dx] = m->plansza[i][j];
        }
    }

    new->p = m->p+dx;
    new->q = m->q+dy;
}

void free_map(map *m){
    int i, j;
    for(i=0; i<m->wiersze; i++){
        free(m->plansza[i]);
    }
    free(m->plansza);
    free(m);
}

map *new_segment_north(map *m){
    map *new = (map*) malloc(sizeof(map));
    alloc_map_memory(new, m->wiersze+N, m->kolumny);
    move_map(new, m, 0, 0);
    new->x_start = m->x_start;
    new->y_start = m->y_start;
    free_map(m);
    
    return new;
}

map *new_segment_south(map *m){
    map *new = (map*) malloc(sizeof(map));
    alloc_map_memory(new, m->wiersze+N, m->kolumny);
    move_map(new, m, 0, N);
    new->x_start = m->x_start;
    new->y_start = m->y_start;
    free_map(m);
    
    return new;
}

map *new_segment_west(map *m){
    map *new = (map*) malloc(sizeof(map));
    alloc_map_memory(new, m->wiersze, m->kolumny+N);
    move_map(new, m, N, 0);
    new->x_start = m->x_start;
    new->y_start = m->y_start;
    free_map(m);
    
    return new;
}

map *new_segment_east(map *m){
    map *new = (map*) malloc(sizeof(map));
    alloc_map_memory(new, m->wiersze, m->kolumny+N);
    move_map(new, m, 0, 0);
    new->x_start = m->x_start;
    new->y_start = m->y_start;
    free_map(m);
    
    return new;
}
