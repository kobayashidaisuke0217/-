#include <Novice.h>
#include "Vec2.h"
#include "collisionfunc.h"

#include "matrix.h"
#include "struct.h"
#include "Boss3.h"
#include "Player.h"
#include "Nucleus.h"
#include "Enemy.h"
#include "BeamPoint.h"
#include "Beams.h"
#include "Triangle.h"
#include "Bullets.h"
#include "Scene.h"
#include<time.h>
#include"tutorial.h"
#include "FireWorks.h"
#include "Explosion.h"
#include "particle.h"
const char kWindowTitle[] = "LC1B_08_コバヤシダイスケ";



float easeInSine(float x) {
	return 1.0f - cosf((x * M_PI) / 2.0f);
}
//float learp(float t, float s, float e) {
//	return (1.0f - t) * s + t * e;
//}

int lineSearch(int flag[], int num) {
	int i;
	for (i = 0; i < num; i++) {
		if (flag[i] == true) {
			return 1;
		}
	}
}

void randShake(Vector2& randam, int& count) {
	count--;

	if (count > 0) {
		randam.x = rand() % count - count;
		randam.y = rand() % count - count;

	}
}


unsigned int GetColor(int red, int green, int blue, int alpha) {
	unsigned int hex = 0x00000000;
	red = red << 24;
	green = green << 16;
	blue = blue << 8;
	alpha = alpha << 0;

	return hex = red + green + blue + alpha;
}

