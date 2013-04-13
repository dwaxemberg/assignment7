struct supplies {
  int tobacco;
  int matches;
  int paper;
};

#define TOBACCO 1
#define MATCHES 2
#define PAPER 3

program smoker_problem {
  version homework_version {
    int get_me_my_supply(struct supplies) = 1;
    void stop_service(struct supplies) = 2;
  } = 1;
} = 87654;

