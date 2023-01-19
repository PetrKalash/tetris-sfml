#include "tetris.h"

int32_t Tetris::m_total_points = 0;

Tetris::Tetris() : m_tetramino{}, m_delay{}, m_timer{}, m_field{}, m_fill{}{}

Tetris::Tetris(Sprite &sprite_tiles) : m_tetramino(sprite_tiles), m_delay{0.3}, m_timer{}, m_field{false}, m_fill{}{}

bool Tetris::is_tetramino_touched()
{
	std::array<Point, 4> temp_cord = m_tetramino.get_sprite_cords();

	// Как только одна из фигур тетрамино достигла конца поля или фигурки соприкасаются, начинаем новую генерацию тетрамино
	for (size_t i {}; i < 4; ++i) {
		if (temp_cord.at(i).y == m_height || m_field.at(temp_cord.at(i).x).at(temp_cord.at(i).y+1)) return true;
	}
	return false;
}

void Tetris::tetris_event(RenderWindow &window)
{
	// Копия фигурки тетрамино на случай, если основная фигурка выйдет за пределы игрового поля
	Tetramino temp_tetramino = m_tetramino;

	Event event;
	while (window.pollEvent(event)) {
		// Обработка нажатия кнопки выхода из программы. Если был нажат крестик, выходим из окна
		if (event.type == Event::Closed) window.close();

		// Обработка нажатия стрелок на клавиатуре
		if (event.type == Event::KeyPressed) {
			// Если пользователь нажал клавишу вверх, поворачиваем фигуру
			if (event.key.code == Keyboard::Up) m_tetramino.rotate();

			// Если пользователь нажал клавишу вправо, смещаем все блоки по x на +1
			else if (event.key.code == Keyboard::Right) m_tetramino.move_right();

			// Если пользователь нажал клавишу влево, смещаем все блоки по x на -1
			else if (event.key.code == Keyboard::Left) m_tetramino.move_left();

			// Если пользователь нажал клавишу вниз, то ускоряем падение блоков
			else if (Keyboard::isKeyPressed(Keyboard::Down)) m_tetramino.fast_down(m_delay);
		}
	}

	// Как только мы переместили фигурку тетрамино, делаем обязательную проверку на то, что она не вышла за пределы
	check(temp_tetramino);
}

void Tetris::check(Tetramino &temp_tetramino)
{
	// Временная переменная, хранящая координаты тетрамино
	std::array<Point, 4> temp = m_tetramino.get_sprite_cords();

	for (size_t i {}; i < 4; ++i) {
		// Если фигурка тетрамино вышла за границы игрового поля
		if (temp.at(i).x > m_width || temp.at(i).x < 0 || m_field.at(temp.at(i).x).at(temp.at(i).y) == true) {
			// Возвращаем ее изначальное положение на игровом поле
			m_tetramino = temp_tetramino;
		}
	}
}

// Перемещение фигурки тетрамино вниз
void Tetris::tetris_down(Clock &clock)
{
	// Получаем время, прошедшее с начала отсчета и конвертируем его в секунды
	float time = clock.getElapsedTime().asSeconds(); clock.restart();
	// Прибавляем все время
	m_timer += time;

	// Как только прошло заданное время
	if (m_timer > m_delay) {
		// Перемещаем фигурку тетрамино вниз (по оси y на одну единицу, т.к. вертикаль)
		m_tetramino.move_down();
		// Обнуляем таймер и начинаем заново отсчет времени
		m_timer = 0;
	}
}

// Вывод фигурок тетрамино на поле
void Tetris::tetris_print(RenderWindow &window, Sprite &sprite_tiles)
{
	// После того, как одна фигурка была перемещена вниз после заданного промежутка времени, выводим ее новое положение
	m_tetramino.print_tetramino(window);

	// И отрисовываем все фигурки тетрамино, которые уже упали на поле
	for (size_t x{}; x < m_fill.size(); x++)
		for (size_t y{}; y < m_fill.at(x).size(); y++)
			// Отрисовка квадратика тетриса
			window.draw(m_fill.at(x).at(y));
}

void Tetris::points_print(RenderWindow &window, Font &font) const
{
	// Вывод очков игры - создаем текст, указываем размер шрифта
	Text points(std::to_string(m_total_points), font, 40);
	// Цвет текста - белый
	points.setFillColor(Color::White);
	// Координаты установки текста
	points.setPosition(240, 410);
	// Отрисовка текста
	window.draw(points);
}

void Tetris::tetris_condition_add(RenderWindow &window, Sprite &sprite_tiles)
{
	std::array<Point, 4> temp_cord = m_tetramino.get_sprite_cords();
	Sprite temp_sprite = m_tetramino.get_sprite_tetramino();

	if (is_tetramino_touched()) {
		for (size_t i{}; i < 4; ++i) {
			// Как только фигурка установлена на игровом поле, мы присваиваем заполненным ячейкам значение true
			m_field.at(temp_cord.at(i).x).at(temp_cord.at(i).y) = true;
			// Добавляем в массив ячеек спрайт фигурки тетрамино
			m_fill.at(temp_cord.at(i).x).at(temp_cord.at(i).y) = temp_sprite;

			//Установка позиции квадратика тетриса (18x18 - размер квадратика)
			m_fill.at(temp_cord.at(i).x).at(temp_cord.at(i).y).setPosition(temp_cord.at(i).x * 18.f, temp_cord.at(i).y * 18.f);
			//Смещение фигурки от изначального положения
			m_fill.at(temp_cord.at(i).x).at(temp_cord.at(i).y).move(36, 52);
		}
		// Начинаем добавление новой фигурки тетрамино на игровое поле
		m_tetramino.add_tetramino(m_tetramino, m_delay, sprite_tiles);
	}
}

void Tetris::search_delete_lines()
{
	// Удаление линии с полным заполнением фигурок тетрамино
	for (size_t y{}; y < m_height + 1; ++y) {
		
		int32_t count{};		// заполненные фигурки тетрамино
		
		for (size_t x {}; x < m_width + 1; ++x) {
			// Если в строке y мы нашли заполненную координату x, увеличиваем счетчик
			if (m_field.at(x).at(y)) count++;
		}
		// Перебрав всю строку, мы проверяем, заполнена ли она полностью фигурками тетрамино, и если да, то удаляем
		if (count == m_width + 1) delete_lines(y);
	}
}

void Tetris::delete_lines(size_t line)
{
	// Перебираем все строки, которые нам нужно будет сдвинуть вниз
	for (size_t y{line}; y > 0; --y) {
		// Перебираем все координаты x для сдвига
		for (size_t x {}; x < m_width + 1; ++x) {
			m_field.at(x).at(y) = m_field.at(x).at(y - 1);
			m_fill.at(x).at(y) = m_fill.at(x).at(y - 1);
			m_fill.at(x).at(y).move(0, 18);
		}
	}
	// После того, как мы удалили линию, прибавляем кол-во заработанных очков
	m_total_points += 10;
}

void Tetris::game_over(RenderWindow &window, Font &font, Sprite &sprite_background) const
{
	std::array<Point, 4> temp = m_tetramino.get_sprite_cords();

	for (size_t i {}; i < 4; ++i) {
		if (m_field.at(temp.at(i).x).at(temp.at(i).y)) {
			Text game("Game Over!", font, 40);
			game.setStyle(Text::Bold);
			game.setFillColor(Color::Red);
			game.setPosition(m_width * 3.5, m_height * 12);
			window.draw(game);
			sprite_background.setColor(sf::Color(50, 50, 50, 128)); 
		}
	}
}