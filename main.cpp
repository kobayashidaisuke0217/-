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
const char kWindowTitle[] = "LC1B_08_コバヤシダイスケ";



float easeInSine(float x) {
	return 1.0f - cosf((x * M_PI) / 2.0f);
}
float learp(float t, float s, float e) {
	return (1.0f - t) * s + t * e;
}

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

	Player* player = new Player({ 100,300,36.0f,6,RED,100 },{0,0});

	Nucleus* nucleus[12];

	for (int i = 0; i < 12; i++) {
		nucleus[i] = new Nucleus(circleReset);
	}

	int mousePressTime = 0;
	nucleus[0]->nucleus.center = { 300, 180 };
	nucleus[1]->nucleus.center = { 1000, 180 };
	nucleus[2]->nucleus.center = { 640, 540 };
	//右上
	nucleus[3]->nucleus.center = { 1580, 180 };
	nucleus[4]->nucleus.center = { 2280, 180 };
	nucleus[5]->nucleus.center = { 1920, 540 };
	//左下
	nucleus[6]->nucleus.center = { 300, 1260 };
	nucleus[7]->nucleus.center = { 1000, 1260 };
	nucleus[8]->nucleus.center = { 640, 900 };
	//右下
	nucleus[9]->nucleus.center = { 1580 , 1260 };
	nucleus[10]->nucleus.center = { 2280 , 1260 };
	nucleus[11]->nucleus.center = { 1920, 900 };
	for (int i = 0; i < nucleus[0]->max; i++) {
		nucleus[i]->nucleus.radius = 36.0f;
		nucleus[i]->nucleus.color = WHITE;
		nucleus[i]->nucleusPrePos = nucleus[i]->nucleus.center;
		nucleus[i]->nucleusSuctionPos = nucleus[i]->nucleus.center;
	}

	const int enemyNum = 3;
	Enemy* enemy[enemyNum];

	for (int i = 0; i < enemyNum; i++) {
		enemy[i] = new Enemy(circleReset);
	/*	enemy[i]->enemyAlive = true;
		enemy[i]->enemyScreenIn = false;*/
	}
	enemy[0]->enemy = { 600,300,36.0f,6.0f,WHITE,100 };
	enemy[1]->enemy = { 1400,100,36.0f,6.0f,WHITE,100 };
	enemy[2]->enemy = { 2000,200,36.0f,6.0f,WHITE,100 };

	const int beamNum = 4;//ビーム発射地点
	BeamPoint* beamPoint[beamNum];

	for (int i = 0; i < beamNum; i++) {
		beamPoint[i] = new BeamPoint(circleReset);
	}

	beamPoint[0]->beamPoint = { 0,0,36.0f,6.0f,RED,100 };
	beamPoint[1]->beamPoint = { 2560,1440,36.0f,6.0f,RED,100 };
	beamPoint[2]->beamPoint = { 0,1440,36.0f,6.0f,RED,100 };
	beamPoint[3]->beamPoint = { 2560,0,36.0f,6.0f,RED,100 };

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

	int tutorial[4]; 
	tutorial[0] = Novice::LoadTexture("./Resources/image/tutorial.png");//チュートリアル
	tutorial[1] = Novice::LoadTexture("./Resources/image/tutorial.png");//チュートリアル
	tutorial[2] = Novice::LoadTexture("./Resources/image/tutorial.png");//チュートリアル
	tutorial[3] = Novice::LoadTexture("./Resources/image/tutorial.png");//チュートリアル
	
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

	float triangleSide = 0;

	int triangleBreak = false;

	bool playerFlag = true;//自機生存フラグ

	Vector2 boundPoint = { 2560,720 };//反射する座標、Xx1280、Yx720

	int gamemode = 0;//ゲームモード管理 0でスタート前,1で第一ステージ2でボス１
	int scrollMode = 0;//0でスクロールしない　1でスクロールする

	int leftx = 0;
	int lefty = 0;

	int rightx = 0;
	int righty = 0;

	int stickNo = 0;

	bool beemHit = false;

	int fadeoutFlag[2] = { false };
	int fadeoutClar = 0x00000000;
	int fadeoutTime = 0;


	int nucleusSuctionCount = 0;
	int nucleusSuctionFlag[12] = { false };

	//ボス
	Boss3 lastboss;
	Baria rasBossBaria;
	BossBeam bossBeam;
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



	bossBeam.count = 0;
	bossBeam.EndPos = { 0,0 };
	bossBeam.flag = false;
	bossBeam.leftDown = { 0,0 };
	bossBeam.leftTop = { 0,0 };
	bossBeam.ob = { 0,0 };
	bossBeam.pos = { 0,0 };
	bossBeam.rightDown = { 0,0 };
	bossBeam.rightTop = { 0,0 };
	bossBeam.theta = 0;
	bossBeam.size = 16;

	int tutorialPosx[4] = { 640,1500,2000,0 };
	int tutorialPosy[4] = { -360,-360,-360,-360 };
	int tutorialCount = { 0 };
	int tutorialSpeed = { 6 };
	

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Novice::GetAnalogInputLeft(stickNo, &leftx, &lefty);
		Novice::GetAnalogInputRight(stickNo, &triangle->mouseX, &triangle->mouseY);
		//Novice::SetWindowMode(kFullscreen);
		///
		/// ↓更新処理ここから
		///

		

		if (gamemode == 0) {//ゲーム開始画面
			if (Novice::IsTriggerButton(0, kPadButton10) || keys[DIK_V]) {

				fadeoutFlag[0] = true;

			}

			if (fadeoutFlag[0] == true && fadeoutFlag[1] == false) {
				fadeoutClar += 0x5;

			}
			if (fadeoutClar >= 256)
			{
				fadeoutClar = 0;
			}

			if (fadeoutClar == 255)
			{
				fadeoutClar = 255;
				fadeoutFlag[1] = true;
				fadeoutTime++;
				if (fadeoutTime == 40)
				{
					fadeoutFlag[0] = false;
					fadeoutFlag[1] = false;
					fadeoutTime = 0;
					gamemode = 1;
				}
			}
			Boss3Reset(lastboss, rasBossBaria,bossBeam);
		}

		if (keys[DIK_Z]) {
			gamemode = 2;
		}
		if (keys[DIK_X]) {
			gamemode = 3;
		}
		if (keys[DIK_C]) {
			stunOnFlag = true;
		}

		if (gamemode >= 1) {//ゲームスタート
			if (gamemode == 1) {//ステージ1
				scrollMode = 0;
				beamPoint[0]->beamAtackStart = false;
				for (int i = 0; i < enemyNum; i++) {
					enemy[i]->enemy.center.y += enemy[i]->enemy.speed;
					if (enemy[i]->enemy.center.y <= 100 || enemy[i]->enemy.center.y >= 620) {
						enemy[i]->enemy.speed *= -1;
					}
				}
				
				if (player->player.center.x > 320 && tutorialPosy[tutorialCount] <= 0) {
					tutorialPosy[tutorialCount] += tutorialSpeed;
				}
				if (tutorialPosy[tutorialCount] == 0) {
					tutorialCount += 1;
				}
				if (player->player.center.x > 1400 && tutorialPosy[tutorialCount] <= 0 && tutorialCount ==1) {
					tutorialPosy[tutorialCount] += tutorialSpeed;
				}
				if (tutorialPosy[tutorialCount] == 0) {
					tutorialCount += 1;
				}
				if (player->player.center.x > 1600 && tutorialPosy[tutorialCount] <= 0 && tutorialCount == 2) {
					tutorialPosy[tutorialCount] += tutorialSpeed;
				}
				if (player->player.center.x >= 2500) {
					fadeoutFlag[0] = true;
				}
				if (fadeoutFlag[0] == true && fadeoutFlag[1] == false) {
					fadeoutClar += 0x5;
				}
				if (fadeoutFlag[0] == true && fadeoutClar >= 256)
				{
					fadeoutClar = 0;
				}
				if (fadeoutClar == 250)
				{
					fadeoutClar = 255;
					fadeoutFlag[1] = true;
				}
				if (fadeoutFlag[1] == true)
				{
					fadeoutTime++;
				}
				if (fadeoutTime == 40)
				{
					fadeoutFlag[0] = false;
					fadeoutFlag[1] = false;
					fadeoutTime = 0;
					gamemode = 2;
				}
			}
			if (gamemode == 2) {//ステージ2
				scrollMode = 1;
				beamPoint[0]->beamAtackStart = true;
				beams[0]->beamMode = 0;
				for (int i = 0; i < enemyNum; i++) {
					enemy[i]->enemyAlive = false;
				}
				if (lastboss.isAlive == true) {
					if (CircleCollisinHit(player->player.center, player->player.radius, lastboss.pos, lastboss.radius) == true) {
						triangle->atackSpeed.x =  -triangle->atackSpeed.x*0.7 ;
						triangle->atackSpeed.y = -triangle->atackSpeed.y * 0.7;
						
					}
				}
			}
			if (gamemode == 3) {
				for (int i = 0; i < enemyNum; i++) {
					enemy[i]->enemyAlive = false;
				}
				BossBeamAtack(lastboss, bossBeam, player->player.center);
				if (bossBeam.flag == true) {
					if(RectCollisionHit(bossBeam.pos, bossBeam.EndPos, player->player.center, player->player.radius, bossBeam.size)==true) {
						gamemode = 0;
					}
				}
				BossBaria(lastboss, rasBossBaria);
				for (int i = 0; i < nucleusSuctionCount; i++) {
					BossBariaCollision(rasBossBaria, throwPos[i], hitradius[i], nucleusSuctionCount, throwDamageFlag[i]);
				}
				/*for (int i = 0; i < 4; i++) {
					if (throwDamageFlag[i] == true) {
						if (enemy[j]->enemyAlive == true && throwDamageFlag[i] == true) {
							if (CircleCollisinHit(throwPos[i], hitradius[i], enemy[j]->enemy.center, enemy[j]->enemy.radius) == true && throwFlag[i] == true) {
								enemy[j]->enemyAlive = false;
								throwDamageFlag[i] = false;
								lastboss.HP -= 2;
							}
						}
					}
				}*/
				scrollMode = 1;
				beamPoint[0]->beamAtackStart = true;
				beams[0]->beamMode = 0;
			}

			if (scrollMode == 0) {
				boundPoint = { 2559,719 };
			}
			if (scrollMode >= 1) {
				boundPoint = { 2559,1439 };
			}
			//プレイヤーの操作
			if (triangle->pattern == 0 || triangle->pattern == 5) {
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
						triangle->atackSpeed = { 0,0 };
						triangle->pattern = 0;
					}
				}
			}
			if (triangle->pattern == 0) {
				triangle->atackSpeed = { 0,0 };
				for (int i = 0; i < nucleus[0]->max; i++) {
					nucleus[i]->nucleus.center = nucleus[i]->nucleusPrePos;
					//nucleus[i]->nucleusSuctionFlag = false;
					nucleusSuctionFlag[i] = false;
					nucleus[i]->nucleus.radius = 36.0f;
					nucleus[i]->nucleus.color = WHITE;
				}
			}

			if (Novice::IsPressButton(0, kPadButton10) || keys[DIK_SPACE]) {

				triangle->PressCount++;
				//ゲージ
				triangle->playerSpeed = triangle->PressCount * 4;

				if (triangle->pattern <= 1 && triangle->atackSpeed.x <= 0.3f && triangle->atackSpeed.x >= -0.3f && triangle->atackSpeed.y <= 0.3f && triangle->atackSpeed.y >= -0.3f) {
					gaugeRight.x = 30 + triangle->playerSpeed;
				}
				if (triangle->PressCount >= 20) {
					triangle->PressCount = 0;
				}
			}
			//スペースを押してなおかつ止まっているとき
			if (Novice::IsTriggerButton(0, kPadButton9) || preKeys[DIK_SPACE] && keys[DIK_SPACE] == 0 /*&& atackSpeed.x <= 0.3f && atackSpeed.x >= -0.3f && atackSpeed.y <= 0.3f && atackSpeed.y >= -0.3f*/) {
				//一つ目の点を求める
				if (triangle->pattern == 0) {
					triangle->playerEndSpeed = 0;
					triangle->triangleSpeed = 0;
					triangle->line.start = player->player.center;
					triangle->atackSpeed = { 0,0 };
					triangle->pattern = 1;
				}
				//二つ目の点を求める
				else if (triangle->pattern == 1) {
					triangle->line.vertex = player->player.center;
					triangle->preLineVertex = triangle->line.vertex;
					triangle->atackSpeed = { 0,0 };
					triangle->pattern = 2;
				}
				//三つ目の点を求める
				else if (triangle->pattern == 2) {
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



				/*	throwPos = { throwradian.x + throwPos.x,throwradian.y + throwPos.y };*/



			}

			player->player.center = Add(player->player.center, triangle->atackSpeed);


			//三角形と核の当たり判定を計算する
			for (int i = 0; i < nucleus[0]->max; i++) {

				nucleus[i]->exterior = Product(triangle->line.start, triangle->line.end, nucleus[i]->nucleus.center);

				nucleus[i]->exterior2 = Product(triangle->line.end, triangle->line.vertex, nucleus[i]->nucleus.center);

				nucleus[i]->exterior3 = Product(triangle->line.vertex, triangle->line.start, nucleus[i]->nucleus.center);
				if (triangle->pattern == 4) {
					if (nucleus[i]->exterior > 0.0f && nucleus[i]->exterior2 > 0.0f && nucleus[i]->exterior3 > 0.0f || nucleus[i]->exterior < 0.0f && nucleus[i]->exterior2 < 0.0f && nucleus[i]->exterior3 < 0.0f) {
						nucleus[i]->nucleus.color = BLUE;
						//nucleus[i]->nucleusSuctionFlag = true;
						nucleusSuctionFlag[i] = true;
						if (nucleus[i]->nucleusCountfrag == false) {
							nucleusSuctionCount++;
							if (nucleusSuctionCount >= 4) {
								nucleusSuctionCount = 4;
							}
							nucleus[i]->nucleusCountfrag = true;
						}
					}
					else {
						nucleus[i]->nucleus.color = WHITE;

					}
				}
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
				if (triangle->pattern >= 4) {
					if (triangleBreak == true) {
						/*if (nucleus[i]->nucleusSuctionFlag == true) {*/
						if(nucleusSuctionFlag[i]==true){

							nucleus[i]->nucleus.center.x = learp(easeInSine(triangle->triangleSpeed), nucleus[i]->nucleusPrePos.x, triangle->line.start.x);
							nucleus[i]->nucleus.center.y = learp(easeInSine(triangle->triangleSpeed), nucleus[i]->nucleusPrePos.y, triangle->line.start.y);
							nucleus[i]->nucleus.radius = learp(easeInSine(triangle->triangleSpeed), 32, 0);
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
						nucleus[i]->nucleus.radius = 36;
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
									nucleusSuctionFlag[i] = false;
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
						if (CircleCollisinHit(throwPos[i], hitradius[i], enemy[j]->enemy.center, enemy[j]->enemy.radius) == true && throwFlag[i] == true) {
							enemy[j]->enemyAlive = false;
							throwDamageFlag[i] = false;
							lastboss.HP -= 2;
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
					if (bullet[i]->bulletOnFlag == false && bullet[j]->bullettimer<= 0 && enemy[j]->enemyAlive == true && enemy[j]->enemyScreenIn == true) {
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
			if (beamPoint[0]->beamAtackStart == true) {
				if (beams[0]->atackFlag == false && beams[0]->beamMode == 0) {
					beams[0]->preCount++;
				}
				if (beams[0]->preCount >= 10 && beams[0]->preCount <= 30 || beams[0]->preCount >= 50 && beams[0]->preCount <= 70 || beams[0]->preCount >= 90 && beams[0]->preCount <= 110) {
					beams[1]->atackFlag = true;
				}
				else {
					beams[1]->atackFlag = false;
				}

				if (beams[0]->preCount == 60) {
					beams[0]->preAtack = true;
					for (int i = 0; i < 4; i++) {
						beams[i]->beam.pos = beams[0]->beemStart;
						beams[i]->beam.angle = { beams[0]->beemStart.x - beamPoint[i]->beamPoint.center.x,beams[0]->beemStart.y - beamPoint[i]->beamPoint.center.y };
						beams[i]->beam.radian = Normalais(beams[i]->beam.angle);
						beams[i]->beam.EndPos = Multiply(beams[i]->beam.radian, beams[i]->beam.size);

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



					}
				}
				if (beams[0]->preCount >= 130) {
					beams[0]->atackFlag = true;
					beams[0]->preAtack = false;
					beams[0]->beamAttackchange += 1;
					beams[0]->preCount = 0;
				}

				if (beams[0]->beamAttackchange <= 5) {
					beamPoint[0]->beamPoint = { 0,0,36.0f,6.0f,RED,100 };
					beamPoint[1]->beamPoint = { 2560,1440,36.0f,6.0f,RED,100 };
					beamPoint[2]->beamPoint = { 0,1440,36.0f,6.0f,RED,100 };
					beamPoint[3]->beamPoint = { 2560,0,36.0f,6.0f,RED,100 };
				}
				if (beams[0]->beamAttackchange > 5) {
					beamPoint[0]->beamPoint = { 0,720,36.0f,6.0f,RED,100 };
					beamPoint[1]->beamPoint = { 2560,720,36.0f,6.0f,RED,100 };
					beamPoint[2]->beamPoint = { 1280,0,36.0f,6.0f,RED,100 };
					beamPoint[3]->beamPoint = { 1280,1440,36.0f,6.0f,RED,100 };
				}

				if (beams[0]->beamAttackchange > 10) {
					beams[0]->beamAttackchange = 0;
				}

				if (beams[0]->atackFlag == true) {
					beams[0]->atackCount++;

					for (int i = 0; i < 4; i++) {

						if (RectCollisionHit(beams[i]->beam.pos, beams[i]->beam.EndPos, player->player.center, 32, player->player.radius) == true) {//自機の生死フラグ = false;
							Novice::ScreenPrintf(40, 40, "Hit");
							beemHit = true;
							triangle->atackSpeed.x = triangle->atackSpeed.x * 0.8;
							triangle->atackSpeed.y = triangle->atackSpeed.y * 0.8;
						}
					}


				}

				if (beams[0]->atackCount >= 30) {
					beams[0]->atackFlag = false;
					beams[0]->atackCount = 0;
				}
			}

			//デバッグ用エンターで戻す
			if (Novice::IsPressButton(0, kPadButton8) || preKeys[DIK_RETURN] && keys[DIK_RETURN] == 0) {
				triangle->pattern = 0;
				beemHit = false;
				for (int i = 0; i < nucleusSuctionCount; i++) {
					throwFlag[i] = false;
				}
				for (int i = 1; i < nucleus[0]->max; i++) {
					nucleus[i]->nucleus.radius = 36;
					nucleus[i]->nucleus.center = nucleus[i]->nucleusPrePos;
				}
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		//Novice::DrawSprite(1280 * 0 - scroll.x, 720 * 0 - scroll.y, stage[0], 1, 1, 0.0f, GREEN);
		Novice::DrawSprite(1280 * 1 - player->scroll.x + RandShake.x, 720 * 0 - player->scroll.y + RandShake.y, stage[1], 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(1280 * 0 - player->scroll.x + RandShake.x, 720 * 1 - player->scroll.y + RandShake.y, stage[2], 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(1280 * 1 - player->scroll.x + RandShake.x, 720 * 1 - player->scroll.y + RandShake.y, stage[3], 1, 1, 0.0f, 0xFFFFFFFF);

		if (gamemode == 0) {//ゲーム開始画面

		}

		if (gamemode >= 1) {//ゲームスタート
			if (gamemode == 1) {//ステージ1
				
			}
			for (int i = 0; i < 4; i++) {
				Novice::DrawSprite(tutorialPosx[i] - player->scroll.x, tutorialPosy[i] - player->scroll.y, tutorial[i], 1, 1, 0.0f, 0xFFFFFFFF);
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
					}//Novice::DrawTriangle(Start[i].x - scroll.x, Start[i].y - scroll.y, End[i].x - scroll.x, End[i].y - scroll.y, Vertex[i].x - scroll.x, Vertex[i].y - scroll.y, WHITE, kFillModeWireFrame);

				}

				if (throwDamageFlag[i] == true) {
					Novice::DrawTriangle(Start[i].x - player->scroll.x + RandShake.x, Start[i].y - player->scroll.y + RandShake.y, End[i].x - player->scroll.x + RandShake.x, End[i].y - player->scroll.y + RandShake.y, Vertex[i].x - player->scroll.x + RandShake.x, Vertex[i].y - player->scroll.y + RandShake.y, WHITE, kFillModeWireFrame);
					Novice::DrawEllipse(throwPos[i].x - player->scroll.x + RandShake.x, throwPos[i].y - player->scroll.y + RandShake.y, hitradius[i], hitradius[i], 0, RED, kFillModeWireFrame);
				}
			}
			for (int i = 0; i < bulletNum; i++) {//弾
				if (bullet[i]->bulletOnFlag == true) {
					Novice::DrawEllipse(bullet[i]->bullet.center.x - player->scroll.x + RandShake.x, bullet[i]->bullet.center.y - player->scroll.y + RandShake.y, bullet[i]->bullet.radius, bullet[i]->bullet.radius, 0.0f, BLACK, kFillModeSolid);
				}
			}

			if (playerFlag == true) {//自機(仮)
				float monitorx = player->player.center.x - player->scroll.x;
				float monitory = player->player.center.y - player->scroll.y;
				Novice::DrawEllipse(monitorx + RandShake.x, monitory + RandShake.y, player->player.radius, player->player.radius, 0.0f, player->player.color, kFillModeSolid);
				Novice::DrawEllipse(monitorx + triangle->mouseX / 1000 + RandShake.x, monitory + triangle->mouseY / 1000 + RandShake.y, 10, 10, 0, WHITE, kFillModeSolid);
			}

			for (int i = 0; i < nucleus[0]->max; i++) {
				//if (nucleus[i]->nucleusSuctionFlag == false) {
				if(nucleusSuctionFlag[i]==false){
					Novice::DrawEllipse(nucleus[i]->nucleus.center.x - player->scroll.x + RandShake.x, nucleus[i]->nucleus.center.y - player->scroll.y + RandShake.y, nucleus[i]->nucleus.radius, nucleus[i]->nucleus.radius, 0, nucleus[i]->nucleus.color, kFillModeSolid);
				}
				else {
					Novice::DrawEllipse(nucleus[i]->nucleusSuctionPos.x - player->scroll.x + RandShake.x, nucleus[i]->nucleusSuctionPos.y - player->scroll.y + RandShake.y, nucleus[i]->nucleus.radius, nucleus[i]->nucleus.radius, 0, nucleus[i]->nucleus.color, kFillModeSolid);
				}
			}


			if (beams[0]->atackFlag == true) {

				for (int i = 0; i < 4; i++) {
					Novice::DrawQuad(beams[i]->BTop.pos.x - player->scroll.x, beams[i]->BTop.pos.y - player->scroll.y, beams[i]->BTop.EndPos.x - player->scroll.x, beams[i]->BTop.EndPos.y - player->scroll.y, beams[i]->BDown.pos.x - player->scroll.x, beams[i]->BDown.pos.y - player->scroll.y, beams[i]->BDown.EndPos.x - player->scroll.x, beams[i]->BDown.EndPos.y - player->scroll.y, 0, 0, 1, 1, WhiteP, WHITE);

				}

			}
			if (beams[1]->atackFlag == true) {

				for (int i = 0; i < 4; i++) {
					Novice::DrawQuad(beams[i]->BTop.pos.x - player->scroll.x, beams[i]->BTop.pos.y - player->scroll.y, beams[i]->BTop.EndPos.x - player->scroll.x, beams[i]->BTop.EndPos.y - player->scroll.y, beams[i]->BDown.pos.x - player->scroll.x, beams[i]->BDown.pos.y - player->scroll.y, beams[i]->BDown.EndPos.x - player->scroll.x, beams[i]->BDown.EndPos.y - player->scroll.y, 0, 0, 1, 1, WhiteP, 0xFFFF33);

				}

			}

			for (int i = 0; i < beamNum; i++) {//ビームポイント
				if (beamPoint[i]->beamAlive == true) {
					Novice::DrawEllipse(beamPoint[i]->beamPoint.center.x - player->scroll.x + RandShake.x, beamPoint[i]->beamPoint.center.y - player->scroll.y + RandShake.y, beamPoint[i]->beamPoint.radius, beamPoint[i]->beamPoint.radius, 0, beamPoint[i]->beamPoint.color, kFillModeSolid);
				}
			}

			for (int i = 0; i < enemyNum; i++) {//敵
				if (enemy[i]->enemyAlive == true) {
					Novice::DrawEllipse(enemy[i]->enemy.center.x - player->scroll.x + RandShake.x, enemy[i]->enemy.center.y - player->scroll.y + RandShake.y, enemy[i]->enemy.radius, enemy[i]->enemy.radius, 0, BLUE, kFillModeSolid);
				}
			}
			if (beemHit == true) {
				Novice::ScreenPrintf(30, 100, "HiT");
			}
			Novice::DrawQuad(gaugeleft.x, gaugeleft.y, gaugeleft.x, gaugeleft.y + 30, gaugeRight.x, gaugeRight.y, gaugeRight.x, gaugeRight.y + 30, 0, 0, 100, 100, WhiteP, WHITE);

			if (gamemode == 3) {
				if (bossBeam.flag == true) {
					Novice::DrawQuad(bossBeam.leftTop.x -player-> scroll.x, bossBeam.leftTop.y - player->scroll.y, bossBeam.rightTop.x - player->scroll.x, bossBeam.rightTop.y - player->scroll.y, bossBeam.leftDown.x - player->scroll.x, bossBeam.leftDown.y - player->scroll.y, bossBeam.rightDown.x - player->scroll.x, bossBeam.rightDown.y - player->scroll.y, 0, 0, 1, 1, WhiteP, BLUE);
				}
				Novice::DrawEllipse(lastboss.pos.x - player->scroll.x , lastboss.pos.y - player->scroll.y, lastboss.radius, lastboss.radius, 0, RED, kFillModeWireFrame);
				if (rasBossBaria.isAlive == true) {
					Novice::DrawQuad(rasBossBaria.leftTop.x - player->scroll.x, rasBossBaria.leftTop.y - player->scroll.y, rasBossBaria.leftDown.x - player->scroll.x, rasBossBaria.leftDown.y - player->scroll.y, rasBossBaria.rightTop.x - player->scroll.x, rasBossBaria.rightTop.y - player->scroll.y, rasBossBaria.rightDown.x - player->scroll.x, rasBossBaria.rightDown.y - player->scroll.y, 0, 0, 1, 1, WhiteP, GetColor(255, 0, 0, rasBossBaria.alpha));
				}
				Novice::ScreenPrintf(30, 300, "%f", rasBossBaria.leftTop.y);
			}
		}
		if (fadeoutFlag[0] == true) {
			Novice::DrawBox(0, 0, 1280, 720, 0, fadeoutClar, kFillModeSolid);
		}

		Novice::ScreenPrintf(20, 20, "%d", player->scroll.x);
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


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
