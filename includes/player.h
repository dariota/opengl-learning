/*
 * player.h
 *
 *  Created on: 2 Feb 2016
 *      Author: Dario Tavares Antunes
 */

#ifndef PLAYER_H
#define PLAYER_H

struct player *newPlayer(struct entity *e, struct camera *c);
void pushButton(struct player *p, int button);
void releaseButton(struct player *p, int button);
void updatePlayer(struct entity *e);
void freePlayer(struct player *p);

#endif
