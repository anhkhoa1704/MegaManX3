#pragma once

class Scene {
public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
};