#include<bangtal.h>

SceneID scene1;
ObjectID startbutton, endbutton, restartbutton, playbutton, playupbutton, playdownbutton, spaceship, rock1, rock2, rock3, rock4, rock5, rock6, rock7;
TimerID timer1;
int spaceshipX = 0, spaceshipY = 500; 



//사용자 정의함수 (endGame, startGame, hitrock, pushbutton, createObject)
//hitrock 함수의 경우, 모든 rock을 한 함수로 정의했을 때, 좌표 구간끼리 충돌이 일어나 모든 rock에 대한 실행이 어려우므로, 7개의 함수로 분리했습니다.
//게임이 좀 어렵습니다.
// and, or 사용하여 if 줄이기

void endGame(bool success) {

	if (success) {
		showMessage("성공!");
	}
	else {
		showMessage("실패!");
	}

	hideObject(playbutton);
	hideObject(playupbutton);
	hideObject(playdownbutton);
	showObject(endbutton);
	showObject(restartbutton);

	spaceshipX = 0;
	spaceshipY = 500;
	locateObject(spaceship, scene1, spaceshipX, spaceshipY);
	stopTimer(timer1);
}

void startGame() {
	hideObject(startbutton);
	hideObject(endbutton);
	hideObject(restartbutton);
	showObject(playbutton);
	showObject(playupbutton);
	showObject(playdownbutton);
	setTimer(timer1, 15.0f);
	startTimer(timer1);
}

void hitrock1() {
	if (spaceshipX > 500) {
		if (spaceshipX < 790) {
			if (spaceshipY < 580) {
				if (spaceshipY > 390) {
					endGame(false);
				}
			}
		}
	}
}

void hitrock2() {
	if (spaceshipX > 660) {
		if (spaceshipX < 950) {
			if (spaceshipY < 320) {
				if (spaceshipY > 140) {
					endGame(false);
				}
			}
		}
	}
}

void hitrock3() {
	if (spaceshipX > 90) {
		if (spaceshipX < 330) {
			if (spaceshipY > 360) {
				if (spaceshipY < 620) {
					endGame(false);
				}
			}
		}
	}
}

void hitrock4() {
	if (spaceshipX > 560) {
		if (spaceshipX < 580) {
			if (spaceshipY < 180) {
				endGame(false);
			}
		}
	}
}

void hitrock5() {
	if (spaceshipX > 360) {
		if (spaceshipX < 660) {
			if (spaceshipY < 380) {
				if (spaceshipY > 160) {
					endGame(false);
				}
			}
		}
	}
}

void hitrock6() {
	if (spaceshipX > 800) {
		if (spaceshipY > 490) {
			endGame(false);
		}
	}
}

void hitrock7() {
	if (spaceshipX > 910) {
		if (spaceshipY > 320) {
			endGame(false);
		}
	}
}  

void pushbutton(ObjectID object) {

	if (object == playbutton) {
		spaceshipX = spaceshipX + 30;
		locateObject(spaceship, scene1, spaceshipX, spaceshipY);

		hitrock1();
		hitrock2();
		hitrock3();
		hitrock4();
		hitrock5();
		hitrock6();
		hitrock7();
	}
	else if (object == playupbutton) {
		spaceshipY = spaceshipY + 30;
		locateObject(spaceship, scene1, spaceshipX, spaceshipY);
		
		hitrock1();
		hitrock2();
		hitrock3();
		hitrock4();
		hitrock5();
		hitrock6();
		hitrock7();
		
	}
	else if (object == playdownbutton) {
		spaceshipY = spaceshipY - 30;
		locateObject(spaceship, scene1, spaceshipX, spaceshipY);

		hitrock1();
		hitrock2();
		hitrock3();
		hitrock4();
		hitrock5();
		hitrock6();
		hitrock7();
	}
}

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if(shown) {
		showObject(object);
	}
	return object;
}




//마우스콜백 함수

void mousecallback(ObjectID object, int x, int y, MouseAction) {

	if (object == endbutton) {
		endGame();
	}

	else if (object == startbutton) {
		startGame();
	}

	else if (object == restartbutton) {
		startGame();
	}

	else if (object == playbutton) {
		pushbutton(playbutton);
		
		if (spaceshipX > 1280) {
			endGame(true);

		}
	
	}
	else if (object == playupbutton) {
		pushbutton(playupbutton);

		if (spaceshipY > 630) {
			endGame(false);
		}
		
	}
	else if (object == playdownbutton) {
		pushbutton(playdownbutton);

		if (spaceshipY < 0) {
			endGame(false);
		}
		
	}

}



//타이머콜백 함수

void timerCallback(TimerID timer) {
	if (timer == timer1) {
		
		endGame(false);

	}
}



//메인함수

int main() {
	
	setMouseCallback(mousecallback);
	setTimerCallback(timerCallback);

	scene1 = createScene("우주레이스", "space.png");
	
	startbutton = createObject("start.png", scene1, 590, 70, true);
	endbutton = createObject("end.png", scene1, 590, 20, true);
	spaceship = createObject("spaceship.png", scene1, spaceshipX, spaceshipY, true);
	restartbutton = createObject("restart.png", scene1, 590, 70, false);
	playbutton = createObject("play.png", scene1, 640, 60, false);
	playupbutton = createObject("playup.png", scene1, 590, 100, false);
	playdownbutton = createObject("playdown.png", scene1, 590, 20, false);
	rock1 = createObject("rock.png", scene1, 640, 500, true); 
	rock2 = createObject("rock.png", scene1, 800, 250, true);
	rock3 = createObject("rockup.png", scene1, 240, 470, true);
	rock4 = createObject("rock.png", scene1, 700, 80, true);
	rock5 = createObject("rock.png", scene1, 500, 270, true);
	rock6 = createObject("rock.png", scene1, 950, 600, true);
	rock7 = createObject("rock.png", scene1, 1050, 420, true);
	
	timer1 = createTimer(15.0f);
	showTimer(timer1);

	startGame(scene1);
}