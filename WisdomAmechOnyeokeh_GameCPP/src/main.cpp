#include <raylib.h>
#include "BaseChar.h"
#include "Player.h"
#include "Platforms.h"
#include <vector>
#include "Collectible.h"
#include "Obstacle.h"

void DebugDrawLine(int, int);

enum GameState
{
    MENU,
    ABOUT,
    GAME
};

int main(){

    GameState currentState = MENU;
    bool isGameRunning = false;
    
    const int windowWidth {1280};
    const int windowHeight {720};
    constexpr const char* platformAStatic = "assets/textures/props/Grey Off.png";
    constexpr const char* platformAAnimation = "assets/textures/props/Grey On (32x8).png";
    constexpr const char* fruitA = "assets/textures/props/Apple.png";
    constexpr const char* fruitB = "assets/textures/props/Orange.png";
    constexpr const char* fruitC = "assets/textures/props/Cherries.png";
    constexpr const char* sawPath = "assets/textures/props/On (38x38).png";
    
    InitWindow(windowWidth, windowHeight, "Mechi's Fruit Ninja");

    // Background and Backgorund Collision
    Texture2D dynamicBackground {LoadTexture("assets/textures/bg/Green.png")};
    float panX{};
    float panY {};
    int dynamicBgScale{4};
    Rectangle dynamicBgSource{panX, panY, static_cast<float>(windowWidth)/dynamicBgScale, static_cast<float>(windowHeight)/dynamicBgScale};
    Rectangle dynamicBgDest{0.0f,0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight)};
    SetTextureWrap(dynamicBackground, TEXTURE_WRAP_REPEAT); 

    Texture2D background {LoadTexture("assets/textures/bg/WorldMap.png")};
    Image wallCollisionMap {LoadImage("assets/textures/bg/WorldMap_Alpha.png")};
    const float mapScale {4.0f};

    
    Vector2 startPoint {800, 3000};
    Player playerChar{startPoint};

    // Create Cam and set target
    Camera2D camera {};
    camera.target = {playerChar.getPos()};
    camera.offset = (Vector2){ windowWidth/2.0f, windowHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.6f;

    // setup PLATFORMS
    Vector2 platformLocs[] = {{1200, 2900},{1900,3000}, {2352, 2600}, {650,2200},{650,1950}, {650,1700}, 
                             {650,1450}, {2000,1750},{2420,1750}, {2400,1290},{3050,2098}, {3502,2500}};
    
    std::vector<Platforms> platforms;
    platforms.reserve(sizeof(platformLocs)/sizeof(platformLocs[0]));

    for (const auto& loc : platformLocs){
        platforms.emplace_back(platformAStatic, platformAAnimation, loc);
    }
    


    // Setup Fruits
    Vector2 appleLocs[] = {{2375, 3000}, {2450, 3000}, {2550, 3000},{640,2110},{640,1815},{640,1530},{640,1245},{2750,2400},{2850,2600}};
    int totalApples = sizeof(appleLocs)/sizeof(appleLocs[0]);
    
    Vector2 orangeLocs[] = {{1160, 2750} , {3380,2950},{1564,1100}, {1750, 700},{2250,700}, {2550,700}, {3545,880},{2750,2300},{2750,2600}};
    int totalOranges = sizeof(orangeLocs)/sizeof(orangeLocs[0]);
    
    Vector2 cherriesLocs[] = {{2350, 2200}, {2350, 2100},{2950,880}, {2950,1080},{2750,2200}, {2750,2500},{2950,2600}, {3550,1520} , {3550,1620}};
    int totalCherries =  sizeof(cherriesLocs)/sizeof(cherriesLocs[0]);

    std::vector<Collectible> fruits;
    int totalFruitCount {totalApples+ totalOranges + totalCherries};
    fruits.reserve(totalFruitCount);

    for (const auto& fruitloc : appleLocs){
        fruits.emplace_back(fruitA, fruitloc);
    }
    for (const auto& fruitloc :orangeLocs){ 
        fruits.emplace_back(fruitB,fruitloc);
    }
    for (const auto& fruitloc :cherriesLocs){ 
        fruits.emplace_back(fruitC,fruitloc);
    }


    // saw sprites

    Vector2 sawLocs[] = {{1600, 3200},{1150,2440}, {1340,1472}, {2840, 3120},{2950,1000}};
    int totalSaws = sizeof(sawLocs)/sizeof(sawLocs[0]);
    std::vector<Obstacle> saws;
    saws.reserve(totalSaws);

    for (int i = 0; i <totalSaws; i++){
        saws.emplace_back(sawPath, sawLocs[i]);
        if (i < 0){
            // wont move
        }
        else if (i < 3){
            saws.back().setMovingSide(true);
        }
        else{
            saws.back().setMovingUp(true);
        }
    }

    
    SetTargetFPS (60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        float dT = GetFrameTime();

        // Draw Looping Background
        panY -= 10.0f * dT;
        dynamicBgSource.y = panY;
        DrawTexturePro(dynamicBackground, dynamicBgSource, dynamicBgDest, {}, 0.0f,WHITE);
        // DebugDrawLine(windowWidth,windowHeight);

        if (currentState == MENU)
        {
            // MEnu State
            DrawText("Mechi's Fruit Ninja", windowWidth/2 - 320, 150, 60, RED);

            if(isGameRunning){
                DrawText("Press ENTER to Continue", windowWidth/2 - 135, 340, 20, RED);
            }
            else{
                DrawText("Press ENTER to Start", windowWidth/2 - 115, 340, 20, RED);
            }
            DrawText("Press A for About", windowWidth/2 - 100, 380, 20, RED);
            DrawText("Press ESC to Quit", windowWidth/2 - 100, 420, 20, RED);

            if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){
                currentState = GAME;
            }

            if (IsKeyPressed(KEY_A) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
                currentState = ABOUT;
            }

            if (IsKeyPressed(KEY_ESCAPE)){
                CloseWindow();
            }
        }

        else if (currentState == ABOUT)
        {
            DrawText("ABOUT", windowWidth/2 - 70, 190, 40, RED);

            DrawText("Collect all fruits and avoid the saws to win.", windowWidth/2 - 230, 340, 20, RED);
            DrawText("Press BACKSPACE to return", windowWidth/2 - 160, 380, 20, RED);
            DrawText("Created by Wisdom Amechi Onyeokeh | April 2026 | Submission for University of Staffordshire", windowWidth/2 - 485, windowHeight-50, 20, BLACK);

            if (IsKeyPressed(KEY_BACKSPACE)|| IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
            {
                currentState = MENU;
            }
        }

        else if (currentState == GAME)
        {
            isGameRunning = true;

            //Game LOOP
            BeginMode2D(camera);
    
            //DebugPosition
            // Vector2 pPos = playerChar.getPos();
            // DrawText(TextFormat("%.0f, %.0f", pPos.x, (pPos.y + 74)), (pPos.x - 90), pPos.y - 90, 60, RED);

            
            if (playerChar.getLife() > 0 && playerChar.getFruitCount() != totalFruitCount){
                playerChar.tick(GetFrameTime(),wallCollisionMap, mapScale,platforms);
            }
            

            for(auto& platform : platforms){
                platform.render();
            }

            for (auto& s : saws){
                s.render(dT);
            }

            DrawRectangle(-1200,0,1400,4500,Color{33,31,48,255});
            DrawRectangle(background.width*mapScale,0,1000,4500,Color{33,31,48,255});
            DrawTextureEx(background,Vector2 {0,0},0.0f,mapScale,WHITE);
            

            
            for ( auto& f : fruits){
                f.render(dT);
            }
            
            for (auto& f : fruits)
            {
                if (!f.getIsHit())
                {
                    if (CheckCollisionRecs(playerChar.getCollisionRec(), f.getCollisionRec()))
                    {
                        f.setHitState(true);
                        playerChar.addFruit(); 
                    }
                }
            }

            
            camera.target = {playerChar.getPos()};

            if (IsKeyPressed(KEY_BACKSPACE) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)){
                currentState = MENU;
            }

            EndMode2D();

            // check ssaw collision
            if (playerChar.getLife() > 0){
                bool isTouchingSaw = false;
                for (auto& s: saws)
                {

                    if (CheckCollisionRecs(playerChar.getCollisionRec(), s.getCollisionRec()))
                    {
                        isTouchingSaw = true;

                        if (!playerChar.isReceivingDamage){
                            playerChar.reduceHealth();
                            playerChar.isReceivingDamage = true;
                        }

                        DrawText("OUCH", (windowWidth/2) - 50, windowHeight/2, 30, WHITE);
                    }
                }

                // if not hitting any saw
                if (!isTouchingSaw){
                    playerChar.isReceivingDamage = false;
                }
            }
            else{
                DrawText("YOU DIED", windowWidth/2 - 100, windowHeight/2, 50, RED);
                DrawText("Press R to Restart", windowWidth/2 - 80, windowHeight/2 + 60, 20, GRAY);
            }

            
            if(playerChar.getLife() < 1 && (IsKeyPressed(KEY_R) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))){
                // currentState = MENU;
                WaitTime(0.3f);
                playerChar.reset(startPoint);
                for (auto& f : fruits){
                    f.setHitState(false);
                }
  
            }

            if(playerChar.getFruitCount() == totalFruitCount){
                DrawText("YOU WIN", windowWidth/2 - 100, windowHeight/2, 50, BLUE);
                DrawText("Press R to Restart", windowWidth/2 - 80, windowHeight/2 + 60, 20, GRAY);
                if(IsKeyPressed(KEY_R) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){
                    WaitTime(0.3f);
                    playerChar.reset(startPoint);
                    for (auto& f : fruits){
                        f.setHitState(false);
                    }
                }
            }
            
            DrawText(TextFormat("Life: %i", playerChar.getLife()), 12, 12 , 20, RED);
            DrawText(TextFormat("Fruits: %i", playerChar.getFruitCount()), windowWidth - 100 , 12, 20, RED);
        }
        EndDrawing();
    }
    

    UnloadTexture(background);
    UnloadTexture(dynamicBackground);
    CloseWindow();
    return 0;
}

void DebugDrawLine(int windowWidth, int windowHeight){
    DrawLine(windowWidth/2, 0, windowWidth/2, windowHeight,BLACK);
    // DrawLine(0,(windowHeight/2) + 65,windowWidth, (windowHeight/2) + 65, BLACK);
    DrawLine(0,(windowHeight/2),windowWidth, (windowHeight/2), BLACK);
}