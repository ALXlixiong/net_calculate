#pragma once 

struct Request_t{
  int cal_kind;//calculate kind (1)date(2)number(3)conversion of number systems
  int x;
  int y;
  char op;
};

struct Response_t{
  int status;
  int result;
};
