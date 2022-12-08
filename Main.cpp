#include <iostream>
#include "Renderer/Renderer.h"
#include "Renderer/Canvas.h"
#include "Object/Sphere.h"
#include "Object/Plane.h"
#include "Object/Scene.h"
#include "Renderer/Camera.h"

int main(int, char**)
{
    const int width = 1000;
    const int height = 500;
    const int samples = 100;

    Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow(width, height);

    Canvas canvas(width, height, renderer);
    Camera camera({ 0, 1, 2 }, { 0, 0, 0 }, { 0, 1, 0 }, 70.0f, width / (float)height);
    Scene scene;

    scene.AddObject(std::make_unique<Sphere>(glm::vec3{ 0, 0, -1 }, 0.5f, std::make_unique<Lambertian>(color3{ 0, 1, 0 })));
    scene.AddObject(std::make_unique<Plane>(glm::vec3{ 0, -0.5, 0 }, glm::vec3{ 0, 1, 0 }, std::make_unique<Lambertian>(color3{ 0.2f, 0.2f, 0.2f })));

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
        {

            quit = true;
            break;
        }

        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;
            }
            break;
        }
        }

        canvas.Clear({ 0, 0, 0, 1 });

        renderer.Render(canvas, scene, camera, samples);

        canvas.Update();

        renderer.CopyCanvas(canvas);

        renderer.Present();
    }

    renderer.Shutdown();
    return 0;
}