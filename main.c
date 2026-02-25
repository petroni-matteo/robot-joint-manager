#include <stdio.h>
#include "robot.h" /* Importiamo la nostra interfaccia */

int main() {
    TipoLista listaRobot = NULL; 
    int scelta;
    int idInput;
    float posInput;
    char nomeFileInput[LEN_STR];

    do {
        printf("\n--- GESTIONE ROBOT (Pannello Operatore) ---\n");
        printf("1. Stampa tutti i motori\n");
        printf("2. Cerca motore per ID\n");
        printf("3. Aggiungi motore\n");
        printf("4. Elimina motore\n");
        printf("5. Modifica posizione (Jog)\n");
        printf("6. Salva su file\n");
        printf("7. Carica da file\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        
        leggiIntero(&scelta);

        switch (scelta) {
            case 1:
                stampaLista(listaRobot);
                break;
            case 2:
                printf("Inserisci ID da cercare: ");
                leggiIntero(&idInput);
                stampaQuelMotore(listaRobot, idInput);
                break;
            case 3:
                listaRobot = aggiungiMotore(listaRobot); 
                break;
            case 4:
                printf("Inserisci ID da eliminare: ");
                leggiIntero(&idInput);
                listaRobot = eliminaMotore(listaRobot, idInput);
                break;
            case 5:
                printf("Inserisci ID motore: ");
                leggiIntero(&idInput);
                printf("Nuova posizione: ");
                leggiFloat(&posInput);
                modificaPosizione(listaRobot, idInput, posInput);
                break;
            case 6:
                printf("Nome file per il salvataggio: ");
                leggiStringa(nomeFileInput);
                salvaSuFile(listaRobot, nomeFileInput);
                break;
            case 7:
                printf("Nome file da caricare: ");
                leggiStringa(nomeFileInput);
                listaRobot = caricaDaFile(listaRobot, nomeFileInput);
                break;
            case 0:
                printf("Arresto del sistema.\n");
                break;
            default:
                printf("Comando non riconosciuto.\n");
        }
    } while (scelta != 0);

    return 0;
}