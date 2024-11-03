#pragma once
//#include <iostream>
//#include <functional>
//#include <unordered_map>
//#include <vector>
//#include <memory>
//#include <thread>
//#include <chrono>
//#include <string>
//
//namespace fatum::input {
//    struct Hook {
//        struct Data;
//
//        void operator()(Data data) { callback(std::move(data)); };
//
//        enum Type {
//            None,
//            KeyPressed,
//            PostRender,
//            PreUpdate,
//        };
//
//        struct Data {
//            unsigned int key = 0;
//            Type type;
//            Data(Type _type) : type(_type) {}
//            Data(Type _type, unsigned int _key) : type(_type),key(_key) {}
//        };
//
//        struct Handler {
//            void operator()(Data&& data) {
//                auto it = _hooks.find(data.type);
//                if (it == _hooks.end()) return;
//                for (const std::unique_ptr<Hook>& hook : it->second) (*hook)(data);
//            }
//
//            void addHook(Type type, std::string_view id, std::function<void(Data)> clb) {
//                _hooks[type].push_back(std::make_unique<Hook>(id,clb));
//            }
//
//        private:
//            std::unordered_map<Type, std::vector<std::unique_ptr<Hook>>> _hooks;
//        };
//
//        Hook(std::string_view id, std::function<void(Data)> clb) : callback(std::move(clb)), unique_id(id) {}
//
//    protected:
//      
//        const std::function<void(Data)> callback;
//        const std::string unique_id;
//    };
//
//
//    static void onKeyPressSafe(int virtual_key, const std::function<void()>& callback, unsigned long long delay) {
//        callback();
//        std::this_thread::sleep_for(std::chrono::microseconds{ delay });
//    }
//
//
//}