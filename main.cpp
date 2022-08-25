
#include <crow.h>
#include <InfluxDBFactory.h>
#include "Data.h"

struct Middleware {
    std::string message;

    Middleware() :
            message("foo") {
    }

    void setMessage(const std::string &newMsg) {
        message = newMsg;
    }

    struct context {
    };

    void before_handle(crow::request &, crow::response &, context &) {
        CROW_LOG_DEBUG << " - MESSAGE: " << message;
    }

    void after_handle(crow::request & /*req*/, crow::response & /*res*/, context & /*ctx*/) {
    }
};

int main() {
    auto db = influxdb::InfluxDBFactory::Get("http://localhost:8086?db=temperature_db");
    db->createDatabaseIfNotExists();
    crow::App<Middleware> app;
    std::mutex mtx;

    CROW_ROUTE(app, "/")
            ([] {
                crow::mustache::context x;
                auto page = crow::mustache::load("index.html");
                return page.render(x);
            });

    CROW_ROUTE(app, "/set_data").methods("POST"_method)
            ([&db](const crow::request &req) {
                auto x = crow::json::load(req.body);
                string fan_speed;
                string fan_color;
                string pump_speed;
                string pump_color;
                if (x["type"] == "fan") {
                    fan_speed = x["fan_speed"].s();
                    fan_color = x["fan_color"].s();
                    db->write(influxdb::Point{"speed"}.addTag("type", "fan").addTag("param", "speed").addField("value",
                                                                                                               fan_speed));
                    db->write(influxdb::Point{"color"}.addTag("type", "fan").addTag("param", "color").addField("value",
                                                                                                               fan_color));
                }
                else if (x["type"] == "pump"){
                    pump_speed = x["pump_speed"].s();
                    pump_color = x["pump_color"].s();
                    db->write(influxdb::Point{"speed"}.addTag("type", "pump").addTag("param", "speed").addField("value",
                                                                                                               pump_speed));
                    db->write(influxdb::Point{"color"}.addTag("type", "pump").addTag("param", "color").addField("value",
                                                                                                               pump_color));
                }
                return crow::response(200);
            });

    CROW_ROUTE(app, "/charts")
            ([]() {
                crow::mustache::context x;
                auto page = crow::mustache::load("charts.html");
                return page.render(x);
            });

    CROW_ROUTE(app, "/controls")
            ([]() {
                crow::mustache::context x;
                auto page = crow::mustache::load("controls.html");
                return page.render(x);
            });

    CROW_ROUTE(app, "/index")
            ([]() {
                crow::mustache::context x;
                auto page = crow::mustache::load("index.html");
                return page.render(x);
            });
    CROW_ROUTE(app, "/logout")
            ([]() {

                crow::mustache::context x;
                auto page = crow::mustache::load("login.html");
                return page.render(x);
            });

    CROW_ROUTE(app, "/forgot-password")
            ([]() {

                crow::mustache::context x;
                auto page = crow::mustache::load("forgot-password.html");
                return page.render(x);
            });

    CROW_ROUTE(app, "/get_data")
            ([]() {
                const string n[2] = {"/sys/class/hwmon/hwmon4/temp1_input", // cpu
                                     "/sys/class/hwmon/hwmon7/temp1_input"}; // gpu
                string ss = "/proc/stat"; // load cpu
                string s = "/proc/meminfo"; // memory load
                Data d;

                return crow::json::wvalue({
                                                  {"cpu_temp", d.cpu_gpu(n[0])},
                                                  {"cpu",      d.cpu_load(ss)},
                                                  {"gpu_temp", d.cpu_gpu(n[1])},
                                                  {"gpu",      d.memory_load(s).second}
                                          });
            });
    app.port(18080)
            .multithreaded()
            .run();
}
