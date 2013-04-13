#include "stdio.h"
#include <errno.h>
#include <rpc/rpc.h>
#include "smoking.h"

struct supplies sup = {4, 3, 5};

int *get_me_my_supply_1_svc(struct supplies* needed,  struct svc_req *rqstp) {
    static int response;
    char* txt;
    if (needed->tobacco > 0) {
      txt = "TOBACCO";
      if (sup.tobacco > 0) {
        sup.tobacco--;
        response = 1;
      }
      else {
        response = 0;
      }
    }
    else if (needed->paper > 0) {
      txt = "PAPER";
      if (sup.paper > 0) {
        sup.paper--;
        response = 1;
      }
      else {
        response = 0;
      }
    }
    else if (needed->matches > 0) {
      txt = "MATCHES";
      if (sup.matches > 0) {
        sup.matches--;
        response = 1;
      }
      else {
        response = 0;
      }
    }
    printf("The server received request for %s\n", txt);
    fflush(NULL);
    return &response;
}

void *stop_service_1_svc(struct supplies* needed, struct svc_req *rqstp) {
    printf("Request for termination received.");
    fflush(NULL);
    exit(0);
}
