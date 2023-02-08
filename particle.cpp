#include "particle.h"
void particleTriangle(parManag& par, Vector2 player) {
	for (int i = 0; i < 16; i++) {
		if (par.par[i].isAlive == false) {
			par.par[i]. randStart = player.x;
			par.par[i].pos.y = player.y;
			
			par.par[i].pos.x =rand()%(int)player.x+32-(int)player.x-32;
			
			par.par[i].originalvertex = { 0, -6 };
			par.par[i].originalEnd = { 3, 3 };
			par.par[i].originalstart = { -3, -3 };
			par.par[i].isAlive = true;
			par.par[i].count = 0;
			break;
		}
		if (par.par[i].isAlive == true) {
			par.par[i].count++;
			par.par[i].theta += 1.0f / 10.0f;
			par.par[i].pos.y -= 2;
			Matrix2x2 rotateMatrix = MakeRotateMatrix(par.par[i].theta);

			par.par[i].start = MatrixMultiply(par.par[i].originalstart, rotateMatrix);

			par.par[i].vertex = MatrixMultiply(par.par[i].originalvertex, rotateMatrix);

			par.par[i].End = MatrixMultiply(par.par[i].originalEnd, rotateMatrix);

			par.par[i].start = Add(par.par[i].start, par.par[i].pos);
			par.par[i].vertex = Add(par.par[i].vertex, par.par[i].pos);
			par.par[i].End = Add(par.par[i].End, par.par[i].pos);
		}
		if (par.par[i].count >= 20) {
			par.par[i].isAlive = false;
		}
	}
}