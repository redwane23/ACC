#include "driver.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;

void run_simulation(VehicleState& state) {

    namespace beast = boost::beast;         // from <boost/beast.hpp>
    namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
    namespace net = boost::asio;            // from <boost/asio.hpp>
    using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


    auto last_sim_time = std::chrono::steady_clock::now();
    const std::chrono::microseconds  target_interval(10000); 
    auto next_tick = std::chrono::steady_clock::now();

    auto last_send_time = std::chrono::steady_clock::now();
    const std::chrono::milliseconds send_interval(16);
    auto now = std::chrono::steady_clock::now();

    double target_speed = 3; // this values in in m/s 
    try {
        std::string host = "localhost"; 
        std::string port = "8000";     
        std::string target = "/ws/simumation/data_center/?client_type=controller"; // The specific WebSocket URL route

        net::io_context ioc;
        tcp::resolver resolver{ioc};
        websocket::stream<tcp::socket> ws{ioc};
        auto const results = resolver.resolve(host, port);
        net::connect(ws.next_layer(), results.begin(), results.end());
        ws.handshake(host, target);

        while (state.running) {

            next_tick += target_interval;
            auto now = std::chrono::steady_clock::now();
            double dt = std::chrono::duration<double>(now - last_sim_time).count();
            last_sim_time = now;

            // 1. Get current force from the Controller
            double F = state.force_cmd.load();

            // a = F / m 
            double a = F / 1500.0; 
            
            // 3. Update state (Euler Integration)
            state.cur_velocity.store( state.cur_velocity.load() + (a * dt) );

            double current_z = state.z.load();
            double next_z = current_z + (state.v_error.load() * dt);

            const double z_limit = 12.0; 
            if (next_z > z_limit) next_z = z_limit;
            if (next_z < -z_limit) next_z = -z_limit;

            state.z.store(next_z);

            state.pos_x.store( state.pos_x +(state.cur_velocity.load() * dt) );
            state.acceleration.store(a);
            
            state.v_error.store( state.cur_velocity.load() - target_speed );

            if(now - last_send_time >= send_interval) {
                json response;
                response["data"] = {
                    {"x_position", state.pos_x.load()},
                    {"current_velocity", state.cur_velocity.load()},
                };
                response["sender"]="conroller";

                ws.write(net::buffer(response.dump()));
                last_send_time = now;
            }

            std::this_thread::sleep_until(next_tick);

        }

        }
        catch (std::exception const& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            state.running = false; // Stop the simulation on error
            std::cout << "Simulation thread exiting due to error." << std::endl;
        }
}