#include <rpc/rpc.h>
#include "stdlib.h"
#include <errno.h>
#include "stdio.h"
#include "smoking.h"
#include <unistd.h>

int smoke(struct supplies*, CLIENT*);

int main(int argc, char** argv) {
    CLIENT *cl;
    if (argc != 5) {
        printf("Usage: ./smoker1 HOSTNAME t p m\n");
        return 1;
    }

    char* server_hostname = argv[1];
    cl = clnt_create(server_hostname, smoker_problem, homework_version, "udp");
    if (cl == NULL) {
       clnt_pcreateerror("Error creating smoker1 client");
       exit(EXIT_FAILURE);
    }

    struct supplies sup = {atoi(argv[2]), atoi(argv[3]), atoi(argv[4])};

    if (sup.tobacco == -1) {
        stop_service_1(&sup, cl);
        printf("Terminated server\n");
        return 0;
    }
    while(smoke(&sup, cl)){
    }
    exit(EXIT_SUCCESS);
}
int smoke(struct supplies* sup, CLIENT* cl) {
  if (sup->tobacco < 1) {
    struct supplies needed = {1,0,0};
    sup->tobacco += *get_me_my_supply_1(&needed, cl);
  }
  if (sup->matches < 1) {
    struct supplies needed = {0,0,1};
    sup->matches += *get_me_my_supply_1(&needed, cl);
  }
  if (sup->paper < 1) {
    struct supplies needed = {0,1,0};
    sup->paper += *get_me_my_supply_1(&needed, cl);
  }
  if (sup->tobacco > 0 && sup->matches > 0 && sup->paper > 0) {
        sup->tobacco--;
        sup->matches--;
        sup->paper--;
        printf("Smoker1: Smoking");
        sleep(1);
        return 1;
  }
  else {
    printf("Smoker1: Sadly, no more tobaccos, and I will go kill myself!");
    return 0;
  }
}
