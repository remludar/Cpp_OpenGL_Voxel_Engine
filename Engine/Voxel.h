#pragma once
class Voxel
{
public:
	Voxel();
	~Voxel();

	void SetActive(bool active);
	bool IsActive();

private:
	bool _isActive;

};

