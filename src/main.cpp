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
    std::regex pattern(
    R"((set|rm|show|set time|reset time|reset timers|reset all)\s+)"
    R"(\{(Impianto fotovoltaico|Pompa di calore \+ termostato|Scaldabagno|Frigorifero|Lavatrice|Lavastoviglie|Tapparelle elettriche|Forno a microonde|Asciugatrice|Televisore)\}\s*)"
    R"((\{(on|off|([01]\d|2[0-3]):[0-5]\d)\})?\s*)"
    R"((\{([01]\d|2[0-3]):[0-5]\d\})?)"
    );

    std::smatch match;
    std::vector<std::string> result;

    // Match dell'input con il pattern
    if (std::regex_match(in, match, pattern)) {
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "---------------------------------------------------------------" << std::endl;
    help();

    while(true){
        bool start = true;
        while(true){
            std::cout << "Vuoi procedere con la gestione della casa? [ENTER]" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Vuoi uscire dal programma? 'exit'" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Vuoi rileggere la lista dei comandi? 'help'" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            std::string input;
            std::cin >> input;
            if (input == "\n") break;
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
           
            do {
                // Puliamo il buffer di std::cin
                std::cin.ignore();
                // Leggiamo l'intera riga in input
                std::getline(std::cin, input);
                // Il vettore command riceve il comando già suddiviso
                command = readCommand(input);
                if (command.empty()){
                    std::cout<<command.size()<< std::endl;
                    std::cout << "Hai sbagliato a scrivere il comando, riprova:" << std::endl;
                    std::cin.ignore();
                }
            } while (command.empty());
            
            Device* d = nullptr;
            // CONTROLLARE CHE ORARI INSERITI SIANO VALIDI
            switch(command.size()){
                case 1:
                    if (command[0] == "show") house.show();
                    else if (command[0] == "reset time") house.reset_time();
                    else if (command[0] == "reset timers") house.reset_timers();
                    else if (command[0] == "reset all") house.reset_all();
                    break;
                case 2:
                    if (command[0] == "rm"){
                        d = house.search_device(command[1]);
                        d -> rm();
                    } else if (command[0] == "show"){
                        d = house.search_device(command[1]);
                        d -> show();
                    } else if (command[0] == "set time") house.set_time(command[1]);
                    break;
                case 3:
                    if (command[2] == "on" || command[2] == "off"){
                        d = house.search_device(command[1]);
                        d -> set(command[2]);
                        std::cout << "Il dispositivo " << d -> get_name() << "si è ";
                        if (command[2] == "on") std::cout << "acceso" << std::endl;
                        else std::cout << "spento" << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                        break;
                    } else {
                        d = house.search_device(command[1]);
                        d -> set(command[2], "");
                        std::cout << "Il dispositivo " << d -> get_name();
                        break;
                    }
                case 4:
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
                default:
                    std::cout << "Comando sbagliato, riprova:" << std::endl;
                    break;
            } 
        }
    }
    return 0;
}