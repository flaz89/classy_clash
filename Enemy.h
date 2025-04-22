#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter {
private:
    Character* target{};
    float damageperSec{10.f};
    float radius{25.f};
public:
    Enemy(Vector2 pos, Texture2D tex_idle, Texture2D tex_run);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* enemyTarget) {target = enemyTarget;}
    virtual Vector2 getScreenPos() override;

};

