#include "Player.hpp"

using namespace Core;

Player::Player()
	: m_name("Player ")
{
	m_name.append(std::to_string(cnt++));
}

Player::Player(std::string name)
	: m_name(name)
{
}
