#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <zmq.hpp>

int main(int argc, char const *argv[])
{
  zmq::context_t ctx;
  zmq::socket_t sock(ctx, ZMQ_SUB);
  sock.connect("tcp://localhost:4040");
  sock.setsockopt (ZMQ_SUBSCRIBE, "" , 0);

  std::vector<std::string> ans;

  while(1)
  {
    zmq::message_t answ;
    sock.recv(answ);
    if(std::string(static_cast<char*>(answ.data()), answ.size()) == "end") break;
    ans.push_back(std::string(static_cast<char*>(answ.data()), answ.size()));
  }
  //Сортировка
  std::sort(ans.begin(), ans.end(),[](std::string str1, std::string str2){
    auto iter1 = std::find(str1.begin(), str1.end(), ' ');
    auto iter2 = std::find(str2.begin(), str2.end(), ' ');
    iter1 = std::next(iter1);
    iter2 = std::next(iter2);
    return (*iter1) < (*iter2);
  });
  for(auto i:ans)
  {
    std::cout<<i<<std::endl;
  }
  return 0;
}
