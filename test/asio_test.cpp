/*
 * Copyright 2017, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   asio_test.cpp
 * Author: alex
 *
 * Created on May 5, 2017, 9:03 PM
 */

#include <chrono>
#include <iostream>

#include "asio.hpp"

#include "staticlib/config/assert.hpp"

void test_connect() {
    asio::io_service service{};
    asio::ip::tcp::socket socket{service, asio::ip::tcp::v4()};
    asio::steady_timer timer{service};
    bool connect_cancelled = false;
    bool timer_cancelled = false;
    asio::ip::tcp::endpoint endpoint{asio::ip::address_v4::from_string("127.0.0.1"), 4242};
    std::string error_message = "";

    timer.expires_from_now(std::chrono::seconds(1));

    socket.async_connect(endpoint, [&](const asio::error_code& ec) {
        if (connect_cancelled) {
            return;
        }
        timer_cancelled = true;
        timer.cancel();
        if (ec) {
            error_message = "ERROR: " + ec.message();
        }
    });

    timer.async_wait([&](const asio::error_code&) {
        if (timer_cancelled) {
            return;
        }
        connect_cancelled = true;
        socket.close();
        error_message = "ERROR: Connection timed out (-1)";
    });

    service.run();
}

int main() {
    try {
        test_connect();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

