#pragma once
#include "Canvas.h"
#include "../Math/Ray.h"
#include "../Math/Color.h"
#include <SDL.h>

class Object;
class Scene;

class Renderer
{
public:
	Renderer() = default;
	void Render(Canvas& canvas, Object* object);
	bool Initialize();
	void Shutdown();
	bool CreateWindow(int width, int height);

	void CopyCanvas(const Canvas& canvas);
	void Present();

	friend class Canvas;

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };

	color3 GetBackgroundFromRay(const Ray& ray);
};