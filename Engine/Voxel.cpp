#include "Voxel.h"


Voxel::Voxel()
{
}


Voxel::~Voxel()
{
}

void Voxel::SetActive(bool active)
{
	_isActive = active;
}

bool Voxel::IsActive()
{
	return _isActive;
}