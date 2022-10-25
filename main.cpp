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

struct params{
    uint8_t cpu_usage = 0;
    uint8_t cpu_temp = 255;
    uint8_t mem_usage = 254;
    uint8_t gpu_temp = 253;
};

array<params, 4> get_hardware_data(unique_ptr<influxdb::InfluxDB> &db){
    const string n[2] = {"/sys/class/hwmon/hwmon4/temp1_input", // cpu
                         "/sys/class/hwmon/hwmon7/temp1_input"}; // gpu
    string ss = "/proc/stat"; // load cpu
    string s = "/proc/meminfo"; // memory load
    Data d;
    
//    int n1 = d.cpu_load(ss);
//    int n2 = d.cpu_gpu(n[0]);
//    int n3 = d.memory_load(s).second;
//    int n4 = d.cpu_gpu(n[1]);

//    int n1 = 1;
//    int n2 = 2;
//    int n3 = 3;
//    int n4 = 4;
//
//    db->write(influxdb::Point{"cpu_usage0"}.addTag("type", "cpu_usage").addField("value", n1));
//    db->write(influxdb::Point{"cpu_temp0"}.addTag("type", "cpu_temp").addField("value", n2));
//    db->write(influxdb::Point{"mem_usage0"}.addTag("type", "mem_usage").addField("value",n3));
//    db->write(influxdb::Point{"gpu_temp0"}.addTag("type", "gpu_temp").addField("value", n4));
//
//    db->write(influxdb::Point{"cpu_usage1"}.addTag("type", "cpu_usage").addField("value", n1));
//    db->write(influxdb::Point{"cpu_temp1"}.addTag("type", "cpu_temp").addField("value", n2));
//    db->write(influxdb::Point{"mem_usage1"}.addTag("type", "mem_usage").addField("value",n3));
//    db->write(influxdb::Point{"gpu_temp1"}.addTag("type", "gpu_temp").addField("value", n4));
//
//    db->write(influxdb::Point{"cpu_usage2"}.addTag("type", "cpu_usage").addField("value", n1));
//    db->write(influxdb::Point{"cpu_temp2"}.addTag("type", "cpu_temp").addField("value", n2));
//    db->write(influxdb::Point{"mem_usage2"}.addTag("type", "mem_usage").addField("value",n3));
//    db->write(influxdb::Point{"gpu_temp2"}.addTag("type", "gpu_temp").addField("value", n4));
//
//    db->write(influxdb::Point{"cpu_usage3"}.addTag("type", "cpu_usage").addField("value", n1));
//    db->write(influxdb::Point{"cpu_temp3"}.addTag("type", "cpu_temp").addField("value", n2));
//    db->write(influxdb::Point{"mem_usage3"}.addTag("type", "mem_usage").addField("value",n3));
//    db->write(influxdb::Point{"gpu_temp3"}.addTag("type", "gpu_temp").addField("value", n4));

    array<params, 4> p;

    //rpi0
    for (auto i: db->query("select last(value) from cpu_usage0")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[0].cpu_usage = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from cpu_temp0")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[0].cpu_temp = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from mem_usage0")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[0].mem_usage = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from gpu_temp0")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[0].gpu_temp = stoi(field.substr(pos + 1));
    }

    //rpi1
    for (auto i: db->query("select last(value) from cpu_usage1")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[1].cpu_usage = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from cpu_temp1")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[1].cpu_temp = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from mem_usage1")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[1].mem_usage = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from gpu_temp1")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[1].gpu_temp = stoi(field.substr(pos + 1));
    }

    //rpi2
    for (auto i: db->query("select last(value) from cpu_usage2")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[2].cpu_usage = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from cpu_temp2")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[2].cpu_temp = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from mem_usage2")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[2].mem_usage = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from gpu_temp2")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[2].gpu_temp = stoi(field.substr(pos + 1));
    }

    //rpi3
    for (auto i: db->query("select last(value) from cpu_usage3")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[3].cpu_usage = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from cpu_temp3")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[3].cpu_temp = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from mem_usage3")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[3].mem_usage = stoi(field.substr(pos + 1));
    }

    for (auto i: db->query("select last(value) from gpu_temp3")) {
        string field = i.getFields();
        auto pos = field.find('=');
        p[3].gpu_temp = stoi(field.substr(pos + 1));
    }
    return p;
}

int main() {
    auto db = influxdb::InfluxDBFactory::Get("http://localhost:8086?db=cluster");
    db->createDatabaseIfNotExists();
    crow::App<Middleware> app;
    std::mutex mtx;

    CROW_ROUTE(app, "/")
            ([] {
                crow::mustache::context x;
                auto page = crow::mustache::load("index.html");
                return page.render(x);
            });

    CROW_ROUTE(app, "/login")
            ([] {
                crow::mustache::context x;
                auto page = crow::mustache::load("login.html");
                return page.render(x);
            });

    CROW_ROUTE(app, "/auth").methods("POST"_method)
            ([](const crow::request &req) {
                auto y = crow::json::load(req.body);
                if (y["login"] == "root") {
                    if (y["password"] == "1234pass") {
                        return crow::response(200);
                    }
                }
                return crow::response(401);
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
                } else if (x["type"] == "pump") {
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

    CROW_ROUTE(app, "/get_data")
            ([&db]() {
                auto hw = get_hardware_data(db);

                return crow::json::wvalue({
                                                  {"cpu_temp0", hw[0].cpu_temp},
                                                  {"cpu_usage0",      hw[0].cpu_usage},
                                                  {"gpu_temp0", hw[0].gpu_temp},
                                                  {"mem_usage0",      hw[0].mem_usage},
                                                  {"cpu_temp1", hw[1].cpu_temp},
                                                  {"cpu_usage1",      hw[1].cpu_usage},
                                                  {"gpu_temp1", hw[1].gpu_temp},
                                                  {"mem_usage1",      hw[1].mem_usage},
                                                  {"cpu_temp2", hw[2].cpu_temp},
                                                  {"cpu_usage2",      hw[2].cpu_usage},
                                                  {"gpu_temp2", hw[2].gpu_temp},
                                                  {"mem_usage2",      hw[2].mem_usage},
                                                  {"cpu_temp3", hw[3].cpu_temp},
                                                  {"cpu_usage3",      hw[3].cpu_usage},
                                                  {"gpu_temp3", hw[3].gpu_temp},
                                                  {"mem_usage3",      hw[3].mem_usage}
                                          });
            });
    app.port(18080)
            .multithreaded()
            .run();
}
