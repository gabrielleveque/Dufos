#include <iostream>
#include <raylib.h>
#include <vector>
#include <algorithm>
#include "Registry/Registry.hpp"
#include "Entity/Entity.hpp"
#include "Component/Position.hpp"
#include "Component/Sprite.hpp"
#include "Component/Scale.hpp"
#include "Component/ZIndex.hpp"

int main()
{
    InitWindow(800, 600, "ECS Test - Sprite Rendering");
    SetTargetFPS(60);

    Registry registry;

    Entity grass1 = registry.createEntity("Grass1");
    Entity grass2 = registry.createEntity("Grass2");
    Entity stone = registry.createEntity("Stone");
    Entity lineMap = registry.createEntity("LineMap");
    Entity water = registry.createEntity("Water");

    grass1.add<Position>(100.0f, 100.0f);
    grass1.add<Sprite>("assets/Grass1.png");
    grass1.add<Scale>(1.0f, 1.0f);
    grass1.add<ZIndex>(0);

    grass2.add<Position>(250.0f, 100.0f);
    grass2.add<Sprite>("assets/Grass2.png");
    grass2.add<Scale>(1.5f, 1.5f);
    grass2.add<ZIndex>(2);

    stone.add<Position>(400.0f, 100.0f);
    stone.add<Sprite>("assets/Stone.png");
    stone.add<Scale>(2.0f, 2.0f);
    stone.add<ZIndex>(3);

    lineMap.add<Position>(100.0f, 300.0f);
    lineMap.add<Sprite>("assets/LineMap.png");
    lineMap.add<Scale>(1.0f, 1.0f);
    lineMap.add<ZIndex>(1);

    water.add<Position>(550.0f, 100.0f);
    water.add<Sprite>("assets/Water.png", 48, 36, 5, 0.18f, 5);
    water.add<Scale>(2.0f, 2.0f);
    water.add<ZIndex>(0);

    std::vector<Entity> entities = {grass1, grass2, stone, lineMap, water};

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        for (auto& entity : entities)
        {
            Sprite* sprite = entity.get<Sprite>();
            if (sprite)
            {
                sprite->updateAnimation(dt);
            }
        }

        std::sort(entities.begin(), entities.end(), [](Entity& a, Entity& b)
        {
            ZIndex* zIndexA = a.get<ZIndex>();
            ZIndex* zIndexB = b.get<ZIndex>();

            if (!zIndexA && !zIndexB) return false;
            if (!zIndexA) return true;
            if (!zIndexB) return false;

            return zIndexA->getIndex() < zIndexB->getIndex();
        });

        BeginDrawing();
        ClearBackground(DARKGRAY);

        for (auto& entity : entities)
        {
            Position* pos = entity.get<Position>();
            Sprite* sprite = entity.get<Sprite>();
            Scale* scale = entity.get<Scale>();

            if (pos && sprite && scale)
            {
                sprite->drawSprite(*pos, *scale);
            }
        }

        DrawText("ECS Test - Sprite Rendering", 10, 10, 20, DARKGRAY);
        DrawFPS(10, 550);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
