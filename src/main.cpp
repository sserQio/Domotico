// Tutto il gruppo

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <regex>
#include "../include/m.h"
#include "../include/cp.h"
#include "../include/system.h"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

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
    std::cout << "show all" << std::endl;
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
    
    std::regex pattern(
        R"((set|rm|show|set time|reset time|reset timers|reset all|show all))"
        R"((?:\s+\{(Impianto fotovoltaico|Pompa di calore \+ termostato|Scaldabagno|Frigorifero|Lavatrice|Lavastoviglie|Tapparelle elettriche|Forno a microonde|Asciugatrice|Televisore)\})?)"
        R"((\s+\{(on|off|(?:[01]\d|2[0-3]):[0-5]\d)\})?)"
        R"((?:\s+\{((?:[01]\d|2[0-3]):[0-5]\d)\})?)"
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
    // Creiamo un sistema house che ospiterà i dispositivi
    System house{};
    double max_limit = house.get_system_limit();
    std::cout << BOLD << "Il sistema di gestione dei dispositivi elettrici è stato creato" << RESET << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    help();

    while(true){
        bool start = true;
        while(true){
            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "Vuoi procedere con la gestione dei dispositivi?" BOLD << " [y]es" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Vuoi uscire dal programma?" BOLD << " [q]uit" RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Vuoi rileggere la lista dei comandi?" << BOLD << " [h]elp" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "---------------------------------------------------------------" << std::endl;

            std::string input;
            std::cin >> input;
            if (input == "y" || input == "Y") break;
            else if (input == "h" || input == "H") help(); // FUNZIONE HELP
            else if (input == "q" || input == "Q"){
                std::cout << "Esco dall'esecuzione del programma..." << std::endl;
                start = false;
                break;
            } else std::cout << RED << "Il comando inserito non è valido, riprovare" << RESET << std::endl;
        }
        if (!start) break;
        else {
            std::string input;
            // Dichiariamo il vettore di stringhe per prendere il comando dell'utente
            std::vector<std::string> command;
            std::cout << "Inserire il comando: ";
           
            // Puliamo il buffer di std::cin
            std::cin.ignore();
            // Leggiamo l'intera riga in input
            std::getline(std::cin, input);
            // Il vettore command riceve il comando già suddiviso
            command = readCommand(input);
            
            Device* d = nullptr;
                switch(command.size()){
                case 2: {
                    std::cout << std::endl;
                    if (command[0] == "show all") {
                        std::cout << "[" << house.current_time << "] " << "L'orario corrente è: [" << house.current_time << "]" << std::endl;
                        house.show_all();
                    }
                    else if (command[0] == "reset time") {
                        std::cout << "[" << house.current_time << "] " << "L'orario corrente è: [" << house.current_time << "]" << std::endl;
                        house.reset_time();
                    } 
                    else if (command[0] == "reset timers") {
                        std::cout << "[" << house.current_time << "] " << "L'orario corrente è: [" << house.current_time << "]" << std::endl;
                        house.reset_timers();
                    }
                    else if (command[0] == "reset all") {
                        std::cout << "[" << house.current_time << "] " << "L'orario corrente è: [" << house.current_time << "]" << std::endl;
                        house.reset_all();
                    }
                    if (command[0] == "rm"){
                        std::cout << "[" << house.current_time << "] " << "L'orario corrente è: [" << house.current_time << "]" << std::endl;
                        d = house.search_device(command[1]);
                        d -> rm();
                        std::cout << YELLOW << "[" << house.current_time << "] " << "Rimosso il timer dal dispositivo " << d -> get_name() << RESET << std::endl;
                    } else if (command[0] == "show"){
                        std::cout << "[" << house.current_time << "] " << "L'orario corrente è: [" << house.current_time << "]" << std::endl;
                        d = house.search_device(command[1]);
                        d -> show();
                    }
                    break;
                }
                case 3: {
                    if (command[2] == "on" || command[2] == "off"){
                        std::cout << "[" << house.current_time << "] " << "L'orario corrente è: [" << house.current_time << "]" << std::endl;
                        d = house.search_device(command[1]);
                        if (command[2] == "off"){
                            if (d -> get_is_on() == false) {
                                std::cout << YELLOW << "Il dispositivo era già spento" << RESET << std::endl;
                                break;
                            }
                            CP* cp_ptr = dynamic_cast<CP*>(d);
                            Stime app = cp_ptr -> get_autoStart() + cp_ptr -> get_duration();
                            if (cp_ptr && app < house.current_time){
                                cp_ptr -> set_total_consumption(house.current_time); 
                            } else {
                                d -> update_total_consumption(house.current_time);
                                // Condizione per evitare che venga contata più volte la produzione dell'impianto fotovoltaico 
                                if (d -> get_name() == "Impianto fotovoltaico"){
                                    // app riceve la durata della produzione dell'Impianto fotovoltaico
                                    app = house.current_time - d -> get_autoStart();
                                    // Aggiornamento di max_limit in seguito alla produzione del Pannello fotovoltaico
                                    max_limit += (d -> get_consumption() * (app.get_hours() + ((double)app.get_minutes()/60)));
                                }
                            }
                           
                        }
                        d -> set(command[2]);
                        std::cout << "[" << house.current_time << "] Il dispositivo " << d -> get_name() << " si è ";
                        if (command[2] == "on") std::cout << GREEN << "acceso" << RESET << std::endl;
                        else std::cout << RED << "spento" << RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                        break;
                    } 
                    if (command[0] == "set time") {
                        std::cout << "[" << house.current_time << "] " << "L'orario corrente è: [" << house.current_time << "]" << std::endl;
                        max_limit += house.set_time(command[2]);
                        break;
                    } else {
                        d = house.search_device(command[1]);
                        M* m_ptr = dynamic_cast<M*>(d);
                        if (m_ptr){
                            std::cout << RED << "Errore! Non puoi assegnare solo un orario per un dispositivo di tipo M" << RESET << std::endl;
                            break;
                        }
                        if (d -> get_is_on() == true){
                            d -> set(command[2], "");
                            std::cout << "[" << house.current_time << "] Impostato un timer per il dispositivo " << d -> get_name() << " dalle " << GREEN << d -> get_autoStart() << RESET << std::endl;
                        } else {
                            std::cout << BLUE << "Il dispositivo è spento, prima è necessario accenderlo" << RESET << std::endl;
                        }
                        break;
                    }
                }  
                case 4: {
                    std::cout << "[" << house.current_time << "] " << "L'orario corrente è: [" << house.current_time << "]" << std::endl;
                    std::cout << std::endl;
                    d = house.search_device(command[1]);
                    CP* cp_ptr = dynamic_cast<CP*>(d);
                    if (cp_ptr){
                        std::cout << RED << "Errore: non puoi assegnare un orario di spegnimento per un dispositivo di tipo CP" << RESET << std::endl;
                        break;
                    }
                    M* m_ptr = dynamic_cast<M*>(d);
                    if (m_ptr -> get_is_on() == true){
                        Stime first = command[2];
                        Stime second = command[3];
                        if (second < first) {
                            std::cout << RED << "Errore: gli orari inseriti non sono corretti" << RESET << std::endl;
                        }
                        else {
                            m_ptr -> set(command[2], command[3]);
                            std::cout << "[" << house.current_time << "] " << "Impostato un timer per il dispositivo " << m_ptr -> get_name() << " dalle " << GREEN << m_ptr -> get_autoStart() << RESET << " alle: " << RED << m_ptr -> get_stop() << RESET << std::endl;
                        }
                    } else {
                        std::cout << BLUE << "Il dispositivo è spento, prima è necessario accenderlo" << RESET << std::endl;
                    }
                    break;
                }
                default: {
                    std::cout << RED << "Il comando inserito non è valido, riprovare" << RESET << std::endl;
                    break;
                }
            } 
        }
    }
    return 0;
}