#ifndef _COVALENT_HPP
#define _COVALENT_HPP

#include <SFML/Network.hpp>
#include <map>
#include <vector>

namespace app {

struct CovalentInfo {
  // General items.
  std::string msg;
  bool isValid;

  // Covalent-specific.
  std::string serverIP;
  int serverPort;
  std::string serverKey;

  // General items the server might send us.
  std::map<std::string, std::string> params;
};

static void getCovalentParams(CovalentInfo &info, const std::string &json) {
  // Now try to parse out the json object ..
  if (json.length() > 1024) {
    printf("Possible buffer overflow detected - bailing.\n");
    return;
  }

  // For safety reasons, we treat this as a subset of json - ie, max-length =
  // 1024.
  int len = json.length();

  // Still try our best to fetch all the params.
  std::vector<std::string> params;

  // Make a copy of the data to parse.
  char *data = new char[len * 2];
  strcpy(data, json.c_str());

  char *p = strtok(data, ",");
  while (p) {
    std::string token(p);
    if (token.find_first_of("{") == 0)
      token = token.substr(1);
    if (token.find_first_of("}") == token.length() - 1)
      token = token.substr(0, token.length() - 1);

    params.push_back(token);
    printf("Token: %s\n", token.c_str());

    p = strtok(NULL, ",");
  }

  // Now that we have all the data, allocate it to the corret places and clean
  // up memory.
  delete[] data;

  // Still need to split params by another token.
  for (auto i : params) {
    std::string::size_type pos = i.find_first_of(":");
    if (pos == std::string::npos) {
      printf("Could not dismantle variable %s\n", i.c_str());
      continue;
    }

    // While building name/value pairs - strip off extra quotes
    std::string name = i.substr(1, pos - 2);
    std::string value = i.substr(pos + 2, i.length() - (pos + 3));

    printf("Found name/value pair [%s][%s]\n", name.c_str(), value.c_str());

    if (name == "result") {
      info.isValid = (value.find_first_of("s") == 0);
    } else if (name == "server_ip") {
      info.serverIP = value;
    } else if (name == "server_port") {
      info.serverPort = atoi(value.c_str());
    } else {
      info.params[name] = value;
    }
  }
}

static void getCovalentInfo(CovalentInfo &info) {
  // Do some network stuff - block for some time.
  info.isValid = false;
  info.msg = "Waiting to connect to server.";

  sf::Http http("http://www.shaheedabdol.co.za/");
  sf::Http::Request request;

  request.setMethod(sf::Http::Request::Method::Get);
  request.setUri("covalent.php?request=fs_clnt_6253_2635");
  sf::Http::Response response = http.sendRequest(request);

  if (response.getStatus() == sf::Http::Response::Status::Ok) {
    info.isValid = true;
    info.msg = "Fetched covalent info from server.";

    getCovalentParams(info, response.getBody());
  } else {
    info.isValid = false;
    info.msg = response.getBody();
  }
}

class ChatThread {
public:
  ChatThread(CovalentInfo &info) {
    // Get the data we need, then pass it over to the network.
  }

  ~ChatThread() {
    // Make sure to disconnect from the server.
  }
};

static ChatThread *StartChatThread(CovalentInfo &info) {
  // Do some stuff to start the chat thread - hello to server etc.
  // Start a chat session to the server.
  // return the chat thread object.
  return new ChatThread(info);
}
}

#endif // _COVALENT_HPP