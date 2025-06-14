#pragma once

#include "Core/Application.h"
#include "Core/Camera.h"

class GameApp : public Ethereal::Application
{
public:
	GameApp();
	~GameApp();

protected:
	void OnInit() override;
	void OnUpdate() override;
	void OnShutdown() override;

private:
	Ethereal::Camera m_Camera;
};