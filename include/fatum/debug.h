#pragma once
#include <string>
#include <string_view>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <memory>
#include <array>
namespace fatum {
	class Logger{
	protected:
		const std::string source;
	public:
		struct Data;
		std::vector<Data> list{};

		virtual void entry(const std::string_view );
		virtual void entryCrash(const std::string_view);

		Logger(std::string_view umi) : source(umi) {}
		
		struct Data {
			const std::string text;
			const std::chrono::system_clock::time_point time;

			const std::string formatted() const;

			Data(const std::string_view text) : text(text), time(std::chrono::system_clock::now()) {};
		};
	};
}
