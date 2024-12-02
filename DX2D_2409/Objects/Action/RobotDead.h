#pragma once
class RobotDead : public RobotAction
{
public:
	RobotDead(Robot* robot);

	void Update()override;
	void Render()override;
};

