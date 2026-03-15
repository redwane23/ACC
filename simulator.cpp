#include <chrono>
#include <thread>
#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp> 
#include <stdatomic.h>
#include "headers/vehical_state.h"


using json = nlohmann::json;

extern "C" void* run_simulation(void* arg) {
    VehicleState* state = (VehicleState*)arg;

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

        int running = atomic_load(&state->running);


        while (running) {

            next_tick += target_interval;
            auto now = std::chrono::steady_clock::now();
            double dt = std::chrono::duration<double>(now - last_sim_time).count();
            last_sim_time = now;

            // 1. Get current force from the Controller
            double F = atomic_load(&state->force_cmd);
            // a = F / m 
            double a = F / 1500.0; 
            
            // 3. Update state (Euler Integration)
            atomic_store(&state->cur_velocity,atomic_load(&state->cur_velocity) + (a * dt) );

            double current_z = atomic_load(&state->z);
            double next_z = current_z + (atomic_load(&state->v_error) * dt);

            const double z_limit = 12.0; 
            if (next_z > z_limit) next_z = z_limit;
            if (next_z < -z_limit) next_z = -z_limit;

            atomic_store(&state->z,next_z);

            atomic_store(&state->pos_x, atomic_load(&state->pos_x) + (atomic_load(&state->cur_velocity) * dt) );
            atomic_store(&state->acceleration, a);
            
            atomic_store(&state->v_error, atomic_load(&state->cur_velocity) - target_speed);

            if(now - last_send_time >= send_interval) {
                json response;
                response["data"] = {
                    {"x_position", atomic_load(&state->pos_x)},
                    {"current_velocity",atomic_load(&state->cur_velocity)},
                    {"acceleration", atomic_load(&state->acceleration)},
                    {"v_error", atomic_load(&state->v_error)},
                    {"z", atomic_load(&state->z)}
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
            state->running = false; // Stop the simulation on error
            std::cout << "Simulation thread exiting due to error." << std::endl;
        }
}