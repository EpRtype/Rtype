#include	"Server.hpp"

int     main()
{
  Server	*s = Server::getInstance();
  try {
    s->init();
  }
  catch (const std::exception) {
    std::cout << "Error: Init socket fail. Server will quit." << std::endl;
    return (0);
  }
  s->running();
  return (0);
}
