#include <drogon/drogon.h>

int main() {
    // handler for the root path "/"
    drogon::app().registerHandler("/", [](const drogon::HttpRequestPtr& req, 
                                          std::function<void (const drogon::HttpResponsePtr &)> &&callback) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setBody("<h1>Hello World from Dashboard!</h1>");
        callback(resp);
    });

    drogon::app().addListener("0.0.0.0", 8080);

    // Running the server
    LOG_INFO << "Server running on http://localhost:8080";
    drogon::app().run();

    return 0;
}