#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windorWidth{384};
    const int windowHeight{384};
    InitWindow(windorWidth, windowHeight, "Born2Slay!");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0};
    const float mapScale{4.0f};

    Character war{windorWidth, windowHeight};

    Prop props[2]{
            Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
            Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
        };

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for (auto enemy : enemies)
    {
        enemy->setTarget(&war);
    }
    goblin.setTarget(&war);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(war.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        for (auto prop : props)
        {
            prop.Render(war.getWorldPos());
        }

        if (!war.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string warHealth = "Health: ";
            warHealth.append(std::to_string(war.getHealth()), 0, 5);
            DrawText(warHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        war.tick(GetFrameTime());
        if (war.getWorldPos().x < 0.f ||
            war.getWorldPos().y < 0.f ||
            war.getWorldPos().x + windorWidth > map.width * mapScale ||
            war.getWorldPos().y + windowHeight > map.height * mapScale)
            {
                war.undoMovement();
            }

            for (auto prop : props)
            {
               if (CheckCollisionRecs(prop.getCollisionRec(war.getWorldPos()), war.GetCollisionRec()))
               {
                    war.undoMovement();
               }
            }
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
               if (CheckCollisionRecs(enemy->GetCollisionRec(), war.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                } 
            }
            
        }
        EndDrawing();
    }
    CloseWindow();
}