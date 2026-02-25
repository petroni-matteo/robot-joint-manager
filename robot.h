#ifndef ROBOT_H
#define ROBOT_H

/* Le costanti di sistema */
#define LEN_STR 30

/* --- DEFINIZIONE STRUTTURE DATI --- */
typedef struct {
    int id;                 
    char nome[LEN_STR];     
    float min;              
    float max;              
    float corrente;         
} TipoMotore;

struct StructNodo {
    TipoMotore info;
    struct StructNodo *next;
};

typedef struct StructNodo TipoNodo;
typedef TipoNodo * TipoLista;

/* --- PROTOTIPI DELLE FUNZIONI --- */
/* Input sicuro */
void leggiIntero(int *n);
void leggiFloat(float *f);
void leggiStringa(char *s);

/* Gestione Lista */
TipoLista aggiungiMotore(TipoLista testa);
void stampaLista(TipoLista testa);
void stampaQuelMotore(TipoLista testa, int id);
TipoLista eliminaMotore(TipoLista testa, int id);
void modificaPosizione(TipoLista testa, int id, float nuovaPos);
TipoLista cercaNodo(TipoLista testa, int id);

/* Gestione File */
void salvaSuFile(TipoLista testa, char *nmf);
TipoLista caricaDaFile(TipoLista testa, char *nmf);

#endif