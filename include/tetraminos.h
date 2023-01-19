#pragma once
#include <SFML/Graphics.hpp>
#include <array>

using namespace sf;

// Точка с целыми координатами
struct Point
{
	int32_t x, y;										// координаты фигуры
};

// Генерация фигурок тетрамино
class Tetramino
{
private:
	int32_t m_type;										// тип фигурки тетрамино
	Sprite m_tiles;										// спрайт блока тетрамино
	std::array<Point, 4> m_cords;						// точка для каждого блока тетрамино (x, y)
	std::array<std::array <int32_t, 4>, 7> m_figures;	// фигурки тетрамино

public:
	/* Конструкторы */

	// Конструктор по умолчанию
	Tetramino();
	// Конструктор для установки начальной координаты тетрамино
	Tetramino(Sprite &tiles);

	/* Методы */

	// Перемещение фигурки тетрамино вправо
	void move_right();
	// Перемещение фигурки тетрамино влево
	void move_left();
	// Перемещение фигурки тетрамино вниз
	void move_down();
	// Быстрое перемещение фигурки тетрамино вниз
	void fast_down(double &delay);
	// Поворот фигурки тетрамино
	void rotate();
	// Вывод фигурок тетрамино на экран
	void print_tetramino(RenderWindow &window);
	// Создание новой фигурки тетрамино
	void add_tetramino(Tetramino &tetramino, double &delay, Sprite &sprite_tiles);

	/* Геттеры */

	// Возвращение координат блоков фигурки тетрамино
	std::array<Point, 4> get_sprite_cords() const;
	// Вовзращение спрайта фигурки тетрамино
	Sprite get_sprite_tetramino() const;
};