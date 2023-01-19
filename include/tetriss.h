#pragma once
#include "tetramino.h"

// Игра тетрис
class Tetris
{
private:
	static const int32_t m_width = 11;									// ширина игрового поля
	static const int32_t m_height = 16;									// высота игрового поля

	Tetramino m_tetramino;												// фигурка тетрамино
	std::array<std::array <Sprite, m_height + 1>, m_width + 1> m_fill;	// упавшие фигурки

	double m_delay;														// задержка по времени перемещения
	double m_timer;														// сумма времени работы программы

	std::array<std::array <bool, m_height + 1>, m_width + 1> m_field;	// игровое поле (true - ячейка занята, false - свободна)

	static int32_t m_total_points;										// кол-во очков за каждый собранный ряд

	// Проверка, что одна фигурка тетрамино соприкоснулась с другой и был достигнут конец поля
	bool is_tetramino_touched();

public:
	/* Конструкторы */

	// Конструктор по умолчанию
	Tetris();
	// Конструктор для генерации игрового поля тетриса
	Tetris(Sprite &sprite_tiles);

	/* Методы */

	// Отработка событий при нажатии клавиш
	void tetris_event(RenderWindow &window);
	// Проверка тетрамино на выход за границы игрового поля
	void check(Tetramino &temp_tetramino);
	// Перемещение фигурки тетрамино вниз
	void tetris_down(Clock &clock);
	// Вывод всех фигурок тетрамино
	void tetris_print(RenderWindow &window, Sprite &sprite_tiles);
	// Вывод очков фигурок тетрамино
	void points_print(RenderWindow &window, Font &font) const;
	// Добавление на поле новой фигурки тетрамино
	void tetris_condition_add(RenderWindow &window, Sprite &sprite_tiles);
	// Поиск собранной линии
	void search_delete_lines();
	// Удаление собранной линии
	void delete_lines(size_t y);
	// Отображение конца игры
	void game_over(RenderWindow &window, Font &font, Sprite &sprite_background) const;
};