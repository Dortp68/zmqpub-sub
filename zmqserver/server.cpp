#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <zmq.hpp>


std::vector<std::string> GetData()
{
  std::ifstream file1 ("../student_file_1.txt");
  std::ifstream file2 ("../student_file_2.txt");
  std::vector<std::string> list1;
  std::string tmp;
  //Чтение из первого файла
  while (getline(file1, tmp))
  {
    list1.push_back(tmp);
  }
  file1.close();
  std::string list2;
  //Чтение из второго файла построчно и поиск одинаковых элементов с первым файлом
  while (getline(file2, list2))
  {
    auto result = std::find_if(list1.begin(), list1.end(),
    [&list2](std::string tmp) {
    auto iter1 = std::find(tmp.begin(), tmp.end(), ' ');
    auto iter2 = std::find(list2.begin(), list2.end(), ' ');
    iter1 = std::next(iter1);
    iter2 = std::next(iter2);
    return(std::equal(iter1, tmp.end(), iter2, list2.end())); });
    if (result == list1.end())
    {
      list1.push_back(list2);
    }
  }
  file2.close();
  for(auto item:list1)
  {
    std::cout<<item<<std::endl;
  }
  return list1;
}


int main(int argc, char const *argv[])
{
  zmq::context_t ctx;
  zmq::socket_t sock(ctx, ZMQ_PUB);
  zmq_bind(sock, "tcp://*:4040");
  std::cout<<"Starting server\n";

  //Работа с данными
  std::vector<std::string> pub = GetData();

  int i = 0;
  while(i<pub.size())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::string tmp = pub[i];
    i++;
    zmq::message_t msg(tmp);
    sock.send(msg, zmq::send_flags::none);

  }
  std::string tmp = "end";
  zmq::message_t msg(tmp);
  sock.send(msg, zmq::send_flags::none);

  return 0;
}
