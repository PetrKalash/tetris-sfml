#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tetramino.h"
#include "Tetris.h"
#include <array>

using namespace sf;

int main(int *argv, char argc[])
{
	//=================Сглаживание===================
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	//===============================================

	//================Содержимое окна================
	// Окно программы
	RenderWindow window(VideoMode(320, 480), "Tetris");
	// Текстура фигур тетриса
	Texture texture_tiles, texture_background;
	// Загрузка текстур
	texture_tiles.loadFromFile("resources\\img\\tiles.png");
	texture_background.loadFromFile("resources\\img\\background-tetris.jpg");
	// Создание спрайтов из текстур
	Sprite sprite_tiles(texture_tiles), sprite_background(texture_background);
	//===============================================

	//====================Звуки======================
	// Загрузка и запуск фоновой музыки
	Music music;
	music.openFromFile("resources\\music\\tetris_music.ogg"); //загружаем файл
	music.play();
	//===============================================

	//=================Часы-таймер===================
	Clock clock;
	//===============================================

	//===================Тетрис======================
	Tetris tetris_game(sprite_tiles);		// запуск игры тетрис
	//===============================================

	//===================Шрифты======================
	Font font;								// шрифт для очков
	font.loadFromFile("resources\\fonts\\NunitoSans-Regular.ttf");
	//===============================================

	// Выполняем программу до тех пор, пока не выйдем из нее
	while (window.isOpen()) {
		// Задний фон приложения
		window.clear(Color::White);
		window.draw(sprite_background);

		tetris_game.tetris_event(window);
		tetris_game.tetris_down(clock);
		tetris_game.tetris_print(window, sprite_tiles);
		tetris_game.tetris_condition_add(window, sprite_tiles);
		tetris_game.points_print(window, font);
		tetris_game.search_delete_lines();
		tetris_game.game_over(window, font, sprite_background);

		// Отрисовка содержимого окна
		window.display();
	}
	return 0;
}