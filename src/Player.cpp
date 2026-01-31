#include "Player.hpp"

using namespace Core;

unsigned Player::cnt = 0u;

Player::Player() : m_name("Player ") { m_name.append(std::to_string(cnt++)); }

Player::Player(std::string name) : m_name(name) { }

void Player::take(const Card& card) { m_cards.push_back(card); }
