#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *titolo;
    char *regista;
    int anno;
    float durata;
}Film;
int file_exists(char *filename) {
    FILE *fileBinario= fopen(filename,"rb");
    if (fileBinario == NULL) {
        return 0;
    }else {
        return 1;
    }
}
int main(void) {
    int dimensione=4;

    Film *elenco;
    if (file_exists("canzoni.dat")) {
        FILE *file=fopen("canzoni.dat","rb");
        fread(&dimensione,sizeof(int),1,file);
        fread(elenco,sizeof(Film),dimensione,file);
    }else {

    }
    return 0;
}