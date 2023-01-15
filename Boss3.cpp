#include "Boss3.h"

void BossAtackRotatet(Boss3 &a, Vector2 &player) {

}
void BossBariaOpen(Baria& a,Vector2 &bullet,int count,bool frag) {
	if (a.isAlive == true) {
		if (CircleCollisinHit(a.pos, a.size, bullet, 32/*バレットサイズ*/) == true) {
			a.HP -= 1;
			
		}
		if (a.HP <= 0) {
			a.isAlive = false;
	}
}
	
}
