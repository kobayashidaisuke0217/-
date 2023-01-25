#include <Novice.h>
#include "Vec2.h"
#include "collisionfunc.h"

#include "matrix.h"
#include "struct.h"
#include "Boss3.h"
#include "Scene.h"

//void Scene::SceneChange(int gamemode,int scrollMode,const int enemyNum,
//	Circle enemy,Circle beamPoint,Circle player,Circle nucleus,Line triangle,
//	Beam beams,Boss3 lastboss, Baria rasBossBaria) {
//	if (gamemode >= 1) {//ゲームスタート
//		if (gamemode == 1) {//ステージ1
//			scrollMode = 0;
//			beamPoint[0]->beamAtackStart = false;
//			for (int i = 0; i < enemyNum; i++) {
//				enemy[i]->enemy.center.y += enemy[i]->enemy.speed;
//				if (enemy[i]->enemy.center.y <= 100 || enemy[i]->enemy.center.y >= 620) {
//					enemy[i]->enemy.speed *= -1;
//				}
//			}
//
//			if (player.center.x >= 2000) {
//				gamemode = 2;
//			}
//		}
//		if (gamemode == 2) {//ステージ2
//			scrollMode = 1;
//			beamPoint[0]->beamAtackStart = true;
//			beams[0]->beamMode = 0;
//			for (int i = 0; i < enemyNum; i++) {
//				enemy[i]->enemyAlive = false;
//			}
//			if (lastboss.isAlive == true) {
//				if (CircleCollisinHit(player->player.center, player->player.radius, lastboss.pos, lastboss.radius) == true) {
//					triangle->atackSpeed = { 0,0 };
//					triangle->pattern = 0;
//				}
//			}
//		}
//		if (gamemode == 3) {
//			for (int i = 0; i < enemyNum; i++) {
//				enemy[i]->enemyAlive = false;
//			}
//
//			BossBaria(lastboss, rasBossBaria);
//			for (int i = 0; i < nucleus[0]->nucleusSuctionCount; i++) {
//				BossBariaCollision(rasBossBaria, throwPos[i], hitradius[i], nucleus[0]->nucleusSuctionCount, throwDamageFlag[i]);
//			}
//			scrollMode = 1;
//			beamPoint[0]->beamAtackStart = true;
//			beams[0]->beamMode = 0;
//		}
//}