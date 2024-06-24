#include <iostream>

class EthicalCompetition {
private:
  class Connection {
  public:
    void connect() {
      std::cout << "Connecting..." << std::endl;
    }
  };

public:
  void HardWork() {
    Connection conn;
    conn.connect();
  }
};

int main() {
  EthicalCompetition competition;
  competition.HardWork();

  // The following line will result in a compilation error because Connection is private
  EthicalCompetition::Connection conn;
  conn.connect();

  return 0;
}
