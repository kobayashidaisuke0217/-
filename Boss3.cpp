#include "Boss3.h"

void BossAtackRotatet(Boss3 &a, Vector2 &player) {

}
void BossBariaOpen(Baria& a,Vector2 &bullet,int count,bool frag) {
	if (a.isAlive == true) {
		if (CircleCollisinHit(a.pos, a.size, bullet, 32/*�o���b�g�T�C�Y*/) == true) {
			a.HP -= 1;
			
		}
		if (a.HP <= 0) {
			a.isAlive = false;
	}
}
	
}
