# **Space Invaders UML Summary**
This design plans to use a layered, object-oriented architecture so that each class has one clear responsibility and the game remains maintainable as features grow. Engine owns the game loop (input->update->render) and SDL runtime context. Game flow is modeled with Scene states (such as TitleScene (required), PlayScene, and CreditsScene (required)), so menu logic never mixes with gameplay logic. This makes transitions explicit too. 

Gameplay entities inherit from GameObject, but behavior is mostly added through Component composition (Transform, Sprite, Collider, Velocity, Health, Weapon). This makes it so that deep inheritance isn't used, and also lets us reuse behavior across entities like players, enemies, bullets and barriers. PlayerShip, Enemy, Projecticle, represent different identities, which is why they are not reusable, as reusable mechanics stay in components.

CollisionSystem performs manual AABB collision checks, EnemyFormation controls group movement/drop behavior. Projectile Count is low, so we avoided pooling for more simplicity with managing projectiles in PlayScene. Input is processed via InputHandler and Command objects, so key mappings and player actions are separated. EventBus (Observer Style) reduces interdependence by broadcasting events like EnemyKilled or PlayerHit to ScoreManager, UI, and other subscribers like audio.

Resource/service classes keep the infrastructure centralized. AssetManager handles SDL_image sprite loading/caching, AudioManager wraps miniaudio playback, ScoreManager owns points/lives rules. Overall, the design intentionally applies patterns from the textbook (GameLoop, State, Component, Command, Observer) for a good game design.

* Game Loop: Engine runs input, update, and renders every frame
* State: TitleScene, PlayScene, and CreditsScene separate screen-specific behavior
* Component: GameObject behavior is composed from reusable components (sprite, collider, etc.)
* Command: input actions are mapped to command objects instead of hardcoded key logic in entities
* Observer: EventBus broadcasts gameplay events to subscribed systems (score, UI…)
* Object Pool OMITTED due to lack of quantitative objects

