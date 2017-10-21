#include <iostream>
#include <cstdio>
#include <string>


#define no_argument            0
#define required_argument      1
#define optional_argument      2


struct option {
  const char *name;
  int has_arg;
  int *flag;
  int val;
};


const struct option info[] = {
  {"--help",no_argument,NULL,'h'},
  {"--name",required_argument,NULL,'s'},
  {"--attempts",optional_argument,NULL,'f'},
  {"--score",optional_argument,NULL,'f'},
  {"--next_round",required_argument,NULL,'f'},
  {NULL,0,NULL,0}
};


struct player{
  std::string name;
  int attempts = -1;
  double score = -1;
  bool next_round = false;
};


int getopt_long(int argc, char **argv, const struct option *longopts,
               int& optarg, struct player p){
  
  std::string action(argv[optarg++]);
  size_t index = action.find('=');
  std::string value;
  bool flag = 0;
  if (index != std::string::npos){
    value = action.substr(index+1, action.length());
  }
  if ((optarg!=argc) and (argv[optarg][0] != '-')){
    value = argv[optarg++];
  }
  else{
    flag = 1;
  }
  
  if (action == "--help"){
    const char *usage =
    R"(where PARAMS are from list:
    --help
    
    --name <name_of_player>
    
    --score <his_score>
    
    --attempts <count=-1>
    
    --next_round <win=0>
    
)";
    
    std::cout <<("This is help. Try --help.\n");
    std::cout << "Usage: " <<  "[PARAMS]" << std::endl;
    std::cout << usage;
    
  }
  else if (action == "--name"){
    if (flag == 0){
      p.name = value;
      std::cout << p.name<< std::endl;
    }
    else
      printf("found \"name\" without value\n");
  }
  else if (action == "--attempts"){
    if (flag == 0){
      p.attempts = atoi(value.c_str());
      std::cout << p.attempts<< std::endl;
    }
    else
      printf("found \"attempts\" without value\n");
  }
  else if (action == "--score"){
    if (flag == 0){
      p.score = atof(value.c_str());
      std::cout << p.score<< std::endl;
    }
    else
      printf("found \"score\" without value\n");
  }
  else if (action == "--next_round"){
    if (flag == 0){
      p.next_round = atoi(value.c_str());
      std::cout << p.next_round<< std::endl;
    }
    else
      printf("found \"next_round\" without value\n");
  }
  return 0;
}


int main (int argc, char **argv){
  int optarg = 1;
  player p;
  
  while (optarg != argc){
    getopt_long(argc, argv, info, optarg, p);
  }
  return 0;
};
