#pragma once

#include "Core/Application.h"

class GameApp : public Ethereal::Application
{
public:
	GameApp();
	~GameApp();

protected:
	void OnInit() override;
	void OnUpdate() override;
	void OnShutdown() override;
};