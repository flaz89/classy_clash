#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) : 
windowWidth(winWidth),
windowHeight(winHeight) {
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos() {
    return Vector2 {
        static_cast<float>(windowWidth) * 0.5f - (width * 0.5f) * scale,
        static_cast<float>(windowHeight) * 0.5f - (height * 0.5f) * scale
    };
}

void Character::tick(float deltaTime) {

    if (!getAlive()) return;
   
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) velocity.x -= 1.0;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) velocity.x += 1.0;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) velocity.y -= 1.0;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 swordOrigin{};
    Vector2 swordOffset{};
    float rotation{};

    if (rightLeft > 0.f) {
        swordOrigin = {0.f, weapon.height * scale};
        swordOffset = {33.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + swordOffset.x,
             getScreenPos().y + swordOffset.y - weapon.height * scale, 
             weapon.width * scale, 
             weapon.height * scale
            };
        rotation = 35.f;
        IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? rotation = 35.f : rotation = 0.f;
    } else {
        swordOrigin = {weapon.width * scale, weapon.height * scale, };
        swordOffset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + swordOffset.x - weapon.width * scale,
             getScreenPos().y + swordOffset.y - weapon.height * scale, 
             weapon.width * scale, 
             weapon.height * scale
            };
        IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? rotation = -35.f : rotation = 0.f;
    }


    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + swordOffset.x, getScreenPos().y + swordOffset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, swordOrigin, rotation, WHITE);

    //DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}

void Character::takeDamage(float damage) {
    this->health -= damage;
    if (health <= 0.f) {
        this->setAlive(false);
    }
}


