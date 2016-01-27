#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#ifdef CURSES
extern "C" {
    #include <curses.h>
}
#endif

using boost::asio::ip::tcp;



class command {
    public:
            command() { }
};

class game {
    public:
       game () { };
       std::vector<command> commandBuffer;
};

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket, game g) :  socket_(std::move(socket)), game_(g)  {
    }
  session(tcp::socket socket) :  socket_(std::move(socket))  { }
  game game_;

  void start()
  {
    do_read();
  }

private:
  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            do_write(length);

            command c;
//            self->game_.commandBuffer.push_back(c);

          }
        });
  }

  void do_write(std::size_t length)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};


class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket_))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
};

#ifdef CURSES
void curses_print() {

 WINDOW * mainwin;
 if ( (mainwin = initscr()) == NULL ) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }


    /*  Display "Hello, world!" in the centre of the
        screen, call refresh() to show our changes, and
        sleep() for a few seconds to get the full screen effect  */

    mvaddstr(13, 33, "Hello, world!");
    refresh();
    sleep(3);


    /*  Clean up after ourselves  */

    delwin(mainwin);
    endwin();
    refresh();


}
#endif

int main(int argc, char* argv[])
{
#ifdef CURSES
    curses_print();
#endif
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    server s(io_service, std::atoi(argv[1]));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
