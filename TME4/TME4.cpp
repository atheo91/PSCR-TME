//Question 2 : Les thread marche sans ce marche sur les pied, mais je pense qu'il peuvent se toucher par malchance.


#include <iostream>
#include <chrono>
#include <thread>
#include "Banque.h"
#include "Compte.h"


//Effectue une transation, demande une banque, le nombre de compte dans cette banque, et l'argent avec laquel ils commence
void traitment_transation(Banque &B, const int num_compte, const int start_money) {
    int i, j, m, s_time;

    for (int C = 0; C < 1000; ++C) {

        i = rand() % num_compte;
        j = rand() % num_compte;
        m = rand() % start_money + 1;
        s_time = rand() % 21;

        B.transfert(i,j,m);

        std::this_thread::sleep_for(std::chrono::milliseconds(s_time));
    }
}



int main()
{
    int N = 5; //Nombre de thread
    int num_compte = 10; //Nombre de compte
    int start_money = 101;


    Banque B(num_compte, start_money); 

    std::vector<std::thread> t; 
    for (int i = 0; i < N; ++i) {
        t.emplace_back(traitment_transation, std::ref(B), num_compte, start_money);
    }
    for (auto& d : t) {
        d.join();
    }

    for (int i = 0; i < num_compte; ++i){
        std::cout << "[" << i << "]: " << B.solde_compte(i) << std::endl;
    }
}
