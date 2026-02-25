#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "robot.h" /* Importiamo il nostro schema elettrico */

/* --- IMPLEMENTAZIONE FUNZIONI DI SUPPORTO (INPUT SICURO) --- */

void leggiIntero(int *n) {
    while (scanf("%d", n) != 1) {
        printf("Errore: devi inserire un numero intero! Riprova: ");
        while(getchar() != '\n'); 
    }
    while(getchar() != '\n'); 
}

void leggiFloat(float *f) {
    while (scanf("%f", f) != 1) {
        printf("Errore: devi inserire un valore numerico! Riprova: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');
}

void leggiStringa(char *s) {
    scanf("%s", s);
    while(getchar() != '\n');
}

/* --- IMPLEMENTAZIONE FUNZIONI LISTA --- */

TipoLista cercaNodo(TipoLista testa, int id) {
    TipoLista p = testa;
    while (p != NULL) {
        if (p->info.id == id)
            return p;
        p = p->next;
    }
    return NULL;
}

void stampaDatiMotore(TipoMotore m) {
    printf("ID: %d | Nome: %-10s | Pos: %6.2f | Range: [%.1f, %.1f]\n",
           m.id, m.nome, m.corrente, m.min, m.max);
}

void stampaLista(TipoLista testa) {
    TipoLista p = testa;
    if (p == NULL) {
        printf("La lista e' vuota.\n");
        return;
    }
    printf("\n--- ELENCO MOTORI ---\n");
    while (p != NULL) {
        stampaDatiMotore(p->info);
        p = p->next;
    }
    printf("---------------------\n");
}

void stampaQuelMotore(TipoLista testa, int id) {
    TipoLista p = cercaNodo(testa, id);
    if (p != NULL)
        stampaDatiMotore(p->info);
    else
        printf("Nessun motore trovato con ID %d.\n", id);
}

TipoLista aggiungiMotore(TipoLista testa) {
    TipoLista nuovo;
    int id_temp;

    printf("Inserisci ID univoco: ");
    leggiIntero(&id_temp);

    if (cercaNodo(testa, id_temp) != NULL) {
        printf("Errore: ID gia' presente in lista.\n");
        return testa;
    }

    nuovo = malloc(sizeof(TipoNodo));
    if (nuovo == NULL) {
        printf("Errore malloc: memoria esaurita.\n");
        return testa;
    }

    nuovo->info.id = id_temp;
    printf("Nome asse (senza spazi): ");
    leggiStringa(nuovo->info.nome);

    do {
        printf("Rotazione Max (>0): ");
        leggiFloat(&nuovo->info.max);
        if (nuovo->info.max <= 0) printf("Valore deve essere > 0.\n");
    } while (nuovo->info.max <= 0);

    nuovo->info.min = -nuovo->info.max;
    nuovo->info.corrente = 0.0;
    nuovo->next = testa;

    printf("Motore aggiunto.\n");
    return nuovo;
}

TipoLista eliminaMotore(TipoLista testa, int id) {
    TipoLista curr, prev;
    if (testa == NULL) return NULL;

    if (testa->info.id == id) {
        curr = testa;
        testa = testa->next;
        free(curr);
        printf("Motore rimosso.\n");
        return testa;
    }

    prev = testa;
    curr = testa->next;
    while (curr != NULL) {
        if (curr->info.id == id) {
            prev->next = curr->next;
            free(curr);
            printf("Motore rimosso.\n");
            return testa;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("ID non trovato.\n");
    return testa;
}

void modificaPosizione(TipoLista testa, int id, float nuovaPos) {
    TipoLista p = cercaNodo(testa, id);
    if (p == NULL) {
        printf("Motore non trovato.\n");
        return;
    }

    if (nuovaPos > p->info.max || nuovaPos < p->info.min) {
        printf("ALLARME: Posizione fuori dai limiti!\n");
    } else {
        p->info.corrente = nuovaPos;
        printf("Posizione aggiornata.\n");
    }
}

void salvaSuFile(TipoLista testa, char *nmf) {
    FILE *f = fopen(nmf, "w");
    TipoLista p = testa;
    if (f == NULL) {
        printf("Errore apertura file.\n");
        return;
    }

    while (p != NULL) {
        fprintf(f, "%d %s %.2f %.2f %.2f\n",
                p->info.id, p->info.nome, p->info.min,
                p->info.max, p->info.corrente);
        p = p->next;
    }
    printf("Salvataggio completato.\n");
    fclose(f);
}

TipoLista caricaDaFile(TipoLista testa, char *nmf) {
    FILE *f = fopen(nmf, "r");
    TipoLista nuovo;
    int letto;

    if (f == NULL) {
        printf("File non trovato.\n");
        return testa;
    }

    printf("Caricamento in corso...\n");
    while (1) {
        nuovo = malloc(sizeof(TipoNodo));
        if (nuovo == NULL) break;

        letto = fscanf(f, "%d %s %f %f %f",
                       &nuovo->info.id, nuovo->info.nome,
                       &nuovo->info.min, &nuovo->info.max,
                       &nuovo->info.corrente);
        
        if (letto != 5) {
            free(nuovo);
            break;
        }
        
        nuovo->next = testa;
        testa = nuovo;
    }

    fclose(f);
    printf("Caricamento terminato.\n");
    return testa;
}