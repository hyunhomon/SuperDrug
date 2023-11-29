#include "../../Header/Util/pch.h"
#include "../../Header/Scene/GameScene.h"

#define MAP_WIDTH (SCREEN_WIDTH * 3 / 48)
#define MAP_HEIGHT (SCREEN_HEIGHT / 48)
#define GRID 48

typedef struct {
	double x, y, speed, shootTimer, shootDelay;
	int w, h, curHp, maxHp;
	bool idle, crouch, dir;

	SDL_Texture* img;

	Animation anim_idle;
	Animation anim_stand_move_left;
	Animation anim_stand_move_right;
	Animation anim_stand_shoot;
	Animation anim_crouch_move;
	Animation anim_crouch_shoot;

} Player;

typedef struct {
	double x, y, speed;
	int w, h;
	bool dir;

	SDL_Texture* img;

	Animation anim_move;

} Goomba;

typedef struct {
	double x, y, speed;
	int w, h;
	bool dir;

	SDL_Texture* img;

} Mushroom;

typedef struct {
	double x, y, speed;
	int w, h;
	bool dir;

	SDL_Texture* img_left;
	SDL_Texture* img_right;

	Mix_Chunk* sound;

} Bullet;

typedef struct {
	int status;
	double goombaSpawnTimer, goombaSpawnDelay;

	SDL_Texture* img_bg;
	SDL_Texture* img_brick1;
	SDL_Texture* img_brick2;

	SDL_Texture* img_player;
	SDL_Texture* img_goomba;
	SDL_Texture* img_mushroom;
	SDL_Texture* img_bullet_left;
	SDL_Texture* img_bullet_right;

	Mix_Music* bgm;

	Player player;
	Goomba goombaBase;
	Mushroom mushroomBase;
	Bullet bulletBase;

	List goombaList;
	List bulletList;

} GameScene;

GameScene gameScene;

void Map_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (map[i][j] == 1) {
				SDL_Rect rect = { j * GRID, i * GRID, GRID, GRID };
				SDL_RenderFillRect(renderer, &rect);

				Image_Draw(renderer, j * GRID, i * GRID, gameScene.img_brick1);
			}
			else if (map[i][j] == 2) {
				SDL_Rect rect = { j * GRID, i * GRID, GRID, GRID };
				SDL_RenderFillRect(renderer, &rect);

				Image_Draw(renderer, j * GRID, i * GRID, gameScene.img_brick2);
			}
		}
	}
}

void Player_Init()
{
	Player* p = &gameScene.player;

	p->x = 590.0;
	p->y = 585.0;

	p->img = gameScene.img_player;
	getImageSize(p->img, &p->w, &p->h);

	p->idle = true;
	p->dir = true;

	p->speed = 120.0;

	p->curHp = 5;
	p->maxHp = 5;

	p->shootTimer = 0.0;
	p->shootDelay = 0.5;
}

void Player_Update(double dt)
{
	Player* p = &gameScene.player;
	SDL_Rect playerRect = { p->x, p->y, p->w, p->h };

	int posX = 0, posY = 0;

	// key input
	if (getKeyState(SDL_SCANCODE_LEFT) == KEY_HOLD) {
		Animation_Update(&p->anim_stand_move_left, dt);
		p->img = getCurrentFrame(&p->anim_stand_move_left);

		posX -= 1;
		p->dir = false;
		p->idle = false;
	}
	else if (getKeyState(SDL_SCANCODE_RIGHT) == KEY_HOLD) {
		Animation_Update(&p->anim_stand_move_right, dt);
		p->img = getCurrentFrame(&p->anim_stand_move_right);

		posX += 1;
		p->dir = true;
		p->idle = false;
	}
	else {
		p->idle = true;
	}

	// move
	p->x += posX * p->speed * dt;
	p->y += posY * p->speed * dt;

	// wall collision
	if (p->x < 0.0) {
		p->x = 0.0;
	}
	if (p->x > SCREEN_WIDTH - p->w) {
		p->x = SCREEN_WIDTH - p->w;
	}
	if (p->y < 0.0) {
		p->y = 0.0;
	}
	if (p->y > SCREEN_HEIGHT - p->h) {
		p->y = SCREEN_HEIGHT - p->h;
	}
}

