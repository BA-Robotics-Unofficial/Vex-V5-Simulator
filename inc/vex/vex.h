#pragma once
#include"utils.h"
#include<SDL.h>
#include<SDL_image.h>
namespace vex
{
	enum fontType
	{
		mono12,
		mono15,
		mono20,
		mono30,
		mono40,
		mono60,
		prop20,
		prop30,
		prop40,
		prop60
	};
	enum timeUnits
	{
		msec,
		seconds
	};

	struct color
	{
	private:
		u32 m_argb;
	public:
		color();
		color(u32 value);
		color(u8 r, u8 g, u8 b);
		~color() = default;

		u32 rgb() const;
		u32 rgb(u32 value);
		u32 rgb(u8 r, u8 g, u8 b);

		void operator=(u32 value);
		operator u32() const;
	};

	class brain
	{
	private:
		class lcd
		{
		private:
            SDL_Texture* m_font;
			SDL_Mutex* m_render_mutex;
			SDL_Renderer* m_renderer;
			SDL_Window* m_window;
			//Console
			i32 m_row;
			i32 m_max_rows;
			i32 m_row_height = 20;
			i32 m_col;
			i32 m_max_col;
			i32 m_col_width = 10;
			char m_textstr[48*24];

			//Drawing
			i32 m_pen_width = 1;

			i32 m_origin_x;
			i32 m_origin_y = -32;

			i32 m_pen_color;
			i32 m_fill_color;

			i32 rowToPixel(i32 row);
			i32 colToPixel(i32 col);
			void p_drawLine(SDL_Renderer* render, int x1, int y1, int x2, int y2, int w);
            void p_drawChar(SDL_Renderer* render, int x, int y, char c);
		public:
			bool m_running;

			lcd();
			~lcd();

			//Console
			void clearLine(i32 l);
			void print(const char* text ...);
			void setCursor(i32 x, i32 y);
			void setFont(fontType font);
			void newLine();

			//Console gets
			i32 column();
			i32 row();

			//Pixels
			void setPenColor(const color& c);
			void setFillColor(const color& c);
			void setPenWidth(u32 w);
			void clearScreen();
			void clearScreen(const color& c);
			void drawPixel(i32 x, i32 y);
			void drawLine(i32 x1, i32 y1, i32 x2, i32 y2);
			void drawRectangle(i32 x, i32 y, i32 w, i32 h);
			void drawCircle(i32 x, i32 y, i32 r);
			void setOrigin(i32 x, i32 y);

			//Management
			void update();
			bool render();
		};
	public:
		lcd Screen = {};
		brain();
	};
	void wait(double time, timeUnits unit);
}