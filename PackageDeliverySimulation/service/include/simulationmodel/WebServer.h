/**
Copyright (c) 2019 Dan Orban
*/

#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <map>
#include <string>
#include <vector>

#include "libwebsockets.h"
#include "libwebsockets/lws-service.h"

/**
 * @class WebServerBase
 * @brief Helps set up what a web server needs to run.
 */
class WebServerBase {
 public:
  /**
   * @brief Parameter constructor, sets up default values
   * @param port type int contains port number. Default is "8081"
   * @param webDir type std::string& contains string to help create a path to a web directory. Default is "."
   */
  WebServerBase(int port = 8081, const std::string& webDir = ".");
  /**
   * @brief Deconstructor for WebServerBase
   */
  virtual ~WebServerBase();
/**
 * @class Session
 * @brief Session specifics
 */
  class Session {
    friend class WebServerBase;

   public:
  /**
   * @brief Default constructor for Session
   */
    Session();
  /**
   * @brief Deconstructor for Session
   */
    virtual ~Session();
  /**
   * @brief gets ID of session
   * @return ID of session
   */
    virtual int getId() const { return id; }
  /**
   * @brief receives message of session
   * @param msg type const std::string& containing message
   */
    virtual void receiveMessage(const std::string& msg) {}
    /**
   * @brief sends message of session
   * @param msg type const std::string& containing message
   */
    virtual void sendMessage(const std::string& msg);
  /**
   * @brief updates session
   */
    virtual void update() {}
  /**
   * @brief sends outgoing messages from server and ensures any additional messages are written if remaining in queue
   */
    virtual void onWrite();

   private:
    void* state;
    int id;
  };
  /**
   * @brief Creates a service for the session. Default time = 10.
   */
  void service(int time = 10);
  /**
   * @brief Creates a session
   * @param info type void* containing info needed to create session
   */
  virtual void createSession(void* info);

 protected:
   /**
   * @brief Creates a session
   * @return a Session pointer
   */
  virtual Session* createSession() { return new Session(); }

 public:
  lws_context* context = nullptr;
  std::vector<Session*> sessions;
  std::map<int, Session*> sessionMap;
  std::string webDir;
};

template <typename T>
/**
 * @class WebServer
 * @brief Creates a Web Server session. Inherits from WebServerBase.
 */
class WebServer : public WebServerBase {
 public:
   /**
   * @brief A parameter constructor with default constructers for setting up the web server
   * @param port type int contains port number. Default is "8081"
   * @param webDir type std::string& contains string to help create a path to a web directory. Default is "."
   */
  WebServer(int port = 8081, const std::string& webDir = ".")
      : WebServerBase(port, webDir) {}

 protected:
   /**
   * @brief Creates a session
   * @return a Session pointer
   */
  Session* createSession() { return new T(); }
};

template <typename T, typename STATE>
/**
 * @class WebServerWithState
 * @brief Creates a Web Server session but has state. Inherits from WebServerBase
 */
class WebServerWithState : public WebServerBase {
 public:
   /**
   * @brief A parameter constructor with default constructers for setting up the web server
   * @param state type STATE contains state of web server
   * @param port type int contains port number. Default is "8081"
   * @param webDir type std::string& contains string to help create a path to a web directory. Default is "."
   */
  WebServerWithState(STATE state, int port = 8081,
                     const std::string& webDir = ".")
      : WebServerBase(port, webDir), state(state) {}

 protected:
   /**
   * @brief Creates a session
   * @return a Session pointer
   */
  Session* createSession() { return new T(state); }

 private:
  STATE state;
};

// JSON support
#include "picojson.h"

/**
 * @class JSONSession
 * @brief Creates JSON Session. Inherits from WebServerBase::Session
 */
class JSONSession : public WebServerBase::Session {
 public:
    /**
   * @brief Receives JSON
   * @param val type picojson::value& contains value of Json to receive
   */
  virtual void receiveJSON(picojson::value& val) {}
    /**
   * @brief Sends JSON
   * @param val type picojson::value& contains value of Json to send
   */
  virtual void sendJSON(picojson::value& val) { sendMessage(val.serialize()); }
    /**
   * @brief Receives message
   * @param msg type std::string& contains message
   */
  void receiveMessage(const std::string& msg) {
    static std::string buf = "";
    picojson::value val;
    std::string err = picojson::parse(val, msg);
    if (err.empty() && val.is<picojson::object>()) {
      buf = "";
      receiveJSON(val);
    } else {
      buf += msg;
      err = picojson::parse(val, buf);
      if (err.empty() && val.is<picojson::object>()) {
        buf = "";
        receiveJSON(val);
      }
    }
  }
};

#include "util/json.h"
/**
 * @class JsonSession
 * @brief Receives/handles commands from web server. Inherits from JSONSession
 */
class JsonSession : public JSONSession {
 public:
  /**
   * @brief Receive a command from the web server
   * @param val: the command (in JSON format)
   */
  void receiveJSON(picojson::value& val) {
    JsonObject data = JsonValue(val);

    std::string cmd = data["command"];

    JsonObject returnValue;
    returnValue["id"] = data["id"];

    receiveCommand(cmd, data, returnValue);
    JsonValue retVal(returnValue);
    sendJSON(retVal.getValue());
  }

  /**
   * @brief Handles specific commands from the web server
   * @param cmd: command
   * @param data: data (JSON)
   * @param returnValue: return value (JSON) which will be sent back to the
   * server
   */
  virtual void receiveCommand(const std::string& cmd, const JsonObject& data,
                              JsonObject& returnValue) = 0;
};

#endif  // WEBSERVER_H_