void Goomba_Update(double dt)
{
	// goomba create
	gameScene.goombaSpawnTimer += dt;
	if (gameScene.goombaSpawnTimer >= gameScene.goombaSpawnDelay) {
		Goomba* goomba = (Goomba*)malloc(sizeof(Goomba));
		memcpy(goomba, &gameScene.goombaBase, sizeof(Goomba));

		int randomPosX = rand() % 2;

		// left or right create
		if (randomPosX < 1) {
			goomba->x = 0;
			goomba->dir = true;
		}
		else {
			goomba->x = SCREEN_WIDTH - goomba->w;
			goomba->dir = false;
		}
		goomba->y = 590.0;

		List_Push(&gameScene.goombaList, goomba);

		gameScene.goombaSpawnTimer = 0;
	}

	// goomba update
	Node* goombaNode = gameScene.goombaList.head;
	while (goombaNode != NULL) {
		Goomba* goomba = (Goomba*)goombaNode->val;
		SDL_Rect goombaRect = { goomba->x, goomba->y, goomba->w, goomba->h };

		Animation_Update(&goomba->anim_move, dt);
		goomba->img = getCurrentFrame(&goomba->anim_move);

		// move
		if (goomba->dir) {
			goomba->x += goomba->speed * dt;
		}
		else {
			goomba->x -= goomba->speed * dt;
		}

		// wall collision
		if (goomba->x < 0) {
			goomba->dir = true;
		}
		else if (goomba->x > SCREEN_WIDTH - goomba->w) {
			goomba->dir = false;
		}

		// player collision
		Player* p = &gameScene.player;
		SDL_Rect playerRect = { p->x, p->y, p->w, p->h };

		if (Collision_Check(goombaRect, playerRect)) {
			printf("GAME OVER!");
			gameScene.status = EXIT_GAME;
		}

		goombaNode = goombaNode->next;
	}
}

void Bullet_Update(double dt)
{
	Player* p = &gameScene.player;

	// bullet create
	p->shootTimer += dt;
	if (getKeyState(SDL_SCANCODE_S) == KEY_HOLD && p->shootTimer >= p->shootDelay) {
		Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
		memcpy(bullet, &gameScene.bulletBase, sizeof(Bullet));

		// left or right create
		if (p->dir) {
			bullet->x = p->x + p->w;
		}
		else {
			bullet->x = p->x - p->w;
		}

		bullet->y = p->y + p->h / 2 - 20;

		bullet->dir = p->dir;

		List_Push(&gameScene.bulletList, bullet);

		p->shootTimer = 0.0;
	}

	// bullet update
	Node* bulletNode = gameScene.bulletList.head;
	bool bulletDestroy = false;

	while (bulletNode != NULL) {
		Bullet* bullet = (Bullet*)bulletNode->val;
		SDL_Rect bulletRect = { bullet->x, bullet->y, bullet->w, bullet->h };

		// move
		if (bullet->dir) {
			bullet->x += bullet->speed * dt;
		}
		else {
			bullet->x -= bullet->speed * dt;
		}

		// wall collision
		if (bullet->x > SCREEN_WIDTH || bullet->x < 0) {
			bulletNode = bulletNode->next;
			List_Remove(&gameScene.bulletList, bullet);

			free(bullet);

			continue;
		}

		// goomba collision
		Node* goombaNode = gameScene.goombaList.head;
		while (goombaNode != NULL) {
			Goomba* goomba = (Goomba*)goombaNode->val;
			SDL_Rect goombaRect = { goomba->x, goomba->y, goomba->w, goomba->h };

			if (Collision_Check(bulletRect, goombaRect)) {
				goombaNode = goombaNode->next;
				List_Remove(&gameScene.goombaList, goomba);

				free(goomba);

				bulletDestroy = true;

				continue;
			}

			goombaNode = goombaNode->next;
		}

		if (bulletDestroy) {
			bulletNode = bulletNode->next;
			List_Remove(&gameScene.bulletList, bullet);

			free(bullet);

			bulletDestroy = false;

			continue;
		}

		bulletNode = bulletNode->next;
	}
}

