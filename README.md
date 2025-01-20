README: Simulerat Banksystem

Projektbeskrivning :

Detta projekt simulerar ett grundläggande banksystem som hanterar flera kunder som utför transaktioner samtidigt. Projektet använder multithreading för att simulera samtidiga kunder och synkroniseringstekniker för att säkerställa integriteten hos delade resurser, såsom kontosaldon.

Funktionalitet :

Insättning: Kunder kan sätta in pengar på sina konton.

Uttag: Kunder kan ta ut pengar, förutsatt att det finns tillräckligt med saldo.

Saldokontroll: Kunder kan kontrollera saldot på sina konton.

Tekniker och Koncept :

Multithreading: Används för att simulera samtidiga kunder som utför transaktioner.

Synkronisering: Tekniker som mutex används för att säkerställa att inga datakonflikter eller inkonsekvenser uppstår vid samtidiga transaktioner.

Trådsäkerhet: Designen säkerställer att varje transaktion behandlas korrekt även under hög belastning.

Installation

Klona detta repository:

git clone <repository-url>

Navigera till projektmappen:

cd <projektmapp>

Kompilera koden (t.ex. med g++):

g++ -pthread Client.cpp Bank.cpp BankAccount.cpp main.cpp -o bank_system

Användning

Kör det kompilerade programmet:

./bank_system

Programmet simulerar flera kunder som gör transaktioner och visar resultaten i terminalen.

Struktur

main.cpp: Huvudfilen som innehåller programmets logik.

BankAccount.h och BankAccount.cpp: Klasser för att hantera bankkonton.

Client.h och Client.cpp: Klasser för att representera kunder och deras handlingar.

Bank.h och Bank.cpp: Hanterar transaktioner och synkronisering.

Globals.h och Globals.cpp 

Förbättringar och Vidareutveckling

Funktionalitet: Lägg till funktioner som kontohistorik och överföringar mellan konton.

Prestanda: Optimera synkroniseringsmekanismer för bättre prestanda vid högre belastning.

Testning: Implementera enhetstester för att säkerställa korrekt funktionalitet.

Författare

John Collinder, Erik Dahl, Viktor Kvick, David Reyes.
