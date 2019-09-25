#include <iostream>
#include <unistd.h>
#include <thread>
#include <pthread.h>
#include <math.h>

// g++ -std=c++11 main.cpp -pthread -o foo


void calculateSum(){
    long double answer = 0;
    for(int i = 1; i <= 46300; i++){
        for(int j = 1; j <= i; j++){
            answer += sqrt(i*j);
        }
    }
    std::cout << "Answer: " << answer << "\n";
}

void spawnForks(int n){

    if(n <= 0){
        calculateSum();
        exit(0);
    }
    else{
        if(fork()==0){
            if(n){
                std::cout << getpid() << "\n";
                spawnForks(n-1);
                calculateSum();
                exit(0);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    std::string input;
    int i;

    while(true){
        std::cout << "Enter Command: ";
        std::cin >> input >> i;
        std::cout << "\n";

        if(input == "-e"){
            exit(0);
        }

        if(input == "-i"){
            system("echo Number Of Processores:");
            system("grep -c ^processor /proc/cpuinfo");

            system("echo Hostename:");
            system("hostname");

            system("echo Hardware Platform:");
            system("uname");

            system("cat /proc/meminfo |grep MemTotal");
        }

        if(input == "-f" && i > 0){
            spawnForks(i);
        }

        if(input == "-t" && i > 0 && i < 100){
            
            std::thread threads[5];
            for(int j = 0; j < i; j++){
                threads[j] = std::thread(calculateSum);
            }

            for(int j = 0; j < i; j++){
                threads[j].join();
            }
        }

        std::cout << "\n";
    }

    return 0;
}
