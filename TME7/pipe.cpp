#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <algorithm>  

int main (int argc, char* argv []) {
    int fd[2];

    if(pipe(fd) ==-1){
        std::cout << "error pipe" << std::endl;
    }

    char ** parametres1= new char*[argc+1];
    char ** parametres2= new char*[argc+1];
    int i = 1;//ignore le premier
    int j = 0;

    std::cout << "Analyse commande 1" << std::endl;


    //recupere la commande 1 et ces argument
    while(*argv[i] != '|'){
        parametres1[j] = argv[i];
        std::cout << parametres1[j] << std::endl;
        i++;
        j++;
    }
    parametres1[j] = nullptr;

    i++;
    j = 0;

    std::cout << "Analyse commande 2" << std::endl;

    //recupere la commande 2 et ses argument
    while(argc != i ){
        parametres2[j] = argv[i];
        std::cout << parametres2[j] << std::endl;
        j++;
        i++;
    }
    parametres2[j] = nullptr;

	pid_t pid;
    if((pid= fork()) ==-1){//creation d'un process fils
        std::cout << "error fork" << std::endl;
    }

    //fils
	if (pid==0) {
        //copie du descripteur, le tube en ecriture passera tout ce qui passera en stdout
        dup2(fd[1], STDOUT_FILENO);

        //fermeture de l'ancient descripteur
        close(fd[0]);
        close(fd[1]);
        
        //execute la premiere commande, qui va ecrire dans le stdout, donc dans le tube
        if(execv(parametres1[0], parametres1) == -1){
            std::cout << "error execv" << std::endl;
        }

        delete[] parametres1;
        delete[] parametres2;
		return 0;
	}else{
        //copie du descripteur, le tube en lecture récupère tout ce qui passera en stdin
        dup2(fd[0], STDIN_FILENO);

        //fermeture de l'ancient descripteur
        close(fd[0]);
        close(fd[1]);

        //execute la seconde commande, qui va utiliser le stdin, donc dans le tube
        if(execv(parametres2[0], parametres2) == -1){
            std::cout << "error execv" << std::endl;
        }
    }

	wait(0);

    delete[] parametres1;
    delete[] parametres2;
	return 0;
}