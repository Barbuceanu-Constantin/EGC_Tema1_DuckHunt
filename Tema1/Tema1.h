#pragma once

#include "components/simple_scene.h"
#include "Duck.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;
        int lives, bullets;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        
        void Evadare();
        void Reflexie();
        void WingRotate();
        void InitDuck();
        void RenderObjects();
        void FallingDown();
        void UpdateBodyPoints(float fx, float fy);
        void CreateComponents();
        void InitAngle();
        void InitMatrixes();
        void InitBodyPoints();
        void InitOthers();
        void InitBackground();
        void InitBackgroundComponent(char *name);

     protected:
    };
}   // namespace m1
