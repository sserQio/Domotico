#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <regex>
#include "../include/m.h"
#include "../include/cp.h"
#include "../include/system.h"

void help(){
    // Lista dei comandi stampati a distanza temporale per facilitare la lettura
    // e rendere un po' migliore l'esperienza d'uso
    std::cout << "I comandi disponibili sono i seguenti:" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "set ${DEVICENAME} {on}" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "set ${DEVICENAME} {off}" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "set ${DEVICENAME} ${START} [${STOP}]" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "rm ${DEVICENAME}" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "show" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "show ${DEVICENAME}" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "set time ${TIME}" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "reset time" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "reset timers" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "reset all" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

std::vector<std::string> readCommand(std::string in){
    // Pattern per estrapolare i diversi argument dalla riga di comando
    // std::regex pattern(
    // R"((set|rm|show|set time|reset time|reset timers|reset all)\s+)"
    // R"(\{(Impianto fotovoltaico|Pompa di calore \+ termostato|Scaldabagno|Frigorifero|Lavatrice|Lavastoviglie|Tapparelle elettriche|Forno a microonde|Asciugatrice|Televisore)\}\s*)"
    // R"((\{(on|off|([01]\d|2[0-3]):[0-5]\d)\})?\s*)"
    // R"((\{([01]\d|2[0-3]):[0-5]\d\})?)"
    // );

    std::regex pattern(
        R"((set|rm|show|set time|reset time|reset timers|reset all))"   // Comando principale
        R"((?:\s+\{(Impianto fotovoltaico|Pompa di calore \+ termostato|Scaldabagno|Frigorifero|Lavatrice|Lavastoviglie|Tapparelle elettriche|Forno a microonde|Asciugatrice|Televisore)\})?)" // Secondo argomento opzionale
        R"((\s+\{(on|off|(?:[01]\d|2[0-3]):[0-5]\d)\})?)"            // Terzo argomento opzionale
        R"((?:\s+\{((?:[01]\d|2[0-3]):[0-5]\d)\})?)"                  // Quarto argomento opzionale
    );

    std::smatch match;
    std::vector<std::string> result;




    std::string trimmedInput = std::regex_replace(in, std::regex(R"(^\s+|\s+$)"), "");

    // Match dell'input con il pattern
    if (std::regex_match(trimmedInput, match, pattern)) { // prima era input
        // match[1]: Prima parola (comando principale)
        result.push_back(match[1].str());

        // match[2]: Nome del dispositivo
        result.push_back(match[2].str());

        // match[4]: Terzo argomento (on/off/orario), se esiste
        if (match[4].matched) {
            result.push_back(match[4].str());
        }

        // match[5]: Quarto argomento (orario), se esiste
        if (match[5].matched) {
            result.push_back(match[5].str());
        }
    }
    return result;
}

int main(){
    // Creiamo un sistema casa che ospiterà i dispositivi
    System house{};
    std::cout << "Il sistema di gestione dei dispositivi elettrici è stato creato" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    help();

    while(true){
        bool start = true;
        while(true){
            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "Vuoi procedere con la gestione della casa? [y]es" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Vuoi uscire dal programma? 'exit'" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Vuoi rileggere la lista dei comandi? 'help'" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "---------------------------------------------------------------" << std::endl;

            std::string input;
            std::cin >> input;
            if (input == "y" || input == "Y") break;
            else if (input == "help" || input == "Help" || input == "HELP") help(); // FUNZIONE HELP
            else if (input == "exit" || input == "Exit" || input == "EXIT"){
                std::cout << "Esco dall'esecuzione del programma" << std::endl;
                start = false;
                break;
            } else std::cout << "Il comando inserito non è valido, riprovare" << std::endl;
        }
        if (!start) break; // Non esegue più il ciclo di riga 35
        else {
            std::string input;
            // Dichiariamo il vettore di stringhe per prendere il comando dell'utente
            std::vector<std::string> command;
            std::cout << "Inserisci il comando: ";
           
            
            // Puliamo il buffer di std::cin
            std::cin.ignore();
            // Leggiamo l'intera riga in input
            std::getline(std::cin, input);
            // Il vettore command riceve il comando già suddiviso
            command = readCommand(input);
            
            
            Device* d = nullptr;
            // CONTROLLARE CHE ORARI INSERITI SIANO VALIDI
            std::cout<<"Prima dello switch la grandezza del vettore è: " << command.size() << std::endl;
                switch(command.size()){
                /*case 1: {
                    std::cout << "CASO 1" << std::endl;
                    if (command[0] == "show") house.show();
                    else if (command[0] == "reset time") {
                        house.reset_time();
                        std::cout << "Il sistema è stato riportato alle condizioni iniziali" << std::endl;
                    } 
                    else if (command[0] == "reset timers") house.reset_timers();
                    else if (command[0] == "reset all") house.reset_all();
                    break;
                }*/
                case 2: {
                    std::cout << "CASO 2" << std::endl;
                    for (int i = 0; i < command.size(); i++){
                        std::cout << command[i] << ",";
                    }
                    std::cout << std::endl;
                    //EX CASO 1
                    if (command[0] == "show" && command[1]==" ") house.show();
                    else if (command[0] == "reset time") {
                        house.reset_time();
                        std::cout << "È stata chiamata reset time" << std::endl;
                        std::cout << "Il sistema è stato riportato alle condizioni iniziali" << std::endl;
                    } 
                    else if (command[0] == "reset timers") {
                        house.reset_timers();
                        std::cout << "È stata chiamata reset timers" << std::endl;
                    }
                    else if (command[0] == "reset all") {
                        house.reset_all();
                        std::cout << "È stata chiamata reset all" << std::endl;
                    }
                    //INIZIO VERI CASI 2
                    if (command[0] == "rm"){
                        d = house.search_device(command[1]);
                        d -> rm();
                        std::cout << "Il timer del dispositivo " << d -> get_name() << " è stato rimosso, quindi ora è: " << d -> get_autoStart() << std::endl;
                    } else if (command[0] == "show"){
                        d = house.search_device(command[1]);
                        d -> show();
                    } else if (command[0] == "set time") house.set_time(command[1]);
                    break;
                }
                case 3: {
                    std::cout << "CASO 3" << std::endl;
                    if (command[2] == "on" || command[2] == "off"){
                        d = house.search_device(command[1]);
                        d -> set(command[2]);
                        std::cout << "Il dispositivo " << d -> get_name() << " si è ";
                        if (command[2] == "on") std::cout << "acceso" << std::endl;
                        else std::cout << "spento" << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                        break;
                    } else {
                        d = house.search_device(command[1]);
                        M* m_ptr = dynamic_cast<M*>(d);
                        if (m_ptr){
                            std::cout << "Errore! Non puoi assegnare solo un orario per un dispositivo di tipo M" << std::endl;
                            break;
                        }
                        d -> set(command[2], "");
                        std::cout << "Il dispositivo " << d -> get_name() << " si accende alle: " << d -> get_autoStart() << std::endl;
                        break;
                    }
                }  
                case 4: {
                    std::cout << "CASO 4" << std::endl;
                    for (int i = 0; i < command.size(); i++){
                        std::cout << command[i] << ",";
                    }
                    std::cout << std::endl;
                    d = house.search_device(command[1]);
                    CP* cp_ptr = dynamic_cast<CP*>(d);
                    if (cp_ptr){
                        std::cout << "Errore! Non puoi assegnare un orario di spegnimento per un dispositivo di tipo CP" << std::endl;
                        break;
                    }
                    M* m_ptr = dynamic_cast<M*>(d);
                    m_ptr -> set(command[2], command[3]);
                    std::cout << "Il dispositivo " << m_ptr -> get_name() << "si accende alle: " << m_ptr -> get_autoStart() << " e si spegne alle: " << m_ptr -> get_stop() << std::endl;
                    break;
                }
                default: {
                    std::cout << "Comando sbagliato, riprova:" << std::endl;
                    break;
                }
            } 
        }
    }
    return 0;
}