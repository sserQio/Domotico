Progetto di Barison, Castellini, Petenazzo

* Utilizzo
* * Primo Utilizzo e continuazione dell'esecuzione
Al momento dell'esecuzione viene stampata la lista dei comandi. Digitare:
- "y" per proseguire e poter inserire un comando di gestione del sistema. Questo sarà necessario per ogni iterazione per poter continuare.
- "h" per ricevere in stampa una lista dei comandi di gestione disponibili. 
- "q" per uscire dall'esecuzione.

* * Comandi di Gestione
I comandi di gestione devono essere digitati esattamente come quelli nella lista e le parentesi graffe devono essere incluse. Comunque, in caso venga
inserito un comando non rilevato verrà stampato un messaggio di errore e verrà chiesto di riprovare.
I nomi dei dispositivi sono stati presi dalla tabella nel PDF della consegna e sono stati trascritti esattamente. Inoltre quando è richiesto di inserire
un nome di un dispositivo è necessario digitarlo esattamente come nel PDF, maiuscole incluse (case sensitive).
Per quanto riguarda gli orari è necessario inserirli in formato {hh:mm}.

* * * Funzioni
Abbiamo rinominato la funzione "show" in "show all" a causa di un conflitto nell'input del comando. La funzione "show {DEVICENAME}" tuttavia è
inalterata. Questa modifica si può anche notare chiedendo attraverso input la lista dei comandi.

* Spiegazione della nostra interpretazione
* * Tempo - Orari
Il nostro mondo inizia alle ore 00:01 e finisce alle 23:59.
In particolare se viene impostato qualcosa alle ore 00:00 non viene mostrato a schermo.
L'unico modo per andare avanti col tempo è attraverso il comando set time {hh:mm}.
Quindi se impostando un timer e se non si esegue il comando set time {hh:mm} ma si imposta un secondo timer, il primo viene sovrascritto in
quanto il tempo non è andato avanti.
Con il comando set time {hh:mm} non si può tornare indietro nel tempo e provando viene stampato un messaggio di errore.
La nostra interpretazione riguardo l'accensione di un dispostivo è che quando lo si accende è come se lo si stesse collegando alla corrente.
Mentre quando il timer inizia, esso inizia a lavorare.
Quando un dispositivo finisce un ciclo esso viene automaticamente spento e quindi se si vuole impostare un altro timer, il dispositivo
deve essere nuovamente acceso. Ciò implica che un dispositivo se non è acceso (attraverso il comando set {DEVICENAME} {on}), non gli si
può impostare un timer. Per esplicitare il funzionamento di questa meccanica: quando un dispositivo viene spento, automaticamente il suo
timer si azzera.

* Partizione dei Lavori
Barison Alessia (2103043): stime.cpp, device.h
Castellini Camilla (2103044): system.h, device.cpp*
Petenazzo Sergio (2066693): m.h, cp.h, stime.h, m.cpp, cp.cpp, CMakeLists.txt

Barison, Castellini, Petenazzo: system.cpp, main.cpp + *update_total_consumption() contenuta in device.cpp -> in quanto riscontrate delle problematiche
l'intero gruppo ha revisionato e sistemato insieme i diversi file sopracitati quindi tutti e tre assumiamo la responsabilità di qualsiasi
malfunzionamento.