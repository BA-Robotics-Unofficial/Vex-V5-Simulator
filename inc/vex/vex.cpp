#include"vex.h"
#include<SDL.h>
#include<vector>
#include<SDL_image.h>

using namespace vex;

#include <iostream>

void brain::lcd::p_drawLine(SDL_Renderer* render, int x1, int y1, int x2, int y2, int w)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	int e2;
	int x = x1, y = y1;

	// Generate vector of rects
	std::vector<SDL_FRect> rects;

	while (true) {
		// Add rectangle at the current point to the vector
		rects.push_back({
			(float)(x - w / 2) - m_origin_x,
			(float)(y - w / 2) - m_origin_y,
			(float)w,
			(float)w
			});

		// Check if we've reached the end point
		if (x == x2 && y == y2)
			break;

		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x += sx;
		}
		if (e2 < dx) {
			err += dx;
			y += sy;
		}
	}

	// Render all rectangles at once
	SDL_RenderFillRects(render, rects.data(), rects.size());
}

// Function to extract Alpha component
inline uint8_t getAlpha(uint32_t color) {
	return (color >> 24) & 0xFF;
}

// Function to extract Red component
inline uint8_t getRed(uint32_t color) {
	return (color >> 16) & 0xFF;
}

// Function to extract Green component
inline uint8_t getGreen(uint32_t color) {
	return (color >> 8) & 0xFF;
}

// Function to extract Blue component
inline uint8_t getBlue(uint32_t color) {
	return color & 0xFF;
}

//Color
color::color()
{
	this->m_argb = 0xff000000;
}

color::color(u32 color)
{
	this->m_argb = color;
}

color::color(u8 r, u8 g, u8 b)
{
	this->m_argb = (static_cast<uint32_t>(255) << 24) | (static_cast<uint32_t>(r) << 16) | (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(b);
}

u32 color::rgb() const
{
	return this->m_argb;
}

u32 color::rgb(u32 value)
{
	this->m_argb = value;
	return this->m_argb;
}

u32 color::rgb(u8 r, u8 g, u8 b)
{
	this->m_argb = (static_cast<uint32_t>(255) << 24) | (static_cast<uint32_t>(r) << 16) | (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(b);
	return this->m_argb;
}


//Brain lcd

brain::lcd::lcd()
{
	m_running = true;
	m_window = SDL_CreateWindow("Brain Screen", 480, 272, SDL_WINDOW_HIGH_PIXEL_DENSITY);
	if (m_window == nullptr)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
	}

	m_renderer = SDL_CreateRenderer(m_window, nullptr, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr)
	{
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
	}

	m_render_mutex = SDL_CreateMutex();
}

brain::lcd::~lcd()
{
	SDL_DestroyWindow(m_window);
}

void brain::lcd::setPenColor(const color& c)
{
	m_pen_color = c.rgb();
}

void brain::lcd::setFillColor(const color& c)
{
	m_fill_color = c.rgb();
}

void brain::lcd::setPenWidth(u32 w)
{
	m_pen_width = w;
}

void brain::lcd::clearScreen()
{
	SDL_LockMutex(m_render_mutex);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	SDL_UnlockMutex(m_render_mutex);
}

void brain::lcd::clearScreen(const color& c)
{
	SDL_LockMutex(m_render_mutex);
	SDL_SetRenderDrawColor(m_renderer, getRed(c.rgb()), getGreen(c.rgb()), getBlue(c.rgb()), getAlpha(c.rgb()));
	SDL_RenderClear(m_renderer);
	SDL_UnlockMutex(m_render_mutex);
}

void brain::lcd::drawPixel(i32 x, i32 y)
{
	SDL_LockMutex(m_render_mutex);
	SDL_SetRenderDrawColor(m_renderer, getRed(m_pen_color), getGreen(m_pen_color), getBlue(m_pen_color), getAlpha(m_pen_color));
	SDL_RenderPoint(m_renderer,x-m_origin_x,y-m_origin_y);
	SDL_UnlockMutex(m_render_mutex);
}

void brain::lcd::drawLine(i32 x1, i32 y1, i32 x2, i32 y2)
{
	SDL_LockMutex(m_render_mutex);
	SDL_SetRenderDrawColor(m_renderer, getRed(m_pen_color), getGreen(m_pen_color), getBlue(m_pen_color), getAlpha(m_pen_color));
	p_drawLine(m_renderer, x1, y1, x2, y2, m_pen_width);
	SDL_UnlockMutex(m_render_mutex);
}

void brain::lcd::drawRectangle(i32 x, i32 y, i32 w, i32 h)
{
	SDL_LockMutex(m_render_mutex);
	SDL_FRect rect = {};
	rect.x = x - m_origin_x;
	rect.y = y - m_origin_y;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawColor(m_renderer, getRed(m_fill_color), getGreen(m_fill_color), getBlue(m_fill_color), getAlpha(m_fill_color));
	SDL_RenderFillRect(m_renderer, &rect);
	SDL_SetRenderDrawColor(m_renderer, getRed(m_pen_color), getGreen(m_pen_color), getBlue(m_pen_color), getAlpha(m_pen_color));
	p_drawLine(m_renderer, x, y, x + w, y, m_pen_width);
	p_drawLine(m_renderer, x, y + h, x + w, y+h, m_pen_width);

	p_drawLine(m_renderer, x, y, x, y+h, m_pen_width);
	p_drawLine(m_renderer, x+w, y, x+w, y + h, m_pen_width);
	SDL_UnlockMutex(m_render_mutex);
}

void brain::lcd::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			m_running = false;
		}
		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				m_running = false;
			}
		}
	}
}

bool brain::lcd::render()
{
	return SDL_RenderPresent(m_renderer);
}

//Brain
brain::brain()
{
	
}

//miscelanious
void vex::wait(double time, timeUnits unit)
{
	if (unit == seconds)
	{
		time *= 1000;
	}
	SDL_Delay(time);
}
