#pragma once

#include <string>

namespace Core {
	class Player {
	public:
		Player();
		Player(std::string name);

	private:
		std::string m_name;

		static unsigned cnt;
	};
} // namespace Core