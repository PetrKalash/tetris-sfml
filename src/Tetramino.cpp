#include "tetramino.h"
#include <random>

Tetramino::Tetramino() : m_cords{}, m_tiles{}, m_type{}, m_figures{}{}

Tetramino::Tetramino(Sprite &tiles) : m_cords{}, m_tiles{tiles}, m_type {(std::mt19937(std::random_device{}())() % 7)},
m_figures
{
	1,3,5,7, // I
	2,4,5,7, // S
	3,5,4,6, // Z
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5  // O
}
{
	// Если фигура генерируется в первый раз (стартовая, которую мы не перемещаем), то помещаем ее на поле
	for (size_t i {}; i < 4; ++i) {
		// Нахождение координат фигуры тетрамино (5 % 2; 5 / 2) = (1; 2) - координата числа 5
		m_cords.at(i).x = m_figures.at(m_type).at(i) % 2 + 5;
		m_cords.at(i).y = m_figures.at(m_type).at(i) / 2;
	}
	// Вырезаем из спрайта отдельный квадратик случайного цвета
	m_tiles.setTextureRect(IntRect((std::mt19937(std::random_device{}())() % 8) * 18, 0, 18, 18));
}

void Tetramino::move_right()
{
	// Как только клавиша вправо была обработана, сдвигаем все фигурки тетрамино
	for (size_t i {}; i < 4; ++i) m_cords.at(i).x += 1;
}

void Tetramino::move_left()
{
	for (size_t i{}; i < 4; ++i) m_cords.at(i).x -= 1;
}

void Tetramino::move_down()
{
	for (size_t i{}; i < 4; ++i) m_cords.at(i).y += 1;
}

void Tetramino::fast_down(double &delay)
{
	delay = 0.05f;
}

void Tetramino::rotate()
{
	// Указываем центр вращения (относительно какой точки (квадратика) мы будем вращать тетрамино
	Point center = m_cords.at(1);

	for (size_t i{}; i < 4; ++i) {
		// Временные переменные, т.к. мы будем менять значения координат по x и y
		int32_t x = m_cords.at(i).y - center.y;		// y - y_0
		int32_t y = m_cords.at(i).x - center.x;		// x - x_0

		// Изменяем сами координаты фигуры
		m_cords.at(i).x = center.x - x;				// X = x_0 - (y - y_0);
		m_cords.at(i).y = center.y + y;				// Y = y_0 + (x - x_0);
	}
}

void Tetramino::print_tetramino(RenderWindow &window)
{
	// Отрисовка квадратика тетриса
	for (size_t i{}; i < 4; ++i) {
		// Установка позиции квадратика тетриса (18x18 - размер квадратика)
		m_tiles.setPosition(m_cords.at(i).x * 18.f, m_cords.at(i).y * 18.f);
		// Смещение фигурки от изначального положения
		m_tiles.move(36, 52);
		// Отрисовка квадратика тетриса
		window.draw(m_tiles);
	}
}

void Tetramino::add_tetramino(Tetramino &tetramino, double &delay, Sprite &sprite_tiles)
{
	// Создание новой фигурки тетрамино на поле
	tetramino = Tetramino(sprite_tiles);
	// У новой фигурки тетрамино будет обычная скорость
	delay = 0.5f;
}

std::array<Point, 4> Tetramino::get_sprite_cords() const 
{ 
	return m_cords;
}

Sprite Tetramino::get_sprite_tetramino() const
{
	return m_tiles;
}