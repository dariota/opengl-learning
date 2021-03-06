/*
 * player.h
 *
 *  Created on: 2 Feb 2016
 *      Author: Dario Tavares Antunes
 */

#ifndef PLAYER_H
#define PLAYER_H

struct player {
	struct entity e;
	struct camera *c;
	int buttons[10];
};

struct player *newPlayer(struct entity *e, struct camera *c);
void pushButton(struct player *p, int button);
void releaseButton(struct player *p, int button);
int updatePlayer(struct entity *e);
void freePlayer(struct player *p);

#endif
