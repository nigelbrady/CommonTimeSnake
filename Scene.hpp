#pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace CTG
{    
    class Scene
    {
        private:
            std::string name;

        public:
            Scene(std::string name);

            static int sceneWidth;
            static int sceneHeight;

            static Scene *currentScene;
            static Scene *titleScene;
            static Scene *gameScene;

            std::string GetName();

            virtual bool Event(SDL_Event e);
            virtual void Update(int delta);
            virtual void Draw(SDL_Renderer *ren);

            virtual void OnSceneStarted();
            virtual void OnSceneEnded();

            static void ChangeScene(Scene *newScene);
    };

    
}
