#pragma once
#include "GraphicsDevice.h"
#include "SceneManager.h"
#include "ViewPort.h"
#include "KeyBoard.h"

#define SCREEN_WIDTH			600
#define SCREEN_HEIGHT			600
#define	ANIMATE_RATE			30
#define FPS						60

extern GraphicsDevice*			graphics_device;
extern SceneManager*			scene_manager;
extern ViewPort*				view_port;