void DrawQuad(Vector2 LT, Vector2 RT, Vector2 LD, Vector2 RD, Vector2 Screen, int pic, int color, int a, int b, int c, int d, Vector2 rand) {
	Novice::DrawQuad(LT.x - Screen.x + rand.x, LT.y - Screen.y + rand.y, LD.x + rand.x - Screen.x, LD.y - Screen.y + rand.y, RT.x - Screen.x + rand.x, RT.y - Screen.y + rand.y, RD.x - Screen.x + rand.x, RD.y - Screen.y + rand.y, a, b, c, d, pic, color);
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	int mousePress = false;
	Circle circleReset = { 0,0,0,0,RED,100 };
	Beam beamReset = { 0,0,0,0,0,0,0,0,0,0,0 };
	Bullet bulletReset = { 300,400,32,0,0,RED };

	Player* player = new Player({ 500,300,32.0f,6,RED,100 }, { 0,0 });
	bool playerIsAlive = true;
	Nucleus* nucleus[12];

	for (int i = 0; i < 12; i++) {
		nucleus[i] = new Nucleus(circleReset);
	}

	int mousePressTime = 0;
	nucleus[0]->nucleus.center = { 300, 140 };
	nucleus[1]->nucleus.center = { 1000, 140 };
	nucleus[2]->nucleus.center = { 640, 540 };
	//右上
	nucleus[3]->nucleus.center = { 1580, 140 };
	nucleus[4]->nucleus.center = { 2280, 140 };
	nucleus[5]->nucleus.center = { 1920, 540 };
	//左下
	nucleus[6]->nucleus.center = { 300, 1260 };
	nucleus[7]->nucleus.center = { 1000, 1260 };
	nucleus[8]->nucleus.center = { 640, 900 };
	//右下
	nucleus[9]->nucleus.center = { 1580 , 1260 };
	nucleus[10]->nucleus.center = { 2280 , 1260 };
	nucleus[11]->nucleus.center = { 1920, 900 };
	float nucleuspicRadius[12];
	for (int i = 0; i < nucleus[0]->max; i++) {
		nucleus[i]->nucleus.radius = 32.0f;
		nucleus[i]->nucleus.color = WHITE;
		nucleus[i]->nucleusPrePos = nucleus[i]->nucleus.center;
		nucleus[i]->nucleusSuctionPos = nucleus[i]->nucleus.center;
		nucleuspicRadius[i] = 1;
	}
	bool nucleusResetFlag = false;
	const int enemyNum = 3;
	Enemy* enemy[enemyNum];

	for (int i = 0; i < enemyNum; i++) {
		enemy[i] = new Enemy(circleReset);
		/*	enemy[i]->enemyAlive = true;
			enemy[i]->enemyScreenIn = false;*/
	}
	enemy[0]->enemy = { 600,300,32.0f,6.0f,WHITE,100 };
	enemy[1]->enemy = { 1400,100,32.0f,6.0f,WHITE,100 };
	enemy[2]->enemy = { 2000,200,32.0f,6.0f,WHITE,100 };

	const int beamNum = 4;//ビーム発射地点
	BeamPoint* beamPoint[beamNum];

	int beamAttackchange = 0;
	for (int i = 0; i < beamNum; i++) {
		beamPoint[i] = new BeamPoint(circleReset);
	}

	beamPoint[0]->beamPoint = { 0,0,32.0f,6.0f,RED,100 };
	beamPoint[1]->beamPoint = { 2560,1440,32.0f,6.0f,RED,100 };
	beamPoint[2]->beamPoint = { 0,1440,32.0f,6.0f,RED,100 };
	beamPoint[3]->beamPoint = { 2560,0,32.0f,6.0f,RED,100 };

	for (int i = 0; i < beamNum; i++) {
		beamPoint[i]->beamAlive = true;
	}
	beamPoint[0]->beamAtackStart = false;

	Beams* beams[beamNum];
	for (int i = 0; i < beamNum; i++) {
		beams[i] = new Beams(beamReset);
	}

	for (int i = 0; i < 4; i++) {
		beams[i]->beam.pos = { 0,0 };
		beams[i]->beam.angle = { 0 };
		beams[i]->beam.radian = { 0 };
		beams[i]->beam.EndPos = { 0,0 };

		beams[i]->BTop.pos = { 0,0 };
		beams[i]->BTop.angle = { 0 };
		beams[i]->BTop.radian = { 0 };
		beams[i]->BTop.EndPos = { 0,0 };

		beams[i]->BDown.pos = { 0,0 };
		beams[i]->BDown.angle = { 0 };
		beams[i]->BDown.radian = { 0 };
		beams[i]->BDown.EndPos = { 0,0 };

		beams[i]->beam.size = 2500;

	}

	Triangle* triangle = new Triangle({ {1000.0f,700.0f},{500.0f,400.0f},{100,500}, });

	float theta = 0;

	float playertheta[4] = { 0 };

	const int bulletNum = 16;//敵弾

	Bullets* bullet[bulletNum];

	for (int i = 0; i < bulletNum; i++) {
		bullet[i] = new Bullets(bulletReset);
		bullet[i]->bulletAngle = { 0 , 0 };//角度X
		bullet[i]->bulletOnFlag = false;//弾の発射
		bullet[i]->bulletInductionOnFlag = false;//誘導フラグ
		bullet[i]->bulletInductionTimer = 10;//誘導時間(初期値10)
		bullet[i]->bulletEndTimer = 300;//弾消滅時間(初期値400)
		bullet[i]->bullettimer = 80 + 20 * i;
	}

	Vector2  scrollWall{ //スクロール開始
		640.0f,360.0f
	};

	Vector2  scrollWallEnd{ //スクロール終了
		1920.0f,1080.0f
	};

	Vector2 RandShake;
	RandShake.x = 0;
	RandShake.y = 0;

	int stunOnFlag = false;
	int shakeTimer = 60;//シェイク時間60

	//ゲージ
	Vector2 gaugeleft = { 30,30 };
	Vector2 gaugeRight{ 30,30 };
	int WhiteP = Novice::LoadTexture("white1x1.png");

	int stage[4]; //ステージセレクト
	stage[0] = Novice::LoadTexture("./Resources/image/backGround1.png"); //ステージ左上
	stage[1] = Novice::LoadTexture("./Resources/image/backGround2.png"); //ステージ右上
	stage[2] = Novice::LoadTexture("./Resources/image/backGround3.png"); //ステージ左下
	stage[3] = Novice::LoadTexture("./Resources/image/backGround4.png"); //ステージ右下
	int Bosspic[3];
	Bosspic[0] = Novice::LoadTexture("./Resources/image/Enemy.png");
	Bosspic[1] = Novice::LoadTexture("./Resources/image/Enemy2.png");
	Bosspic[2] = Novice::LoadTexture("./Resources/image/Enemy3.png");
	int BeamPic = Novice::LoadTexture("./Resources/image/Beam.png");
	int nucleusPic = Novice::LoadTexture("./Resources/image/Nucleus.png");
	 int playerPic= Novice::LoadTexture("./Resources/image/Player.png");
	 int playerAimPic=Novice::LoadTexture("./Resources/image/playerAim.png");
	 int BulletPic = Novice::LoadTexture("./Resources/image/Bullet.png");
	 int BeamPointPic = Novice::LoadTexture("./Resources/image/Beampoint.png");
	 int BGPic= Novice::LoadTexture("./Resources/image/Background.png");
	 int StartBG= Novice::LoadTexture("./Resources/image/StartNanu.png");
	 int gameoverPic= Novice::LoadTexture("./Resources/image/gameover.png");
	 int kakomePic = Novice::LoadTexture("./Resources/image/StartNanu2.png");
	 int LTpic = Novice::LoadTexture("./Resources/image/LT.png");
	 int LBpic = Novice::LoadTexture("./Resources/image/LB.png");
	 int RBpic = Novice::LoadTexture("./Resources/image/RB.png");
	 int Lstickpic = Novice::LoadTexture("./Resources/image/Lstick.png");
	 int Rstickpic = Novice::LoadTexture("./Resources/image/Rstick.png");
	 int Clearpic= Novice::LoadTexture("./Resources/image/Gameclear.png");
	 int hpBar1= Novice::LoadTexture("./Resources/image/HP1.png");
	 int hpBar2= Novice::LoadTexture("./Resources/image/HP2.png");
	 int dangerPic = Novice::LoadTexture("./Resources/image/warning.png");
	 int PowerUP=Novice::LoadTexture("./Resources/image/Power1.png");
	 int speed3Pic= Novice::LoadTexture("./Resources/image/speed1.png");
	 int speed2Pic = Novice::LoadTexture("./Resources/image/speed2.png");
	 int speed1Pic = Novice::LoadTexture("./Resources/image/speed3.png");
	 int power1Pic = Novice::LoadTexture("./Resources/image/Power1.png");
	 int power2Pic = Novice::LoadTexture("./Resources/image/Power2.png");
	 int power3Pic = Novice::LoadTexture("./Resources/image/Power3.png");
	Vector2 Start[4];
	Vector2 Vertex[4];
	Vector2 End[4];

	Vector2 throwPos[4];

	float hitradius[4];
	bool throwDamageFlag[4] = { false };
	for (int i = 0; i < 4; i++)
	{
		throwPos[i] = { 0,0 };
		Start[i] = { 0,0 };
		Vertex[i] = { 0,0 };
		End[i] = { 0,0 };
		hitradius[i] = 0;
	};//中心点
	int throwFlag[4] = { false };

	Vector2 throwradian[4] = { 0 };
	Vector2 throwAngle[4] = { 0 };
	Vector2 throwSpeed[4] = { 0 };
	int atackdamage = 0;
	float triangleSide = 0;

	int triangleBreak = false;

	bool playerFlag = true;//自機生存フラグ

	Vector2 boundPoint = { 2560,720 };//反射する座標、Xx1280、Yx720

	int gamemode = 0;//ゲームモード管理 0でスタート前,奇数が操作画面、偶数で変数のリセットなどのロード画面
	int scrollMode = 0;//0でスクロールしない　1でスクロールする

	int leftx = 0;
	int lefty = 0;

	int rightx = 0;
	int righty = 0;

	int stickNo = 0;

	bool beemHit = false;

	int attackHitTimer = 120;//攻撃被弾時タイマー

	int beamPreCount = 0;

	int powerCount=0;
	bool powerFlag = false;
	bool girechange = false;
	int girechangeCount = 0;

	int fadeoutFlag[2] = { false };
	int fadeoutClar = 0x00000000;
	int fadeoutTime = 0;
	int fadeOutAlpha = 0;
	bool fadeoutDrawFlag = false;
	int nucleusSuctionCount = 0;
	int nucleusSuctionFlag[12] = { false };

	//ボス
	Boss3 lastboss;
	Baria rasBossBaria;
	BossBeam bossBeam[2];
	lastboss.patten = 0;

	lastboss.pos = { 1280,720 };
	lastboss.pos = { 1280,720 };
	lastboss.leftDown = { 0,0 };
	lastboss.leftTop = { 0,0 };
	lastboss.rightDown = { 0,0 };
	lastboss.rightTop = { 0,0 };
	lastboss.radius = 128;
	lastboss.HP = 100;
	lastboss.isAlive = true;
	lastboss.select = 0;
	lastboss.selectCount = 0;
	lastboss.rotateRadius = 0;
	lastboss.rotateTheta = 0;
	lastboss.theta = 0;
	lastboss.rotatePlus = 0;
	lastboss.thetaPlus = 0;
	lastboss.originarRT = { 0,0 };
	lastboss.originarRD = { 0,0 };
	lastboss.originarLT = { 0,0 };
	lastboss.originarLD = { 0,0 };
	lastboss.preSelect = 0;
	lastboss.DrawAngle = 0;
	lastboss.returnSpeed = 0;
	lastboss.returnPos = { 0,0 };
	lastboss.battleStart = false;
	lastboss.randPos = { 0,0 };

	rasBossBaria.alpha = 0;
	rasBossBaria.breakCount = 0;
	rasBossBaria.count = 0;
	rasBossBaria.Flag = false;
	rasBossBaria.HP = 0;
	rasBossBaria.pos = { 0,0 };
	rasBossBaria.Endpos = { 0,0 };
	rasBossBaria.leftTop = { 0,0 };
	rasBossBaria.rightTop = { 0,0 };
	rasBossBaria.leftDown = { 0,0 };
	rasBossBaria.rightDown = { 0, 0 };
	rasBossBaria.isAlive = false;
	rasBossBaria.size = 00;


	for (int i = 0; i < 2; i++) {
		bossBeam[i].count = 0;
		bossBeam[i].EndPos = { 0,0 };
		bossBeam[i].flag = false;
		bossBeam[i].leftDown = { 0,0 };
		bossBeam[i].leftTop = { 0,0 };
		bossBeam[i].ob = { 0,0 };
		bossBeam[i].pos = { 0,0 };
		bossBeam[i].rightDown = { 0,0 };
		bossBeam[i].rightTop = { 0,0 };
		bossBeam[i].theta = 0;
		bossBeam[i].size = 16;
	}
	srand(time(nullptr));

	/*bossBeam.parob = { 0,0 };
	bossBeam.partheta = 0;
	for (int i = 0; i < 30; i++) {
		bossBeam.par[i].isAlive = false;
		bossBeam.par[i].pos = { 0,0 };
		bossBeam.par[i].size = 8;
		bossBeam.par[i].speed = 0;
		bossBeam.par[i].startPos = { 0,0 };

	}*/
	/*bossBeam.parob = { 0,0 };
	bossBeam.partheta = 0;*/
	/*チュートリアル*/
	parManag particle;
	
	for (int i = 0; i < 12; i++) {

		particle.par[i].theta = 0;
		particle.par[i].count = 0;
		particle.par[i].pos = { 0,0 };
		particle.par[i].vertex = { 0, 0 };
		particle.par[i].End = { 0, 0 };
		particle.par[i].start = { 0, 0 };
		particle.par[i].originalvertex = { 0, -6 };
		particle.par[i].originalEnd = { 3, 3 };
		particle.par[i].originalstart = { -3, -3 };
		particle.par[i].isAlive = false;
		particle.par[i].count = 0;
		particle.par[i].randStart = 0;

	}
	Tutrial tutrial[6];
	for (int i = 0; i < 6; i++) {
		tutrial[i].downFlag = false;
		tutrial[i].pos = { i * 400.0f + 200.0f,-400 };
		tutrial[i].player = { 0,0,16,0,WHITE,1 };
		tutrial[i].sizeX = 300;
		tutrial[i].sizeY = 200;
		tutrial[i].speed = 0;
		tutrial[i].downFlag;
		tutrial[i].count = 0;
		tutrial[i].Ob = { 0,0 };
		tutrial[i].moveob = { 0,0 };
	}

	FireWorks* fireworks = new FireWorks;
	FireWorks* fireworks2 = new FireWorks;
	FireWorks* fireworks3 = new FireWorks;

	fireworks->fireWorksCenter.center = { 300,300 };
	fireworks->fireWorksCenter.color = RED;

	fireworks2->fireWorksCenter.center = { 800,500 };
	fireworks2->fireWorksCenter.color = BLUE;

	fireworks3->fireWorksCenter.center = { 1000,200 };
	fireworks3->fireWorksCenter.color = GREEN;

	Explosion* explosion = new Explosion;
	Explosion* explosion2 = new Explosion;
	Explosion* explosion3 = new Explosion;

	

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Novice::GetAnalogInputLeft(stickNo, &leftx, &lefty);
		Novice::GetAnalogInputRight(stickNo, &triangle->mouseX, &triangle->mouseY);
		Novice::SetWindowMode(kFullscreen);
		///
		/// ↓更新処理ここから
		///
		 explosion->pos = { lastboss.pos.x - 80,lastboss.pos.y - 80 };
		explosion2->pos = { lastboss.pos.x + 50,lastboss.pos.y };
		explosion3->pos = { lastboss.pos.x - 30,lastboss.pos.y + 20 };
		
		if (keys[DIK_C]) {
			stunOnFlag = true;
		}
		player->Hit();
		player->Reflect();
		if (gamemode <= 7) {
			if (player->HP <= 0) {
				playerIsAlive = false;
				gamemode = 8;
			}
		}
		if (gamemode == 8) {
			scrollMode = 2;
			


			if (playerIsAlive == false) {
				gamemode = 9;
			}
			else {
				gamemode = 10;
				fireworks->startFlag = true;
				fireworks2->startFlag = true;
				fireworks3->startFlag = true;
			}

		}
		if (gamemode == 9 || gamemode == 10) {
			fireworks->Update(keys);
			fireworks2->Update(keys);
			fireworks3->Update(keys);
			if (Novice::IsTriggerButton(0, kPadButton10) || keys[DIK_V]) {
				gamemode = 11;
			}

		}
		if (gamemode == 11) {

			fadeoutFlag[0] = true;

			/*	if (fadeOutAlpha >= 255) {
					gamemode = 0;
				}*/
		}
		if (fadeoutFlag[0] == true) {
			fadeOutAlpha += 5;

		}
		if (fadeOutAlpha >= 255) {
			fadeoutFlag[1] = true;
			fadeoutFlag[0] = false;
			if (gamemode == 100) {
				gamemode = 1;
			}
			else if (gamemode == 11) {
				gamemode = 0;
				playerIsAlive = true;
			}
			else if (gamemode == 9 || gamemode == 10) {
				gamemode = 11;
			}

			else {


				gamemode++;
			}
		}
		else if (fadeOutAlpha <= 0) {
			fadeoutFlag[1] = false;
		}
		if (fadeOutAlpha > 0) {
			fadeoutDrawFlag = true;
		}
		if (fadeoutFlag[1] == true) {
			fadeOutAlpha -= 5;
		}

		if (fadeOutAlpha >= 250) {
			if (playerIsAlive == true) {
				player->HP = 30;
			}
		}
		if (fadeoutFlag[0] == true) {
			fadeoutFlag[1] = false;
		}
		if (gamemode == 0) {//ゲーム開始画面
			player->scroll = { 0,0 };
			triangle->pattern = 0;
			for (int i = 0; i < 4; i++) {
				beams[i]->atackFlag = false;
			}
			if (Novice::IsTriggerButton(0, kPadButton10) || keys[DIK_V]) {
				gamemode = 100;

			}
			for (int i = 0; i < 6; i++) {
				TutrialReset(tutrial[i]);
			}
			for (int i = 0; i < 2; i++) {
				Boss3Reset(lastboss, rasBossBaria, bossBeam[i]);
				lastboss.battleStart = false;

			}
			player->Reset();

		}
		if (gamemode == 100) {

			fadeoutFlag[0] = true;



			if (fadeOutAlpha >= 255) {
				triangle->pattern = 0;


			}
		}
		if (gamemode == 3 || gamemode == 5 || gamemode == 7) {
			/*if (lastboss.isAlive == false) {
				lastboss.battleStart = false;

			}*/
		}

		if (gamemode == 2 && fadeoutFlag[0] == false) {
			triangle->pattern = 0;
			player->Reset();

			fadeoutFlag[0] = true;

			for (int i = 0; i < 2; i++) {
				Boss3Reset(lastboss, rasBossBaria, bossBeam[i]);
			}
			lastboss.HP = 25;
			if (fadeOutAlpha >= 255) {
				triangle->pattern = 0;
				gamemode = 3;

			}
			lastboss.battleStart = false;
		}
		if (gamemode == 4) {
			triangle->pattern = 0;
			player->Reset();

			fadeoutFlag[0] = true;

			for (int i = 0; i < 2; i++) {
				Boss3Reset(lastboss, rasBossBaria, bossBeam[i]);
			}
			lastboss.HP = 50;
			if (fadeOutAlpha >= 255) {
				triangle->pattern = 0;
				gamemode = 5;
			}
			lastboss.battleStart = false;
		}
		if (gamemode == 6) {
			triangle->pattern = 0;
			player->Reset();

			fadeoutFlag[0] = true;

			for (int i = 0; i < 2; i++) {
				Boss3Reset(lastboss, rasBossBaria, bossBeam[i]);
			}
			lastboss.HP = 100;
			if (fadeOutAlpha >= 255) {
				triangle->pattern = 0;
				gamemode = 7;
			}
			lastboss.battleStart = false;
		}
		if (gamemode >= 1) {//ゲームスタート
			if (gamemode == 1) {//チュートリアル
				fadeoutFlag[0] = false;
				lastboss.battleStart = true;
				scrollMode = 0;
				beamPoint[0]->beamAtackStart = false;
				tutrial[0].downFlag = true;
				for (int i = 0; i < 6; i++) {
					TutrialCome(tutrial[i], player->player.center);

				}
				if (tutrial[0].downFlag == true) {
					TutorialMove(tutrial[0]);
				}

				for (int i = 0; i < enemyNum; i++) {
					enemy[i]->enemy.center.y += enemy[i]->enemy.speed;
					if (enemy[i]->enemy.center.y <= 100 || enemy[i]->enemy.center.y >= 620) {
						enemy[i]->enemy.speed *= -1;
					}
				}
				for (int i = 0; i < enemyNum; i++) {
					enemy[i]->enemyAlive = false;
				}
				if (player->player.center.x >= 2500) {
					lastboss.battleStart = false;
					gamemode = 2;

				}

			}
			if (gamemode == 3) {//ステージ1
				fadeoutFlag[0] = false;
				BossSetpos(lastboss);
				scrollMode = 1;
				if (lastboss.HP <= 0 && lastboss.battleStart == true) {
					explosion->explosionFlag = true;
					explosion2->explosionFlag = true;
					explosion3->explosionFlag = true;
					explosion->Update();
					explosion2->Update();
					explosion3->Update();
					if (explosion->explosionCount >= 3) {
						gamemode += 1;
						explosion->explosionCount = 0;
						explosion2->explosionCount = 0;
						explosion3->explosionCount = 0;
						explosion->enemyAlphaTimer = 255;
						explosion2->enemyAlphaTimer = 255;
						explosion3->enemyAlphaTimer = 255;
					}
				}
				if (lastboss.battleStart == true && lastboss.isAlive == true) {
					beamPoint[0]->beamAtackStart = true;
					beams[0]->beamMode = 0;
					for (int i = 0; i < enemyNum; i++) {
						if (i >= 1) {
							enemy[i]->enemyAlive = false;
						}
					}
					enemy[0]->enemyAlive = true;
					enemy[0]->enemy.center = lastboss.pos;
					if (lastboss.isAlive == true) {
						Boss1Pattern(lastboss, bossBeam[0], player->player.center);
						if (CircleCollisinHit(player->player.center, player->player.radius, lastboss.pos, lastboss.radius) == true && player->reflect == false) {
							triangle->atackSpeed.x = -triangle->atackSpeed.x * 0.7;
							triangle->atackSpeed.y = -triangle->atackSpeed.y * 0.7;
							player->reflect = true;
							player->hit = true;
							player->HP -= 1;
							attackHitTimer = 120;
						}
						if (bossBeam[0].flag == true) {
							if (RectCollisionHit(bossBeam[0].pos, bossBeam[0].EndPos, player->player.center, player->player.radius, bossBeam[0].size) == true && player->hit == false) {

								player->hit = true;
								player->HP -= 1;
								attackHitTimer = 120;
							}
						}


					}
				}
			}
			if (gamemode == 5) {//ステージ2
				fadeoutFlag[0] = false;
				BossSetpos(lastboss);
				scrollMode = 1;
				beamPoint[0]->beamAtackStart = true;
				beams[0]->beamMode = 0;
				if (lastboss.isAlive == false) {
					bossBeam->flag = false;
				}
				if (lastboss.HP <= 0) {
					explosion->explosionFlag = true;
					explosion2->explosionFlag = true;
					explosion3->explosionFlag = true;
					explosion->Update();
					explosion2->Update();
					explosion3->Update();
					if (explosion->explosionCount >= 3) {
						gamemode += 1;
						explosion->explosionCount = 0;
						explosion2->explosionCount = 0;
						explosion3->explosionCount = 0;
						explosion->enemyAlphaTimer = 255;
						explosion2->enemyAlphaTimer = 255;
						explosion3->enemyAlphaTimer = 255;
					}
				}
				if (lastboss.battleStart == true && lastboss.isAlive == true) {
					Boss2Pattern(lastboss, bossBeam[0], player->player.center, rasBossBaria);
					if (bossBeam[0].flag == true) {
						if (RectCollisionHit(bossBeam[0].pos, bossBeam[0].EndPos, player->player.center, player->player.radius, bossBeam[0].size) == true && player->hit == false) {

							player->hit = true;
							player->HP -= 1;
							attackHitTimer = 120;
						}
					}

					for (int i = 0; i < nucleusSuctionCount; i++) {
						BossBariaCollision(rasBossBaria, throwPos[i], hitradius[i], nucleusSuctionCount, throwDamageFlag[i]);
					}
					for (int i = 0; i < enemyNum; i++) {
						if (i >= 1) {
							enemy[i]->enemyAlive = false;
						}
					}
					enemy[0]->enemyAlive = true;
					enemy[0]->enemy.center = lastboss.pos;
					if (lastboss.isAlive == true) {
						if (CircleCollisinHit(player->player.center, player->player.radius, lastboss.pos, lastboss.radius) == true && player->reflect == false) {
							triangle->atackSpeed.x = -triangle->atackSpeed.x * 0.7;
							triangle->atackSpeed.y = -triangle->atackSpeed.y * 0.7;
							player->reflect = true;
							player->hit = true;
							attackHitTimer = 120;
							player->HP -= 1;
						}
					}
				}
			}
			if (gamemode == 7) {
				fadeoutFlag[0] = false;
				BossSetpos(lastboss);
				if (lastboss.isAlive == false) {
					bossBeam->flag = false;
				}
				if (lastboss.battleStart == true && lastboss.isAlive == true) {

					if (CircleCollisinHit(player->player.center, player->player.radius, lastboss.pos, lastboss.radius) == true && player->reflect == false) {
						triangle->atackSpeed.x = -triangle->atackSpeed.x * 0.7;
						triangle->atackSpeed.y = -triangle->atackSpeed.y * 0.7;
						player->hit = true;
						player->reflect = true;
						attackHitTimer = 120;
						player->HP -= 1;
					}

					for (int i = 0; i < enemyNum; i++) {

						enemy[i]->enemyAlive = false;

					}

					for (int i = 0; i < 2; i++) {

						Boss3Pattern(lastboss, bossBeam[0], bossBeam[1], player->player.center, rasBossBaria);
						if (bossBeam[i].flag == true) {
							if (RectCollisionHit(bossBeam[i].pos, bossBeam[i].EndPos, player->player.center, player->player.radius, bossBeam[i].size) == true && player->hit == false) {

								player->hit = true;
								player->HP -= 1;
								attackHitTimer = 120;
							}
						}
					}
					for (int i = 0; i < nucleusSuctionCount; i++) {
						BossBariaCollision(rasBossBaria, throwPos[i], hitradius[i], nucleusSuctionCount, throwDamageFlag[i]);
					}
					scrollMode = 1;
					beamPoint[0]->beamAtackStart = true;
					beams[0]->beamMode = 0;
				}
				if (lastboss.HP <= 0) {
					explosion->explosionFlag = true;
					explosion2->explosionFlag = true;
					explosion3->explosionFlag = true;
					explosion->Update();
					explosion2->Update();
					explosion3->Update();
					if (explosion->explosionCount >= 3) {
						gamemode += 1;
						explosion->explosionCount = 0;
						explosion2->explosionCount = 0;
						explosion3->explosionCount = 0;
						explosion->enemyAlphaTimer = 255;
						explosion2->enemyAlphaTimer = 255;
						explosion3->enemyAlphaTimer = 255;
					}
				}
			}
			if (scrollMode == 0) {
				boundPoint = { 2559,719 };
			}
			if (scrollMode == 1) {
				boundPoint = { 2559,1439 };
			}
			if (scrollMode == 2) {
				boundPoint = { 1280,720 };
			}
			//プレイヤーの操作
			if (triangle->pattern == 0 || triangle->pattern == 5 ) {

				player->Move(keys, preKeys, leftx, lefty, scrollWall, scrollWallEnd, scrollMode);
			}

			//通常移動時の移動可能範囲
			if (player->player.center.x >= boundPoint.x - player->player.radius) { //右方向
				player->player.center.x = boundPoint.x - player->player.radius;
			}
			if (player->player.center.x <= 0 + player->player.radius) { //左方向
				player->player.center.x = 0 + player->player.radius;
			}
			if (player->player.center.y <= player->player.radius) { //上方向
				player->player.center.y = player->player.radius;
			}
			if (player->player.center.y >= boundPoint.y - player->player.radius) { //下方向
				player->player.center.y = boundPoint.y - player->player.radius;
			}

			///スクロール終了時の座標修正
			if (player->player.center.x <= scrollWall.x) {
				player->scroll.x = 0.0f;
			}
			if (player->player.center.x >= 1920.0f) {
				player->scroll.x = 1280.0f;
			}
			if (player->player.center.y <= scrollWall.y) {
				player->scroll.y = 0.0f;
			}
			if (player->player.center.y >= 1080.0f) {
				player->scroll.y = 720.0f;
			}

			////画面端で跳ね返る
			if (player->player.center.x <= 0 + player->player.radius) {//左方向
				triangle->atackSpeed.x = -triangle->atackSpeed.x * 0.9;
				triangle->atackSpeed.x = -triangle->atackSpeed.x * 0.8;
			}
			if (player->player.center.x >= boundPoint.x - player->player.radius) {//右方向
				triangle->atackSpeed.x = -triangle->atackSpeed.x * 0.8;
			}
			if (player->player.center.y <= player->player.radius) {//上方向
				triangle->atackSpeed.y = -triangle->atackSpeed.y * 0.8;
			}
			if (player->player.center.y >= boundPoint.y - player->player.radius) {//下方向
				triangle->atackSpeed.y = -triangle->atackSpeed.y * 0.8;
			}

			for (int i = 0; i < enemyNum; i++) {
				if (enemy[i]->enemyAlive == true) {
					if (CircleCollisinHit(player->player.center, player->player.radius, enemy[i]->enemy.center, enemy[i]->enemy.radius) == true) {
						triangle->atackSpeed.x = -triangle->atackSpeed.x * 0.7;
						triangle->atackSpeed.y = -triangle->atackSpeed.y * 0.7;
					}
				}
			}
			if (triangle->pattern == 0) {
				girechange = true;
				girechangeCount = 0;
				triangle->atackSpeed = { 0,0 };
				for (int i = 0; i < nucleus[0]->max; i++) {
					if (nucleusResetFlag == false) {
						/*	nucleus[i]->nucleusPrePos.x = rand() % i * 640 + (i + 1) * 640;
							nucleus[i]->nucleusPrePos.y=rand()%i**/
						nucleusResetFlag = true;

					}
					nucleus[i]->nucleus.center = nucleus[i]->nucleusPrePos;
					nucleus[i]->nucleusSuctionFlag = false;
					nucleusSuctionFlag[i] = false;
					nucleus[i]->nucleus.radius = 32.0f;
					nucleuspicRadius[i] = 1;
					nucleus[i]->nucleus.color = WHITE;
					if (nucleus[i]->RespornCount >= 240) {
						nucleus[i]->isAlive = true;

						nucleus[i]->RespornCount = 0;
					}
				}
			}

			if (Novice::IsTriggerButton(0, kPadButton10) || keys[DIK_SPACE]) {

				triangle->PressCount++;
				//ゲージ
				girechange = true;
				girechangeCount = 0;
				if (triangle->PressCount >= 3) {
					triangle->PressCount = 0;
				}

			}
			if (girechange == true) {
				
				particleTriangle(particle, player->player.center);
				
				girechangeCount++;
			}
			else {
				for (int i = 0; i < 16; i++) {
					particle.par[i].isAlive = false;
				}
			}
			if (girechangeCount >= 60){
				girechange = false;
				girechangeCount = 0;
		}
			//スペースを押してなおかつ止まっているとき
			if (Novice::IsTriggerButton(0, kPadButton9) || preKeys[DIK_SPACE] && keys[DIK_SPACE] == 0 /*&& atackSpeed.x <= 0.3f && atackSpeed.x >= -0.3f && atackSpeed.y <= 0.3f && atackSpeed.y >= -0.3f*/) {
				//一つ目の点を求める
				
				if (triangle->PressCount == 0) {
					triangle->playerSpeed = 40;
				}
				if (triangle->PressCount == 1) {
					triangle->playerSpeed = 60;
				}
				if (triangle->PressCount == 2) {
					triangle->playerSpeed = 80;
				}
				if (triangle->pattern == 0) {
					girechange = true;
					girechangeCount = 0;
					triangle->playerEndSpeed = 0;
					triangle->triangleSpeed = 0;
					triangle->line.start = player->player.center;
					triangle->atackSpeed = { 0,0 };
					triangle->pattern = 1;
				}
				//二つ目の点を求める
				else if (triangle->pattern == 1) {
					girechange = true;
					girechangeCount = 0;
					triangle->line.vertex = player->player.center;
					triangle->preLineVertex = triangle->line.vertex;
					triangle->atackSpeed = { 0,0 };
					triangle->pattern = 2;
				}
				//三つ目の点を求める
				else if (triangle->pattern == 2) {
					girechange = true;
					girechangeCount = 0;
					triangle->line.end = player->player.center;
					triangle->preLineEnd = triangle->line.end;
					triangle->atackSpeed = { 0,0 };
					triangle->pattern = 3;
				}


				//プレイヤーを飛ばす
				if (triangle->pattern <= 2) {

					triangle->mouse = { (float)triangle->mouseX + player->scroll.x,(float)triangle->mouseY + player->scroll.y };
					triangle->playerAngle = VectorProduct(triangle->mouse, player->player.center);
					triangle->atackSpeed = Multiply(Normalais(triangle->playerAngle), triangle->playerSpeed);

				}
			}

			//プレイヤーのスピードを計算
			if (triangle->pattern <= 2) {
				triangle->atackSpeed = Multiply(triangle->atackSpeed, triangle->stop);
				if (player->player.center.x >= scrollWall.x && player->player.center.x <= scrollWallEnd.x) {
					player->scroll.x = player->player.center.x - 640;
				}
				if (player->player.center.y >= scrollWall.y && player->player.center.y <= scrollWallEnd.y && scrollMode == 1) {
					player->scroll.y = player->player.center.y - 360;
				}
			}
			//最期の点を求めてから最初の点に戻る
			if (triangle->pattern == 3) {
				if (triangle->playerEndSpeed <= 1.0) {
					triangle->playerEndSpeed += 0.1f;
				}
				player->player.center.x = learp(easeInSine(triangle->playerEndSpeed), triangle->line.end.x, triangle->line.start.x);
				player->player.center.y = learp(easeInSine(triangle->playerEndSpeed), triangle->line.end.y, triangle->line.start.y);
				if (player->player.center.x >= scrollWall.x && player->player.center.x <= scrollWallEnd.x) {
					player->scroll.x = player->player.center.x - 640;
				}
				if (player->player.center.y >= scrollWall.y && player->player.center.y <= scrollWallEnd.y && scrollMode == 1) {
					player->scroll.y = player->player.center.y - 360;
				}
				if (triangle->playerEndSpeed >= 1.0f) {
					triangle->pattern = 4;
				}
				playertheta[0] = 0;
				playertheta[1] = 1.0f / 2.0f * M_PI;
				playertheta[2] = M_PI;
				playertheta[3] = 3.0f / 2.0f * M_PI;
				nucleusSuctionCount = 0;
				for (int i = 0; i < 4; i++) {
					throwDamageFlag[i] = false;
					throwFlag[i] = false;
				}
				for (int i = 0; i < 12; i++) {
					nucleus[i]->nucleusCountfrag = false;

				}
			}
			//作った三角形を回収して武器にする
			if (triangle->pattern == 4) {
				triangleSide = sqrtf((triangle->originalLine.vertex.x - triangle->originalLine.end.x) * (triangle->originalLine.vertex.x - triangle->originalLine.end.x) + (triangle->originalLine.vertex.y - triangle->originalLine.end.y) * (triangle->originalLine.vertex.y - triangle->originalLine.end.y));

				Vector2  lineStartToEnd = { triangle->line.start.x - triangle->preLineEnd.x,triangle->line.start.y - triangle->preLineEnd.y };
				Vector2  lineStartToEndRadian = Normalais(lineStartToEnd);
				Vector2  lineStartToEndAngle = Multiply(lineStartToEndRadian, triangleSide);
				Vector2 triangleTop = Add(triangle->line.start, lineStartToEndAngle);

				Vector2  lineStartToVertex = { triangle->line.start.x - triangle->preLineVertex.x,triangle->line.start.y - triangle->preLineVertex.y };
				Vector2  lineStartToVertexRadian = Normalais(lineStartToVertex);
				Vector2  lineStartToVertexAngle = Multiply(lineStartToVertexRadian, triangleSide);
				Vector2 triangleDown = Add(triangle->line.start, lineStartToVertexAngle);

				if (triangle->triangleSpeed <= 1.0) {
					triangle->triangleSpeed += 0.15;
				}

				triangle->line.end.x = learp(easeInSine(triangle->triangleSpeed), triangle->preLineEnd.x, triangleTop.x);
				triangle->line.end.y = learp(easeInSine(triangle->triangleSpeed), triangle->preLineEnd.y, triangleTop.y);

				triangle->line.vertex.x = learp(easeInSine(triangle->triangleSpeed), triangle->preLineVertex.x, triangleDown.x);
				triangle->line.vertex.y = learp(easeInSine(triangle->triangleSpeed), triangle->preLineVertex.y, triangleDown.y);
			}

			player->player.center = Add(player->player.center, triangle->atackSpeed);


			//三角形と核の当たり判定を計算する
			for (int i = 0; i < nucleus[0]->max; i++) {
				if (nucleus[i]->isAlive == true) {
					nucleus[i]->exterior = Product(triangle->line.start, triangle->line.end, nucleus[i]->nucleus.center);

					nucleus[i]->exterior2 = Product(triangle->line.end, triangle->line.vertex, nucleus[i]->nucleus.center);

					nucleus[i]->exterior3 = Product(triangle->line.vertex, triangle->line.start, nucleus[i]->nucleus.center);
					if (triangle->pattern == 4) {
						if (nucleus[i]->exterior > 0.0f && nucleus[i]->exterior2 > 0.0f && nucleus[i]->exterior3 > 0.0f || nucleus[i]->exterior < 0.0f && nucleus[i]->exterior2 < 0.0f && nucleus[i]->exterior3 < 0.0f) {
							nucleus[i]->nucleus.color = BLUE;
							nucleus[i]->isAlive = false;
							nucleusSuctionFlag[i] = true;
							powerFlag = true;
							if (nucleus[i]->nucleusCountfrag == false) {
								nucleusSuctionCount++;
								if (nucleusSuctionCount >= 4) {
									nucleusSuctionCount = 4;
								}
								atackdamage = nucleusSuctionCount;
								nucleus[i]->nucleusCountfrag = true;
							}
						}
						else {
							nucleus[i]->nucleus.color = WHITE;

						}
					}
				}
				
			}
			if (powerFlag == true) {
				powerCount++;
			}
			if (powerCount >= 60) {
				powerCount = 0;
				powerFlag = false;
			}

			triangleBreak = lineSearch(nucleusSuctionFlag, nucleus[0]->max);

			//三角形と敵の当たり判定
			for (int i = 0; i < 2; i++) {

				nucleus[i]->enemyexterior = Product(triangle->line.start, triangle->line.vertex, enemy[i]->enemy.center);
				nucleus[i]->enemyexterior2 = Product(triangle->line.vertex, triangle->line.end, enemy[i]->enemy.center);


				nucleus[i]->enemyexterior3 = Product(triangle->line.end, triangle->line.start, enemy[i]->enemy.center);

				if (triangle->pattern == 4) {
					if (nucleus[i]->enemyexterior > 0.0f && nucleus[i]->enemyexterior2 > 0.0f && nucleus[i]->enemyexterior3 > 0.0f || nucleus[i]->enemyexterior < 0.0f && nucleus[i]->enemyexterior2 < 0.0f && nucleus[i]->enemyexterior3 < 0.0f) {
						if (enemy[i]->enemyAlive == true) {
							triangleBreak = false;
						}

					}

				}

			}

			for (int i = 0; i < nucleus[0]->max; i++) {
				if (nucleus[i]->isAlive == false) {
					nucleus[i]->RespornCount++;
				}
				if (triangle->pattern >= 4) {
					if (triangleBreak == true) {
						/*if (nucleus[i]->nucleusSuctionFlag == true) {*/
						if (nucleusSuctionFlag[i] == true) {

							nucleus[i]->nucleus.center.x = learp(easeInSine(triangle->triangleSpeed), nucleus[i]->nucleusPrePos.x, triangle->line.start.x);
							nucleus[i]->nucleus.center.y = learp(easeInSine(triangle->triangleSpeed), nucleus[i]->nucleusPrePos.y, triangle->line.start.y);
							nucleus[i]->nucleus.radius = learp(easeInSine(triangle->triangleSpeed), 32, 0);
							nucleuspicRadius[i] = learp(easeInSine(triangle->triangleSpeed), 1, 0);
							if (triangle->triangleSpeed >= 1.0f) {
								triangle->triangleSpeed = 1;
							}

							nucleus[i]->nucleusSuctionPos.x = (triangle->line.start.x + triangle->line.end.x + triangle->line.vertex.x) / 3;
							nucleus[i]->nucleusSuctionPos.y = (triangle->line.start.y + triangle->line.end.y + triangle->line.vertex.y) / 3;


							if (triangle->triangleSpeed >= 1.0f) {

								triangle->pattern = 5;
							}
						}
					}
					else {
						triangle->pattern = 0;
						for (int j = 0; j < 4; j++) {
							throwFlag[j] = false;
						}
						nucleus[i]->nucleus.radius = 32;
						nucleuspicRadius[i] = 1;
					}
				}
			}

			//攻撃の準備をする
			if (triangle->pattern == 5) {
				for (int i = 0; i < nucleusSuctionCount; i++) {
					if (throwFlag[i] == false) {
						throwPos[i].x = (Start[i].x + End[i].x + Vertex[i].x) / 3;
						throwPos[i].y = (Start[i].y + End[i].y + Vertex[i].y) / 3;

						playertheta[i] += 1 / 30.0f;
						theta += 1 / 10.0f;
						throwPos[i] = { player->player.center.x + cosf(playertheta[i]) * 60,player->player.center.y + sinf(playertheta[i]) * 60 };
						Matrix2x2 rotateMatrix = MakeRotateMatrix(theta);

						Start[i] = MatrixMultiply(triangle->originalLine.start, rotateMatrix);

						Vertex[i] = MatrixMultiply(triangle->originalLine.vertex, rotateMatrix);

						End[i] = MatrixMultiply(triangle->originalLine.end, rotateMatrix);

						Start[i] = Add(Start[i], throwPos[i]);
						Vertex[i] = Add(Vertex[i], throwPos[i]);
						End[i] = Add(End[i], throwPos[i]);
					}
				}
				//攻撃フラグをtureにする
				if (Novice::IsTriggerButton(0, kPadButton9) || keys[DIK_V] && preKeys[DIK_V] == 0 || Novice::IsPressMouse(0)) {
					mousePressTime++;
					mousePress = true;
					for (int i = 0; i < nucleusSuctionCount; i++) {

						if (throwFlag[i] == false) {
							throwAngle[i] = { (float)triangle->mouseX - throwPos[i].x + player->scroll.x,(float)triangle->mouseY - throwPos[i].y + player->scroll.y };
							throwradian[i] = Normalais(throwAngle[i]);
							throwSpeed[i] = Multiply(throwradian[i], 16);
							throwDamageFlag[i] = true;




							throwFlag[i] = true;
							if (throwFlag[nucleusSuctionCount - 1] == true) {
								triangle->pattern = 0;
								for (int j = 0; j < nucleus[0]->max; j++) {
									//nucleus[j]->nucleusSuctionFlag = false;

								}
							}
							break;
						}
					}
				}
			}

			//攻撃処理
			for (int i = 0; i < nucleusSuctionCount; i++) {
				if (throwDamageFlag[i] == true) {
					throwPos[i] = Add(throwPos[i], throwSpeed[i]);
					theta += 1 / 10.0f;
					Matrix2x2 rotateMatrix = MakeRotateMatrix(theta);

					Start[i] = MatrixMultiply(triangle->originalLine.start, rotateMatrix);

					Vertex[i] = MatrixMultiply(triangle->originalLine.vertex, rotateMatrix);

					End[i] = MatrixMultiply(triangle->originalLine.end, rotateMatrix);

					Start[i] = Add(Start[i], throwPos[i]);
					Vertex[i] = Add(Vertex[i], throwPos[i]);
					End[i] = Add(End[i], throwPos[i]);


					hitradius[i] = sqrtf((throwPos[i].x - Start[i].x) * (throwPos[i].x - Start[i].x) + (throwPos[i].y - Start[i].y) * (throwPos[i].y - Start[i].y));



				}
				//攻撃とエネミーの当たり判定
				for (int j = 0; j < 3; j++) {
					if (enemy[j]->enemyAlive == true && throwDamageFlag[i] == true) {
						if (CircleCollisinHit(throwPos[i], hitradius[i], enemy[j]->enemy.center, enemy[j]->enemy.radius) == true) {
							enemy[j]->enemyAlive = false;
							throwDamageFlag[i] = false;
						}
					}
				}
				if (throwDamageFlag[i] == true) {
					if (CircleCollisinHit(throwPos[i], hitradius[i], lastboss.pos, lastboss.radius) == true) {
						throwDamageFlag[i] = false;
						lastboss.HP -= atackdamage;
						//lastboss.HP -= 10;
					}
				}
				for (int j = 0; j < 4; j++) {
					if (throwDamageFlag[i] == true && beamPoint[j]->beamAlive == true) {

						if (CircleCollisinHit(throwPos[i], hitradius[i], beamPoint[j]->beamPoint.center, beamPoint[j]->beamPoint.radius) == true) {
							throwDamageFlag[i] = false;
							beamPoint[j]->beamAlive = false;
							beamPoint[j]->Break = true;
						}
					}

				}
			}

			//画面内の敵を感知
			for (int i = 0; i < enemyNum; i++) {
				if (enemy[i]->enemy.center.x > player->player.center.x - 1280 / 2 && enemy[i]->enemy.center.x < player->player.center.x + 1280 / 2) {
					enemy[i]->enemyScreenIn = true;
				}
				else {
					enemy[i]->enemyScreenIn = false;
				}
			}

			//誘導弾
			for (int j = 0; j < enemyNum; j++) {
				for (int i = 0; i < bulletNum; i++) {
					if (bullet[i]->bulletOnFlag == false && bullet[j]->bullettimer <= 0 && enemy[j]->enemyAlive == true && enemy[j]->enemyScreenIn == true && lastboss.isAlive == true) {
						bullet[i]->bullet.center = { enemy[j]->enemy.center.x ,enemy[j]->enemy.center.y };
						bullet[i]->bulletOnFlag = true;
						bullet[j]->bullettimer = 80 + 20 * i;
						bullet[i]->bulletInductionOnFlag = true;
					}
				}
				bullet[j]->bullettimer--;
			}

			for (int i = 0; i < bulletNum; i++) {
				if (bullet[i]->bulletOnFlag == true) {//弾を置いたら
					bullet[i]->bulletEndTimer--;
					bullet[i]->bullet.speed = Multiply(Normalais(bullet[i]->bulletAngle), 6);
					bullet[i]->bullet.center = Add(bullet[i]->bullet.center, bullet[i]->bullet.speed);
					if (bullet[i]->bulletInductionOnFlag == true) {//誘導時間忠
						bullet[i]->bulletInductionTimer--;
						bullet[i]->bulletAngle = { (float)player->player.center.x - bullet[i]->bullet.center.x, (float)player->player.center.y - bullet[i]->bullet.center.y };
					}
					if (CircleCollisinHit(bullet[i]->bullet.center, bullet[i]->bullet.radius, player->player.center, player->player.radius) == true) {//ボールと弾がぶつかったとき
						//playerFlag = false;//生存判定をfalseにする
						bullet[i]->bulletInductionTimer = 10;
						bullet[i]->bulletInductionOnFlag = false;
						bullet[i]->bulletOnFlag = false;
						bullet[i]->bulletEndTimer = 400;
						player->HP -= 1;
						attackHitTimer = 120;
					}
				}

				if (bullet[i]->bulletEndTimer <= 0) {
					bullet[i]->bulletInductionTimer = 10;
					bullet[i]->bulletInductionOnFlag = false;
					bullet[i]->bulletOnFlag = false;
					bullet[i]->bulletEndTimer = 400;
				}

				if (bullet[i]->bulletInductionTimer <= 0) {//誘導タイマーが0で誘導終了
					bullet[i]->bulletInductionOnFlag = false;
					bullet[i]->bullet.speed = Multiply(Normalais(bullet[i]->bulletAngle), 4);
					bullet[i]->bullet.center = Add(bullet[i]->bullet.center, bullet[i]->bullet.speed);
				}
			}


			//スタン
			if (stunOnFlag == true) {
				triangle->pattern = 5;
				shakeTimer--;
				triangle->atackSpeed = { 0,0 };
				if (shakeTimer <= 255 && shakeTimer > 0) {
					RandShake.x = rand() % 11 - 5;
					RandShake.y = rand() % 11 - 5;
				}
				if (shakeTimer < 0) {
					shakeTimer = 60;
					stunOnFlag = false;
				}
			}

			//ビーム
			beams[0]->beemStart = { 1280 ,720 };
			for (int i = 0; i < 4; i++) {
				if (lastboss.isAlive == false) {
					beams[i]->atackFlag = false;
					beams[i]->preAtack = false;
					beams[i]->atackCount = 0;
					beams[i]->preCount = 0;
					beamPreCount = 0;
					if (gamemode <= 7) {
						beamPoint[i]->beamAlive = true;
					}
				}
			}
			if (beamPoint[0]->beamAtackStart == true && lastboss.battleStart == true) {
				if (beams[0]->beamMode == 0) {
					beamPreCount++;
				}
				for (int i = 0; i < 4; i++) {


					if (beamPreCount >= 10 && beamPreCount <= 40 || beamPreCount >= 60 && beamPreCount <= 90) {

						beams[i]->preAtack = true;
					}
					else {
						beams[i]->preAtack = false;
					}



				}

			}

			for (int i = 0; i < 4; i++) {

				beams[i]->beam.pos = beams[0]->beemStart;
				beams[i]->beam.angle = { beamPoint[i]->beamPoint.center.x - beams[0]->beemStart.x ,beamPoint[i]->beamPoint.center.y - beams[0]->beemStart.y };
				beams[i]->beam.radian = Normalais(beams[i]->beam.angle);
				beams[i]->beam.EndPos = Multiply(beams[i]->beam.radian, Distance(beamPoint[i]->beamPoint.center, { 1280,720 }));

				beams[i]->beam.EndPos.x += beams[i]->beam.pos.x;
				beams[i]->beam.EndPos.y += beams[i]->beam.pos.y;

				beams[i]->BTop.radian = { -beams[i]->beam.radian.y,beams[i]->beam.radian.x };
				beams[i]->BTop.angle = Multiply(beams[i]->BTop.radian, 32);
				beams[i]->BTop.pos = { beams[i]->beam.pos.x + beams[i]->BTop.angle.x,beams[i]->beam.pos.y + beams[i]->BTop.angle.y };
				beams[i]->BTop.EndPos = { beams[i]->beam.EndPos.x + beams[i]->BTop.angle.x,beams[i]->beam.EndPos.y + beams[i]->BTop.angle.y };

				beams[i]->BDown.radian = { beams[i]->beam.radian.y,-beams[i]->beam.radian.x };
				beams[i]->BDown.angle = Multiply(beams[i]->BDown.radian, 32);
				beams[i]->BDown.pos = { beams[i]->beam.pos.x + beams[i]->BDown.angle.x,beams[i]->beam.pos.y + beams[i]->BDown.angle.y };
				beams[i]->BDown.EndPos = { beams[i]->beam.EndPos.x + beams[i]->BDown.angle.x,beams[i]->beam.EndPos.y + beams[i]->BDown.angle.y };

				if (beamPreCount == 120 && beamPoint[i]->beamAlive == true) {
					beams[i]->atackFlag = true;

				}
			}
			for (int i = 0; i < 4; i++) {
				if (beamPreCount > 200) {
					beams[i]->atackFlag = false;
					beams[i]->preAtack = true;
					beamAttackchange += 1;
					beamPreCount = 0;
				}
				if (beamPreCount < 120) {
					beams[i]->atackFlag = false;
				}
				if (beamPoint[i]->beamAlive == false) {

					beams[i]->atackFlag = false;
					beams[i]->preAtack = false;

				}
			}

			if (beamAttackchange <= 5) {
				beamPoint[0]->beamPoint = { 0 + beamPoint[0]->beamPoint.radius,0 + beamPoint[0]->beamPoint.radius,36.0f,6.0f,RED,100 };
				beamPoint[2]->beamPoint = { 2560 - beamPoint[0]->beamPoint.radius,0 + beamPoint[0]->beamPoint.radius,36.0f,6.0f,RED,100 };
				beamPoint[3]->beamPoint = { 0 + beamPoint[0]->beamPoint.radius,1440 - beamPoint[0]->beamPoint.radius,36.0f,6.0f,RED,100 };
				beamPoint[1]->beamPoint = { 2560 - beamPoint[0]->beamPoint.radius,1440 - beamPoint[0]->beamPoint.radius,36.0f,6.0f,RED,100 };
			}
			if (beamAttackchange > 5) {
				beamPoint[0]->beamPoint = { 1280,0 + beamPoint[0]->beamPoint.radius,36.0f,6.0f,RED,100 };
				beamPoint[2]->beamPoint = { 2560 - beamPoint[0]->beamPoint.radius,720,36.0f,6.0f,RED,100 };
				beamPoint[1]->beamPoint = { 1280,1440 - beamPoint[0]->beamPoint.radius,36.0f,6.0f,RED,100 };
				beamPoint[3]->beamPoint = { 0 + beamPoint[0]->beamPoint.radius,720,36.0f,6.0f,RED,100 };
			}

			if (beamAttackchange > 10) {
				beamAttackchange = 0;
			}
			for (int i = 0; i < 4; i++) {
				if (beams[i]->atackFlag == true) {
					beams[i]->atackCount++;
					if (RectCollisionHit(beams[i]->beam.pos, beams[i]->beam.EndPos, player->player.center, 32, player->player.radius) == true && player->hit == false) {//自機の生死フラグ = false;

						beemHit = true;
						triangle->atackSpeed.x = triangle->atackSpeed.x * 0.8;
						triangle->atackSpeed.y = triangle->atackSpeed.y * 0.8;
						player->hit = true;
						player->HP -= 1;
						attackHitTimer = 120;
					}
				}
				if (beams[i]->atackCount >= 40) {
					beams[i]->atackCount = 0;
				}
				if (beamPoint[i]->Break == true) {
					beamPoint[i]->Resporn++;
				}
				if (beamPoint[i]->Resporn >= 500 && beamPreCount == 0) {
					beamPoint[i]->beamAlive = true;
					beamPoint[i]->Break - false;
					beamPoint[i]->Resporn = 0;
				}


			}
			if (lastboss.HP <= 0) {
				lastboss.isAlive = false;
			}

			if (attackHitTimer > 0) {
				attackHitTimer--;
			}
			else {
				attackHitTimer = 0;
			}


			//デバッグ用エンターで戻す
			if (Novice::IsPressButton(0, kPadButton8) || preKeys[DIK_RETURN] && keys[DIK_RETURN] == 0) {
				triangle->pattern = 0;
				beemHit = false;
				for (int i = 0; i < nucleusSuctionCount; i++) {
					throwFlag[i] = false;
				}

			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawSprite(1280 * 0 - player->scroll.x, 720 * 0 - player->scroll.y, BGPic, 1, 1, 0.0f, 0xffffffff);
		Novice::DrawSprite(1280 * 1 - player->scroll.x + RandShake.x, 720 * 0 - player->scroll.y + RandShake.y, BGPic, 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(1280 * 0 - player->scroll.x + RandShake.x, 720 * 1 - player->scroll.y + RandShake.y, BGPic, 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(1280 * 1 - player->scroll.x + RandShake.x, 720 * 1 - player->scroll.y + RandShake.y, BGPic, 1, 1, 0.0f, 0xFFFFFFFF);

		if (gamemode == 0) {//ゲーム開始画面
			Novice::DrawSprite(0, 0, StartBG, 1, 1, 0, 0xffffffff);
			Novice::DrawSprite(0, 0, kakomePic, 1, 1, 0, 0xffffffff);
		}

		if (gamemode == 1 || gamemode == 3 || gamemode == 5 || gamemode == 7) {//ゲームスタート
			if (gamemode == 1) {//ステージ1
				for (int i = 0; i < 6; i++) {
					Novice::DrawBox(tutrial[i].pos.x - player->scroll.x, tutrial[i].pos.y - player->scroll.y, tutrial[i].sizeX, tutrial[i].sizeY, 0, 0x333333ff, kFillModeSolid);
					if (i == 0) {

						Novice::DrawSprite(tutrial[i].Ob.x - player->scroll.x, tutrial[i].Ob.y - player->scroll.y, playerPic, 0.5, 0.5, 0, WHITE);
						Novice::DrawSprite(tutrial[i].player.center.x - player->scroll.x, tutrial[i].player.center.y - player->scroll.y - 80, Lstickpic, 2, 2, 0, WHITE);

					}
				}
				if (tutrial[1].downFlag == true) {
					TutrialGauge(tutrial[1], player->scroll,LTpic,Rstickpic,RBpic,playerPic,speed1Pic,speed2Pic,speed3Pic);
				}
				if (tutrial[2].downFlag == true) {
					TutrialMoveReset(tutrial[2], player->scroll, playerPic, LBpic);
				}
				
				if (tutrial[3].downFlag == true) {
					TutorialRepel(tutrial[3], playerPic, nucleusPic, player->scroll);
				}
				if (tutrial[4].downFlag == true) {
					TutrialAttack(tutrial[4], player->scroll, playerPic, Rstickpic, RBpic);
				}
				if (tutrial[5].downFlag == true) {
					TutorialPowerUp(tutrial[5], player->scroll, playerPic, nucleusPic, power1Pic);
				}
			}

			if (triangle->pattern == 1) {
				Novice::DrawLine(triangle->line.start.x - player->scroll.x + RandShake.x, triangle->line.start.y - player->scroll.y + RandShake.y, player->player.center.x - player->scroll.x + RandShake.x, player->player.center.y - player->scroll.y + RandShake.y, WHITE);
			}
			if (triangle->pattern == 2) {
				Novice::DrawLine(player->player.center.x - player->scroll.x + RandShake.x, player->player.center.y - player->scroll.y + RandShake.y, triangle->line.vertex.x - player->scroll.x + RandShake.x, triangle->line.vertex.y - player->scroll.y + RandShake.y, WHITE);
				Novice::DrawLine(triangle->line.start.x - player->scroll.x + RandShake.x, triangle->line.start.y - player->scroll.y + RandShake.y, triangle->line.vertex.x - player->scroll.x + RandShake.x, triangle->line.vertex.y - player->scroll.y + RandShake.y, WHITE);
			}
			if (triangle->pattern == 3) {
				Novice::DrawLine(triangle->line.end.x - player->scroll.x + RandShake.x, triangle->line.end.y - player->scroll.y + RandShake.y, triangle->line.vertex.x - player->scroll.x + RandShake.x, triangle->line.vertex.y - player->scroll.y + RandShake.y, WHITE);
				Novice::DrawLine(triangle->line.start.x - player->scroll.x + RandShake.x, triangle->line.start.y - player->scroll.y + RandShake.y, triangle->line.vertex.x - player->scroll.x + RandShake.x, triangle->line.vertex.y - player->scroll.y + RandShake.y, WHITE);
				Novice::DrawLine(triangle->line.end.x - player->scroll.x + RandShake.x, triangle->line.end.y - player->scroll.y + RandShake.y, player->player.center.x - player->scroll.x + RandShake.x, player->player.center.y - player->scroll.y + RandShake.y, WHITE);
			}
			if (triangle->pattern == 4) {
				Novice::DrawTriangle(triangle->line.start.x - player->scroll.x + RandShake.x, triangle->line.start.y - player->scroll.y + RandShake.y, triangle->line.end.x - player->scroll.x + RandShake.x, triangle->line.end.y - player->scroll.y + RandShake.y, triangle->line.vertex.x - player->scroll.x + RandShake.x, triangle->line.vertex.y - player->scroll.y + RandShake.y, WHITE, kFillModeWireFrame);
			}
			for (int i = 0; i < nucleusSuctionCount; i++) {
				if (triangle->pattern == 5) {
					if (throwFlag[i] == false) {
						Novice::DrawTriangle(Start[i].x - player->scroll.x + RandShake.x, Start[i].y - player->scroll.y + RandShake.y, End[i].x - player->scroll.x + RandShake.x, End[i].y - player->scroll.y + RandShake.y, Vertex[i].x - player->scroll.x + RandShake.x, Vertex[i].y - player->scroll.y + RandShake.y, WHITE, kFillModeWireFrame);
					}

				}

				if (throwDamageFlag[i] == true) {
					Novice::DrawTriangle(Start[i].x - player->scroll.x + RandShake.x, Start[i].y - player->scroll.y + RandShake.y, End[i].x - player->scroll.x + RandShake.x, End[i].y - player->scroll.y + RandShake.y, Vertex[i].x - player->scroll.x + RandShake.x, Vertex[i].y - player->scroll.y + RandShake.y, WHITE, kFillModeWireFrame);
					Novice::DrawEllipse(throwPos[i].x - player->scroll.x + RandShake.x, throwPos[i].y - player->scroll.y + RandShake.y, hitradius[i], hitradius[i], 0, RED, kFillModeWireFrame);
				}
			}

			for (int i = 0; i < bulletNum; i++) {//弾
				if (bullet[i]->bulletOnFlag == true) {
					Novice::DrawSprite(bullet[i]->bullet.center.x - player->scroll.x + RandShake.x - bullet[i]->bullet.radius, bullet[i]->bullet.center.y - player->scroll.y + RandShake.y - bullet[i]->bullet.radius, BulletPic, 1, 1, 0, WHITE);

				}
			}

			if (playerFlag == true) {//自機(仮)
				float monitorx = player->player.center.x - player->scroll.x;
				float monitory = player->player.center.y - player->scroll.y;
				float aimx = monitorx + triangle->mouseX / 1000 + RandShake.x;
				float aimy = monitory + triangle->mouseY / 1000 + RandShake.y;
				for (int i = 0; i < 12; i++) {
					if (girechange == true) {
						if (triangle->PressCount == 0) {
							Novice::DrawTriangle(particle.par[i].start.x-player->scroll.x, particle.par[i].start.y - player->scroll.y, particle.par[i].vertex.x - player->scroll.x, particle.par[i].vertex.y - player->scroll.y, particle.par[i].End.x - player->scroll.x, particle.par[i].End.y - player->scroll.y, GetColor(148,214,218,155), kFillModeSolid);
						}
						if (triangle->PressCount == 1) {
							Novice::DrawTriangle(particle.par[i].start.x - player->scroll.x, particle.par[i].start.y - player->scroll.y, particle.par[i].vertex.x - player->scroll.x, particle.par[i].vertex.y - player->scroll.y, particle.par[i].End.x - player->scroll.x, particle.par[i].End.y - player->scroll.y, GetColor(204,255,102,155), kFillModeSolid);

						}
						if (triangle->PressCount == 2) {
							Novice::DrawTriangle(particle.par[i].start.x - player->scroll.x, particle.par[i].start.y - player->scroll.y, particle.par[i].vertex.x - player->scroll.x, particle.par[i].vertex.y - player->scroll.y, particle.par[i].End.x - player->scroll.x, particle.par[i].End.y - player->scroll.y, 0xcd5c5c9b, kFillModeSolid);

						}
					}
				}
				if (powerFlag == true) {
					if (nucleusSuctionCount == 2) {
						Novice::DrawSprite(monitorx + RandShake.x - player->player.radius, monitory + RandShake.y - player->player.radius * 4, power1Pic, 0.5, 0.5, 0, WHITE);
					}
					else if (nucleusSuctionCount == 2) {
						Novice::DrawSprite(monitorx + RandShake.x - player->player.radius, monitory + RandShake.y - player->player.radius * 4, power2Pic, 0.5, 0.5, 0, WHITE);

					}
					else if (nucleusSuctionCount == 3) {
						Novice::DrawSprite(monitorx + RandShake.x - player->player.radius, monitory + RandShake.y - player->player.radius * 4, power3Pic, 0.5, 0.5, 0, WHITE);

					}
				}
				if (player->hit == false) {
					if (triangle->pattern == 0) {
						if (triangle->PressCount == 0) {
							Novice::DrawSprite(monitorx + RandShake.x - player->player.radius * 2, monitory + RandShake.y - player->player.radius * 2, speed1Pic, 1, 1, 0, WHITE);
						}
						else if (triangle->PressCount == 1) {
							Novice::DrawSprite(monitorx + RandShake.x - player->player.radius * 2, monitory + RandShake.y - player->player.radius * 2, speed2Pic, 1, 1, 0, WHITE);

						}
						else if (triangle->PressCount == 2) {
							Novice::DrawSprite(monitorx + RandShake.x - player->player.radius * 2, monitory + RandShake.y - player->player.radius * 2, speed3Pic, 1, 1, 0, WHITE);

						}
					}
					Novice::DrawSprite(monitorx + RandShake.x - player->player.radius, monitory + RandShake.y - player->player.radius, playerPic, 1, 1, 0, WHITE);
					Novice::DrawSprite(aimx - 10, aimy - 10, playerAimPic, 1, 1, 0, WHITE);
				}
				else {
					if (player->hitCount % 3 != 0) {
						Novice::DrawSprite(monitorx + RandShake.x - player->player.radius, monitory + RandShake.y - player->player.radius, playerPic, 1, 1, 0, WHITE);
						Novice::DrawSprite(aimx - 10, aimy - 10, playerAimPic, 1, 1, 0, WHITE);
					}
				}
				if (attackHitTimer > 0) {
					Novice::DrawSprite(monitorx + RandShake.x - player->player.radius - 30, monitory + RandShake.y - player->player.radius - 60, hpBar1, 1, 1, 0.0f, 0xFFFFFFFF);
					Novice::DrawBox(monitorx + RandShake.x - player->player.radius - 30 + 3, monitory + RandShake.y - player->player.radius - 60 + 20, player->HP * 4, 24, 0.0f, RED, kFillModeSolid);
					Novice::DrawSprite(monitorx + RandShake.x - player->player.radius - 30, monitory + RandShake.y - player->player.radius - 60, hpBar2, 1, 1, 0.0f, 0xFFFFFFFF);
				}
			}

			for (int i = 0; i < nucleus[0]->max; i++) {

				if (nucleusSuctionFlag[i] == false) {
					if (nucleus[i]->isAlive == true) {
						Novice::DrawSprite(nucleus[i]->nucleus.center.x - player->scroll.x + RandShake.x - nucleus[i]->nucleus.radius, nucleus[i]->nucleus.center.y - player->scroll.y + RandShake.y - nucleus[i]->nucleus.radius, nucleusPic, nucleuspicRadius[i], nucleuspicRadius[i], 0, WHITE);
					}
				}
				else {
					Novice::DrawSprite(nucleus[i]->nucleusSuctionPos.x - player->scroll.x + RandShake.x - nucleus[i]->nucleus.radius, nucleus[i]->nucleusSuctionPos.y - player->scroll.y + RandShake.y - nucleus[i]->nucleus.radius, nucleusPic, nucleuspicRadius[i], nucleuspicRadius[i], 0, WHITE);


				}
			}







			for (int i = 0; i < beamNum; i++) {//ビームポイント
				if (beams[i]->atackFlag == true) {
					Novice::DrawQuad(beams[i]->BTop.pos.x - player->scroll.x, beams[i]->BTop.pos.y - player->scroll.y, beams[i]->BTop.EndPos.x - player->scroll.x, beams[i]->BTop.EndPos.y - player->scroll.y, beams[i]->BDown.pos.x - player->scroll.x, beams[i]->BDown.pos.y - player->scroll.y, beams[i]->BDown.EndPos.x - player->scroll.x, beams[i]->BDown.EndPos.y - player->scroll.y, 0, 0, 1280, 32, BeamPic, WHITE);

				}
				if (beams[i]->preAtack == true) {

					Novice::DrawQuad(beams[i]->BTop.pos.x - player->scroll.x, beams[i]->BTop.pos.y - player->scroll.y, beams[i]->BTop.EndPos.x - player->scroll.x, beams[i]->BTop.EndPos.y - player->scroll.y, beams[i]->BDown.pos.x - player->scroll.x, beams[i]->BDown.pos.y - player->scroll.y, beams[i]->BDown.EndPos.x - player->scroll.x, beams[i]->BDown.EndPos.y - player->scroll.y, 0, 0, 1, 1, WhiteP, 0xFFFF33);



				}
			}
			for (int i = 0; i < beamNum; i++) {//ビームポイント
				if (beamPoint[i]->beamAlive == true) {
					Novice::DrawSprite(beamPoint[i]->beamPoint.center.x - player->scroll.x + RandShake.x - beamPoint[i]->beamPoint.radius, beamPoint[i]->beamPoint.center.y - player->scroll.y + RandShake.y - beamPoint[i]->beamPoint.radius, BeamPointPic, 1, 1, 0, WHITE);
				}
				
			}

			if (gamemode == 1) {
				for (int i = 0; i < enemyNum; i++) {//敵

					if (enemy[i]->enemyAlive == true) {
						Novice::DrawSprite(enemy[i]->enemy.center.x - player->scroll.x + RandShake.x - enemy[i]->enemy.radius, enemy[i]->enemy.center.y - player->scroll.y + RandShake.y - enemy[i]->enemy.radius, BeamPointPic, 1, 1, 0, WHITE);
						;
					}
				}
			}
			
			Novice::DrawQuad(gaugeleft.x, gaugeleft.y, gaugeleft.x, gaugeleft.y + 30, gaugeRight.x, gaugeRight.y, gaugeRight.x, gaugeRight.y + 30, 0, 0, 100, 100, WhiteP, WHITE);

			for (int i = 0; i < 2; i++) {
				if (bossBeam[i].flag == true) {

					Novice::DrawQuad(bossBeam[i].leftTop.x - player->scroll.x, bossBeam[i].leftTop.y - player->scroll.y, bossBeam[i].rightTop.x - player->scroll.x, bossBeam[i].rightTop.y - player->scroll.y, bossBeam[i].leftDown.x - player->scroll.x, bossBeam[i].leftDown.y - player->scroll.y, bossBeam[i].rightDown.x - player->scroll.x, bossBeam[i].rightDown.y - player->scroll.y, 0, 0, 1, 1, WhiteP, WHITE);
				}
			}
			if (gamemode >= 3) {

				if (gamemode == 7) {
					BossDanger(lastboss, player->scroll, dangerPic);
					DrawQuad(lastboss.leftTop, lastboss.leftDown, lastboss.rightTop, lastboss.rightDown, player->scroll, Bosspic[0], GetColor(255, 255, 255, explosion->enemyAlphaTimer), 0, 0, 256, 256, lastboss.randPos);

				}
				else if (gamemode == 5) {
					BossDanger(lastboss, player->scroll, dangerPic);
					DrawQuad(lastboss.leftTop, lastboss.leftDown, lastboss.rightTop, lastboss.rightDown, player->scroll, Bosspic[1], GetColor(255, 255, 255, explosion->enemyAlphaTimer), 0, 0, 256, 256, lastboss.randPos);

				}
				else if (gamemode == 3) {
					BossDanger(lastboss, player->scroll, dangerPic);
					DrawQuad(lastboss.leftTop, lastboss.leftDown, lastboss.rightTop, lastboss.rightDown, player->scroll, Bosspic[2], GetColor(255, 255, 255, explosion->enemyAlphaTimer), 0, 0, 256, 256, lastboss.randPos);
				}
				if (lastboss.isAlive == true) {
					Novice::DrawSprite(lastboss.pos.x - player->scroll.x - 64, lastboss.pos.y - player->scroll.y - 170, hpBar1, 1, 1, 0.0f, 0xFFFFFFFF);

					if (gamemode == 3) {
						Novice::DrawBox(lastboss.pos.x - player->scroll.x - 61, lastboss.pos.y - player->scroll.y - 150, (lastboss.HP + lastboss.HP / 5) * 4, 24, 0.0f, BLUE, kFillModeSolid);
					}
					if (gamemode == 5) {
						Novice::DrawBox(lastboss.pos.x - player->scroll.x - 61, lastboss.pos.y - player->scroll.y - 150, (lastboss.HP + lastboss.HP / 5) * 2, 24, 0.0f, BLUE, kFillModeSolid);
					}
					if (gamemode == 7) {
						Novice::DrawBox(lastboss.pos.x - player->scroll.x - 61, lastboss.pos.y - player->scroll.y - 150, (lastboss.HP + lastboss.HP / 5), 24, 0.0f, BLUE, kFillModeSolid);
					}

					Novice::DrawSprite(lastboss.pos.x - player->scroll.x - 64, lastboss.pos.y - player->scroll.y - 170, hpBar2, 1, 1, 0.0f, 0xFFFFFFFF);
				}
			}
			
			if (rasBossBaria.isAlive == true) {
				Novice::DrawQuad(rasBossBaria.leftTop.x - player->scroll.x, rasBossBaria.leftTop.y - player->scroll.y, rasBossBaria.leftDown.x - player->scroll.x, rasBossBaria.leftDown.y - player->scroll.y, rasBossBaria.rightTop.x - player->scroll.x, rasBossBaria.rightTop.y - player->scroll.y, rasBossBaria.rightDown.x - player->scroll.x, rasBossBaria.rightDown.y - player->scroll.y, 0, 0, 1, 1, WhiteP, GetColor(255, 0, 0, rasBossBaria.alpha));
			}

			explosion->Draw(player->scroll);
			explosion2->Draw(player->scroll);
			explosion3->Draw(player->scroll);
		}



		if (fadeoutDrawFlag == true) {
			Novice::DrawBox(0, 0, 1280, 720, 0, GetColor(0, 0, 0, fadeOutAlpha), kFillModeSolid);
		}
		if (gamemode == 9) {

			Novice::DrawSprite(0, 0, gameoverPic, 1, 1, 0, WHITE);
		}
		if (gamemode == 10) {
			Novice::DrawSprite(0, 0, Clearpic, 1, 1, 0, WHITE);
			fireworks->Draw(GetColor(255, rand() % 255, rand() % 255, fireworks->fireWorksAlpha));
			fireworks2->Draw(GetColor(rand() % 255, 255, 255, fireworks2->fireWorksAlpha));
			fireworks3->Draw(GetColor(rand() % 255, 255, rand() % 255, fireworks3->fireWorksAlpha));
		}
	
		///
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete player;
	delete triangle;
	for (int i = 0; i < nucleus[0]->max; i++) {
		delete nucleus[i];
	}
	for (int i = 0; i < beamNum; i++) {
		delete beamPoint[i];
		delete beams[i];
	}
	for (int i = 0; i < bulletNum; i++) {
		delete bullet[i];
	}
	delete fireworks;
	delete fireworks2;
	delete fireworks3;
	delete explosion;
	delete explosion2;
	delete explosion3;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
