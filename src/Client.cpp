#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char *argv[]) {

  char *server_ip = argv[1];
  char *message = argv[2];

  int client;
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(7000); /* рекомендуется всегда использовать htons() 
  для преобразования порта в сетевой порядок байт, чтобы гарантировать корректную 
  работу вашего сетевого приложения на разных платформах.
  */
  // addr.sin_addr.s_addr = htons(INADDR_LOOPBACK); // INADDR_LOOPBACK - адрес интерфейса внутренней петли (loopback interface)
  addr.sin_addr.s_addr = inet_addr(server_ip);
  

  // файловый дескриптор (число)
  client = socket(AF_INET, SOCK_STREAM, 0);

  if (client >= 0) 
    cout << "Сокет успешно создался" << endl;
  else {
    cout << "Проблема создания сокета";
    return 1;
  }

  if (connect(client, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
    cout << "Не удалось подключится";
    return 1;
  } else {
    cout << "TEST" << endl;
    send(client, message, sizeof(message), 0);
    cout << "Отправил ваше сообщение: " << message << endl;
  }

  return 0;
}
