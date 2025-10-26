#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
typedef struct {
    char titolo[100];
    char regista[100];
    int anno;
    float durata;
}Film;
int file_exists(char *filename) {
    FILE *fileBinario= fopen(filename,"rb");
    if (fileBinario == NULL) {
        return 0;
    }
        return 1;
}
Film Aggiungi_Film(Film film) {

    fflush(stdin);
    printf("Inserire titolo:");
    fgets(film.titolo, 100, stdin);

    printf("Inserire regista:");
    fgets(film.regista, 100, stdin);

    film.titolo[strcspn(film.titolo, "\n")] = '\0'; //rimuovo \n dalla stringa
    film.regista[strcspn(film.regista, "\n")] = '\0';

    do {
        printf("Inserire anno:");
        scanf(" %d",&film.anno);
    }while (film.anno<1500 || film.anno>2025);

    do {
        printf("Inserire durata:");
        scanf(" %f",&film.durata);
    }while (film.durata<=0 || film.durata>6);

    return film;

}
void VisualizzaLibreria(Film *elenco,int dim) {
    for (int i=0;i<dim;i++) {
       printf("Titolo: %s \n",elenco[i].titolo);
        printf("Regista: %s \n",elenco[i].regista);
        printf("Anno: %d \n",elenco[i].anno);
        printf("Durata: %.2f ore\n",elenco[i].durata);
    }
}
void CercaParola(Film *elenco,int dimensione) {
    fflush(stdin);
    char *parola;
    parola =(char *) malloc(dimensione * sizeof(char)*100);
    printf("Inserire la parola da ricercare:");
    fgets(parola,100, stdin);
    parola[strcspn(parola, "\n")] = '\0';
    char *ricerca;
    for (int i=0;i<dimensione;i++) {
        ricerca=strstr(elenco[i].titolo,parola);
        if (ricerca!=NULL) {
            printf("Titolo: %s \n",elenco[i].titolo);
            printf("Regista: %s \n",elenco[i].regista);
            printf("Anno: %d \n",elenco[i].anno);
            printf("Durata: %.2f ore\n",elenco[i].durata);
        }
    }
    free(parola);
}
void OrdinaFilm(Film *elenco,int dim) {
    Film temp;
    for (int i = 0; i < dim ; i++) {
        for (int j = i ; j < dim; j++) {
            if (elenco[i].anno > elenco[j].anno) {
                temp = elenco[i];
                elenco[i] = elenco[j];
                elenco[j] = temp;
            }
        }
    }
}
void SalvaSuFile(Film *elenco,int dim) {
    FILE *file=fopen("elenco.dat","wb");
    fwrite(&dim,sizeof(int),1,file);
    fwrite(elenco,sizeof(Film),dim,file);
    fclose(file);
}
int main(void) {
    int dimensione=0;

    Film *elenco;
    if (file_exists("elenco.dat")) {  //
        FILE *file=fopen("elenco.dat","rb");
        fread(&dimensione,sizeof(int),1,file);
        elenco=(Film*)malloc(sizeof(Film)*dimensione);
        fread(elenco,sizeof(Film),dimensione,file);
        fclose(file);
    }else {
        elenco=(Film*)malloc(sizeof(Film) * dimensione);
        if (elenco==NULL) {
            printf("errore di allocazione");
            free(elenco);
            exit(1);
        }
    }
    int scelta;
    Film *temp;
    do {
        do {
            printf("\n1 - Aggiungi Film\n2 - Visualizza Libreria\n3 - Cerca film per parola\n4 - Ordina Film\n5 - Salva su file \n6 - Esci \n Scelta: ");
            scanf(" %d", &scelta);
        } while (scelta < 1 || scelta > 5);
        switch(scelta) {
            case 1:
                dimensione++;
                temp=realloc(elenco,dimensione*sizeof(Film)); //puntatore temporaneo per riallocare
                if (temp==NULL) {
                    printf("errore di allocazione");
                    free(elenco);
                    free(temp);
                    exit(1);
                }
                elenco=temp;
                elenco[dimensione -1]=Aggiungi_Film(elenco[dimensione-1]);
                break;
            case 2:
                if (dimensione>0) {
                    VisualizzaLibreria(elenco,dimensione);
                }else {
                    printf("Libreria vuota\n");
                }
                break;
            case 3:
                CercaParola(elenco,dimensione);
                break;
            case 4:
                OrdinaFilm(elenco,dimensione);
                break;
            case 5:
                SalvaSuFile(elenco,dimensione);
                break;
            case 6:
                free(elenco);
                break;
        }
        if (scelta==6) {
            exit(0);
        }
    }while (true);
}