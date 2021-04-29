
// --------------------------------------------------------------------------------------

// Autor:
    // Norman Steinhoff

// Jahr
    // 2021

// --------------------------------------------------------------------------------------

// Verwendete Abkürzungen:
    // Vor. == Voraussetzung
    // Eff. == Effekt
    // Erg. == Ergebnis
    // Anm. == Anmerkung

// --------------------------------------------------------------------------------------

// neueren POSIX_Standard festlegen
// Wird für { sigaction() } und { nanosleep() } benötigt.
#define _POSIX_C_SOURCE 199309L

// Standard_Header einbinden
#include <signal.h>
#include <stdio.h>

// Konstanten
#define OK 0
#define ERROR 1

// Vor.:
// -
// Eff.:
// *    Man kann einem Profikiller bei der Arbeit zusehen :)
// Erg.:
// -
// Anm.:
// * Mit { ./kill -9 pid1 pid 2 } kann man die Prozesse mit den Prozess_Nummern { pid1 } und { pid2 } beenden.
int main(int argc, char *argv[]) {

    //Ergebnis initialisieren
    int result = OK;

    // Variablen deklarieren bzw initialisieren
    int signal; // Signal_Nummer
    int pid; // Prozess_Nummer
    int start_index = 2; // Wird in Schleife weiter unten verwendet.
    int stop_index = argc; // Wird in Schleife weiter unten verwendet.
    int signal_count; // Anzahl gescannter Signal_Nummern
    int pid_count; // Anzahl gescannter PID's
    int kill_result = -1; // Ergebnis Kill_Versuchs

    // Signal_Nummer ermitteln
    signal_count = sscanf(argv[1], "-%d", &signal);

    // Prüfen ob Signal_Nummer vorhanden
    if (0 == signal_count) { // nicht vorhanden

        // Da keine Signal_Nummer vorhanden war, wird diese implizit gesetzt.
        signal = SIGINT;

        // Da keine Signal_Nummer vorhanden war, muss bereits das erste Argument eine PID sein.
        // Daher wird der Start_Index zurück gesetzt.
        start_index = 1;
    }

    for (int a = start_index; a < stop_index; ++a) {

        // Prozess_Nummer lesen
        pid_count = sscanf(argv[a], "%d", &pid);

        // Prüfen ob Prozess_Nummer vorhanden
        if ( 1 == pid_count ) {

            // Signal an Prozess senden
            kill_result = kill(pid, signal);
        }
        else {

            // Fehlermeldung senden
            printf("PID konnte nicht ermittelt werden.\n");

            // Fehler registrieren
            result = ERROR;
        }

        if (-1 == kill_result) {

            // Fehlermeldung senden
            printf("Das Signal %d konnte nicht an den Prozess %d gesendet werden.\n", signal, pid);

            // Fehler registrieren
            result = ERROR;
        }
        
    }
    
    // Ergebnis liefern
    return result;
}