void __Animation_Init__()
{
	SDL_Renderer* renderer = Get_Renderer();

	Animation_Init(&gameScene.player.anim_stand_move_left, 10, ANIM_LOOP_ON);
	Animation_Init(&gameScene.player.anim_stand_move_right, 10, ANIM_LOOP_ON);
	Animation_Init(&gameScene.goombaBase.anim_move, 10, ANIM_LOOP_ON);

	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/0.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/1.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/2.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/3.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/4.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/5.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/6.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/7.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/8.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/9.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/10.png"));
	appendTexture(&gameScene.player.anim_stand_move_left, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Left/11.png"));

	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/0.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/1.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/2.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/3.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/4.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/5.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/6.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/7.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/8.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/9.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/10.png"));
	appendTexture(&gameScene.player.anim_stand_move_right, Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/11.png"));

	appendTexture(&gameScene.goombaBase.anim_move, Image_Load(renderer, "./Asset/Image/Mario/Enemy/Goomba/0.png"));
	appendTexture(&gameScene.goombaBase.anim_move, Image_Load(renderer, "./Asset/Image/Mario/Enemy/Goomba/1.png"));
}

void GameScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();

	gameScene.img_bg = Image_Load(renderer, "./Asset/Image/Background/Background.png");
	gameScene.img_brick1 = Image_Load(renderer, "./Asset/Image/Mario/Object/brick1.png");
	gameScene.img_brick2 = Image_Load(renderer, "./Asset/Image/Mario/Object/brick2.png");

	// player init
	gameScene.img_player = Image_Load(renderer, "./Asset/Image/MetalSlug/PlayerWalking/Right/0.png");

	Player_Init();

	// goomba init
	gameScene.img_goomba = Image_Load(renderer, "./Asset/Image/Mario/Enemy/Goomba/0.png");

	getImageSize(gameScene.img_goomba, &gameScene.goombaBase.w, &gameScene.goombaBase.h);
	gameScene.goombaBase.img = gameScene.img_goomba;
	gameScene.goombaBase.img = gameScene.img_goomba;
	gameScene.goombaBase.speed = 100.0;
	gameScene.goombaSpawnTimer = 0.0;
	gameScene.goombaSpawnDelay = 0.5;

	// bullet init
	gameScene.img_bullet_left = Image_Load(renderer, "./Asset/Image/Mario/Object/BulletLeft.png");
	gameScene.img_bullet_right = Image_Load(renderer, "./Asset/Image/Mario/Object/BulletRight.png");

	getImageSize(gameScene.img_bullet_left, &gameScene.bulletBase.w, &gameScene.bulletBase.h);
	gameScene.bulletBase.img_left = gameScene.img_bullet_left;
	gameScene.bulletBase.img_right = gameScene.img_bullet_right;
	gameScene.bulletBase.speed = 700.0;

	// anim init
	__Animation_Init__();

	// sound init
	/*gameScene.bgm = Mix_LoadWAV("./Asset/Sound/Mario/BGM/overworld.wav");
	gameScene.bulletBase.sound = Mix_LoadWAV("./Asset/Sound/Mario/blockhit.wav");*/

	// list init
	List_Init(&gameScene.goombaList);
	List_Init(&gameScene.bulletList);

	/*Mix_PlayMusic(gameScene.bgm, 1);*/
}

void GameScene_Event()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			gameScene.status = EXIT_GAME;
			break;
		}
	}
}

void GameScene_Update()
{
	double dt = getDeltaTime();

	int mouseX = 0, mouseY = 0;
	getCurrentMousePos(&mouseX, &mouseY);

	Player_Update(dt);
	Goomba_Update(dt);
	Bullet_Update(dt);
}

void GameScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	Image_Draw(renderer, 0, 0, gameScene.img_bg);
	Image_Draw(renderer, gameScene.player.x, gameScene.player.y, gameScene.player.img);

	Map_Render();

	// goomba render
	Node* goombaNode = gameScene.goombaList.head;
	while (goombaNode != NULL) {
		Goomba* goomba = (Goomba*)goombaNode->val;

		Image_Draw(renderer, goomba->x, goomba->y, goomba->img);

		goombaNode = goombaNode->next;
	}
	
	// bullet render
	Node* bulletNode = gameScene.bulletList.head;
	while (bulletNode != NULL) {
		Bullet* bullet = (Bullet*)bulletNode->val;

		if (bullet->dir) {
			Image_Draw(renderer, bullet->x, bullet->y, bullet->img_right);
		}
		else {
			Image_Draw(renderer, bullet->x, bullet->y, bullet->img_left);
		}
		
		bulletNode = bulletNode->next;
	}

	SDL_RenderPresent(renderer);
}

void GameScene_Release()
{
	SDL_DestroyTexture(gameScene.img_bg);
	SDL_DestroyTexture(gameScene.player.img);

	SDL_DestroyTexture(gameScene.img_goomba);

	SDL_DestroyTexture(gameScene.img_bullet_left);
	SDL_DestroyTexture(gameScene.img_bullet_right);

	List_Release(&gameScene.goombaList);
	List_Release(&gameScene.bulletList);

	Animation_Release_With_Texture(&gameScene.player.anim_stand_move_left);
	Animation_Release_With_Texture(&gameScene.player.anim_stand_move_right);

	/*Mix_FreeMusic(gameScene.bgm);*/
}

int GameScene_Loop()
{
	gameScene.status = SCENE_LOOP;

	while (gameScene.status == SCENE_LOOP) {
		Util_Update();

		GameScene_Event();
		GameScene_Update();
		GameScene_Render();
	}

	return gameScene.status;
}
