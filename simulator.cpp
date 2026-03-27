#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp> 
#include <stdatomic.h>
#include "headers/vehical_state.h"
#include <stdatomic.h>

using json = nlohmann::json;

extern "C" void* run_simulation(void* arg) {
    SystemState* state = (SystemState*)arg;

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

    double sim_time = 0.0;
    double dt;

    double F;
    double a;
    const double z_limit = 12.0; 

    double current_v_lead;
    double current_z;
    double next_z;
    double z;

    double v_lead_current;
    double v_error;
    json response;

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
            dt = std::chrono::duration<double>(now - last_sim_time).count();
            last_sim_time = now;
            sim_time += dt;

            // Get control force
            F = atomic_load(&state->force_cmd);
            // Optional saturation
            a = F / 1500.0;

            // Lead vehicle velocity (prescribed)
            v_lead_current = 20.0 + 5.0 * std::sin(0.2 * sim_time);


            // Update ego vehicle
            atomic_store(&state->v_ego, atomic_load(&state->v_ego) + (a * dt));
            atomic_store(&state->pos_x, atomic_load(&state->pos_x) + (atomic_load(&state->v_ego) * dt));
            atomic_store(&state->ego_acceleration, a);


            // Update lead position
            atomic_store(&state->x_lead, atomic_load(&state->x_lead) + ( atomic_load(&state->v_lead) * dt));

            // Integral term (e.g., for LQR)
            v_error = atomic_load(&state->v_ego) - atomic_load(&state->v_lead); // track lead speed
            atomic_store(&state->v_error, v_error);
            z = atomic_load(&state->z) + v_error * dt;
            atomic_store(&state->z, z);

            // 4. Send updated state to the visule handler every 66ms
            if(now - last_send_time >= send_interval) {

                response["data"] = {
                    {"x_position", atomic_load(&state->pos_x)},
                    {"current_velocity",atomic_load(&state->v_ego)},
                    {"acceleration", atomic_load(&state->ego_acceleration)},
                    {"v_error", atomic_load(&state->v_error)},
                    {"z", atomic_load(&state->z)},
                    {"x_lead",atomic_load(&state->x_lead) },
                    {"v_lead",atomic_load(&state->v_lead)},
                };
                // std::cout << " x_lead " << atomic_load(&state->x_lead) << std::endl;
                response["sender"]="conroller";

                ws.write(net::buffer(response.dump()));
                last_send_time = now;

            }
            //setting a fixed tick rate of 100Hz will be higher at later 
            std::this_thread::sleep_until(next_tick);

        }

        }
        //error handler
        catch (std::exception const& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            state->running = false; // Stop the simulation on error
            std::cout << "Simulation thread exiting due to error." << std::endl;
        }
}