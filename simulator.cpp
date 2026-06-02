#include <chrono>
#include <thread>
#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp>
#include <librdkafka/rdkafkacpp.h>
#include <string>
#include <pthread.h> 
#include "headers/vehical_state.h"
#include "modules/switching_moduale.h"

using json = nlohmann::json;

extern "C" void* run_simulation(void* arg) {
    Sim_threads* threads_info = (Sim_threads*)arg;
    SystemState* state = threads_info->ctrl_args->state;

    const char* env_broker = std::getenv("KAFKA_BROKER");
    std::string brokers = (env_broker != nullptr) ? env_broker : "localhost:9094";
    std::string topic_name = "cpp_data";
    std::string errstr;

    auto last_sim_time = std::chrono::steady_clock::now();
    const std::chrono::microseconds target_interval(10000);
    auto next_tick = std::chrono::steady_clock::now();
    auto last_send_time = std::chrono::steady_clock::now();
    const std::chrono::milliseconds send_interval(16);

    auto last_target_change = std::chrono::steady_clock::now();   
    const std::chrono::seconds target_change_interval(10); 

    double sim_time = 0.0;
    double dt;
    double F ;
    double acceleration_cmd; // Assuming a mass of 1500 kg for the  vehicle
    int cr;//cansel result for check
    // Initial check of running state
    pthread_mutex_lock(&state->lock);
    bool running = state->running;
    pthread_mutex_unlock(&state->lock);

    try {
        RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
        conf->set("queue.buffering.max.ms", "1", errstr);
        conf->set("bootstrap.servers", brokers, errstr);
        conf->set("linger.ms", "0", errstr);    
        conf->set("socket.nagle.disable", "true", errstr);


        conf->set("auto.offset.reset", "earliest", errstr);
        conf->set("enable.auto.commit", "false", errstr);


        conf->set("batch.num.messages", "1", errstr); 
        conf->set("max.in.flight", "1", errstr); 
        RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr);
        if (!producer) {
            std::cerr << "ERROR: Failed to create producer: " << errstr << std::endl;
            return NULL;
        }

        RdKafka::Conf *conf_consumer = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

        conf_consumer->set("api.version.request", "true", errstr);
        conf_consumer->set("bootstrap.servers", brokers, errstr);
        conf_consumer->set("group.id", "controller_group_20260429", errstr);
        conf_consumer->set("auto.offset.reset", "stored", errstr);   
        conf_consumer->set("enable.auto.commit", "false", errstr);       
        conf_consumer->set("api.version.request.timeout.ms", "10000", errstr);
        conf_consumer->set("debug", "broker,protocol", errstr);
        conf_consumer->set("enable.auto.offset.store", "true", errstr);
        RdKafka::KafkaConsumer *consumer = RdKafka::KafkaConsumer::create(conf_consumer, errstr);
        if (!consumer) {
            std::cerr << "ERROR: Failed to create consumer: " << errstr << std::endl;
            return NULL;
        }

                RdKafka::Metadata *md;
                while (running) {
                    RdKafka::ErrorCode err = consumer->metadata(true, NULL, &md, 2000);
                    if (err == RdKafka::ERR_NO_ERROR) {
                        delete md;
                        break; 
                    }
                    // std::cout << "Consumer waiting for broker connection..." << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }


        RdKafka::TopicPartition *tp = RdKafka::TopicPartition::create("controller_commands", 0, 0);
            std::vector<RdKafka::TopicPartition*> partitions;
            partitions.push_back(tp);
            
            RdKafka::ErrorCode err_assign = consumer->assign(partitions);
            if (err_assign != RdKafka::ERR_NO_ERROR) {
                std::cerr << "Assign error: " << RdKafka::err2str(err_assign) << std::endl;
            }
            
            // Important: Clean up the helper object
            RdKafka::TopicPartition::destroy(partitions);
            



            RdKafka::Metadata *metadata;
            RdKafka::ErrorCode err;
            std::cout << "Consumer syncing with broker..." << std::endl;
            do {
                // This forces the client to fetch broker capabilities
                err = consumer->metadata(true, NULL, &metadata, 5000); 
                if (err != RdKafka::ERR_NO_ERROR) {
                    std::cerr << "Consumer connection failed, retrying: " << RdKafka::err2str(err) << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            } while (err != RdKafka::ERR_NO_ERROR);
            delete metadata;

   
        while (running) {
            auto now = std::chrono::steady_clock::now();
            dt = std::chrono::duration<double>(now - last_sim_time).count();
            last_sim_time = now;
            sim_time += dt;

            //physics update
            pthread_mutex_lock(&state->lock);

            F = state->force_cmd;
            acceleration_cmd = F / 1500.0; // Assuming a mass of 1500 kg for the  vehicle


            state->v_ego += (acceleration_cmd * dt);
            state->ego_acceleration = acceleration_cmd;
            state->pos_x += (state->v_ego * dt);

            if (threads_info->current_mode == 'L') {
                state->v_error = state->v_ego - state->target_speed;
                state->digital_velocity = state->previous_velocity + acceleration_cmd * dt;
                state->previous_velocity = state->v_ego;
                if (now - last_target_change >= target_change_interval) {

                    double new_target = 15.0 + (rand() % 11); // 15..25 m/s
                    state->target_speed = new_target;
                    last_target_change = now;
                    std::cout << "[L mode] Target speed changed to " << new_target << " m/s" << std::endl;
                }
                
            }

            else if (threads_info->current_mode == 'M') {
                state->v_lead = 20.0 + 2.0 * std::sin(0.2 * sim_time);
                state->x_lead += (state->v_lead * dt);
                state->v_error = state->v_ego - state->v_lead;
                std::cout <<" im excuting : " << std::endl;
            }

            double log_x = state->pos_x;
            double log_v = state->v_ego;
            double log_a = state->ego_acceleration;
            double log_ve = state->v_error;
            double log_xl = state->x_lead;
            double log_vl = state->v_lead;

            pthread_mutex_unlock(&state->lock);


            if (now - last_send_time >= send_interval) {
                last_send_time = now;
                json response;
                response["data"] = {
                    {"x_position", log_x},
                    {"current_velocity", log_v},
                    {"acceleration", log_a},
                    {"v_error", log_ve},
                    {"x_lead", log_xl},
                    {"v_lead", log_vl},
                    {"target_speed", state->target_speed},
                    {"mode", std::string(1, threads_info->current_mode)}
                };
                
                response["sender"] = "controller";
                std::string message = response.dump();
                producer->produce(
                    topic_name, RdKafka::Topic::PARTITION_UA,
                    RdKafka::Producer::RK_MSG_COPY,
                    const_cast<char *>(message.c_str()), message.size(),
                    NULL, 0, 0, NULL
                );
                producer->poll(0);
                producer->flush(0);

            }


            RdKafka::Message *msg = consumer->consume(0);

            if (msg->err() == RdKafka::ERR_NO_ERROR) {
                std::string cmd(static_cast<char*>(msg->payload()), msg->len());
                pthread_mutex_lock(&state->lock);

                if (cmd == "stop") {
                    state->running = false;
                    std::cout << "Stopping simulation..." << std::endl;

                } else if (cmd == "reset") {
                    state->pos_x = 0.0;
                    state->v_ego = 0.0;
                    state->ego_acceleration = 0.0;
                    state->v_lead = 20.0;
                    state->x_lead = 50.0;
                    state->v_error = 0.0;

                } else if (cmd == "MPC") {

                    cr=pthread_cancel(threads_info->LQR_thread);
                    if(cr==0){
                        printf("LQR Cancellation request delivered successfully.\n");
                    } else {

                        printf("Failed to cancel LQR thread. Error code: %d\n", cr);
                    }
                    pthread_create(&threads_info->MPC_thread, NULL, (void* (*)(void*))MPC_gap_based_controller, threads_info->ctrl_args->state);

                    threads_info->ctrl_args->state->x_lead = threads_info->ctrl_args->state->pos_x + 35.0; 
                    threads_info->current_mode = 'M';
                    threads_info->target_mode = 'M';
                    
                } else if (cmd == "LQR") {


                    std::cout << "Switching to LQR controller..." << std::endl;

                    cr = pthread_cancel(threads_info->MPC_thread);
                    if(cr == 0){
                        printf("MPC Cancellation request delivered successfully.\n");
                    } else {
                        printf("Failed to cancel LQR thread. Error code: %d\n", cr);
                    }
                    

                    pthread_create(&threads_info->LQR_thread, NULL, (void* (*)(void*))LQR_speed_base_controller, threads_info->ctrl_args);
          
                    threads_info->ctrl_args->state->x_lead = threads_info->ctrl_args->state->pos_x - 300.0;  //hide it
                    threads_info->current_mode = 'L';
                    threads_info->target_mode = 'L';
                }

                pthread_mutex_unlock(&state->lock);
                std::cout << "Received command: " << cmd << std::endl;
            }
            
             else if (msg->err() != RdKafka::ERR__TIMED_OUT) {
                std::cerr << "Consumer error: " << msg->errstr() << std::endl;
            }
            delete msg;

            // Check running status for loop condition
            pthread_mutex_lock(&state->lock);
            running = state->running;
            pthread_mutex_unlock(&state->lock);

            next_tick += target_interval;
            std::this_thread::sleep_until(next_tick);
        }

        delete producer;
        delete consumer;
        delete conf;
        delete conf_consumer;
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        pthread_mutex_lock(&state->lock);
        state->running = false;
        pthread_mutex_unlock(&state->lock);
    }
    return NULL;
}
