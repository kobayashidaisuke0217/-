#include <Novice.h>
#include "Vec2.h"
#include "collisionfunc.h"

#include "matrix.h"

const char kWindowTitle[] = "LC1B_08_コバヤシダイスケ";

struct Circle {
	Vector2 center;//中心
	float radius;//半径
	float speed;//速度
	unsigned int color;
};

struct Bullet {
	Vector2 center;
	float radius;
	Vector2 speed;
	unsigned int color;
};

struct Line {
	Vector2 start;
	Vector2 vertex;
	Vector2 end;
};

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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	int mousePress = false;
	Circle player = {//自機
		{500,300},
	36.0f,
	6.0f,
	  RED ,
	};
	Circle nucleus[12];
	Vector2 nucleusPrePos[12];
	Vector2 nucleusSuctionPos[12];
	int nucleusSuctionCount = 0;
	int max = 12;
	int nucleusCountfrag[12] = { false };

	int mousePressTime = 0;
	for (int i = 0; i < max; i++) {
		nucleus[0].center = { 300, 180 };
		nucleus[1].center = { 1000, 180 };
		nucleus[2].center = { 640, 540 };
		//右上
		nucleus[3].center = { 1580, 180 };
		nucleus[4].center = { 2280, 180 };
		nucleus[5].center = { 1920, 540 };
		//左下
		nucleus[6].center = { 300, 1260 };
		nucleus[7].center = { 1000, 1260 };
		nucleus[8].center = { 640, 900 };
		//右下
		nucleus[9].center = { 1580 , 1260 };
		nucleus[10].center = { 2280 , 1260 };
		nucleus[11].center = { 1920, 900 };
		nucleus[i].radius = 36.0f;
		nucleus[i].color = WHITE;
		nucleusPrePos[i] = nucleus[i].center;
		nucleusSuctionPos[i] = nucleus[i].center;
	}

	const int enemyNum = 3;
	Circle enemy[enemyNum];
	enemy[0] = {//敵
	{600,300},
		36.0f,
		6.0f,
		WHITE,
	};
	enemy[1] = {//敵
	{1400,100},
		36.0f,
		6.0f,
		WHITE,
	};
	enemy[2] = {//敵
	{2000,200},
		36.0f,
		6.0f,
		WHITE,
	};

	const int beamNum = 4;//ビーム発射地点

	int beamAlive[beamNum];//ビーム発射地点の生存フラグ
	int beamAtackStart = false;//ビーム開始
	Circle beamPoint[beamNum];

	beamPoint[0] = {//ビーム1と連動
	{0,0},
		36.0f,
		6.0f,
		WHITE,
	};
	beamPoint[1] = {//ビーム0と連動
	{2560,1440},
		36.0f,
		6.0f,
		WHITE,
	};
	beamPoint[2] = {//ビーム3と連動
	{0,1440},
		36.0f,
		6.0f,
		RED,
	};
	beamPoint[3] = {//ビーム4と連動
	{2560,0},
		36.0f,
		6.0f,
		RED,
	};

	for (int i = 0; i < beamNum; i++) {
		beamAlive[i] = true;
	}

	Beam beam;
	beam.pos = { 0,0 };
	beam.angle = { 0 };
	beam.radian = { 0 };
	beam.EndPos = { 0,0 };

	beam.size = 0;

	Beam beam2;

	beam2.pos = { 0,0 };
	beam2.angle = { 0,0 };
	beam2.radian = { 0,0 };
	beam2.EndPos = { 0,0 };

	Beam beam3;
	beam3.pos = { 0,0 };
	beam3.angle = { 0,0 };
	beam3.radian = { 0,0 };
	beam3.EndPos = { 0,0 };

	Beam beam4;
	beam4.pos = { 0,0 };
	beam4.angle = { 0 };
	beam4.radian = { 0 };
	beam4.EndPos = { 0,0 };

	beam4.size = 0;

	Beam beam5;

	beam5.pos = { 0,0 };
	beam5.angle = { 0,0 };
	beam5.radian = { 0,0 };
	beam5.EndPos = { 0,0 };

	Beam beam6;
	beam6.pos = { 0,0 };
	beam6.angle = { 0,0 };
	beam6.radian = { 0,0 };
	beam6.EndPos = { 0,0 };

	int atackFlag = false;
	int beamMode = 0;//0で十字、1で薙ぎ払い
	int preAtack = false;
	int atackCount = 0;
	int preCount = 0;
	int beamSize = 32;//ビームの太さ
	int beamAttackchange = 0;//ビーム攻撃の場所変更

	Vector2 starttoEnd = { 0 };
	Vector2 toplayerB1 = { 0 };
	float exteriorB1 = 0;

	Vector2 starttoEnd2 = { 0 };
	Vector2 toplayerB2 = { 0 };
	float exteriorB2 = { 0 };

	Vector2 endtoEnd = { 0 };
	Vector2 toplayerB3 = { 0 };
	float exteriorB3 = 0;

	Vector2 starttoStart = { 0 };
	Vector2 toplayerB4 = { 0 };
	float exteriorB4 = 0;

	Vector2 starttoEndS = { 0 };
	Vector2 toplayerB1S = { 0 };
	float exteriorB1S = 0;

	Vector2 starttoEnd2S = { 0 };
	Vector2 toplayerB2S = { 0 };
	float exteriorB2S = { 0 };

	Vector2 endtoEndS = { 0 };
	Vector2 toplayerB3S = { 0 };
	float exteriorB3S = 0;

	Vector2 starttoStartS = { 0 };
	Vector2 toplayerB4S = { 0 };
	float exteriorB4S = 0;

	Line line = {
		{1000.0f,700.0f},
		{500.0f,400.0f},
		{100,500},
	};
	Line originalLine = {
		{24.0f,24.0f},
		{0.0f,-36.0f},
		{-24.0f,24.0f},
	};

	int PressCount = 0;
	int atackFrag = false;
	float playerSpeed = 0;
	Vector2 atackSpeed = { 0 };

	int mouseX, mouseY;
	Vector2 mouse = { 0,0 };
	float stop = 0.93;
	enum Atack {
		non,
		start,
		vertex,
		end,
		suction,
		atack,
	};
	int pattern = 0;

	float playerEndSpeed = 0;
	Vector2 playerAngle = { 0 };

	Vector2 toEnd = { 0 };
	Vector2 toplayer[12] = { 0 };
	float exterior[12] = { 0 };

	Vector2 toEnd2 = { 0 };
	Vector2 toplayer2[12] = { 0 };
	float exterior2[12] = { 0 };

	Vector2 toEnd3 = { 0 };
	Vector2 toplayer3[12] = { 0 };
	float exterior3[12] = { 0 };

	float triangleSpeed = 0;

	Vector2 preLineEnd = { 0 };
	Vector2 preLineVertex = { 0 };


	Vector2 toenemy[12];
	float enemyexterior[12];

	Vector2 toenemy2[12];
	float enemyexterior2[12];

	Vector2 toenemy3[12];
	float enemyexterior3[12];
	int nucleusSuctionFlag[12] = { false };


	float theta = 0;

	float playertheta[4] = { 0 };

	const int bulletNum = 16;//敵弾
	Bullet bullet[bulletNum];//弾
	Vector2 bulletAngle[bulletNum];
	int bulletOnFlag[bulletNum];//弾の発射
	int bulletInductionOnFlag[bulletNum];//誘導フラグ
	int bulletInductionTimer[bulletNum];//誘導時間(初期値100)
	int bulletEndTimer[bulletNum];//弾消滅時間(初期値400)
	int bullettimer[bulletNum];//弾の発射クールダウン

	for (int i = 0; i < bulletNum; i++) {
		bullet[i].speed = { 0 , 0 };//速度
		bullet[i].center = { 300,400 };//座標
		bullet[i].radius = 32;//弾大きさ
		bulletAngle[i] = { 0 , 0 };//角度X
		bulletOnFlag[i] = false;//弾の発射
		bulletInductionOnFlag[i] = false;//誘導フラグ
		bulletInductionTimer[i] = 10;//誘導時間(初期値10)
		bulletEndTimer[i] = 300;//弾消滅時間(初期値400)
		bullettimer[i] = 80 + 20 * i;
	}

	Vector2 scroll;//スクロール
	scroll.x = player.center.x;
	scroll.y = player.center.y;

	Vector2  scrollwall{ //スクロール開始
		640.0f,360.0f
	};

	Vector2  scrollwallend{ //スクロール終了
		1920.0f,1080.0f
	};

	Vector2 randshake;
	randshake.x = 0;
	randshake.y = 0;

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

	Vector2 Start[4];
	Vector2 Vertex[4];
	Vector2 End[4];

	Vector2 throwPos[4];

	float hitradius[4];
	int throwDamageFlag[4] = { false };
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

	int playerFlag = true;//自機生存フラグ

	int enemyAlive[enemyNum] = { true };//敵生存フラグ
	int enemyScreenIn[enemyNum];//敵が画面内に居るか

	for (int i = 0; i < enemyNum; i++) {
		enemyAlive[i] = true;
		enemyScreenIn[i] = false;
	}

	Vector2 boundPoint = { 2560,720 };//反射する座標、Xx1280、Yx720

	int gamemode = 0;//ゲームモード管理 0でスタート前,1で第一ステージ2でボス１
	int scrollMode = 0;//0でスクロールしない　1でスクロールする

	int leftx = 0;
	int lefty = 0;

	int rightx = 0;
	int righty = 0;

	int stickNo = 0;

	bool beemHit = false;

	float thetaBeam = 1.0f / 8.0f * M_PI;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		//Novice::GetMousePosition(&mouseX, &mouseY);
		Novice::GetAnalogInputLeft(stickNo, &leftx, &lefty);
		Novice::GetAnalogInputRight(stickNo, &mouseX, &mouseY);
		Novice::SetWindowMode(kFullscreen);
		///
		/// ↓更新処理ここから
		///

		if (gamemode == 0) {//ゲーム開始画面
			if (Novice::IsTriggerButton(0, kPadButton10) || keys[DIK_V]) {
				gamemode = 1;
			}
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
				beamAtackStart = false;
				for (int i = 0; i < enemyNum; i++) {
					enemy[i].center.y += enemy[i].speed;
					if (enemy[i].center.y <= 100 || enemy[i].center.y >= 620) {
						enemy[i].speed *= -1;
					}
				}
				/*if (Novice::IsTriggerButton(0, kPadButton11) || keys[DIK_V]) {
					gamemode = 2;
				}*/
				if (player.center.x >= 2000) {
					gamemode = 2;
				}
			}
			if (gamemode == 2) {//ステージ2
				scrollMode = 1;
				beamAtackStart = true;
				beamMode = 0;
				for (int i = 0; i < enemyNum; i++) {
					enemyAlive[i] = false;
				}
				enemyAlive[0] = true;
				enemy[0].center.x = 1280;
				enemy[0].center.y = 720;
			}
			if (gamemode == 3) {

			}

			Novice::ScreenPrintf(0, 0, "%d,%d", beamPoint[0].center.x, beamPoint[0].center.y);

			if (scrollMode == 0) {
				boundPoint = { 2559,719 };
			}
			if (scrollMode == 1) {
				boundPoint = { 2559,1439 };
			}
			//プレイヤーの操作
			if (pattern == 0 || pattern == 5) {
				if (leftx < -10000 || keys[DIK_A] != 0) {
					player.center.x -= player.speed;
					if (player.center.x >= scrollwall.x && player.center.x <= scrollwallend.x) {
						scroll.x -= player.speed;
					}
				}
				// 右キーを押したら右に動かす
				if (leftx > 10000 || keys[DIK_D] != 0) {
					player.center.x += player.speed;
					if (player.center.x >= scrollwall.x && player.center.x <= scrollwallend.x) {
						scroll.x += player.speed;
					}
				}
				// 上キーを押したら上に動かす
				if (lefty < -10000 || keys[DIK_W] != 0) {
					player.center.y -= player.speed;
					if (player.center.y >= scrollwall.y && player.center.y <= scrollwallend.y && scrollMode == 1) {
						scroll.y -= player.speed;
					}
				}
				// 下キーを押したら下に動かす
				if (lefty > 10000 || keys[DIK_S] != 0) {
					player.center.y += player.speed;
					if (player.center.y >= scrollwall.y && player.center.y <= scrollwallend.y && scrollMode == 1) {
						scroll.y += player.speed;
					}
				}
			}

			//通常移動時の移動可能範囲
			if (player.center.x >= boundPoint.x - player.radius) { //右方向
				player.center.x = boundPoint.x - player.radius;
			}
			if (player.center.x <= 0 + player.radius) { //左方向
				player.center.x = 0 + player.radius;
			}
			if (player.center.y <= player.radius) { //上方向
				player.center.y = player.radius;
			}
			if (player.center.y >= boundPoint.y - player.radius) { //下方向
				player.center.y = boundPoint.y - player.radius;
			}

			///スクロール終了時の座標修正
			if (player.center.x <= scrollwall.x) {
				scroll.x = 0.0f;
			}
			if (player.center.x >= 1920.0f) {
				scroll.x = 1280.0f;
			}
			if (player.center.y <= scrollwall.y) {
				scroll.y = 0.0f;
			}
			if (player.center.y >= 1080.0f) {
				scroll.y = 720.0f;
			}

			////画面端で跳ね返る
			if (player.center.x <= 0 + player.radius) {//左方向
				atackSpeed.x = -atackSpeed.x * 0.9;
			}
			if (player.center.x >= boundPoint.x - player.radius) {//右方向
				atackSpeed.x = -atackSpeed.x * 0.9;
			}
			if (player.center.y <= player.radius) {//上方向
				atackSpeed.y = -atackSpeed.y * 0.9;
			}
			if (player.center.y >= boundPoint.y - player.radius) {//下方向
				atackSpeed.y = -atackSpeed.y * 0.9;
			}

			if (pattern == 0) {
				atackSpeed = { 0,0 };
				for (int i = 0; i < max; i++) {
					nucleus[i].center = nucleusPrePos[i];
					nucleusSuctionFlag[i] = false;
					nucleus[i].radius = 36.0f;
					nucleus[i].color = WHITE;
				}
			}
			if (Novice::IsPressButton(0, kPadButton10) || keys[DIK_SPACE]) {

				PressCount++;
				//ゲージ
				playerSpeed = PressCount * 4;

				if (pattern <= 1 && atackSpeed.x <= 0.3f && atackSpeed.x >= -0.3f && atackSpeed.y <= 0.3f && atackSpeed.y >= -0.3f) {
					gaugeRight.x = 30 + playerSpeed;
				}
				if (PressCount >= 20) {
					PressCount = 0;
				}
			}
			//スペースを押してなおかつ止まっているとき
			if (Novice::IsTriggerButton(0, kPadButton9) || preKeys[DIK_SPACE] && keys[DIK_SPACE] == 0 && atackSpeed.x <= 0.3f && atackSpeed.x >= -0.3f && atackSpeed.y <= 0.3f && atackSpeed.y >= -0.3f) {
				//一つ目の点を求める
				if (pattern == 0) {
					playerEndSpeed = 0;
					triangleSpeed = 0;
					line.start = player.center;
					atackSpeed = { 0,0 };
					pattern = 1;
				}
				//二つ目の点を求める
				else if (pattern == 1) {
					line.vertex = player.center;
					preLineVertex = line.vertex;
					atackSpeed = { 0,0 };
					pattern = 2;
				}
				//三つ目の点を求める
				else if (pattern == 2) {
					line.end = player.center;
					preLineEnd = line.end;
					atackSpeed = { 0,0 };
					pattern = 3;
				}


				//プレイヤーを飛ばす
				if (pattern <= 2) {


					mouse = { (float)mouseX + scroll.x,(float)mouseY + scroll.y };
					playerAngle = VectorProduct(mouse, player.center);
					atackSpeed = Multiply(Normalais(playerAngle), playerSpeed);

				}
			}

			//プレイヤーのスピードを計算
			if (pattern <= 2) {
				atackSpeed = Multiply(atackSpeed, stop);
				if (player.center.x >= scrollwall.x && player.center.x <= scrollwallend.x) {
					scroll.x = player.center.x - 640;
				}
				if (player.center.y >= scrollwall.y && player.center.y <= scrollwallend.y && scrollMode == 1) {
					scroll.y = player.center.y - 360;
				}
			}
			//最期の点を求めてから最初の点に戻る
			if (pattern == 3) {
				if (playerEndSpeed <= 1.0) {
					playerEndSpeed += 0.1f;
				}
				player.center.x = learp(easeInSine(playerEndSpeed), line.end.x, line.start.x);
				player.center.y = learp(easeInSine(playerEndSpeed), line.end.y, line.start.y);
				if (player.center.x >= scrollwall.x && player.center.x <= scrollwallend.x) {
					scroll.x = player.center.x - 640;
				}
				if (player.center.y >= scrollwall.y && player.center.y <= scrollwallend.y && scrollMode == 1) {
					scroll.y = player.center.y - 360;
				}
				if (playerEndSpeed >= 1.0f) {
					pattern = 4;
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
					nucleusCountfrag[i] = false;

				}
			}
			//作った三角形を回収して武器にする
			if (pattern == 4) {
				triangleSide = sqrtf((originalLine.vertex.x - originalLine.end.x) * (originalLine.vertex.x - originalLine.end.x) + (originalLine.vertex.y - originalLine.end.y) * (originalLine.vertex.y - originalLine.end.y));

				Vector2  lineStartToEnd = { line.start.x - preLineEnd.x,line.start.y - preLineEnd.y };
				Vector2  lineStartToEndRadian = Normalais(lineStartToEnd);
				Vector2  lineStartToEndAngle = Multiply(lineStartToEndRadian, triangleSide);
				Vector2 triangleTop = Add(line.start, lineStartToEndAngle);

				Vector2  lineStartToVertex = { line.start.x - preLineVertex.x,line.start.y - preLineVertex.y };
				Vector2  lineStartToVertexRadian = Normalais(lineStartToVertex);
				Vector2  lineStartToVertexAngle = Multiply(lineStartToVertexRadian, triangleSide);
				Vector2 triangleDown = Add(line.start, lineStartToVertexAngle);

				if (triangleSpeed <= 1.0) {
					triangleSpeed += 0.15;
				}

				line.end.x = learp(easeInSine(triangleSpeed), preLineEnd.x, triangleTop.x);
				line.end.y = learp(easeInSine(triangleSpeed), preLineEnd.y, triangleTop.y);

				line.vertex.x = learp(easeInSine(triangleSpeed), preLineVertex.x, triangleDown.x);
				line.vertex.y = learp(easeInSine(triangleSpeed), preLineVertex.y, triangleDown.y);



				/*	throwPos = { throwradian.x + throwPos.x,throwradian.y + throwPos.y };*/



			}

			player.center = Add(player.center, atackSpeed);


			//三角形と核の当たり判定を計算する
			for (int i = 0; i < max; i++) {
				toEnd = VectorProduct(line.start, line.end);
				toplayer[i] = VectorProduct(nucleus[i].center, line.start);
				exterior[i] = Product(toEnd, toplayer[i]);

				toEnd2 = VectorProduct(line.end, line.vertex);
				toplayer2[i] = VectorProduct(nucleus[i].center, line.end);
				exterior2[i] = Product(toEnd2, toplayer2[i]);

				toEnd3 = VectorProduct(line.vertex, line.start);
				toplayer3[i] = VectorProduct(nucleus[i].center, line.vertex);
				exterior3[i] = Product(toEnd3, toplayer3[i]);
				if (pattern == 4) {
					if (exterior[i] > 0.0f && exterior2[i] > 0.0f && exterior3[i] > 0.0f || exterior[i] < 0.0f && exterior2[i] < 0.0f && exterior3[i] < 0.0f) {
						nucleus[i].color = BLUE;
						nucleusSuctionFlag[i] = true;
						if (nucleusCountfrag[i] == false) {
							nucleusSuctionCount++;
							if (nucleusSuctionCount >= 4) {
								nucleusSuctionCount = 4;
							}
							nucleusCountfrag[i] = true;
						}
					}
					else {
						nucleus[i].color = WHITE;

					}
				}
			}


			triangleBreak = lineSearch(nucleusSuctionFlag, max);
			//三角形と敵の当たり判定
			for (int i = 0; i < 2; i++) {
				toenemy[i] = VectorProduct(enemy[i].center, line.start);
				enemyexterior[i] = Product(toEnd, toenemy[i]);

				toenemy2[i] = VectorProduct(enemy[i].center, line.end);
				enemyexterior2[i] = Product(toEnd2, toenemy2[i]);

				toenemy3[i] = VectorProduct(enemy[i].center, line.vertex);
				enemyexterior3[i] = Product(toEnd3, toenemy3[i]);

				if (pattern == 4) {
					if (enemyexterior[i] > 0.0f && enemyexterior2[i] > 0.0f && enemyexterior3[i] > 0.0f || enemyexterior[i] < 0.0f && enemyexterior2[i] < 0.0f && enemyexterior3[i] < 0.0f) {
						if (enemyAlive[i] == true) {
							triangleBreak = false;
						}

					}

				}

			}
			for (int i = 0; i < max; i++) {
				if (pattern >= 4) {
					if (triangleBreak == true) {
						if (nucleusSuctionFlag[i] == true) {


							nucleus[i].center.x = learp(easeInSine(triangleSpeed), nucleusPrePos[i].x, line.start.x);
							nucleus[i].center.y = learp(easeInSine(triangleSpeed), nucleusPrePos[i].y, line.start.y);
							nucleus[i].radius = learp(easeInSine(triangleSpeed), 32, 0);

							nucleusSuctionPos[i].x = (line.start.x + line.end.x + line.vertex.x) / 3;
							nucleusSuctionPos[i].y = (line.start.y + line.end.y + line.vertex.y) / 3;


							if (triangleSpeed >= 1.0f) {

								pattern = 5;
							}


						}
					}
					else {
						pattern = 0;
						for (int j = 0; j < 4; j++) {
							throwFlag[j] = false;
						}
						nucleus[i].radius = 36;
					}
				}
			}

			//攻撃の準備をする
			if (pattern == 5) {
				for (int i = 0; i < nucleusSuctionCount; i++) {
					if (throwFlag[i] == false) {
						throwPos[i].x = (Start[i].x + End[i].x + Vertex[i].x) / 3;
						throwPos[i].y = (Start[i].y + End[i].y + Vertex[i].y) / 3;

						playertheta[i] += 1 / 30.0f;
						theta += 1 / 10.0f;
						throwPos[i] = { player.center.x + cosf(playertheta[i]) * 60,player.center.y + sinf(playertheta[i]) * 60 };
						Matrix2x2 rotateMatrix = MakeRotateMatrix(theta);

						Start[i] = MatrixMultiply(originalLine.start, rotateMatrix);

						Vertex[i] = MatrixMultiply(originalLine.vertex, rotateMatrix);

						End[i] = MatrixMultiply(originalLine.end, rotateMatrix);

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
							throwAngle[i] = { (float)mouseX - throwPos[i].x + scroll.x,(float)mouseY - throwPos[i].y + scroll.y };
							throwradian[i] = Normalais(throwAngle[i]);
							throwSpeed[i] = Multiply(throwradian[i], 8);
							throwDamageFlag[i] = true;


							throwFlag[i] = true;
							if (throwFlag[nucleusSuctionCount - 1] == true) {
								pattern = 0;
								for (int j = 0; j < max; j++) {
									nucleusSuctionFlag[j] = false;
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

					Start[i] = MatrixMultiply(originalLine.start, rotateMatrix);

					Vertex[i] = MatrixMultiply(originalLine.vertex, rotateMatrix);

					End[i] = MatrixMultiply(originalLine.end, rotateMatrix);

					Start[i] = Add(Start[i], throwPos[i]);
					Vertex[i] = Add(Vertex[i], throwPos[i]);
					End[i] = Add(End[i], throwPos[i]);


					hitradius[i] = sqrtf((throwPos[i].x - Start[i].x) * (throwPos[i].x - Start[i].x) + (throwPos[i].y - Start[i].y) * (throwPos[i].y - Start[i].y));



				}
				//攻撃とエネミーの当たり判定
				for (int j = 0; j < 2; j++) {
					if (enemyAlive[j] == true && throwDamageFlag[i] == true) {
						if (CircleCollisinHit(throwPos[i], hitradius[i], enemy[j].center, enemy[j].radius) == true && throwFlag[i] == true) {
							enemyAlive[j] = false;
							throwDamageFlag[i] = false;
						}
					}
				}
			}

			//画面内の敵を感知
			for (int i = 0; i < enemyNum; i++) {
				if (enemy[i].center.x > player.center.x - 1280 / 2 && enemy[i].center.x < player.center.x + 1280 / 2) {
					enemyScreenIn[i] = true;
				}
				else {
					enemyScreenIn[i] = false;
				}
			}

			//誘導弾
			for (int j = 0; j < enemyNum; j++) {
				for (int i = 0; i < bulletNum; i++) {
					if (bulletOnFlag[i] == false && bullettimer[j] <= 0 && enemyAlive[j] == true && enemyScreenIn[j] == true) {
						bullet[i].center = { enemy[j].center.x ,enemy[j].center.y };
						bulletOnFlag[i] = true;
						bullettimer[j] = 80 + 20 * i;
						bulletInductionOnFlag[i] = true;
					}
				}
				bullettimer[j]--;
			}

			for (int i = 0; i < bulletNum; i++) {
				if (bulletOnFlag[i] == true) {//弾を置いたら
					bulletEndTimer[i]--;
					bullet[i].speed = Multiply(Normalais(bulletAngle[i]), 6);
					bullet[i].center = Add(bullet[i].center, bullet[i].speed);
					if (bulletInductionOnFlag[i] == true) {//誘導時間忠
						bulletInductionTimer[i]--;
						bulletAngle[i] = { (float)player.center.x - bullet[i].center.x, (float)player.center.y - bullet[i].center.y };
					}
					if (CircleCollisinHit(bullet[i].center, bullet[i].radius, player.center, player.radius) == true) {//ボールと弾がぶつかったとき
						//playerFlag = false;//生存判定をfalseにする
						bulletInductionTimer[i] = 10;
						bulletInductionOnFlag[i] = false;
						bulletOnFlag[i] = false;
						bulletEndTimer[i] = 400;
					}
				}

				if (bulletEndTimer[i] <= 0) {
					bulletInductionTimer[i] = 10;
					bulletInductionOnFlag[i] = false;
					bulletOnFlag[i] = false;
					bulletEndTimer[i] = 400;
				}

				if (bulletInductionTimer[i] <= 0) {//誘導タイマーが0で誘導終了
					bulletInductionOnFlag[i] = false;
					bullet[i].speed = Multiply(Normalais(bulletAngle[i]), 4);
					bullet[i].center = Add(bullet[i].center, bullet[i].speed);
				}
			}

			//スタン
			if (stunOnFlag == true) {
				pattern = 5;
				shakeTimer--;
				if (shakeTimer <= 255 && shakeTimer > 0) {
					randshake.x = rand() % 11 - 5;
					randshake.y = rand() % 11 - 5;
				}
				if (shakeTimer < 0) {
					shakeTimer = 60;
					stunOnFlag = false;
				}
			}

			//ビーム
			if (beamAtackStart == true) {
				if (atackFlag == false && beamMode == 0) {
					preCount++;
				}
				if (preCount == 60) {
					preAtack = true;

					beam.pos = { beamPoint[0].center.x,beamPoint[0].center.y };
					beam.angle = { beamPoint[1].center.x - beam.pos.x, beamPoint[1].center.y - beam.pos.y };
					beam.radian = Normalais(beam.angle);
					beam.EndPos = Multiply(beam.radian, beam.size);

					beam.EndPos.x += beam.pos.x;
					beam.EndPos.y += beam.pos.y;


					beam2.radian = { -beam.radian.y,beam.radian.x };
					beam2.angle = Multiply(beam2.radian, beamSize);
					beam2.pos = { beamPoint[1].center.x + beam2.angle.x, beamPoint[1].center.y + beam2.angle.y };
					beam2.EndPos.x = beam.EndPos.x + beam2.angle.x;
					beam2.EndPos.y = beam.EndPos.y + beam2.angle.y;


					beam3.radian = { beam.radian.y,-beam.radian.x };
					beam3.angle = Multiply(beam3.radian, beamSize);
					beam3.pos = { beamPoint[1].center.x + beam3.angle.x,beamPoint[1].center.y + beam3.angle.y };
					beam3.EndPos.x = beam.EndPos.x + beam3.angle.x;
					beam3.EndPos.y = beam.EndPos.y + beam3.angle.y;

					beam4.pos = { beamPoint[2].center.x,beamPoint[2].center.y };
					beam4.angle = { beamPoint[3].center.x - beam4.pos.x, beamPoint[3].center.y - beam4.pos.y };
					beam4.radian = Normalais(beam4.angle);
					beam4.EndPos = Multiply(beam4.radian, beam4.size);

					beam4.EndPos.x += beam4.pos.x;
					beam4.EndPos.y += beam4.pos.y;


					beam5.radian = { -beam4.radian.y,beam4.radian.x };
					beam5.angle = Multiply(beam5.radian, beamSize);
					beam5.pos = { beamPoint[3].center.x + beam5.angle.x, beamPoint[3].center.y + beam5.angle.y };
					beam5.EndPos.x = beam4.EndPos.x + beam5.angle.x;
					beam5.EndPos.y = beam4.EndPos.y + beam5.angle.y;


					beam6.radian = { beam4.radian.y,-beam4.radian.x };
					beam6.angle = Multiply(beam6.radian, beamSize);
					beam6.pos = { beamPoint[3].center.x + beam6.angle.x,beamPoint[3].center.y + beam6.angle.y };
					beam6.EndPos.x = beam4.EndPos.x + beam6.angle.x;
					beam6.EndPos.y = beam4.EndPos.y + beam6.angle.y;

				}
				if (preCount >= 120) {
					atackFlag = true;
					preAtack = false;
					beamAttackchange += 1;
					preCount = 0;
				}

				if (beamAttackchange <= 5) {
					beamPoint[0] = {//ビーム1と連動
						{0,0},36.0f,6.0f,WHITE,
					};
					beamPoint[1] = {//ビーム0と連動
					{2560,1440},36.0f,6.0f,WHITE,
					};
					beamPoint[2] = {//ビーム3と連動
					{0,1440},36.0f,6.0f,RED,
					};
					beamPoint[3] = {//ビーム4と連動
					{2560,0},36.0f,6.0f,RED,
					};
				}
				if (beamAttackchange > 5) {
					beamPoint[0] = {//ビーム1と連動
					{0,720},36.0f,6.0f,WHITE,
					};
					beamPoint[1] = {//ビーム0と連動
					{2560,720},36.0f,6.0f,WHITE,
					};
					beamPoint[2] = {//ビーム3と連動
					{1280,0},36.0f,6.0f,RED,
					};
					beamPoint[3] = {//ビーム4と連動
					{1280,1440},36.0f,6.0f,RED,
					};
				}
				if (beamAttackchange > 10) {
					beamAttackchange = 0;
				}

				if (atackFlag == true) {
					atackCount++;

					starttoEnd = VectorProduct(beam2.pos, beam2.EndPos);
					toplayerB1 = VectorProduct(player.center, beam2.pos);
					exteriorB1 = Product(starttoEnd, toplayerB1);

					starttoEnd = VectorProduct(beam2.pos, beam2.EndPos);
					toplayerB1 = VectorProduct(player.center, beam2.pos);
					exteriorB1 = Product(starttoEnd, toplayerB1);

					starttoEnd2 = VectorProduct(beam3.EndPos, beam3.pos);
					toplayerB2 = VectorProduct(player.center, beam3.EndPos);
					exteriorB2 = Product(starttoEnd2, toplayerB2);

					starttoStart = VectorProduct(beam3.pos, beam2.pos);
					toplayerB3 = VectorProduct(player.center, beam3.pos);
					exteriorB3 = Product(starttoStart, toplayerB3);

					endtoEnd = VectorProduct(beam2.EndPos, beam3.EndPos);
					toplayerB4 = VectorProduct(player.center, beam2.EndPos);
					exteriorB4 = Product(endtoEnd, toplayerB4);


					starttoEndS = VectorProduct(beam5.pos, beam5.EndPos);
					toplayerB1S = VectorProduct(player.center, beam5.pos);
					exteriorB1S = Product(starttoEndS, toplayerB1S);

					starttoEndS = VectorProduct(beam5.pos, beam5.EndPos);
					toplayerB1S = VectorProduct(player.center, beam5.pos);
					exteriorB1S = Product(starttoEndS, toplayerB1S);

					starttoEnd2S = VectorProduct(beam6.EndPos, beam6.pos);
					toplayerB2S = VectorProduct(player.center, beam6.EndPos);
					exteriorB2S = Product(starttoEnd2S, toplayerB2S);

					starttoStartS = VectorProduct(beam6.pos, beam5.pos);
					toplayerB3S = VectorProduct(player.center, beam6.pos);
					exteriorB3S = Product(starttoStartS, toplayerB3S);

					endtoEndS = VectorProduct(beam5.EndPos, beam6.EndPos);
					toplayerB4S = VectorProduct(player.center, beam5.EndPos);
					exteriorB4S = Product(endtoEndS, toplayerB4S);


					if (exteriorB1 > 0.0f && exteriorB2 > 0.0f && exteriorB3 > 0.0f && exteriorB4 > 0.0f || exteriorB1 < 0.0f && exteriorB2 < 0.0f && exteriorB3 < 0.0f && exteriorB4 < 0.0f ||
						exteriorB1S > 0.0f && exteriorB2S > 0.0f && exteriorB3S > 0.0f && exteriorB4S > 0.0f || exteriorB1S < 0.0f && exteriorB2S < 0.0f && exteriorB3S < 0.0f && exteriorB4S < 0.0f) {
						//自機の生死フラグ = false;
						Novice::ScreenPrintf(40, 40, "Hit");
						beemHit = true;
					}
				}

				if (atackCount >= 30) {
					atackFlag = false;
					atackCount = 0;
				}
			}

			//デバッグ用エンターで戻す
			if (Novice::IsPressButton(0, kPadButton8) || preKeys[DIK_RETURN] && keys[DIK_RETURN] == 0) {
				pattern = 0;
				beemHit = false;
				for (int i = 0; i < nucleusSuctionCount; i++) {
					throwFlag[i] = false;
				}
				for (int i = 1; i < max; i++) {
					nucleus[i].radius = 36;
					nucleus[i].center = nucleusPrePos[i];
				}
				enemyAlive[0] = true;
			}

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		//Novice::DrawSprite(1280 * 0 - scroll.x, 720 * 0 - scroll.y, stage[0], 1, 1, 0.0f, GREEN);
		Novice::DrawSprite(1280 * 1 - scroll.x + randshake.x, 720 * 0 - scroll.y + randshake.y, stage[1], 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(1280 * 0 - scroll.x + randshake.x, 720 * 1 - scroll.y + randshake.y, stage[2], 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(1280 * 1 - scroll.x + randshake.x, 720 * 1 - scroll.y + randshake.y, stage[3], 1, 1, 0.0f, 0xFFFFFFFF);

		if (gamemode == 0) {//ゲーム開始画面

		}

		if (gamemode >= 1) {//ゲームスタート
			if (gamemode == 1) {//ステージ1

			}

			if (pattern == 1) {
				Novice::DrawLine(line.start.x - scroll.x + randshake.x, line.start.y - scroll.y + randshake.y, player.center.x - scroll.x + randshake.x, player.center.y - scroll.y + randshake.y, WHITE);
			}
			if (pattern == 2) {
				Novice::DrawLine(player.center.x - scroll.x + randshake.x, player.center.y - scroll.y + randshake.y, line.vertex.x - scroll.x + randshake.x, line.vertex.y - scroll.y + randshake.y, WHITE);
				Novice::DrawLine(line.start.x - scroll.x + randshake.x, line.start.y - scroll.y + randshake.y, line.vertex.x - scroll.x + randshake.x, line.vertex.y - scroll.y + randshake.y, WHITE);
			}
			if (pattern == 3) {
				Novice::DrawLine(line.end.x - scroll.x + randshake.x, line.end.y - scroll.y + randshake.y, line.vertex.x - scroll.x + randshake.x, line.vertex.y - scroll.y + randshake.y, WHITE);
				Novice::DrawLine(line.start.x - scroll.x + randshake.x, line.start.y - scroll.y + randshake.y, line.vertex.x - scroll.x + randshake.x, line.vertex.y - scroll.y + randshake.y, WHITE);
				Novice::DrawLine(line.end.x - scroll.x + randshake.x, line.end.y - scroll.y + randshake.y, player.center.x - scroll.x + randshake.x, player.center.y - scroll.y + randshake.y, WHITE);
			}
			if (pattern == 4) {
				Novice::DrawTriangle(line.start.x - scroll.x + randshake.x, line.start.y - scroll.y + randshake.y, line.end.x - scroll.x + randshake.x, line.end.y - scroll.y + randshake.y, line.vertex.x - scroll.x + randshake.x, line.vertex.y - scroll.y + randshake.y, WHITE, kFillModeWireFrame);
			}
			for (int i = 0; i < nucleusSuctionCount; i++) {
				if (pattern == 5) {
					if (throwFlag[i] == false) {
						Novice::DrawTriangle(Start[i].x - scroll.x + randshake.x, Start[i].y - scroll.y + randshake.y, End[i].x - scroll.x + randshake.x, End[i].y - scroll.y + randshake.y, Vertex[i].x - scroll.x + randshake.x, Vertex[i].y - scroll.y + randshake.y, WHITE, kFillModeWireFrame);
					}//Novice::DrawTriangle(Start[i].x - scroll.x, Start[i].y - scroll.y, End[i].x - scroll.x, End[i].y - scroll.y, Vertex[i].x - scroll.x, Vertex[i].y - scroll.y, WHITE, kFillModeWireFrame);

				}

				if (throwDamageFlag[i] == true) {
					Novice::DrawTriangle(Start[i].x - scroll.x + randshake.x, Start[i].y - scroll.y + randshake.y, End[i].x - scroll.x + randshake.x, End[i].y - scroll.y + randshake.y, Vertex[i].x - scroll.x + randshake.x, Vertex[i].y - scroll.y + randshake.y, WHITE, kFillModeWireFrame);
					Novice::DrawEllipse(throwPos[i].x - scroll.x + randshake.x, throwPos[i].y - scroll.y + randshake.y, hitradius[i], hitradius[i], 0, RED, kFillModeWireFrame);
				}
			}
			for (int i = 0; i < bulletNum; i++) {//弾
				if (bulletOnFlag[i] == true) {
					Novice::DrawEllipse(bullet[i].center.x - scroll.x + randshake.x, bullet[i].center.y - scroll.y + randshake.y, bullet[i].radius, bullet[i].radius, 0.0f, BLACK, kFillModeSolid);
				}
			}

			if (playerFlag == true) {//自機(仮)
				float monitorx = player.center.x - scroll.x;
				float monitory = player.center.y - scroll.y;
				Novice::DrawEllipse(monitorx + randshake.x, monitory + randshake.y, player.radius, player.radius, 0.0f, player.color, kFillModeSolid);
				Novice::DrawEllipse(monitorx + mouseX / 1000 + randshake.x, monitory + mouseY / 1000 + randshake.y, 10, 10, 0, WHITE, kFillModeSolid);
			}

			for (int i = 0; i < max; i++) {
				if (nucleusSuctionFlag[i] == false) {
					Novice::DrawEllipse(nucleus[i].center.x - scroll.x + randshake.x, nucleus[i].center.y - scroll.y + randshake.y, nucleus[i].radius, nucleus[i].radius, 0, nucleus[i].color, kFillModeSolid);
				}
				else {
					Novice::DrawEllipse(nucleusSuctionPos[i].x - scroll.x + randshake.x, nucleusSuctionPos[i].y - scroll.y + randshake.y, nucleus[i].radius, nucleus[i].radius, 0, nucleus[i].color, kFillModeSolid);
				}
			}

			if (atackFlag == true) {//ビーム
				Novice::DrawQuad(beam2.pos.x - scroll.x + randshake.x, beam2.pos.y - scroll.y + randshake.y, beam2.EndPos.x - scroll.x + randshake.x, beam2.EndPos.y - scroll.y + randshake.y, beam3.pos.x - scroll.x + randshake.x, beam3.pos.y - scroll.y + randshake.y, beam3.EndPos.x - scroll.x + randshake.x, beam3.EndPos.y - scroll.y + randshake.y, 0, 0, 1, 1, WhiteP, WHITE);
			}
			if (atackFlag == true) {//ビーム2
				Novice::DrawQuad(beam5.pos.x - scroll.x + randshake.x, beam5.pos.y - scroll.y + randshake.y, beam5.EndPos.x - scroll.x + randshake.x, beam5.EndPos.y - scroll.y + randshake.y, beam6.pos.x - scroll.x + randshake.x, beam6.pos.y - scroll.y + randshake.y, beam6.EndPos.x - scroll.x + randshake.x, beam6.EndPos.y - scroll.y + randshake.y, 0, 0, 1, 1, WhiteP, WHITE);
			}

			for (int i = 0; i < beamNum; i++) {//ビームポイント
				if (beamAlive[i] == true) {
					Novice::DrawEllipse(beamPoint[i].center.x - scroll.x + randshake.x, beamPoint[i].center.y - scroll.y + randshake.y, beamPoint[i].radius, beamPoint[i].radius, 0, beamPoint[i].color, kFillModeSolid);
				}
			}

			for (int i = 0; i < enemyNum; i++) {//敵
				if (enemyAlive[i] == true) {
					Novice::DrawEllipse(enemy[i].center.x - scroll.x + randshake.x, enemy[i].center.y - scroll.y + randshake.y, enemy[i].radius, enemy[i].radius, 0, BLUE, kFillModeSolid);
				}
			}
			if (beemHit == true) {
				Novice::ScreenPrintf(30, 100, "HiT");
			}
			Novice::DrawQuad(gaugeleft.x, gaugeleft.y, gaugeleft.x, gaugeleft.y + 30, gaugeRight.x, gaugeRight.y, gaugeRight.x, gaugeRight.y + 30, 0, 0, 100, 100, WhiteP, WHITE);

		}

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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
